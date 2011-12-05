/**
 * UTIL header
 */
/* SPI struct transfer block */
struct spi_t_block {
    void *spi_rx;
    const void *spi_tx;
    unsigned spi_t_len;
};
/* SPI enable i/o pins */
static void spi_pio_enable(void);
/* SPI setup mode */
static void spi_set_mode(const unsigned char mode);
/* SPI init */
extern void spi_init(const unsigned char mode);
/* SPI chip select setup */
extern void spi_cs_set(unsigned cs, unsigned bits, unsigned baud, unsigned delay, unsigned polar);
/* SPI chip select */
extern void spi_select(unsigned cs);
/* SPI tarnsfer block */
extern void spi_transfer(struct spi_t_block * t_block, int n);