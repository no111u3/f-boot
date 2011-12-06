/**
 * main code header
 */
/* Includes */
#include <types.h>
#include <AT91RM9200.h>
#include <dbgu.h>
#include <aic.h>
#include <util.h>
#include <at45.h>
/* memory begin address */
#define MEM_BEGIN 0x20000000
/* pointer of memory begin */
#define P_MEM_BEGIN (void *)MEM_BEGIN
/* Memory size in MB */
#define MEM_SIZE_M 128
/* Memory size in kB */
#define MEM_SIZE_K (MEM_SIZE_M << 10)
/* Memory size in B */
#define MEM_SIZE_B (MEM_SIZE_M << 20)
/* global vars */
/** download size */
volatile int dl_size;
/** download start point */
void *pt_start_dl;
/** main menu */
static const char *main_menu = {
  "1: Download [addr]\n"
  "q: Exit and Reboot\n"
};
/* main code */
extern void sys_main(void);
/* first sdram test - test mem size */
static void first_sdram_test(void);
/* first spi test - spi flash detected */
static void first_spi_test(void);
/* download */
static int download(unsigned int address);
/* system interrupt handler */
extern void sys_handler(void);
/* aic asm SYS handler */
extern void aic_asm_sys_handler(void);