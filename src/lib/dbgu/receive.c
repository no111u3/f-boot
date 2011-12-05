/**
* DBGU receive
*/
/* getting char */
extern unsigned dbgu_getc(void) {
    while (!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY));
    return ((AT91C_BASE_DBGU->DBGU_RHR) & 0xff);
}