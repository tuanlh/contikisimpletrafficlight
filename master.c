#include "contiki.h"
#include "dev/leds.h"
#include "sys/etimer.h"
#include "sys/clock.h"
#include "net/rime.h"
#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
static struct etimer t;
static uint8_t count;
/*---------------------------------------------------------------------------*/
PROCESS(blink_process, "LED blink process");
AUTOSTART_PROCESSES(&blink_process);
/*---------------------------------------------------------------------------*/
void
broadcast_an_integer(struct broadcast_conn *bc_conn, int x)
{
  packetbuf_copyfrom(&x, sizeof(x));
  broadcast_send(bc_conn);
}

static void
broadcast_recv(struct broadcast_conn *c, const rimeaddr_t *from)
{
  
}

static struct broadcast_conn broadcast;
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink_process, ev, data)
{
  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  broadcast_open(&broadcast, 129, &broadcast_call);

  count = 1;

  while(1) {
    etimer_set(&t, CLOCK_SECOND);

    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
    leds_off(LEDS_ALL);
    if(count <= 6) {
      leds_on(LEDS_RED);
    } else if (count <= 11) {
      leds_on(LEDS_BLUE);
    } else {
      leds_on(LEDS_GREEN);
    }
    count++;
    broadcast_an_integer(&broadcast, count);
    if (count >= 13)
      count = 1;
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
