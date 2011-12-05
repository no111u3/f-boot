/**
 * PMC initing
 */
/* enable slow clock */
extern void slck_en(void) {
    if (AT91C_PMC_CSS_SLOW_CLK != (AT91C_BASE_PMC->PMC_MCKR & AT91C_PMC_CSS)) {
        /* CPU does no run with slow clock
           commutate clock to slow clock */
        AT91C_BASE_PMC->PMC_MCKR = AT91C_PMC_CSS_SLOW_CLK;
    }
}
/* enable main clock */
extern void mck_en(void) {
    if (AT91C_PMC_CSS_MAIN_CLK != (AT91C_BASE_PMC->PMC_MCKR & AT91C_PMC_CSS)) {
        /* CPU does no run with main clock
           waiting for stable main clock */
        while(!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MOSCS));
        /* commutate clock to main clock */
        AT91C_BASE_PMC->PMC_MCKR = AT91C_PMC_CSS_MAIN_CLK;
    }
}
/* enable PLLA clock */
extern void pllack_en(unsigned short mdiv) {
    if (AT91C_PMC_CSS_PLLA_CLK != (AT91C_BASE_PMC->PMC_MCKR & AT91C_PMC_CSS)) {
        /* CPU does no run with PLLA clock
           waiting for stable PLLA clock */
        while(!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKA));
        /* commutate clock to PLLA clock */
        AT91C_BASE_PMC->PMC_MCKR = mdiv + AT91C_PMC_CSS_PLLA_CLK;
    }
}
/* enable PLLB clock */
extern void pllbck_en(void) {
    if (AT91C_PMC_CSS_PLLB_CLK != (AT91C_BASE_PMC->PMC_MCKR & AT91C_PMC_CSS)) {
        /* CPU does no run with PLLB clock
           waiting for stable PLLB clock */
        while(!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKB));
        /* commutate clock to PLLB clock */
        AT91C_BASE_PMC->PMC_MCKR = AT91C_PMC_CSS_PLLB_CLK;
    }
}
/* main clock init */
extern void mck_init(unsigned int mck_value) {
    volatile int tmp_counter = 0;
    /* setup the PLLA */
    AT91C_BASE_CKGR->CKGR_MOR = mck_value;
    /* waiting for stable main clock */
    while(!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MOSCS)
        && (tmp_counter++ < DELAY_MCK));
}
/* PLLA init */ 
extern void plla_init(unsigned int plla_value) {
    volatile int tmp_counter = 0;
    /* setup the PLLA */
    AT91C_BASE_CKGR->CKGR_PLLAR = plla_value;
    /* waiting for stable PLLA clock */
    while(!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKA)
        && (tmp_counter++ < DELAY_PLL));
}
/* PLLB init */
extern void pllb_init(unsigned int pllb_value) {
    volatile int tmp_counter = 0;
    /* setup the PLLB */
    AT91C_BASE_CKGR->CKGR_PLLBR = pllb_value;
    /* waiting for stable PLLB clock */
    while(!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKB)
        && (tmp_counter++ < DELAY_PLL));
}