struct sockaddr_l2
{
  sa_familiy_t   l2_family;
  unsigned short l2_psm;
  bdaddr_t       l2_bdaddr;
}

int connect( int sock, const struct socaddr* server_info, socklen_t infolen);

int bind( int sock, const struct sockaddr* info, socklen_t infolen);

int listen( int sock, int backlog);

int accept( int server_sock, struct socaddr* client_info, socklent_t infolen);

ssize_t send( int sock, const void* buf, size_t len, int flags);
ssize_t recv( int sock, void* buf, size_t len, int flags);
int close(int sock);

struct sockaddr_l2
{
  sa_familiy_t   l2_family;
  unsigned short l2_psm;
  bdaddr_t       l2_bdaddr;
}

unsigned short int htobs ( unsigned short int num );
unsigned short int btohs ( unsigned short int num );
unsigned int htobl( unsigned int num );
unsigned int btohl( unsigned int num );

struct l2cap_options
{
  uint16_t omtu;
  uint16_t imtu;
  uint16_t flush_to;
  uint8_t  mode;
};

int getsockopt( int sock, int level, int optname, void* optval,
                socklen_t* optlen );

int setsockopt( int sock, int level, int optname, void* optval, 
                socklen_t optlen );


int set_l2cap_mtu( int sock, uint16_t mtu)
{
  struct l2cap_options opts;
  int optlen = sizeof(opts); 
  int status;

  status = getsockopt(sock, SOL_L2CAP, L2CAP_OPTIONS, &opts, &optlen);
  if (status == 0)
  {
    opts.omtu = opts.imtu = mtu;
    status = setsockopt(sock, SOL_L2CAPM L2CAP_OPTIONS, &opts, optlen);
  }
  return status;
}

int sock;
int port;
int status;
struct sockaddr_rc to_bind;

sock = socket( AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM );
to_bind.rc_family = AF_BLUETOOTH;
to_bind.rc_bdaddr = *BDADDR_ANY;
for (port = 1; port <= 30; ++port)
{
  to_bind.rc_channel = port;
  status = bind(sock, (struct sockaddr*)&to_bind, sizeof(to_bind));
  if (status == 0)
  {
    break;
  }
}

uuid_t* sdp_uuid128_create( uuid_t* uuid, const void* data );
uuid_t* sdp_uuid32_create( uuid_t* uuid, uint32_t data );
uuid_t* sdp_uuid16_create( uuid_t* uuid, uint16_t data );

typedef struct _sdp_list sdp_list_t;
struct _sdp_list
{
  sdp_list_t* next;
  void* data;
};

sdp_list_t* sdp_list_append(sdp_list_t* list, void* data);
void sdp_list_free(sdp_list_t* list, sdp_free_func_t f);

typedef struct
{
  uuid_t uuid;
  uint16_t version;
}sdp_profile_desc_t;

sdp_data_t* sdp_data_alloc(uint8_t dtd, const void* value);
sdp_attr_add(sdp_record_t* rec, uint16_t attr, sdp_data_t* data);
sdp_data_free(sdp_data_t* data);
