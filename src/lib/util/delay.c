/**
 * UTIL delay
 */
/* UTIL delay */
extern void util_delay(int tic) {
    volatile int i;
    for (i = 1; i <= tic; i++);
}