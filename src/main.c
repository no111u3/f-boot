/**
 * Main code
 */
/* Includes */
#include <main.h>
/* main code */
extern void sys_main(void) {
    char selector;
    char command_line[40];
    unsigned int d_addr = 0, d_size, r_addr;
    /* first sdram test - test mem size */
    first_sdram_test();
    /* first spi test - spi flash detected */
    first_spi_test();
    /* setup SYS interrupt */
    aic_configure_irq(AT91C_ID_SYS, AT91C_AIC_PRIOR_LOWEST,
                      AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE, aic_asm_sys_handler);
    /* enable SYS interrupt */
    aic_enable_irq(AT91C_ID_SYS);
    /* setup rtt - 1Hz clock */
    AT91C_BASE_ST->ST_RTMR = 0x4000;
    /* main loop */
    while (1) {
        util_printf(main_menu);
        util_gets(command_line);
        util_puts("\n");
        selector = command_line[0];
        switch (selector) {
            /* download throug x-modem */
            case '1':
                d_addr = util_hex_int(&command_line[2]);
                if (d_addr) {
                    util_printf("Download to 0x%x\n", d_addr);
                    d_size = download(d_addr);
                }
                else {
                    util_puts("Undefined download address\n");
                }
            break;
            case '2':
                r_addr = util_hex_int(&command_line[2]);
                if (r_addr) {
                    util_printf("Run code at 0x%x\n", r_addr);
                    asm_run_code(r_addr);
                }
                else {
                    util_puts("Undefined run address\n");
                }
            break;
            /* exit of loop */
            case 'q':
                util_puts("Quit & Reset\n");
                AT91C_BASE_ST->ST_WDMR = 64 | AT91C_ST_RSTEN;
                AT91C_BASE_ST->ST_CR = AT91C_ST_WDRST;
                while (1);
            break;
            /* undef */
            default:
                util_puts("Undefined command\n");
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
/* download */
static int download(unsigned int address) {
    pt_start_dl = (void *)address;
    dl_size = 0;
    /* setup rtt interrupt flag */
    AT91C_BASE_ST->ST_IER = AT91C_ST_RTTINC;
    /* enable RXRDY interrupt in DBGU */
    AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_RXRDY;
    while(!dl_size);
    util_delay(100000);
    if (dl_size > 0) {
        util_printf("\n\nTransfer complete\nByte's sended: %d\n", dl_size);
    }
    else {
        util_puts("Transfer failed\n!");
        dl_size = 0;
    }
    
    return dl_size;
}
/* system interrupt handler */
extern void sys_handler(void) {
    int st_status = AT91C_BASE_ST->ST_SR & AT91C_BASE_ST->ST_IMR;
    int dbgu_status = AT91C_BASE_DBGU->DBGU_CSR & AT91C_BASE_DBGU->DBGU_IMR;
    
    if (dbgu_status & AT91C_US_RXRDY) {
        /* disable RXRDY interrupt in DBGU */
        AT91C_BASE_DBGU->DBGU_IDR |= AT91C_US_RXRDY;
        /* disable rtt interrupt flag */
        AT91C_BASE_ST->ST_IDR = AT91C_ST_RTTINC;
        dl_size = util_xmod_recv(pt_start_dl);
    }
    
    /* handler of rtt - rttinc */
    if (st_status & AT91C_ST_RTTINC) {
        AT91C_BASE_PIOB->PIO_ODSR ^= AT91C_PIO_PB27;
        dbgu_putc('C');
    }
}