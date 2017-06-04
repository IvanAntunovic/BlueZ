int sco_sock = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_SCO);

struct sockaddr_sco
{
  sa_family_t sco_family;
  bdaddr_t sco_bdaddr;
};

int hci_read_voice_setting(int dDevice, uint16_t* vs, int to);
int hci_write_voice_setting(int dDevice, uint16_t* vs, int to);

struct sco_options _sco_options;
int so_size = sizeof(_sco_options);
getsockopt(connected_sco_socket, 
           SOL_SCO, 
           SCO_OTPIONS, 
           &_sco_options,
           &_sco_options);
uint16_t maximum_packet_size = _sco_options.mtu;
