/**
 * UTIL header
 */
/* UTIL puting string */
extern void util_puts(const char * buffer);
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