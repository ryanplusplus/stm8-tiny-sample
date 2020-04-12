/*!
 * @file
 * @brief
 */

#ifndef data_model_h
#define data_model_h

#include <stdint.h>
#include <stdbool.h>
#include "tiny_ram_key_value_store.h"
#include "tiny_ram_key_value_store_macros.h"
#include "motor_power.h"
#include "beep.h"
#include "acceleration.h"

// clang-format off
#define data_model_key_value_pairs(pair) \
  pair(key_left_motor,            motor_power_t) \
  pair(key_right_motor,           motor_power_t) \
  pair(key_beep,                  beep_t) \
  pair(key_left_line_detected,    bool) \
  pair(key_right_line_detected,   bool) \
  pair(key_acceleration,          acceleration_t) \
// clang-format on

enumerate_ram_key_value_pairs(data_model_key_value_pairs);

#define _storage_type_name data_model_storage_t

generate_storage_type_for_ram_key_value_pairs(data_model_key_value_pairs);

typedef struct {
  data_model_storage_t storage;
  tiny_ram_key_value_store_t key_value_store;
} data_model_t;

void data_model_init(data_model_t* self);

i_tiny_key_value_store_t* data_model_key_value_store(data_model_t* self);

#endif
