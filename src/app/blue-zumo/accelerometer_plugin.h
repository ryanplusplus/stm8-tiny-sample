/*!
 * @file
 * @brief
 */

#ifndef accelerometer_plugin_h
#define accelerometer_plugin_h

#include "i_tiny_key_value_store.h"
#include "tiny_event_subscription.h"
#include "lsm303d.h"
#include "i2c.h"

typedef struct {
  lsm303d_t lsm303;
  tiny_event_subscription_t subscription;
} accelerometer_plugin_t;

void accelerometer_plugin_init(
  accelerometer_plugin_t* self,
  i_tiny_key_value_store_t* store,
  tiny_timer_group_t* timer_group);

#endif
