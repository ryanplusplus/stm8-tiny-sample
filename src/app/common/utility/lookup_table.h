/*!
 * @file
 * @brief Linear-interpolated lookup table.
 *
 * Note that the entries are required to be given with x values ascending.
 */

#ifndef lookup_table_h
#define lookup_table_h

#include <stdint.h>

typedef struct {
  uint16_t x;
  uint16_t y;
} lookup_table_entry_t;

typedef struct {
  const lookup_table_entry_t* entries;
  uint16_t entry_count;
} lookup_table_t;

uint16_t lookup_table_lookup(const lookup_table_t* table, uint16_t x);

#endif
