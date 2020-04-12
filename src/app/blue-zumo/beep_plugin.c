/*!
 * @file
 * @brief
 */

#include "stm8s.h"
#include "stm8s_clk.h"
#include "stm8s_beep.h"
#include "beep_plugin.h"
#include "data_model.h"
#include "tiny_utils.h"

enum {
  // BEEPDIV = 16 so that lowest frequency is 128 / 8 / 16 = 1 KHz
  beep_div = 0x0E,

  beep_csr_off = 0,
  beep_csr_1khz = beep_div | BEEP_CSR_BEEPEN | BEEP_FREQUENCY_1KHZ,
  beep_csr_2khz = beep_div | BEEP_CSR_BEEPEN | BEEP_FREQUENCY_2KHZ,
  beep_csr_4khz = beep_div | BEEP_CSR_BEEPEN | BEEP_FREQUENCY_4KHZ
};

static void data_changed(void* context, const void* _args) {
  (void)context;

  reinterpret(args, _args, const tiny_key_value_store_on_change_args_t*);

  if(args->key == key_beep) {
    reinterpret(beep, args->value, const beep_t*);

    switch(*beep) {
      case beep_off:
        BEEP->CSR = 0;
        break;

      case beep_1khz:
        BEEP->CSR = beep_csr_1khz;
        break;

      case beep_2khz:
        BEEP->CSR = beep_csr_2khz;
        break;

      case beep_4khz:
        BEEP->CSR = beep_csr_4khz;
        break;
    }
  }
}

void beep_plugin_init(beep_plugin_t* self, i_tiny_key_value_store_t* key_value_store) {
  // Un-gate clock for AWU
  CLK->PCKENR2 |= (1 << (CLK_PERIPHERAL_AWU & 0xF));

  tiny_event_subscription_init(&self->on_change_subscription, self, data_changed);
  tiny_event_subscribe(tiny_key_value_store_on_change(key_value_store), &self->on_change_subscription);
}
