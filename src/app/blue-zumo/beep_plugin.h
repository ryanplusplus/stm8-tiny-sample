/*!
 * @file
 * @brief
 */

#ifndef beep_plugin_h
#define beep_plugin_h

#include "i_tiny_key_value_store.h"

typedef struct {
  tiny_event_subscription_t on_change_subscription;
} beep_plugin_t;

void beep_plugin_init(beep_plugin_t* self, i_tiny_key_value_store_t* key_value_store);

#endif
