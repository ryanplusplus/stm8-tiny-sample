/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include <stdlib.h>
#include "application.h"
#include "tiny_utils.h"

static tiny_event_subscription_t derp_sub;

static void derp_change(void* context, const void* _args) {
  reinterpret(args, _args, const tiny_key_value_store_on_change_args_t*);
  reinterpret(store, context, i_tiny_key_value_store_t*);

  if(args->key == key_acceleration) {
    reinterpret(value, args->value, const acceleration_t*);
    if(value->x > 10000) {
      motor_power_t power = -30;
      tiny_key_value_store_write(store, key_right_motor, &power);
      tiny_key_value_store_write(store, key_left_motor, &power);
    }
    else if(value->x < -10000) {
      motor_power_t power = 30;
      tiny_key_value_store_write(store, key_right_motor, &power);
      tiny_key_value_store_write(store, key_left_motor, &power);
    }
    else if(abs(value->y) > 10000) {
      motor_power_t power = 0;
      tiny_key_value_store_write(store, key_right_motor, &power);
      tiny_key_value_store_write(store, key_left_motor, &power);
    }
  }
}

static void derp(i_tiny_key_value_store_t* store) {
  tiny_event_subscription_init(&derp_sub, store, derp_change);
  tiny_event_subscribe(tiny_key_value_store_on_change(store), &derp_sub);
}

void application_init(application_t* self, tiny_timer_group_t* timer_group) {
  data_model_init(&self->data_model);
  i_tiny_key_value_store_t* store = data_model_key_value_store(&self->data_model);

  motors_plugin_init(&self->motors_plugin, store);
  beep_plugin_init(&self->beep_plugin, store);
  line_sensors_plugin_init(&self->line_sensors_plugin, store, timer_group);
  accelerometer_plugin_init(&self->accelerometer_plugin, store, timer_group);

  derp(store);
}
