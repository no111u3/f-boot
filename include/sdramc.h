/**
 * SDRAMC header
 */
#define SDRAMC_PORTC_SEL_LINE \
    AT91C_PC16_D16 | AT91C_PC17_D17 | AT91C_PC18_D18 | AT91C_PC19_D19 | \
    AT91C_PC20_D20 | AT91C_PC21_D21 | AT91C_PC22_D22 | AT91C_PC23_D23 | \
    AT91C_PC24_D24 | AT91C_PC25_D25 | AT91C_PC26_D26 | AT91C_PC27_D27 | \
    AT91C_PC28_D28 | AT91C_PC29_D29 | AT91C_PC30_D30 | AT91C_PC31_D31
/* Write Recovery Delay */
#define AT91Cmy_SDRAM_TWR 15
/* Row Cycle Delay */
#define AT91Cmy_SDRAM_TRC 15
/* Row Precharge Delay */
#define AT91Cmy_SDRAM_TRP 15
/* Row to Column Delay */
#define AT91Cmy_SDRAM_TRCD 15
/* Active to Precharge Delay */
#define AT91Cmy_SDRAM_TRAS 15
/* Exit Self Refresh to Active Delay */
#define AT91Cmy_SDRAM_TXSR 15
/* WB = 0, OpMode = 0, CAS = 2, BT = 0, Burst lenght = 0 (1) */
#define AT91Cmy_SDRAM_MR_CHIP 0x0080
/*old -> 0x2E0; 0x170 -> 60 MHz; 0x293 -> 90Mhz; 0x61 -> 16MHz */
#define AT91Cmy_SDRAM_Refresh 0x230
/* SDRAMC enable i/o pins */
static void sdramc_pio_enable(void);
/* AIC EBI init */
static void aic_ebi_init(void);
/* SDRAMC init */
void sdramc_init(void);