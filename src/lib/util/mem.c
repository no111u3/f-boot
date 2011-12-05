/**
 * UTIL memory
 */
/* UTIL memory copy */
extern void util_memcp(void *dst, const void *src, unsigned len) {
	const unsigned *ptr_r = src;
	const unsigned *ptr_fin = ptr_r + (len >> 2);
	unsigned *ptr_w = dst;

	while (ptr_r != ptr_fin) {
		*ptr_w++ = *ptr_r++;
	}

	len &= 0x03;

	const unsigned char *ptr8_r = (unsigned char*) ptr_r;
	const unsigned char *ptr8_fin = ptr8_r + len;
	unsigned char *ptr8_w = (unsigned char *) ptr_w;

	while (ptr8_r != ptr8_fin) {
		*ptr8_w++ = *ptr8_r++;
	}
}