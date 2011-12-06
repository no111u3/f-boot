/**
 * PMC PLL setup
 */
/* PLLA setup */
extern void plla_setup(const char plla_div, const char plla_count,
    const char plla_out, const char plla_mul) {
    volatile int tmp_counter = 0;
    unsigned plla_value = (((plla_div & 0xff) <<  0) | ((plla_count & 0x3f) <<  8) |
        ((plla_out & 0x03) << 14) | (((plla_mul -1) & 0x7ff) << 16) | 0x20000000);
    /* setup the PLLA */
    AT91C_BASE_CKGR->CKGR_PLLAR = plla_value;
    /* waiting for stable PLLA clock */
    while(!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKA)
        && (tmp_counter++ < DELAY_PLL));
}
/* PLLB setup */
extern void pllb_setup(const char pllb_div, const char pllb_count,
    const char pllb_out, const char pllb_mul, const char pllb_usb_96m) {
    volatile int tmp_counter = 0;
    unsigned pllb_value = (((pllb_div & 0xff) <<  0) | ((pllb_count & 0x3f) <<  8) |
        ((pllb_out & 0x03) << 14) | (((pllb_mul -1) & 0x7ff) << 16) |
        ((pllb_usb_96m & 0x01) << 28));
    /* setup the PLLB */
    AT91C_BASE_CKGR->CKGR_PLLBR = pllb_value;
    /* waiting for stable PLLB clock */
    while(!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKB)
        && (tmp_counter++ < DELAY_PLL));
} 
