#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <bluetooth/bluetooth.h> 
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int set_flush_timeout(bdaddr_t* btAddress, int timeout)
{
  int err = 0, dDevice;
  struct hci_conn_info_req* connectionRequest = NULL;
  struct hci_request request = { 0 };
  
  struct
  {
    uint16_t handle; 
    uint16_t flush_timeout;
  } cmd_param;
  
  struct
  {
    uint8_t status;
    uint8_t handle;
  } cmd_response;

  // find the connection handle to the specified bluetooth device
  connectionRequest = (struct hci_conn_info_req*) malloc (
                       sizeof(struct hci_conn_info_req) + 
                       sizeof(struct hci_conn_info));
  bacpy(&connectionRequest->bdaddr, btAddress);
  connectionRequest->type = ACL_LINK;
  dDevice = hci_open_dev( hci_get_route( &connectionRequest->bdaddr ) );
  if (dDevice < 0)
  {
    err = dDevice;
    goto cleanup;
  }
  err = ioctl(dDevice, HCIGETCONNINFO, (unsigned long)connectionRequest);
  if (err)
  {
     goto cleanup;
  }
  
  // build a command packet to send to the bluetooth microcontroller
  cmd_param.handle = connectionRequest->conn_info->handle;
  cmd_param.flush_timeout = htobs(timeout);
  request.ogf = OGF_HOST_CTL; 
  request.ocf = 0x28;
  request.cparam = &cmd_param;
  request.clen = sizeof(cmd_param);
  request.rparam = &cmd_response;
  request.rlen = sizeof(cmd_response);
  request.event = EVT_CMD_COMPLETE;
  
  // SEND THE COMMAND AND WAIT FOR THE RESPONSE
  err = hci_send_req (dDevice, &request, 0);
  if (err)
  {
    goto cleanup;
  }
  
  if (cmd_response.status)
  {
    err = -1;
    errno = bt_error(cmd_response.status);
  }

cleanup:
  free(connectionRequest);
  if (dDevice >= 0)
  {
    close(dDevice);
  }
  return err;
}

int main(int argc, char** argv)
{
  bdaddr_t target;
  int timeout;
  
  if (argc < 3)
  {
    fprintf(stderr, "usage: set-flush-to <addr> <timeout>\n");
    exit(2);
  }
  
  str2ba(argv[1], &target); 
  timeout = atoi(argv[2]);
  return set_flush_timeout(&target, timeout);
}

