/**
 * UTIL header
 */
#define XM_NAK      0x15
#define XM_SOH      0x01
#define XM_ACK      0x06
#define XM_EOT      0x04
#ifdef LIB_H
/* UTIL crc16 */
static unsigned short util_crc16(unsigned char *ptr, int len);
#endif
/* UTIL puting string */
extern void util_puts(const char * buffer);
/* UTIL geting string */
extern void util_gets(char *buffer);
/* UTIL delay */
extern void util_delay(int tic);
/* UTIL unsigned int to hex string */
void util_int_hex(unsigned int number, char *buffer, const unsigned int base);
/* UTIL hex string to unsigned int */
unsigned int util_hex_int(const char *buffer);
/* UTIL printf */
extern unsigned util_printf(const char * format, ...);
/* UTIL memory copy */
extern void util_memcp(void *dst, const void *src, unsigned len);
/* UTIL x-modem reciever */
int util_xmod_recv(void * ptr);