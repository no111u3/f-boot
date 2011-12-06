/**
 * DBGU header
 */
#ifdef LIB_H
/* enable DBGU i/o pins */
static void dbgu_pio_enable(void);
/* clear transmit and receive counters */
static void dbgu_clear_pdc_tx_rx_counters(void);
/* calculate divider */
static unsigned dbgu_calc_divider(unsigned int clock, unsigned int baudrate);
/* DBGU init */
#endif
extern void dbgu_init(unsigned int clock, unsigned int baudrate);
/* putting char */
extern void dbgu_putc(unsigned character);
/* getting char */
extern unsigned dbgu_getc(void);