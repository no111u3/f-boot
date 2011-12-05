/**
 * UTIL printf
 */
#include <stdarg.h>
/* UTIL printf */
extern unsigned util_printf(const char * format, ...) {
    char * s, buffer[16];
    va_list ap;
    
    va_start(ap, format);
    
    do {
        if (*format == '%') {
            format++;
            if (*format == 's') {
                s = va_arg(ap, char *);
                if (s)
                    util_puts(s);
                else
                    util_puts("<NULL>");
            }
            else if (*format == 'c') {
                dbgu_putc(va_arg(ap, unsigned));
            }
            else if (*format == 'x') {
                util_int_str(va_arg(ap, unsigned), buffer, 16);
                util_puts(buffer);
            }
            else if (*format == 'd') {
                util_int_str(va_arg(ap, unsigned), buffer, 10);
                util_puts(buffer);
            }
            else {
                util_puts("%");
            }
        }
        else {
            dbgu_putc(*format);
        }
        format++;
    } while (*format);
    
    va_end(ap);
    
    return 0;
}