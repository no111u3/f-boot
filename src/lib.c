/**
 * System lib
 */
/* Includes */
#include <lib.h>
/* Modules */
/** DBGU */
#include "lib/dbgu.c"
/** PMC */
#include "lib/pmc.c"
/** AIC */
#include "lib/aic.c"
/** SDRAMC */
#include "lib/sdramc.c"
/** SPI */
#include "lib/spi.c"
/** UTIL */
#include "lib/util.c"
/** AT45 flash's */
#include "lib/at45.c"
/* Other functions */
/** Raise */
extern void raise(void) {
    return;
}