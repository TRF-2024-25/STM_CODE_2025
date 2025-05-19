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
double toradian(double x) {
  return x * pi / 180;
}


void locomotion() {
  if (!alignn) {
    alignn = align(alignvalue);
  }

  switch (loco) {

    case 'S':
      if (angle == defaultcontrollerangle) {
        angle = prevangle;
        calc();
        if (alignn) {
          w = 0;
        }
      } else {
    	prevangle = angle;
        calc();
      }
      if (angle != defaultcontrollerangle) {
        if (alignn) {
          w = 0;
        }
      }
      break;
    case 'L':

      w = (joystickwconstant * rotationstrength) / 100;
      if (angle == defaultcontrollerangle) {
        vx = 0;
        vy = 0;
        break;
      } else {
        calc();
        break;
      }
      break;
    case 'R':
      w = -(joystickwconstant * rotationstrength) / 100;
      if (angle == defaultcontrollerangle) {
        vx = 0;
        vy = 0;
        break;
      } else {
        calc();
        break;
      }
      break;

    case 'k':
      w = -kcasew ;
      calc();

      break;
    case 'K':
      w = kcasew ;

      calc();

      break;
    case 'o':
      w = ocasew;

      calc();

      break;
    case 'O':
      w = -ocasew;

      calc();

      break;

    default:
      if (alignn) {
        w = 0;
      }
      calc();
  }
  }
//}

void calc() {
  radiann = toradian(angle);
  vx = cos(radiann) * strength / 100 * multi;
  vy = sin(radiann) * strength / 100 * multi;
}
void locomote() {
  float matrix[3][3] = { { cos((0 + Z_Val) * pi / 180), sin((0 + Z_Val) * pi / 180), d },
                         { cos((120 + Z_Val) * pi / 180), sin((120 + Z_Val) * pi / 180), d },
                         { cos((240 + Z_Val) * pi / 180), sin((240 + Z_Val) * pi / 180), d } };
  base[0] = (matrix[0][0] * vx + matrix[0][1] * vy + w * matrix[0][2]) / r;
  base[1] = (matrix[1][0] * vx + matrix[1][1] * vy + w * matrix[1][2]) / r;
  base[2] = (matrix[2][0] * vx + matrix[2][1] * vy + w * matrix[2][2]) / r;

  if ((base[0] != 0) || (base[1] != 0) || base[2] != 0) {
    dir[0] = (base[0] < 0) ? 0 : 1;
    dir[1] = (base[1] < 0) ? 1 : 0;
    dir[2] = (base[2] < 0) ? 0 : 1;
  }
  setpoint1 = base[0] *  rpmtoradian;
  setpoint2 = base[1] *  rpmtoradian;
  setpoint3 = base[2] *  rpmtoradian;
  setpoint1 = (setpoint1 < 0)?(~setpoint1)+ 1: setpoint1;
  setpoint2= (setpoint2 < 0)?(~setpoint2)+ 1: setpoint2;
  setpoint3 =(setpoint3 < 0)?(~setpoint3)+ 1: setpoint3;
  basepwm[0] = base[0] * base1multiplier ;
  basepwm[1] = base[1] * base2multiplier ;
  basepwm[2] = base[2] * base3multiplier ;

  basepwm[0] = (basepwm[0]<0)?(~basepwm[0]) + 1:basepwm[0];
  basepwm[1] = (basepwm[1]<0)?(~basepwm[1]) + 1:basepwm[1];
  basepwm[2] = (basepwm[2]<0)?(~basepwm[2]) + 1:basepwm[2];


  error1 = ((setpoint1 - rpm1) /  rpmtoradian) * radiantopwm;
  error2 = ((setpoint2 - rpm2) /  rpmtoradian) * radiantopwm;
  error3 = ((setpoint3 - rpm3) /  rpmtoradian) * radiantopwm;


  if (HAL_GetTick() - previousmillis >= sampletime) {
    pwm1 = basepwm[0] + kp1 * (error1) + kd1 * (error1 - preverror1);


    pwm1 = constrain(pwm1, 0, upperlimitlocomotionconstant);
    pwm2 = basepwm[1] + kp2 * (error2) + kd2 * (error2 - preverror2);

    pwm2 = constrain(pwm2, 0, upperlimitlocomotionconstant);
    pwm3 = basepwm[2]+ kp3 * (error3) + kd3 * (error3 - preverror3);

    pwm3 = constrain(pwm3, 0, upperlimitlocomotionconstant);
    preverror1 = error1;
    preverror2 = error2;
    preverror3 = error3;
    previousmillis = HAL_GetTick();
  }

HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, dir[0]);
  TIM2->CCR3 = pwm1;

HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,dir[1]);
  TIM12->CCR2 = pwm2;


 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, dir[2]);
  TIM2->CCR4 = pwm3;

}




#endif /* SRC_LOCOMOTION_H_ */
