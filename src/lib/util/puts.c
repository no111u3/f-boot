/**
 * UTIL puting string
 */
/* UTIL puting string */
extern void util_puts(const char * buffer) {
    while (*buffer) {
        dbgu_putc(*buffer++);
    }
}