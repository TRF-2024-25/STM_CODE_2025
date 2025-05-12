/*
 * rotors.h
 *
 *  Created on: Apr 19, 2025
 *      Author: Harsh
 */

#ifndef INC_ROTORS_H_
#define INC_ROTORS_H_
#include <stdint.h>
#include <math.h>
#include "variables.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim8;

int16_t counter_upper = 0;
int16_t counter_lower = 0;
int16_t counter_4 = 0;
int16_t counter_5 = 0;
int16_t counter_8 = 0;

volatile int rpm_upper = 0;
volatile int rpm_lower = 0;
volatile int rpm1 = 0;
volatile int rpm2 = 0;
volatile int rpm3 = 0;

volatile int RPM_set_lower = 2500;
volatile int RPM_set_upper = 2500;

volatile int error_upper = 0;
volatile int error_lower = 0;

volatile int pwm_upper = 0;
volatile int pwm_lower = 0;

volatile int upper_base = 35000;
volatile int lower_base = 40000;

int prev = 0;
int prev_loco = 0;

int constrain(int value, int min, int max) {
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

float constrain_float(float value,float min,float max){
	if(value<min){
		return min;
	}
	else if(value> max){
		return max;
	}
	else{
		return value;
	}
}
void absolute(int *value) {
	if (*value < 0) {
		*value = (~*value) + 1;
	}
//	return value;
}

void dis_cal() {

	// if (ARdistance > 0.0) {
	ARdistance = 5;
	RPM_set_lower =(isthreepointer) ?(24.073 * ARdistance * ARdistance- 292.51 * ARdistance + 3998.4 - 160)<0? (~(int)(24.073 * ARdistance * ARdistance- 292.51 * ARdistance + 3998.4 - 160) +1):(24.073 * ARdistance * ARdistance- 292.51 * ARdistance + 3998.4 - 160) :2900;
	RPM_set_lower = constrain(RPM_set_lower, 0, 3200);
	RPM_set_upper =(isthreepointer) ?(-104.35 * ARdistance * ARdistance+ 1431.2 * ARdistance - 2596.8 - 190)<0? (~(int)(-104.35 * ARdistance * ARdistance+ 1431.2 * ARdistance - 2596.8 - 190) +1):(-104.35 * ARdistance * ARdistance+ 1431.2 * ARdistance - 2596.8 - 190) :900;
	RPM_set_upper = constrain(RPM_set_upper, 0, 3200);
	lower_base = 17.2*RPM_set_lower + 4088.9+1400;
	upper_base = 16.877*RPM_set_upper + 5313.2+1000;
	// }
}

void rotors(bool flag) {
	// encoder upper PE9    PE11 tim1
	// Encoder lower PA6    PA7 tim3

	// upper pwm  PE5 tim9 channel 1
	// lower pwm  PE6 tim9 channel 2

	// upper direction PE1
	// lower direction PE3
	if (!flag) {
		TIM9->CCR1 = 0;
		TIM9->CCR2 = 0;
		return;
	} else
		dis_cal();
	if (HAL_GetTick() - prev >= 80)

	{
		counter_upper = TIM4->CNT;
		counter_lower = TIM8->CNT;
		counter_upper = counter_upper / 4;
		rpm_upper = (counter_upper * 60000)/(360*((int32_t)HAL_GetTick() - prev));

		counter_lower = counter_lower / 4;
		rpm_lower =(counter_lower * 60000)/(360*((int32_t)HAL_GetTick() - prev));
		rpm_upper = (rpm_upper)<0?(~rpm_upper +1):rpm_upper;
		rpm_lower = (rpm_lower)<0?(~rpm_lower +1):rpm_lower;
		error_upper = RPM_set_upper - rpm_upper;
		error_lower = RPM_set_lower - rpm_lower;

		pwm_upper = upper_base +(kpUpper * error_upper);
		pwm_lower = lower_base +(kpLower * error_lower);

		pwm_upper = constrain(pwm_upper, 0, 65500);
		pwm_lower = constrain(pwm_lower, 0, 65500);



		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, 0);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, 1);

		TIM9->CCR1 =pwm_upper;  //UPPER
		TIM9->CCR2 =pwm_lower;  //LOWER
		prev = HAL_GetTick();
		counter_upper=0;
		counter_lower = 0;
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		__HAL_TIM_SET_COUNTER(&htim8, 0);

	}

}

void feed() {
	HAL_GPIO_WritePin(pistonUp_Port, pistonUp_Pin, 1);
	HAL_Delay(1500);
	HAL_GPIO_WritePin(pistonUp_Port, pistonUp_Pin, 0);
	HAL_GPIO_WritePin(pistonDown_Port, pistonDown_Pin, 1);
	HAL_Delay(200);
	HAL_GPIO_WritePin(pistonDown_Port, pistonDown_Pin, 0);
	HAL_Delay(200);
}

void rpm_cal() {

	if (HAL_GetTick() - prev_loco >= 80) {

		counter_4 = TIM1->CNT;
		counter_5 = TIM3->CNT;
		counter_8 = TIM5->CNT;

		counter_8 = counter_8 / 4;
		rpm1 = (counter_8 *60000)/(360*((int32_t)HAL_GetTick()-prev_loco));

		counter_5 = counter_5 / 4;
		rpm2 = (counter_5 *60000)/(600*((int32_t)HAL_GetTick()-prev_loco));

//		counter_8 = counter_8 / 4;
//		rpm1 = (counter_8 *60000)/(600*((int32_t)HAL_GetTick()-prev_loco));
//
//		counter_5 = counter_5 / 4;
//		rpm2 = (counter_5 *60000)/(360*((int32_t)HAL_GetTick()-prev_loco));

		counter_4 = counter_4 / 4;
		rpm3 =(counter_4 *60000)/(360*((int32_t)HAL_GetTick() -prev_loco));

		rpm1 = (rpm1<0)?(~rpm1) +1 : rpm1;
		rpm2 = (rpm2<0)?(~rpm2) +1: rpm2;
		rpm3 = (rpm3<0)?(~rpm3)+1:rpm3;
//			  rotors();

		prev_loco = HAL_GetTick();
		counter_4, counter_5, counter_8 = 0;
		__HAL_TIM_SET_COUNTER(&htim1, 0);
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		__HAL_TIM_SET_COUNTER(&htim5, 0);

	}
}

#endif /* INC_ROTORS_H_ */
