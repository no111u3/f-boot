/**
 * UTIL geting string
 */
/* UTIL geting string */
extern void util_gets(char *buffer) {
    char *p = buffer;
    char c;
    
    while ((c = dbgu_getc()) && c != '\n') {
        dbgu_putc(c);
        *p++ = c;
    }
    *p = '\0';
}