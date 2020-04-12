/*!
 * @file
 * @brief
 */

#include "stm8s.h"
#include "stm8s_clk.h"
#include "stm8s_tim2.h"
#include "motors_plugin.h"
#include "data_model.h"
#include "tiny_utils.h"

enum {
  pin_6 = 1 << 6,
  pin_7 = 1 << 7,

  period = 800
};

typedef volatile uint8_t reg_t;

static void update_output(motor_power_t power, uint8_t pin, reg_t* ccrh, reg_t* ccrl) {
  if(power >= 0) {
    GPIOC->ODR &= ~pin;
  }
  else {
    GPIOC->ODR |= pin;
    power = -power;
  }

  uint16_t compare = (period * power) / motor_power_max;
  *ccrh = compare >> 8;
  *ccrl = compare & 0xFF;
}

static void data_changed(void* context, const void* _args) {
  (void)context;

  reinterpret(args, _args, const tiny_key_value_store_on_change_args_t*);
  reinterpret(power, args->value, const motor_power_t*);

  switch(args->key) {
    case key_left_motor:
      update_output(*power, pin_6, &TIM2->CCR2H, &TIM2->CCR2L);
      break;

    case key_right_motor:
      update_output(*power, pin_7, &TIM2->CCR1H, &TIM2->CCR1L);
      break;
  }
}

static void initialize_gpio(void) {
  // PC6 push/pull output
  GPIOC->CR1 |= pin_6;
  GPIOC->DDR |= pin_6;

  // PC7 push/pull output
  GPIOC->CR1 |= pin_7;
  GPIOC->DDR |= pin_7;
}

static void initialize_tim2(void) {
  // Un-gate clock for TIM2
  CLK->PCKENR1 |= (1 << CLK_PERIPHERAL_TIMER2);

  // Prescalar == 1, 16 MHz
  TIM2->PSCR = 0;

  // Set frequency via reload register
  // 800 => 20KHz
  TIM2->ARRH = period >> 8;
  TIM2->ARRL = period & 0xFF;

  // Enable TIM2
  // Use shadow register for ARR in case we unlock frequency
  TIM2->CR1 = TIM2_CR1_CEN | TIM2_CR1_ARPE;
}

static void initialize_tim2_channel2(void) {
  // Default to 0% duty cycle
  TIM2->CCR2H = 0;
  TIM2->CCR2L = 0;

  // PWM mode 1
  // Use shadow register for CCMR
  TIM2->CCMR2 = TIM2_OCMODE_PWM1 | TIM2_CCMR_OCxPE;

  // Enable output for channel 2
  TIM2->CCER1 |= TIM2_CCER1_CC2E;
}

void initialize_tim2_channel1(void) {
  // Default to 0% duty cycle
  TIM2->CCR1H = 0;
  TIM2->CCR1L = 0;

  // PWM mode 1
  // Use shadow register for CCMR
  TIM2->CCMR1 = TIM2_OCMODE_PWM1 | TIM2_CCMR_OCxPE;

  // Enable output for channel 1
  TIM2->CCER1 |= TIM2_CCER1_CC1E;
}

void motors_plugin_init(motors_plugin_t* self, i_tiny_key_value_store_t* key_value_store) {
  initialize_gpio();
  initialize_tim2();
  initialize_tim2_channel2();
  initialize_tim2_channel1();

  tiny_event_subscription_init(&self->on_change_subscription, self, data_changed);
  tiny_event_subscribe(tiny_key_value_store_on_change(key_value_store), &self->on_change_subscription);
}
