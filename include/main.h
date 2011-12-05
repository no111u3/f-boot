/**
 * main code header
 */
/* Includes */
#include <types.h>
#include <AT91RM9200.h>
#include <dbgu.h>
#include <util.h>
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
/* main code */
extern void main(void);
/* first sdram test - test mem size */
static void first_sdram_test(void);
/* first spi test - spi flash detected */
static void first_spi_test(void);