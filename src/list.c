uuid_t* sdp_uuid16_create( uuid_t* uuid, uint16_t data);
sdp_list_t* sdp_list_append( sdp_list* list, void* data );
void sdp_set_service_classes( sdp_record_t* rec,
 			      sdp_list_t* class_list );

void sdp_set_profile_descs( sdp_record_t* rec, 
 			    sdp_list_t* profile_ list );

void sdp_set_browse_groups( sdp_record_t* rec,
			    sdp_list_t* browse_list );
void sdp_set_access_protos( sdp_record_t* rec,
			    sdp_list_t* proto_list );
void sdp_set_info_attr( sdp_record_t* rec, const char* name,
 			const char* provider,
			const char* description );

sdp_session_t* sdp_connect( const bdaddr_t* src,
			    const bdaddr_t* dst,
			    uint32_t flags );

int sdp_service_serach_attr_req( sdp_session_t* session,
				 const sdp_list_t* uuid_list,
				 sdp_attrreq_type_t reqtype,
 				 const sdp_list_t* attrid_list,
				 sdp_list_t** response_list );

int sdp_get_access_protos( const sdp_record_t* rec,
			   sdp_list_t** proto_list );
int sdp_get_proto_port( const sdp_list_t* proto_list,
			int proto_uuid );

int sdp_get_service_id(const sdp_record_t* rec,
		       uuid_t* uuid);

int sdp_get_service_classes(const sdp_record_t* rec,
			    sdp_list_t** service_class_list);

int sdp_get_profile_descs(const sdp_record_t rec,
			  sdp_list_t** profile_descriptor_list);

int sdp_get_service_name(const sdp_record_t* rec,
			 char* buf,
			 int len);
int sdp_get_service_desc(const sdp_record_t* rec,
			 char* buf,
			 int len);
int sdp_get_service_name(const sdp_record_t* rec,
			 char* buf,
			 int len);

sock_flags = fcntl(sock, F_GETFL, 0);
fcntl(sock, F_SETFL, sock_flags | O_NONBLOCK);

fd_set readfds, writefds;

FD_ZERO(&readfds);
FD_ZERO(&writefds);
FD_SET(sock, &writefds);

maxfd = sock;


struct timeval timeout;
timeout.tv_sec = 1;
timeout.tv_usec = 500000;

status = select(maxfd + 1, &readfds, &writefds, NULL, &timeout);
if (status > 0 && FD_ISSET(sock, &writefds))
{
  status = send(sock, "hello!", 6, 0);
}


int hci_send_cmd(int sock, uint16_t ogf, uint16_t ocf, uint8_t clen;
                 void* cparam);

struct hci_request
{
  uint16_t ogf;
  uint16_t ocf;
  int      event;
  void 	   *cparam;
  int	   clen;
  void 	   *rparam;
  int	   rlen;
};

int hci_send_req(int sock, struct hci_reqest* req, int timeout);



