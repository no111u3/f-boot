/**
 * SPI
 */
/* Includes */
/* SPI selector decode */
static unsigned spi_cs_dec[] = {
    0x000e0000,
    0x000d0000,
    0x000b0000,
    0x00070000,
};
/** SPI init */
#include "spi/init.c"
/** SPI chip selector */
#include "spi/cs.c"
/** SPI transfer */
#include "spi/transfer.c"