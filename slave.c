#include "contiki.h"
#include "dev/leds.h"
#include "sys/etimer.h"
#include "sys/clock.h"
#include "net/rime.h"

#include <stdio.h> /* For printf() */

PROCESS(blink_process, "LED blink process");
AUTOSTART_PROCESSES(&blink_process);
/*---------------------------------------------------------------------------*/
static void
broadcast_recv(struct broadcast_conn *c, const rimeaddr_t *from)
{
  if(packetbuf_datalen() >= sizeof(int)) {
    uint8_t count = *(int *)packetbuf_dataptr();
    printf("%d\n", count);
    leds_off(LEDS_ALL);
    if(count <= 5) {
      leds_on(LEDS_BLUE);
    } else if (count <= 6) {
      leds_on(LEDS_GREEN);
    } else {
      leds_on(LEDS_RED);
    }
  }
}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink_process, ev, data)
{
  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)
  PROCESS_BEGIN();
  leds_off(LEDS_ALL);
  broadcast_open(&broadcast, 129, &broadcast_call);
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
