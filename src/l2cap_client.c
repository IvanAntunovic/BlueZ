#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>

int main(int argc, char** argv)
{
  struct sockaddr_l2 addr = {0};
  int sock, status;
  char dest[18] = "5C:E0:C5:83:74:FC";

  if (argc < 2)
  {
    fprintf(stderr, "usage: %s <bt_addr>\n", argv[0]);
    return 1;
  }
  strncpy(dest, argv[1], 18);
  
  // allocate a socket
  sock = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
  // set the connection parameters (who to connect to)
  addr.l2_family = AF_BLUETOOTH;
  addr.l2_psm = htobs(0x1001);
  str2ba(dest, &addr.l2_bdaddr);
 
  // connect to server
  status = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  
  // send a message
  if (status == 0)
  {
    status = send(sock, "hello!", 6, 0);
  }
 
  if (status < 0)
  {
     perror("Error while writing to the socket\n");
  }

  close(sock);
  return 0;
}
