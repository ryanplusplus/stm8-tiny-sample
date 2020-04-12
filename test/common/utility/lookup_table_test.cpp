/*!
 * @file
 * @brief
 */

extern "C" {
#include "lookup_table.h"
#include "tiny_utils.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

static const lookup_table_entry_t entries[] = {
  { 100, 1000 },
  { 200, 1100 },
  { 500, 1700 },
  { 600, 1750 }
};

static const lookup_table_t table = {
  entries,
  element_count(entries)
};

TEST_GROUP(lookup_table) {
  uint8_t dummy;

  void setup() {
  }
};

TEST(lookup_table, should_return_first_y_for_x_less_than_lowest_x) {
  CHECK_EQUAL(1000, lookup_table_lookup(&table, 50));
}

TEST(lookup_table, should_return_last_y_for_x_greater_than_highest_x) {
  CHECK_EQUAL(1750, lookup_table_lookup(&table, 650));
}

TEST(lookup_table, should_return_y_for_x_when_x_is_in_the_table) {
  CHECK_EQUAL(1000, lookup_table_lookup(&table, 100));
  CHECK_EQUAL(1100, lookup_table_lookup(&table, 200));
  CHECK_EQUAL(1700, lookup_table_lookup(&table, 500));
  CHECK_EQUAL(1750, lookup_table_lookup(&table, 600));
}

TEST(lookup_table, should_interpolate_when_x_is_between_xs_in_the_table) {
  CHECK_EQUAL(1050, lookup_table_lookup(&table, 150));
  CHECK_EQUAL(1500, lookup_table_lookup(&table, 400));
  CHECK_EQUAL(1725, lookup_table_lookup(&table, 550));
}
