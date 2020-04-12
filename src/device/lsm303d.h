/*!
 * @file
 * @brief
 */

#ifndef lsm303d_h
#define lsm303d_h

#include <stdbool.h>
#include "hal/i_tiny_async_i2c.h"
#include "tiny_timer.h"
#include "tiny_single_subscriber_event.h"

typedef struct {
  struct {
    int16_t x;
    int16_t y;
    int16_t z;
  };
} lsm303d_acceleration_update_t;

typedef struct {
  union {
    uint8_t raw[1];
    lsm303d_acceleration_update_t acceleration;
  };
} lsm303d_read_buffer_t;

typedef struct {
  i_tiny_async_i2c_t* i2c;
  tiny_timer_group_t* timer_group;
  tiny_timer_t timer;

  volatile bool busy;
  volatile bool data_ready;

  lsm303d_read_buffer_t read_buffer;

  tiny_single_subscriber_event_t acceleration_update;
} lsm303d_t;

void lsm303d_init(lsm303d_t* self, tiny_timer_group_t* timer_group, i_tiny_async_i2c_t* i2c);

i_tiny_event_t* lsm303d_on_acceleration_update(lsm303d_t* self);

#endif
