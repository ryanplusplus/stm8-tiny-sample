/*!
 * @file
 * @brief Uses TIM1 to detect the presence of a line. Samples at ~100 Hz.
 *
 * PC3/TIM1_CH3 => Left line sensor
 * PC4/TIM1_CH4 => Right line sensor
 */

#ifndef line_sensors_plugin_h
#define line_sensors_plugin_h

#include "i_tiny_key_value_store.h"
#include "tiny_timer.h"

typedef struct {
  tiny_timer_t timer;
  i_tiny_key_value_store_t* key_value_store;
} line_sensors_plugin_t;

void line_sensors_plugin_init(
  line_sensors_plugin_t* self,
  i_tiny_key_value_store_t* key_value_store,
  tiny_timer_group_t* timer_group);

#endif
