/*
 * locomotion.h
 *
 *  Created on: Apr 23, 2025
 *      Author: Harsh
 */

#ifndef SRC_LOCOMOTION_H_
#define SRC_LOCOMOTION_H_
#include "variables.h"
#include "alignment.h"
void calc();
void locomote();
double toradian(double x) {
  return x * pi / 180;
}


void locomotion() {
  // alignn = false;
  if (!alignn) {
    alignn = align(alignvalue);
  }
  if(!autoloco){


  // Serial.print(s);
  // Serial.print("  ");
  // Serial.print(alpha);
  // Serial.print("  ");
  // Serial.println(Z_Val);
  switch (loco) {

    case 'S':
      if (angle == 400) {
        angle = prevangle;
        calc();
        if (alignn) {
          w = 0;
        }
      } else {
    	prevangle = angle;
        calc();
      }
      if (angle != 400) {
        if (alignn) {
          w = 0;
        }
      }
      break;
    case 'L':
      w = (1.2 * rotationstrength) / 100;
      if (angle == 400) {
        vx = 0;
        vy = 0;
        break;
      } else {
        calc();
        break;
      }
      break;
    case 'R':
      w = -(1.2 * rotationstrength) / 100;
      if (angle == 400) {
        vx = 0;
        vy = 0;
        break;
      } else {
        calc();
        break;
      }
      break;
      // case 'f':
      // angle = 270;
      // strength = (rotationstrength>)

    case 'k':
      w = -1.1;
      calc();

      break;
    case 'K':
      w = 1.1;

      calc();

      break;
    case 'o':
      w = 0.9;

      calc();

      break;
    case 'O':
      w = -0.9;

      calc();

      break;

    default:
      if (alignn) {
        w = 0;
      }
      calc();
  }
  }
}

void calc() {
  // Serial.println("Strength: " + String(strength));
  radiann = toradian(angle);
  vx = cos(radiann) * strength / 100 * multi;
  vy = sin(radiann) * strength / 100 * multi;
}
void locomote() {
//  w = -w;
  float matrix[3][3] = { { cos((0 + Z_Val) * pi / 180), sin((0 + Z_Val) * pi / 180), d },
                         { cos((120 + Z_Val) * pi / 180), sin((120 + Z_Val) * pi / 180), d },
                         { cos((240 + Z_Val) * pi / 180), sin((240 + Z_Val) * pi / 180), d } };
  base[0] = (matrix[0][0] * vx + matrix[0][1] * vy + w * matrix[0][2]) / r;
  base[1] = (matrix[1][0] * vx + matrix[1][1] * vy + w * matrix[1][2]) / r;
  base[2] = (matrix[2][0] * vx + matrix[2][1] * vy + w * matrix[2][2]) / r;

  if ((base[0] != 0) || (base[1] != 0) || base[2] != 0) {
    dir[0] = (base[0] < 0) ? 0 : 1;
    dir[1] = (base[1] < 0) ? 1 : 0;
    dir[2] = (base[2] < 0) ? 1 : 0;
  }
//  setpoint1 = absolute((int)base[0] * 9.549);
//  setpoint2 = absolute((int)base[1] * 9.549);
//  setpoint3 = absolute((int)base[2] * 9.549);
  setpoint1 = base[0] * 9.549;
  setpoint2 = base[1] * 9.549;
  setpoint3 = base[2] * 9.549;
  setpoint1 = (setpoint1 < 0)?(~setpoint1)+ 1: setpoint1;
  setpoint2= (setpoint2 < 0)?(~setpoint2)+ 1: setpoint2;
  setpoint3 =(setpoint3 < 0)?(~setpoint3)+ 1: setpoint3;
  basepwm[0] = base[0] * 980;
  basepwm[1] = base[1] * 960;
  basepwm[2] = base[2] * 990;

  basepwm[0] = (basepwm[0]<0)?(~basepwm[0]) + 1:basepwm[0];
  basepwm[1] = (basepwm[1]<0)?(~basepwm[1]) + 1:basepwm[1];
  basepwm[2] = (basepwm[2]<0)?(~basepwm[2]) + 1:basepwm[2];

  // previous 4.28  high 4.36
  error1 = ((setpoint1 - rpm1) / 9.549) * 1075.2;
  error2 = ((setpoint2 - rpm2) / 9.549) * 1075.2;
  error3 = ((setpoint3 - rpm3) / 9.549) * 1075.2;


  if (HAL_GetTick() - previousmillis >= sampletime) {
    pwm1 = basepwm[0] + kp1 * (error1) + kd1 * (error1 - preverror1);

    // if (pwm1 > 0) {
    //   dirchanged1_flag = false;
    // }
    // if (pwm1 < 0) {
    //   pwm1 = -pwm1;
    //   pwm1 = (pwm1 < 15) ? ((pwm1 > 10) ? pwm1 : 0) : 15;
    //   if (!dirchanged1_flag) {
    //     dir[0] = (dir[0] == 0) ? 1 : 0;
    //     dirchanged1_flag = true;
    //   }
    // }

    pwm1 = constrain(pwm1, 0, 40000);
    // prevPwm1 = currPwm1;
    pwm2 = basepwm[1] + kp2 * (error2) + kd2 * (error2 - preverror2);

    // if (pwm2 > 0) {
    //   dirchanged2_flag = false;
    // }
    // if (pwm2 < 0) {
    //   pwm2 = -pwm2;
    //   pwm2 = (pwm2 < 15) ? ((pwm2 > 10) ? pwm2 : 0) : 15;
    //   if (!dirchanged2_flag) {
    //     dir[1] = (dir[1] == 0) ? 1 : 0;
    //     dirchanged2_flag = true;
    //   }
    // }

    pwm2 = constrain(pwm2, 0, 40000);
    // prevPwm2 = currPwm2;
    pwm3 = basepwm[2]+ kp3 * (error3) + kd3 * (error3 - preverror3);
    // if (pwm3 > 0) {
    //   dirchanged3_flag = false;
    // }
    // if (pwm3 < 0) {
    //   pwm3 = -pwm3;
    //   pwm3 = (pwm3 < 15) ? ((pwm3 > 10) ? pwm3 : 0) : 15;
    //   if (!dirchanged3_flag) {
    //     dir[2] = (dir[2] == 0) ? 1 : 0;
    //     dirchanged3_flag = true;
    //   }
    // }
    pwm3 = constrain(pwm3, 0, 40000);
    // prevPwm3 = currPwm3;
    preverror1 = error1;
    preverror2 = error2;
    preverror3 = error3;
    previousmillis = HAL_GetTick();
  }

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, dir[0]);
    TIM2->CCR3=pwm1;
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, dir[1]);
  TIM2->CCR4=pwm2;
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, dir[2]);
   TIM2->CCR2=pwm3;




}




#endif /* SRC_LOCOMOTION_H_ */
