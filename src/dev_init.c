/** * Device init *//* Includes */#include <dev_init.h>/* device init */extern void dev_init(void) {    /* enable dbgu */    dbgu_init(48000000, 115200);    /* print start message */    util_puts("f-boot ver 0.7.0\n");    /* setup plls and switch to plla */    setup_plls();    /* setup and init aic */    setup_aic();    /* initing sdramc */    sdramc_init();    /* initing spi */    spi_init('m');    /* spi - setup #0 cs, 8bits, 9MHz, 0 delay, 0 mode */    spi_cs_set(0, 8, 10, 0, 0);}/* setup plls and switch to plla */static void setup_plls(void) {    util_puts("Switch to main clock...");    /* waiting for stable */    util_delay(12000);    /* change clock to main clock */    mck_init(AT91C_CKGR_MOSCEN | (0xff << 8));    mck_en();    /* reinit dbgu on 16MHz msck */    dbgu_init(16000000, 115200);    util_delay(12000);    /* put second string */    util_puts("Ok\nRunning on 16MHz clock\n");    /* setup plla value */    util_puts("Setup plla value - Mul: 180 Div: 16 Out clk: 180MHz\n");    util_puts("Init PLLA...");    plla_setup(16, 100, 2, 180);    util_puts("Ok\n");    /* setup pllb value */    util_puts("Setup pllb value - Mul: 96 Div: 16 Out clk: 96MHz\n");    util_puts("Init PLLB...");    pllb_setup(16, 100, 2, 96, 1);    util_puts("Ok\n");    /* switch msck to plla */    util_puts("Switch to plla clock, Pres: 2...");    util_delay(12000);    pllack_en(AT91C_PMC_MDIV_2);    dbgu_init(90000000, 115200);    util_delay(12000);    util_puts("Ok\nRunning on 90MHz clock\n");}/* setup aic */static void setup_aic() {    unsigned int i;    aic_init(AT91C_AIC_BRANCH_OPCODE, aic_default,        aic_default, aic_spirious_int, 0);    /* perform 8 end of interrupt command to make sure AIC will not lock out nIRQ */    i = 8;    while (i-- > 0)        aic_acknowledge_irq();    /* setup basic exception vectors */    aic_set_exception_vector((unsigned int *)0x0C, aic_fetch_abort);    aic_set_exception_vector((unsigned int *)0x10, aic_data_abort);    aic_set_exception_vector((unsigned int *)0x4, aic_undefined); }