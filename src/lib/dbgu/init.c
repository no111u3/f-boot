/**
 * DBGU initing
 */
/* enable DBGU i/o pins */
static void dbgu_pio_enable(void) {
    AT91C_BASE_PIOA->PIO_ASR |= AT91C_PA30_DRXD | AT91C_PA31_DTXD; 
    AT91C_BASE_PIOA->PIO_PDR |= AT91C_PA30_DRXD | AT91C_PA31_DTXD;
}
/* clear transmit and receive counters */
static void dbgu_clear_pdc_tx_rx_counters(void) {
    /* disable the RX and TX PDC transfer requests */
    AT91C_BASE_DBGU->DBGU_PTCR = AT91C_PDC_RXTDIS | AT91C_PDC_TXTDIS;
    
    /* reset all counter register next buffer first */
    AT91C_BASE_DBGU->DBGU_TNPR = (unsigned int) 0;
	AT91C_BASE_DBGU->DBGU_TNCR = 0;
    AT91C_BASE_DBGU->DBGU_RNPR = (unsigned int) 0;
	AT91C_BASE_DBGU->DBGU_RNCR = 0;
    AT91C_BASE_DBGU->DBGU_TPR = (unsigned int) 0;
	AT91C_BASE_DBGU->DBGU_TCR = 0;
    AT91C_BASE_DBGU->DBGU_RPR = (unsigned int) 0;
	AT91C_BASE_DBGU->DBGU_RCR = 0;
    
    /* enable the RX and TX PDC transfer requests */
    AT91C_BASE_DBGU->DBGU_PTCR = AT91C_PDC_RXTEN | AT91C_PDC_TXTEN;
}
/* calculate divider */
static unsigned dbgu_calc_divider(unsigned int clock, unsigned int baudrate) {
    unsigned int baud_value = ((clock*10)/(baudrate * 16));
    if ((baud_value % 10) >= 5)
		baud_value = (baud_value / 10) + 1;
	else
		baud_value /= 10;
    return baud_value;
}
/* DBGU init */
extern void dbgu_init(unsigned int clock, unsigned int baudrate) {
    unsigned int divider;
    /* enabling DBGU pio */
    dbgu_pio_enable();
    
    /* reset receiver and transmitter */
    AT91C_BASE_DBGU->DBGU_CR =
        AT91C_US_RSTRX | AT91C_US_RSTTX | AT91C_US_RXDIS | AT91C_US_TXDIS ;
    
    /* disable interrupts */
    AT91C_BASE_DBGU->DBGU_IDR = (unsigned int) -1;
    
    /* calculate divider */
    divider = dbgu_calc_divider(clock, baudrate);
    /* configuring baud rate divisor */
    AT91C_BASE_DBGU->DBGU_BRGR = divider;
    
    /* clearing transmit and receive counters */
    dbgu_clear_pdc_tx_rx_counters();
    
    /* define the USART mode */
    AT91C_BASE_DBGU->DBGU_MR = AT91C_US_CHMODE_NORMAL | AT91C_US_PAR_NONE;
    
    /* enable  receiver and transmitter */
    AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RXEN | AT91C_US_TXEN;
}