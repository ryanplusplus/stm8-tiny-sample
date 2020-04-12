/*!
 * @file
 * @brief
 */

#include <stdbool.h>
#include <stddef.h>
#include "stm8s.h"
#include "clock.h"
#include "atom.h"
#include "atomqueue.h"
#include "atommutex.h"
#include "atomport-private.h"

enum {
  default_thread_priority = 16,
  pin_5 = (1 << 5)
};

enum {
  queue_message_size = sizeof(bool),
  queue_message_count = 3
};

static ATOM_QUEUE queue;
static uint8_t queue_buffer[queue_message_size * queue_message_count];

static ATOM_MUTEX producer_mutex;

static ATOM_TCB producer_1_tcb;
static uint8_t producer_1_thread_stack[128];

static ATOM_TCB producer_2_tcb;
static uint8_t producer_2_thread_stack[128];

static ATOM_TCB consumer_tcb;
static uint8_t consumer_thread_stack[128];

static uint8_t idle_thread_stack[128];

static void producer_1_thread(uint32_t param) {
  (void)param;

  const bool state = false;

  while(1) {
    atomMutexGet(&producer_mutex, 0);
    {
      (void)atomQueuePut(&queue, 0, &state);
      atomTimerDelay(250);
    }
    atomMutexPut(&producer_mutex);
  }
}

static void producer_2_thread(uint32_t param) {
  (void)param;

  const bool state = true;

  while(1) {
    atomMutexGet(&producer_mutex, 0);
    {
      (void)atomQueuePut(&queue, 0, &state);
      atomTimerDelay(250);
    }
    atomMutexPut(&producer_mutex);
  }
}

static void consumer_thread(uint32_t param) {
  (void)param;

  GPIOB->CR1 |= pin_5;
  GPIOB->DDR |= pin_5;

  while(1) {
    bool state;
    (void)atomQueueGet(&queue, 0, &state);
    GPIOB->ODR = pin_5 * state;
  }
}

static void main_thread(uint32_t param);

void main(void) {
  disableInterrupts();

  clock_init();

  if(atomOSInit(&idle_thread_stack, sizeof(idle_thread_stack), true) == ATOM_OK) {
    int8_t status = ATOM_OK;

    archInitSystemTickTimer();

    status += atomQueueCreate(
      &queue,
      queue_buffer,
      queue_message_size,
      queue_message_count);

    status += atomMutexCreate(
      &producer_mutex);

    status += atomThreadCreate(
      &producer_1_tcb,
      default_thread_priority,
      producer_1_thread,
      0,
      producer_1_thread_stack,
      sizeof(producer_1_thread_stack),
      true);

    status += atomThreadCreate(
      &producer_2_tcb,
      default_thread_priority,
      producer_2_thread,
      0,
      producer_2_thread_stack,
      sizeof(producer_2_thread_stack),
      true);

    status += atomThreadCreate(
      &consumer_tcb,
      default_thread_priority,
      consumer_thread,
      0,
      consumer_thread_stack,
      sizeof(consumer_thread_stack),
      true);

    if(status == ATOM_OK) {
      atomOSStart();
    }
  }

  while(1) {
  }
}
