#include <stdio.h>
#include <stdlib.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>

int main(int argc, char** argv)
{
  uint32_t svc_uuid_int[] = {0, 0, 0, 0xABCD};
  
  int status;
  bdaddr_t target;
  uuid_t svc_uuid;
  sdp_list_t* response_list, *search_list, *attrid_list;
  sdp_session_t* session = 0;
  uint32_t range = 0x0000FFFF;
  uint8_t port = 0;

  if (argc < 2)
  {
    fprintf(stderr, "usage %s <bt_addr>\n", argv[0]);
    exit(2);
  }
  str2ba(argv[1], &target);
  
  // connect to the SDP server running on the remote machine
  session = sdp_connect(BDADDR_ANY, &target, 0);
  
  sdp_uuid128_create(&svc_uuid, &svc_uuid_int);
  search_list = sdp_list_append(0, &svc_uuid);
  attrid_list = sdp_list_append(0, &range);
  
  // get a list of service records that have UUID 0xABCD
  response_list = NULL;
  status = sdp_service_search_attr_req(session, search_list,
           SDP_ATTR_REQ_RANGE, attrid_list, &response_list);

  if (status == 0)
  {
    sdp_list_t* proto_list = NULL;
    sdp_list_t* resp_list = response_list;
    
    // go through each of the service records
    for (; resp_list != NULL; resp_list->next)
    {
      sdp_record_t* rec = (sdp_record_t*)resp_list->data;
      
      // get a list of the protocol squences
      if (sdp_get_access_protos(rec, &proto_list) == 0)
      {
	// get the RFCOMM port number
        port = sdp_get_proto_port( proto_list, RFCOMM_UUID);
   	sdp_list_free(proto_list, 0);
      }
      sdp_record_free(rec);
    }
  }
  sdp_list_free(response_list, 0);
  sdp_list_free(search_list, 0);
  sdp_list_free(attrid_list, 0),
  sdp_close(session);
  
  if (port != 0)
  {
    printf("Found service running on RFCOMM port %d\n", port);
  }

  return 0;

}
