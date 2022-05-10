/*
 * LiteX stdio support for Picolibc.
 *
 * More info: picolibc/doc/os.md
 */


#include <libbase/console.h>
#include <libbase/uart.h>

#include <generated/csr.h>



static int
litex_putc(char c, FILE *file)
{
	(void) file; /* Not used in this function */
#ifdef CSR_UART_BASE
	uart_write(c);
	if (c == '\n')
		litex_putc('\r', NULL);
#endif
	return c;
}
