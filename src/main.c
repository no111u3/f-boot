/**
 * Main code
 */
/* Includes */
#include <main.h>
/* main code */
extern void main(void) {
    /* first sdram test - test mem size */
    first_sdram_test();
    /* first spi test - spi flash detected */
    first_spi_test();
}
/* first sdram test - test mem size */
static void first_sdram_test(void) {
    unsigned int mem_w, mem_r, i, j;
    unsigned int * pmem = P_MEM_BEGIN;
    
    util_puts("\nSDRAM: ");
    for (i = 0; i < MEM_SIZE_K / 4; i++) {
        j = i << 10;
        *(pmem + j) = i;
    }
    
    for (i = 0; i < MEM_SIZE_K / 4; i++) {
        j = i << 10;
        mem_r = *(pmem + j);
        mem_w = i;
        if (mem_r != mem_w) {
            util_printf("0x%x, r - %x, w - %x\n", j, mem_r, mem_w);
            if (i > 0)
                break;
        }
    }
    util_printf("%dkB\n", i * 4);
}
/* first spi test - spi flash detected */
static void first_spi_test(void) {
    util_puts("\nSPI: ");
    at45_init();
}