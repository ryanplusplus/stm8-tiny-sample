/*!
 * @file
 * @brief
 */

#include "lookup_table.h"

uint16_t lookup_table_lookup(const lookup_table_t* table, uint16_t x) {
  if(x < table->entries[0].x) {
    return table->entries[0].y;
  }

  for(uint16_t i = 0; i < table->entry_count; i++) {
    if(x == table->entries[i].x) {
      return table->entries[i].y;
    }

    if(x < table->entries[i].x) {
      uint16_t x0 = table->entries[i - 1].x;
      uint16_t x1 = table->entries[i].x;
      uint16_t y0 = table->entries[i - 1].y;
      uint16_t y1 = table->entries[i].y;

      return y0 + ((y1 - y0) * (x - x0)) / (x1 - x0);
    }
  }

  return table->entries[table->entry_count - 1].y;
}
