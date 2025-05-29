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
//	ARdistance =5;
	Rpm_set_lower =3150;//(isthreepointer) ?abs((int)(24.073 * ARdistance * ARdistance- 292.51 * ARdistance + 3998.4+100)):2900;//(24.073 * ARdistance * ARdistance- 292.51 * ARdistance + 3998.4+100)<0? (~(int)(24.073 * ARdistance * ARdistance- 292.51 * ARdistance + 3998.4+100) +1):(24.073 * ARdistance * ARdistance- 292.51 * ARdistance + 3998.4+100 ) :2900;
	Rpm_set_lower = constrain(Rpm_set_lower, 0, 3200);
	Rpm_set_upper =2550;//(isthreepointer) ?abs((int)(-104.35 * ARdistance * ARdistance+ 1431.2 * ARdistance - 2596.8+150)):900;//(-104.35 * ARdistance * ARdistance+ 1431.2 * ARdistance - 2596.8+150)<0? (~(int)(-104.35 * ARdistance * ARdistance+ 1431.2 * ARdistance - 2596.8+150) +1):(-104.35 * ARdistance * ARdistance+ 1431.2 * ARdistance - 2596.8+150 ) :900;
	Rpm_set_upper = constrain(Rpm_set_upper, 0, 3200);
	baseLower = 17.2*Rpm_set_lower + 4088.9-1000;
	baseUpper = 16.877*Rpm_set_upper + 5313.2-1000;
	// }
}

void rotors(bool flag) {
	if (!flag) {
		TIM12->CCR1 =  0;
		TIM12->CCR2 = 0 ;
		return;
	} else
		dis_cal();
	if (HAL_GetTick() - prev >= RotorsSampling)

	{
		counter_upper = TIM4->CNT;
		counter_lower = TIM8->CNT;
		counter_upper = counter_upper / 4;
		Rpmupper = (counter_upper * sixtythousand)/(ppr*((int32_t)HAL_GetTick() - prev));

		counter_lower = counter_lower / 4;
		Rpmlower =(counter_lower * sixtythousand)/(ppr*((int32_t)HAL_GetTick() - prev));
		Rpmupper = (Rpmupper)<0?(~Rpmupper +1):Rpmupper;
		Rpmlower = (Rpmlower)<0?(~Rpmlower +1):Rpmlower;
		errUpper = Rpm_set_upper - Rpmupper;
		errLower = Rpm_set_lower - Rpmlower;

		PwmUpper = baseUpper+(kpUpper * errUpper);
		PwmLower = baseLower+(kpLower * errLower);

		PwmUpper = constrain(PwmUpper, 0, 65500);
		PwmLower = constrain(PwmLower, 0, 65500);



		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, 0);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1);

		TIM12->CCR2 =PwmUpper;  //UPPER
		TIM12->CCR1 =PwmLower;  //LOWER
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

//	if (HAL_GetTick() - prev_loco >= RotorsSampling) {

		counter_4 = TIM1->CNT;
		counter_5 = TIM3->CNT;
//		counter_5 = TIM8->CNT;
		counter_8 = TIM5->CNT;

		counter_8 = counter_8 / 4;
		rpm1 = (counter_8 *sixtythousand)/(ppr*((int32_t)HAL_GetTick()-prev_loco));

		counter_5 = counter_5 / 4;
		rpm2 = (counter_5 *sixtythousand)/(Sixhunppr*((int32_t)HAL_GetTick()-prev_loco));


		counter_4 = counter_4 / 4;
		rpm3 =(counter_4 *sixtythousand)/(ppr*((int32_t)HAL_GetTick() -prev_loco));

		rpm1 = (rpm1<0)?(~rpm1) +1 : rpm1;
		rpm2 = (rpm2<0)?(~rpm2) +1: rpm2;
		rpm3 = (rpm3<0)?(~rpm3)+1:rpm3;
//			  rotors();

		prev_loco = HAL_GetTick();
		__HAL_TIM_SET_COUNTER(&htim1, 0);
		__HAL_TIM_SET_COUNTER(&htim3, 0);
//		__HAL_TIM_SET_COUNTER(&htim8, 0);
		__HAL_TIM_SET_COUNTER(&htim5, 0);

//	}
}

#endif /* INC_ROTORS_H_ */
