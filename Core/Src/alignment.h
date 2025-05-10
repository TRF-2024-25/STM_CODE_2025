/*
 * alignment.h
 *
 *  Created on: May 2, 2025
 *      Author: Harsh
 */
/*
 * alignment.h
 *
 *  Created on: May 1, 2025
 *      Author: HP
 */

#ifndef SRC_ALIGNMENT_H_
#define SRC_ALIGNMENT_H_

bool align(float target) {

  float delta = target - Z_Val;
  if (delta > 180) {
    delta = delta - 360;
  }
  if (delta < -180) {
    delta = delta + 360;
  }
  if (initialdelta == 0) {
    initialdelta = delta;
  }


  s = delta;
  if (initialdelta < 0) {
    if (delta > -1.6 + initialdelta*0.05 && delta < 1.6) {
      donealign = true;
    }
  } else {
    if (delta > -1.6 && delta < 1.6 + initialdelta*0.05) {
      donealign = true;
    }
  }
  // if (abs(delta) < 1) {
  if (donealign) {
	if(delta < 2 && delta >-2){
    w = 0;
    alignn = true;
    integralalign = 0;
    donealign = false;
    initialdelta = 0;
    return true;}
	else{
		initialdelta =0;
		return false;
	}
  }
  if (HAL_GetTick() - previousalignsampling > 20) {

    if (s< 120.0 && s > -120.0) {
      if (s < 10.0 && s > -10.0) {
        integralalign += s;
        if (integralalign > 100) {
          integralalign = 100.0;
        }
      }
      else{
         integralalign = 0;
      }

      // w = (s < 0) ? s * 0.02 + (s - previousS) * 0.089 + 0.0000018*integralalign  : (s * 0.02  + (s - previousS) * 0.089 + 0.0000018*integralalign );
      errordiff_align = s - previousS;
      if (s < 0) {
        w_align = kp_align * s + kd_align * errordiff_align + ki_align * integralalign - 0.2;
      } else {
        w_align = kp_align * s + kd_align * errordiff_align + ki_align * integralalign + 0.2;
      }

      w_align = constrain_float(w_align, -2, 2);
      w = w_align;
    } else {
      w = (s < 0) ? -2 : 2;
    }
    w = -w;
    previousalignsampling = HAL_GetTick();
    previousS = s;
  }
  // Serial.print("::");
  // Serial.print(w);
//   digitalWrite(A14,0);
  return false;
}

#endif /* SRC_ALIGNMENT_H_ */
