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
	  fromlocomotion = false;
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
    	if(angle <=360){
    	prevangle = angle ;}
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

    case 'K':
      w = kcasew ;
      calc();

      break;
    case 'k':
      w = -kcasew ;

      calc();

      break;
//    case 'o':
//      w = ocasew;
//
//      calc();
//
//      break;
//    case 'O':
//      w = -ocasew;
//
//      calc();
//
//      break;

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

 if (HAL_GetTick() - previousmillis >= sampletime) {
      rpm_cal();
	  if(w!=0 || !bnoallow || !alignn){
		  bnosetpoint = Z_Val;
		  bnoerror =0;
		  fromlocomotion = false;
		  prevw = w;
	  }
	  else if(prevw < 0.1 && prevw > -0.1){
		  prevw =0;
		  if(Rotors_flag == 0){
		 fromlocomotion = true;
		 align(bnosetpoint);}
		  else{
			  fromlocomotion = false;
		  }
	  }
	  else{
		  if(bnoallow){
		  bnosetpoint = Z_Val;
		  prevw = prevw*0.8;
		  w = prevw;}
		  else{
			  bnosetpoint = Z_Val;
		  }
	  }
  float matrix[3][3] = { { cos((0 + Z_Val) * pi / 180), sin((0 + Z_Val) * pi / 180), d },
                         { cos((120 + Z_Val) * pi / 180), sin((120 + Z_Val) * pi / 180), d },
                         { cos((240 + Z_Val) * pi / 180), sin((240 + Z_Val) * pi / 180), d } };
  base[0] = (matrix[0][0] * vx + matrix[0][1] * vy + w * matrix[0][2]) / r;
  base[1] = (matrix[1][0] * vx + matrix[1][1] * vy + w * matrix[1][2]) / r;
  base[2] = (matrix[2][0] * vx + matrix[2][1] * vy + w * matrix[2][2]) / r;
//  bnoerror = (bnosetpoint - Z_Val) <180 ? (bnosetpoint - Z_Val) > -180 ? (bnosetpoint - Z_Val):(bnosetpoint - Z_Val + 360): (bnosetpoint - Z_Val - 360);


//  if(bnoerror <= 4 && bnoerror >= -4){
//	  bnoerror =0;
//  }
//  bno1pid = basepwm[0] + kp1 * (error1) + kd1 * (error1 - preverror1) - (kpbno1 * (bnoerror) + kdbno1*(bnoerror -previousbnoerror)) ;
//  bno2pid = basepwm[1] + kp2 * (error2) + kd2 * (error2 - preverror1) - (kpbno2 * (bnoerror) + kdbno2*(bnoerror -previousbnoerror));
//  bno3pid = basepwm[2] + kp3 * (error3) + kd3 * (error3 - preverror1) - (kpbno3 * (bnoerror) + kdbno3*(bnoerror -previousbnoerror));
    dir[0] = base[0] < 0 ?  0: 1;
    dir[1] = base[1] <0  ? 1: 0;
    dir[2] =  base[2 ]<0 ? 1: 0;

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

    pwm1 = basepwm[0] + kp1 * (error1) + kd1 * (error1 - preverror1); //- (kpbno1 * (bnoerror) + kdbno1*(bnoerror -previousbnoerror))  ;

    pwm1 = constrain(pwm1, 0, upperlimitlocomotionconstant);
    pwm2 = basepwm[1] + kp2 * (error2) + kd2 * (error2 - preverror2); //- (kpbno1 * (bnoerror) + kdbno1*(bnoerror -previousbnoerror));

    pwm2 = constrain(pwm2, 0, upperlimitlocomotionconstant);
    pwm3 = basepwm[2]+ kp3 * (error3) + kd3 * (error3 - preverror3);// - (kpbno1 * (bnoerror) + kdbno1*(bnoerror -previousbnoerror)) ;

    pwm3 = constrain(pwm3, 0, upperlimitlocomotionconstant);
    preverror1 = error1;
    preverror2 = error2;
    preverror3 = error3;
//    previousbnoerror = bnoerror;
    previousmillis = HAL_GetTick();
  }

// R1 LOCOMOTION
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, dir[1]);
  TIM2->CCR4 = pwm2;

HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,dir[0]);
  TIM2->CCR3 = pwm1;


 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, dir[2]);
  TIM2->CCR1 = pwm3;

}




#endif /* SRC_LOCOMOTION_H_ */
