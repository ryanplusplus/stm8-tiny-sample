/*!
 * @file
 * @brief
 */

#include "accelerometer_plugin.h"
#include "data_model.h"
#include "i2c.h"
#include "tiny_utils.h"

static void acceleration_updated(void* context, const void* args) {
  reinterpret(store, context, i_tiny_key_value_store_t*);
  tiny_key_value_store_write(store, key_acceleration, args);
}

void accelerometer_plugin_init(
  accelerometer_plugin_t* self,
  i_tiny_key_value_store_t* store,
  tiny_timer_group_t* timer_group) {
  lsm303d_init(&self->lsm303, timer_group, i2c_init());
  tiny_event_subscription_init(&self->subscription, store, acceleration_updated);
  tiny_event_subscribe(lsm303d_on_acceleration_update(&self->lsm303), &self->subscription);
}
