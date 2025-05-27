#ifndef SRC_DRIBBLE_H_
#define SRC_DRIBBLE_H_

#include "variables.h"
#include "stm32f4xx_hal.h"

ADC_HandleTypeDef hadc1;
uint16_t analogRead_pa4() {
	ADC_ChannelConfTypeDef sConfig = { 0 };
	sConfig.Channel = ADC_CHANNEL_10;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
	uint16_t pot = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	return pot;
}

void dribble() {
	pot_val = analogRead_pa4();

	if (!f_dribble) {
		return;
	}

	if (HAL_GetTick() - prevmillis_d >= sampling) {
		error_d = dribble_sp - pot_val;
		(error_d >= 0) ?
				HAL_GPIO_WritePin(dirPort_d, dirPin_d, 1) :
				HAL_GPIO_WritePin(dirPort_d, dirPin_d, 0);

		if (abs(error_d) <= 20) {

			TIM10->CCR1 = 0;
			while_delay(250);
			switch (count) {
			case -1:
				dribble_sp = var;
				f_dribble = false;
				count = 0;
				break;
			case 0:

//				HAL_GPIO_WritePin(retractLower_Port, retractLower_Pin, 1);
				HAL_GPIO_WritePin(retractUpper_Port, retractUpper_Pin, 1);
				while_delay(100);
//				HAL_GPIO_WritePin(retractLower_Port, retractLower_Pin, 0);
				HAL_GPIO_WritePin(retractUpper_Port, retractUpper_Pin, 0);
				dribble_sp = madhe;
				pot_val = analogRead_pa4();
				error_d = dribble_sp - pot_val;
				count = 1;
				break;
			case 1:
				dribble_sp = khali;
				pot_val = analogRead_pa4();
				prev_error_pot = 0;
				error_d = dribble_sp - pot_val;
				count = 2;

				break;
			case 2:
				dribble_sp = var;
				flag_amkette = true;
				f_dribble = false;
				count = 0;
				HAL_GPIO_WritePin(retractLower_Port, retractLower_Pin, 1);
				HAL_GPIO_WritePin(retractUpper_Port, retractUpper_Pin, 1);
				HAL_GPIO_WritePin(pistonDown_Port, pistonDown_Pin, 1);
				while_delay(200);
				HAL_GPIO_WritePin(retractLower_Port, retractLower_Pin, 0);
				HAL_GPIO_WritePin(retractUpper_Port, retractUpper_Pin, 0);
				HAL_GPIO_WritePin(pistonDown_Port, pistonDown_Pin, 0);
				break;

			default:

				break;
			}

		} else {
			error_d = abs(error_d);
			if (error_d < 100) {
				integral_d += error_d;
			} else {
				integral_d = 0;
			}
			pwm_dribble = 12000 + (error_d * kp_d)
					+ kd_d * (error_d - prev_error_pot) + ki_d * integral_d; // + 0.014 * (error_d - prev_error_pot) + 0.001 * (integral);
			pwm_dribble = constrain(pwm_dribble, 0, 65535);
			TIM10->CCR1 = pwm_dribble;
//        analogWrite(pwmpin_d, pwm_dribble);
		}
		prevmillis_d = HAL_GetTick();
		prev_error_pot = error_d;
	}

}

void while_delay(int d) {
	unsigned long prevmillis1 = HAL_GetTick();
	while (HAL_GetTick() - prevmillis1 <= d) {
		// dribble();

		// locomotion();
		// locomote();
		// recievecmd();
		// encoders();
	}
}

#endif /* SRC_DRIBBLE_H_ */

