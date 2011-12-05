/**
 * SPI chip selector
 */
/* SPI chip select setup */
static void spi_cs_set(unsigned cs, unsigned bits, unsigned baud, unsigned delay, unsigned polar) {
    AT91C_BASE_SPI->SPI_CSR[cs] = (delay << 24) | ((delay >> 1) << 16) |
        (baud << 8) | (((bits - 8) << 4) & 0xf0) | (polar & 0x1);
}
/* SPI chip select */
extern void spi_select(unsigned cs) {
    unsigned spi_mr_tmp = AT91C_BASE_SPI->SPI_MR;
    AT91C_BASE_SPI->SPI_MR = (spi_mr_tmp & 0xfff0ffff) | spi_cs_dec[cs];
}