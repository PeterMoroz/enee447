#include "os.h"
#include "uart.h"
#include "led.h"
#include "time.h"
#include "callout.h"

void do_hex( struct event *ep )
{
	uart_put32x(ep->data.num); uart_puts("\n");
}

void do_blink( struct event *ep )
{
#if 1	// change this to 0 to try the more complex approach
	blink_led_stall(ep->data.num);
#else
	int i;
	namenum_t foo;
	foo.num = 0;
	bring_timeoutq_current();
	for (i=0; i<(ep->data.num*2); i++) {
		if (i & 0x1) {
			create_timeoutq_event( 50 * i * ONE_MSEC, 0, led_off, foo );
		} else {
			create_timeoutq_event( 50 * i * ONE_MSEC, 0, led_on, foo );
		}
	}
#endif
}

void do_butter( namenum_t data )
{
	namenum_t time;
	time.num = 0;

	bring_timeoutq_current();
	create_timeoutq_event( time.num, 0, led_on, time );

	time.num = 750 * ONE_MSEC;
	create_timeoutq_event( time.num, 0, led_on, time );
	create_timeoutq_event( time.num - MILLISEC(100), 0, led_off, time );

	time.num = 1000 * ONE_MSEC;
	create_timeoutq_event( time.num, 0, led_on, time );
	create_timeoutq_event( time.num - MILLISEC(100), 0, led_off, time );

	time.num = 1500 * ONE_MSEC;
	create_timeoutq_event( time.num, 0, led_on, time );
	create_timeoutq_event( time.num - MILLISEC(100), 0, led_off, time );

	time.num = 2000 * ONE_MSEC;
	create_timeoutq_event( time.num, 0, led_on, time );
	create_timeoutq_event( time.num - MILLISEC(100), 0, led_off, time );

	time.num = 2250 * ONE_MSEC;
	create_timeoutq_event( time.num, 0, led_on, time );
	create_timeoutq_event( time.num - MILLISEC(100), 0, led_off, time );

	create_timeoutq_event( time.num + MILLISEC(200), 0, led_off, time );
}

void do_string( struct event *ep )
{
	uart_putns(ep->data.name, 4); uart_puts("\n");
}
