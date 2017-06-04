#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <bluetooth/bluetooth.h> 
#include <bluetooth/rfcomm.h>

int main(int argc, char** argv)
{
  struct sockaddr_rc addr = { 0 };
  int sock, status;
  char dest[18] = "5C:E0:C5:83:74:FC";
  fd_set readfds, writefds;
  int maxfd, sock_flags;

  // allocate a socket
  sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
  if (sock < 0)
  {
    perror("Error while allocating a new socket\n");
    return 1;
  }
  
  // set the conection parameters (who to connect to)
  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = 1;
  str2ba(dest, &addr.rc_bdaddr);

  // put socket in non-blocking mode
  sock_flags = fcntl(sock, F_GETFL, 0);
  fcntl(sock, F_SETFL, sock_flags | O_NONBLOCK);
 
  // initiate connect attempt
  printf("%s %s\n", "Attempting to connect to the device with address:", dest);
  status = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  if (status != 0 && errno != EAGAIN);
  {
    perror("Error while connecting to the device\n");
    return 1;
  }

  // wait for connection to complete or fail
  FD_ZERO(&readfds);
  FD_ZERO(&writefds);
  FD_SET(sock, &writefds);
  maxfd = sock;

  status = select(maxfd + 1, &readfds, &writefds, NULL, NULL);
  if ( status > 0 && FD_ISSET(sock, &writefds) )
  {
    status = send(sock, "hello!", 6, 0);
  }
  if (status < 0)
  {
    perror("Sending operation failed");
  }

  close(sock);
  return 0;
}
