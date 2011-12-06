/**
 * PMC header
 */
/* Defines */
#define DELAY_PLL 100
#define DELAY_MCK 100

/* enable slow clock */
extern void slck_en(void);
/* enable main clock */
extern void mck_en(void);
/* enable PLLA clock */
extern void pllack_en(unsigned short mdiv);
/* enable PLLB clock */
extern void pllbck_en(void);
/* main clock init */
extern void mck_init(unsigned int mck_value);
/* PMC peripheral enable clock */
extern void pmc_periph_clock_enable(unsigned periph_id);
/* PMC peripheral disable clock */
extern void pmc_periph_clock_disable(unsigned periph_id);
/* PLLA setup */
extern void plla_setup(const char plla_div, const char plla_count,
    const char plla_out, const char plla_mul);
/* PLLB setup */
extern void pllb_setup(const char pllb_div, const char pllb_count,
    const char pllb_out, const char pllb_mul, const char pllb_usb_96m);
