#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>

int main(int argc, char** argv)
{
  struct sockaddr_l2 loc_addr = {0}, rem_addr = {0};
  char buffer[1024] = {0};
  int sock, client, bytes_read;
  unsigned int opt = sizeof(rem_addr);
 
  // allocate socket
  sock = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
  
  // bind socket to port 0x1001 of the first available
  // bluetooth adapter
  loc_addr.l2_family = AF_BLUETOOTH;
  loc_addr.l2_bdaddr = *BDADDR_ANY;
  loc_addr.l2_psm = htobs(0x1001);

  bind(sock, (struct sockaddr*)&loc_addr, sizeof(loc_addr));
  
  // put socket into listening mode
  listen(sock, 1);
 
  // accept one connection
  client = accept(sock, (struct sockaddr*)&rem_addr, &opt);

  ba2str(&rem_addr.l2_bdaddr, buffer);
  fprintf(stderr, "accepted connection from %s\n", buffer);
  // read data from the client
  memset(buffer, 0, sizeof(buffer));
  bytes_read = recv(client, buffer, sizeof(buffer), 0);
  if (bytes_read > 0)
  {
    printf("received [%s]\n", buffer);
  }
	
  // close connection  
  close(client);
  close(sock);
  return 0;
}
