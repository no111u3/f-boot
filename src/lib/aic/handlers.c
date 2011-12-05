/**
 * AIC interrupt handlers
 */
/* AIC spirious handler */
extern void aic_spirious_int(void) {
    util_puts("Spirious Interrupt detected\n");
    while (1);
}
/* AIC data abort handler */
extern void aic_data_abort(void) {
    util_puts("Data Abort detected\n");
    while (1);
}
/* AIC fetch abort handler */
extern void aic_fetch_abort(void) {
    util_puts("Fetch Abort detected\n");
    while (1);
}
/* AIC undefined handler */
extern void aic_undefined(void) {
    util_puts("Udefined detected\n");
    while (1);
}
/* AIC default handler */
extern void aic_default(void) {
    util_puts("Handler not install use default");
    while (1);
}
