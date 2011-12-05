/**
 * Main code
 */
/* Includes */
#include <main.h>
/* main code */
extern void main(void) {
    unsigned char flag;
    /* first sdram test - test mem size */
    first_sdram_test();
    /* first spi test - spi flash detected */
    first_spi_test();
    /* main loop */
    while (1) {
        util_printf(main_menu);
        flag = dbgu_getc();
        switch (flag) {
            // exit of loop
            case 'q':
                util_puts("\nQuit & Reset\n");
                AT91C_BASE_ST->ST_WDMR = 64 | AT91C_ST_RSTEN;
                AT91C_BASE_ST->ST_CR = AT91C_ST_WDRST;
                while (1);
            break;
            // undef
            default:
                util_puts("\nUndefined command\n");
            break;
        }
    }
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
/* upload */
static int upload(void * address) {
    pt_start_dl = address;
    dl_size = 0;
    /* setup rtt interrupt flag */
    AT91C_BASE_ST->ST_IER = AT91C_ST_RTTINC;
    /* enable RXRDY interrupt in DBGU */
    AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_RXRDY;
    while(!dl_size);
    delay(100000);
    if (dl_size > 0) {
        util_printf("\n\nTransfer complete\nByte's sended: 0x%x\n", dl_size);
    }
    else {
        util_puts("Transfer failed\n!");
        dl_size = 0;
    }
    
    return dl_size;
}