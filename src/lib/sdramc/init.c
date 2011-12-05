/**
 * SDRAMC initing
 */
/* SDRAMC enable i/o pins */
static void sdramc_pio_enable(void) {
    AT91C_BASE_PIOC->PIO_PDR = SDRAMC_PORTC_SEL_LINE;
    AT91C_BASE_PIOC->PIO_ASR = SDRAMC_PORTC_SEL_LINE;
    AT91C_BASE_PIOC->PIO_PPUER = SDRAMC_PORTC_SEL_LINE;
    AT91C_BASE_PIOC->PIO_MDDR = SDRAMC_PORTC_SEL_LINE;
    
    AT91C_BASE_PIOC->PIO_IFDR = SDRAMC_PORTC_SEL_LINE;
    AT91C_BASE_PIOC->PIO_IDR = SDRAMC_PORTC_SEL_LINE;
    AT91C_BASE_PIOC->PIO_OWDR = SDRAMC_PORTC_SEL_LINE;
}
/* AIC EBI init */
static void aic_ebi_init(void) {
    /* setup MEMC to support all connected memories (CS1 = SDRAM) */
    AT91C_BASE_EBI->EBI_CSA |= AT91C_EBI_CS1A_SDRAMC;
    AT91C_BASE_EBI->EBI_CFGR = 0;
}
/* SDRAMC init */
extern void sdramc_init(void) {
    volatile int i;
    /* base address of sdram region */
    unsigned int * pt_mem_area = (unsigned int *) 0x20000000;
    /* enable SDRAMC pio */
    sdramc_pio_enable();
    /* initing ebi */
    aic_ebi_init();
    /* set NOP mode */
    /*AT91C_BASE_SDRC->SDRC_MR = AT91C_SDRC_MODE_NOP_CMD | AT91C_SDRC_DBW_32_BITS; */
    /* configuring and initing SDRAM */
    AT91C_BASE_SDRC->SDRC_CR = AT91C_SDRC_NC_10 | /* Column A0-A9 */
        AT91C_SDRC_NR_13 | /* Row    A0-A12 */
        AT91C_SDRC_NB_4_BANKS | /* numbers Bank 4 */
        AT91C_SDRC_CAS_2 | /* CAS Latency 2 */
        ((AT91Cmy_SDRAM_TWR <<  7) & AT91C_SDRC_TWR) |
        ((AT91Cmy_SDRAM_TRC << 11) & AT91C_SDRC_TRC) |
        ((AT91Cmy_SDRAM_TRP << 15) & AT91C_SDRC_TRP) |
        ((AT91Cmy_SDRAM_TRCD << 19) & AT91C_SDRC_TRCD) |
        ((AT91Cmy_SDRAM_TRAS << 23) & AT91C_SDRC_TRAS) |
        ((AT91Cmy_SDRAM_TXSR << 27) & AT91C_SDRC_TXSR);
    /* al all banks precharge command is issued to SDRAM devices */
    AT91C_BASE_SDRC->SDRC_MR = AT91C_SDRC_MODE_PRCGALL_CMD | AT91C_SDRC_DBW_32_BITS;
    pt_mem_area[0] = 0x00000000;
    /* eight auot-refresh (CBR) cycles are provided */
    for (i = 0; i < 8; i++) {
        AT91C_BASE_SDRC->SDRC_MR = AT91C_SDRC_MODE_RFSH_CMD | AT91C_SDRC_DBW_32_BITS;
        *pt_mem_area = 0;
    }
    /* a mode register set (MRS) cycle is issued to program the parameters of the SDRAM
       devices, in particular CAS latency and burst length */
    AT91C_BASE_SDRC->SDRC_MR = AT91C_SDRC_MODE_LMR_CMD | AT91C_SDRC_DBW_32_BITS;
    *(pt_mem_area +AT91Cmy_SDRAM_MR_CHIP) = 0x00000000;
    /* write refresh rate into the count field in the SDRAMC refresh timer register. (Refresh
       rate = delay between refresh cycles) */
    AT91C_BASE_SDRC->SDRC_TR = AT91Cmy_SDRAM_Refresh & AT91C_SDRC_COUNT;
    pt_mem_area[0] = 0x00000000;
    /* a normal mode command is provided, 3 clocks after tMRD is met */
    AT91C_BASE_SDRC->SDRC_MR = AT91C_SDRC_MODE_NORMAL_CMD  | AT91C_SDRC_DBW_32_BITS;
    pt_mem_area[0] = 0x00000000;
}