#ifndef PWM_H
#define PWM_H
#include <sys/types.h>

void pwm_configure_gpio_pin(uint, uint32_t, float);
void pwm_start(uint);
void pwm_stop(uint);
#endif
