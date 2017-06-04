#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main ( int argc , char ** argv )
{
	struct sockaddr_rc addr = { 0 };
	int sock, status;
	char destinaton_address[18] = "5C:E0:C5:83:74:FC";
	
	// allocate socket
	sock = socket (AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM) ;
	// bind socket to port 1 of the first available bluetooth adapter
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = 1;
	str2ba(destinaton_address, &addr.rc_bdaddr);
	
	// connect to server
	status = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	//send a message
	if (status == 0)
	{
	  status = send(sock, "hello!", 6, 0);
	}
	else if (status < 0)
	{
	  perror("Error while writing data");
	}

	// close connection
	close(sock);
	return 0 ;
}


