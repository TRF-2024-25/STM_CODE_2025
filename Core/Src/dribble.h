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
	temp_pot = analogRead_pa4();

	if (!f_dribble) {
		return;
	}

	if (HAL_GetTick() - prevmillis_d >= 50) {
		error_d = dribble_sp - temp_pot;
		(error_d >= 0) ?
				HAL_GPIO_WritePin(dirPort_d, dirPin_d, 1) :
				HAL_GPIO_WritePin(dirPort_d, dirPin_d, 0);

		if (abs(error_d) <= 30) {

			TIM10->CCR1 = 0;
			dalay(500);
			switch (count) {
			case 0:

				HAL_GPIO_WritePin(retractLower_Port, retractLower_Pin, 1);
				HAL_GPIO_WritePin(retractUpper_Port, retractUpper_Pin, 1);
				dalay(1000);
				HAL_GPIO_WritePin(retractLower_Port, retractLower_Pin, 0);
				HAL_GPIO_WritePin(retractUpper_Port, retractUpper_Pin, 0);
				dribble_sp = madhe;
				temp_pot = analogRead_pa4();
				error_d = dribble_sp - temp_pot;
				count = 1;
				break;
			case 1:
				dribble_sp = khali;
				temp_pot = analogRead_pa4();
				prev_error_pot = 0;
				error_d = dribble_sp - temp_pot;
				count = 2;

				break;
			case 2:
				dribble_sp = var;
				flag_amkette = true;
				f_dribble = false;
				fOperation = 0;
				count = 0;
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

// void dribble() {

//   if (f_dribble == true) {
//     if (digitalRead(proxy) == 0 && fOperation == 1) {
//       fOperation = 2;
//     } else if (fOperation == 2 && digitalRead(proxy) == 1) {
//       digitalWrite(retractLower, 1);
//       digitalWrite(retractUpper, 1);
//       dalay(100);
//       digitalWrite(retractLower, 0);
//       digitalWrite(retractUpper, 0);
//       fOperation = 3;
//       f_dribble = false;
//       Serial.println("dribble22222222222222222");
//     }
//   } else if (fOperation == 3) {
//     f_power = true;
//     Serial.print(" -set vaR sp- ");
//     dribble_sp = var;
//     fOperation = 4;
//   }
// }

// void power() {
//   if (f_power == true) {
//     Serial.println(" FPOWER TRUE ");
//     Window();
//     if (sp_reached) {
//       Serial.print(" spf ");
//       Serial.print(dribble_sp);
//       if (count == 1) {
//         Serial.print(" madhe sp ");
//         dribble_sp = madhe;
//         dalay(500);
//         sp_reached = false;
//       }
//       if (count == 2) {
//         win_flag = 0;
//         while (digitalRead(A11) == 1) {
//           analogWrite(pwmpin_d, 140);
//         }
//         analogWrite(pwmpin_d, 0);
//         dribble_sp = khali;
//         f_power = false;
//         sp_reached = false;
//         fOperation = 0;
//         f_dribble = false;
//         count = 0;
//         win_flag = 1;
//         sp_reached = false;
//       }
//     }
//   }
// }
// void Window() {
//   if (win_flag) {
//     temp_pot = analogRead(pot);
//     error_pot = dribble_sp - temp_pot;
//     Serial.print(" err ");
//     Serial.println(abs(error_pot));
//     if (error_pot > 0) digitalWrite(dir_d, 1);
//     else digitalWrite(dir_d, 0);

//     if (abs(error_pot) < 30) {
//       Serial.println(" sp reached ");
//       sp_reached = true;
//       analogWrite(pwmpin_d, 0);
//       Serial.println("increment ctr");
//       count++;
//       if (count == 3) {
//         Serial.println(" reset all ");
//         f_power = false;
//         sp_reached = false;
//         fOperation = 0;
//         f_dribble = false;
//         count = 0;
//         return;
//       }
//       return;
//     } else {
//       // pwm_dribble = 30 + error_pot * 0.4 + 0.01 * (error_pot - prev_error_pot);
//       pwm_dribble = 170;
//       pwm_dribble = constrain(pwm_dribble, 0, 200);
//       analogWrite(pwmpin_d, pwm_dribble);
//       Serial.print(" pass pwm ");
//       Serial.println(pwm_dribble);
//     }
//     prev_error_pot = error_pot;
//   }
// }

void dalay(int d) {
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
