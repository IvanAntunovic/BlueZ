typedef struct
{
  uint8_t b[6];
}__atribute__((packed)) bdaddr_t;

int str2ba ( const char *str , bdaddr_t *ba );
int ba2str ( const bdaddr_t *ba , char *str );

int hci_get_route( bdaddr_t *addr );

int hci_devid ( const char *addr );

int hci_open_dev ( int adapter_id );

int hci_inquiry (int adapter_id, int len, int max_rsp, 
                 const uint8_t *lap, inquiry_info** devs, long flags );

typedef struct 
{
  bdaddr_t bdaddr;
  uint8_t pscan_rep_mode;
  uint8_t pscan_period_mode;
  uint8_t pscan_mode;
  uint8_t dev_class[3];
  uint16_t clock_offset;
}__attribute__ ( (packed) ) inquiry_info;

int hci_read_remote_name( int hci_sock, const bdaddr_t * addr, int len, char * name, int timeout );

int dev_id = hci_get_route ( NULL );
if ( dev id < 0 ) 
{
	fprintf ( stderr , "error code %d: %s\n " , errno , strerror ( errno ) ) ;
	exit ( 1 ) ;
}
