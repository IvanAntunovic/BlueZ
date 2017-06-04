#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main(int argc , char **argv)
{
	inquiry_info* devices = NULL;
	int max_rsp, num_devices_discovered, adapter_id, socket, length, flags, i;
	char address[19] = {0};
	char name[248] = {0};
	
	adapter_id = hci_get_route(NULL);
	socket = hci_open_dev(adapter_id);
	if ( adapter_id < 0 ) 
	{
		fprintf(stderr , "error code %d: %s\n " , errno , strerror( errno ));
		perror("Did you forget to enable bluetooth adapter on your device?");
		exit (1);
	}
	if (socket < 0)
	{
		perror("Error while opening socket");
		exit(1);
	}
	
	length = 8;
	max_rsp = 255;
	flags = IREQ_CACHE_FLUSH;
	devices = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
	
	printf("%s\n", "Starting device scan...");
	num_devices_discovered = hci_inquiry(adapter_id, length, max_rsp, NULL, &devices, flags);
	if (num_devices_discovered < 0)
	{
		perror("hci_inquiry");
	}
	else if (num_devices_discovered == 0)
	{
		printf("%s", "No discoverable bluetooth devices found\n");
		return 0;    
	}

	for (i = 0; i < num_devices_discovered; ++i)
	{
		ba2str(&(devices + i)->bdaddr, address);
		memset(name, 0, sizeof(name));
		if (hci_read_remote_name(socket, &(devices + i)->bdaddr, sizeof(name), name, 0) != 0)
		{
			strcpy(name, "[unknown]");
		}
		printf("%s %s\n", address, name);
		printf(" (0x%2.2x%2.2x%2.2x)\n", (devices + i)->dev_class[0], (devices + i)->dev_class[1], (devices + i)->dev_class[2]);

	}
	printf("%s\n", "end device scan...");	

	free(devices);
	close(socket);
	return 0;
}
