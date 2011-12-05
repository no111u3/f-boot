/**
* DBGU transmit
*/
/* putting char */
extern void dbgu_putc(unsigned character) {
    while (!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_TXRDY));
    AT91C_BASE_DBGU->DBGU_THR = (character & 0xff);
}