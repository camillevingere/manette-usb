#include <stdint.h>
#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MAX_DATA 2 //Max data to send or receive

struct libusb_device_handle *device_handle = NULL; // Our USB device handle
uint8_t interrupt_endpoints_addresses[100];		   //Tableau de stockage des adresses des endpoints

//Énumération et connexion au périphérique demandé
int enumeration_bus_id(int status, libusb_context *context)
{
	u_int16_t Vendor_Id;
	u_int16_t Product_Id;

	printf("Donnez le Vendor ID : 0x");
	scanf("%hx", &Vendor_Id);
	printf("Donnez le Product ID : 0x");
	scanf("%hx", &Product_Id);

	printf("Vendor_Id : %d\n", Vendor_Id);
	printf("Product_Id : %d\n", Product_Id);

	libusb_device **list;
	ssize_t count = libusb_get_device_list(context, &list);
	if (count < 0)
	{
		perror("libusb_get_device_list");
		exit(-1);
	}
	ssize_t i = 0;
	for (i = 0; i < count; i++)
	{
		libusb_device *device = list[i];
		struct libusb_device_descriptor desc;
		int status = libusb_get_device_descriptor(device, &desc);
		if (status != 0)
			continue;
		uint8_t bus = libusb_get_bus_number(device);
		uint8_t address = libusb_get_device_address(device);
		printf("Device Found @ (Bus:Address) %d:%d\n", bus, address);
		printf("Vendor ID 0x0%x\n", desc.idVendor);
		printf("Product ID 0x0%x\n", desc.idProduct);

		//Enregistrement du périphérique recherché si c'est le bon
		if ((desc.idVendor == Vendor_Id) && (desc.idProduct == Product_Id))
		{
			printf("\n");
			printf("Controller found\n");

			//On sauve la poignée
			libusb_open(list[i], &device_handle);

			if (!device_handle)
			{
				printf("Error finding USB device\n");
				libusb_exit(NULL);
				exit(-2);
			}
			printf("\n");
			libusb_free_device_list(list, 1);
			return 0;
		}
	}
	printf("\n");
	libusb_free_device_list(list, 1);
	return -1;
}

//Libération des interfaces
int release_interfaces(int status)
{
	struct libusb_device *dev;
	struct libusb_config_descriptor *config;

	//Récupération de la poignée
	dev = libusb_get_device(device_handle);

	if (!dev)
	{
		return -1;
	}

	//Récupération de la configuration du périphérique
	status = libusb_get_active_config_descriptor(dev, &config);

	if (status == LIBUSB_ERROR_NOT_FOUND)
	{
		fprintf(stderr, "Error: Device is unconfigured\n");
		return -1;
	}
	else if (status)
	{
		fprintf(stderr, "Error: failed libusb_get_active_config_descriptor()\n");
		exit(1);
	}

	int i;

	if (config->interface)
	{
		for (i = 0; i < config->bNumInterfaces; i++)
		{
			const struct libusb_interface_descriptor *intf = config->interface[i].altsetting;

			//Libération de l'interface
			status = libusb_release_interface(device_handle, intf->bInterfaceNumber);

			if (status != 0)
			{
				perror("libusb_release_interface");
				exit(-1);
			}

			printf("Interface libérée (Indice:Numéro) %d:%d\n \n", i, intf->bInterfaceNumber);
		}
	}

	//Libération du config descriptor
	libusb_free_config_descriptor(config);

	//Libération du device ouvert précédemment
	libusb_close(device_handle);

	return 0;
}

//Récupérer la configuration du périphérique USB
int get_config(int status, libusb_context *context)
{
	struct libusb_device *dev;
	struct libusb_config_descriptor *config;

	//Récupération de la poignée
	dev = libusb_get_device(device_handle);

	if (!dev)
	{
		return -1;
	}

	//Récupération de la configuration du périphérique
	status = libusb_get_active_config_descriptor(dev, &config);

	if (status == LIBUSB_ERROR_NOT_FOUND)
	{
		fprintf(stderr, "Error: Device is unconfigured\n");
		return -1;
	}
	else if (status)
	{
		fprintf(stderr, "Error: failed "
						"libusb_get_active_config_descriptor()\n");
		exit(1);
	}
	printf("Valeur de la configuration : %d\n \n", config->bConfigurationValue);

	int i, j;

	printf("Nombre total d'interfaces : %d\n \n", config->bNumInterfaces);

	//Intération sur le nombre d'interfaces
	for (i = 0; i < config->bNumInterfaces; i++)
	{
		const struct libusb_interface_descriptor *intf = config->interface[i].altsetting;

		if (intf->bInterfaceClass != LIBUSB_CLASS_VENDOR_SPEC)
			continue;

		//Demande d'utilisation de l'interface
		status = libusb_claim_interface(device_handle, intf->bInterfaceNumber);

		printf("Interface (Indice:Numéro) %d:%d\n \n", i, intf->bInterfaceNumber);

		//Intération sur le nombre de endpoints
		for (j = 0; j < intf->bNumEndpoints; j++)
		{
			printf("Endpoint found @ : %d\n \n", intf->endpoint[j].bEndpointAddress);

			//On garde en mémoire les point d'accès de type interruption
			if ((intf->endpoint[j].bmAttributes & 0b00000011) == LIBUSB_TRANSFER_TYPE_INTERRUPT)
			{
				interrupt_endpoints_addresses[i] = intf->endpoint[j].bEndpointAddress;
				printf("Save\n");
				printf("Endpoint @ : %d\n \n", intf->endpoint[j].bEndpointAddress);
			}
		}
	}

	//Libération du config descriptor
	libusb_free_config_descriptor(config);

	return 0;
}

//Communiquer des données avec la manette
void send_data(int status, libusb_context *context, unsigned char data[MAX_DATA])
{
	uint16_t endpoint_out = interrupt_endpoints_addresses[1]; /* ID of endpoint (bit 8 is 0) */
	int size = MAX_DATA;									  /* size to send or maximum size to receive */
	int timeout = 1000;										  /* timeout in ms */

	/* OUT interrupt, from host to device */
	int bytes_out;
	printf("handle=%p ep=%02x\n", device_handle, endpoint_out);

	//Communication avec la manette
	status = libusb_interrupt_transfer(device_handle, endpoint_out, data, size, &bytes_out, timeout);

	if (status != 0)
	{
		perror("libusb_interrupt_transfer");
		exit(-1);
	}
}

//Test fonctionnement de led sur la manette
void test_led(int status, libusb_context *context)
{
	unsigned char data[MAX_DATA]; /* data to send or to receive */
	data[0] = 0x01;
	data[1] = 0x00;
	//Envoi de la data sur une seule LED
	send_data(status, context, data);
}

//Chenillard sur les leds de la manette
void chenillard(int status, libusb_context *context)
{
	int i;
	unsigned char data[MAX_DATA]; /* data to send or to receive */
	data[0] = 0x01;
	data[1] = 0x00;

	for (i = 0; i < 7; i++)
	{
		//Envoi de la data sur la manette
		send_data(status, context, data);
		//Attente de 1s
		sleep(1);
		//Décalage à gauche
		data[0] = data[0] << 1;
	}

	data[0] = 0x00;
	data[1] = 0x01;

	for (i = 0; i < 2; i++)
	{
		//Envoi de la data sur la manette
		send_data(status, context, data);
		//Attente de 1s
		sleep(1);
		//Décalage à gauche
		data[1] = data[1] << 1;
	}
}

/* Signal Handler for SIGINT */
//On libère la mémoire après le Ctrl+C
void sigint_handler(int sig_num)
{
	libusb_context *context;
	int status = libusb_init(&context);
	int err = 0;

	printf("\n On libère la mémoire avant de d'arrêter le programme \n");

	//Libération des interfaces
	err = release_interfaces(status);

	if (err != 0)
	{
		printf("Erreur de libération des interfaces : %d\n", err);
		exit(-1);
	}

	libusb_exit(context);

	exit(0);
}

int main(void)
{
	signal(SIGINT, sigint_handler);

	libusb_context *context;
	int status = libusb_init(&context);
	int err = 0;

	if (status != 0)
	{
		perror("libusb_init");
		exit(-1);
		return -1;
	}

	//Connexion au port de la manette
	err = enumeration_bus_id(status, context);

	if (err != 0)
	{
		printf("Device USB non trouvé : %d\n", err);
		exit(-1);
		return -1;
	}

	//Récupération des interfaces et des endpoints
	err = get_config(status, context);

	if (err != 0)
	{
		printf("Erreur de récupération des interfaces: %d\n", err);
		exit(-1);
		return -1;
	}

	printf("Appuyez sur a pour tester l'allumage d'une LED\n");
	printf("ou sur n'importe quelle autre touche pour le chenillard\n");

	char c;

	scanf(" %c", &c);

	if (c == 'a')
	{
		//Test allumage d'une seule LED
		test_led(status, context);
	}
	else
	{
		while (1)
		{
			//Chenillard sur les LEDs de la manette
			chenillard(status, context);
		}
	}

	libusb_exit(context);
}
