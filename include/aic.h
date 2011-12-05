/**
 * AIC header
 */
 #define AT91C_AIC_BRANCH_OPCODE ((void (*) ()) 0xe51fff20) /* ldr, pc, [pc, #-&F20] */
/* AIC enable irq */
extern void aic_enable_irq (unsigned int irq_id);
/* AIC disable irq */
extern void aic_disable_irq(unsigned int irq_id);
/* AIC configure irq */
extern unsigned int aic_configure_irq (unsigned int irq_id, unsigned int priority,
    unsigned int src_type, void (*newHandler)(void));
/* AIC set exception vector */
extern unsigned int aic_set_exception_vector(unsigned int *pVector, void (*Handler)());
/* AIC acknowledge irq */
extern void aic_acknowledge_irq ();
/* AIC init */
extern void aic_init(void (*IrqHandler)(), void (*FiqHandler)(),
	void (*DefaultHandler)(), void (*SpuriousHandler)(), unsigned int protectMode);
/* AIC spirious handler */
extern void aic_spirious_int(void);
/* AIC data abort handler */
extern void aic_data_abort(void);
/* AIC fetch abort handler */
extern void aic_fetch_abort(void);
/* AIC undefined handler */
extern void aic_undefined(void);
/* AIC default handler */
extern void aic_default(void);