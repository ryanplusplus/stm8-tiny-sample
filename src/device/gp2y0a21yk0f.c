/*!
 * @file
 * @brief
 */

#include "gp2y0a21yk0f.h"
#include "lookup_table.h"
#include "tiny_utils.h"

#define Volts(x) (uint16_t)((x / 5) * UINT16_MAX)

static const lookup_table_entry_t entries[] = {
  { Volts(0.5), 60 },
  { Volts(0.75), 27 },
  { Volts(1.0), 27 },
  { Volts(1.5), 17 },
  { Volts(2.0), 13 },
  { Volts(2.5), 9 },
  { Volts(3.0), 7 },
};

static const lookup_table_t lookup_table = {
  entries,
  element_count(entries)
};

distance_in_cm_t gp2y0a21yk0f_counts_to_distance(tiny_analog_input_counts_t counts) {
  return (distance_in_cm_t)lookup_table_lookup(&lookup_table, counts);
}
