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
    if (delta > -nextanglesetpointalignmentconstant + initialdelta*alignmentinitialdeltamultiplier && delta < nextanglesetpointalignmentconstant) {
      donealign = true;
    }
  } else {
    if (delta > -nextanglesetpointalignmentconstant && delta < nextanglesetpointalignmentconstant + initialdelta*alignmentinitialdeltamultiplier) {
      donealign = true;
    }
  }
  if (donealign) {
	if(delta < alignmentsetpoint && delta >-alignmentsetpoint){
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
  if (HAL_GetTick() - previousalignsampling > alignmentsamplingtime) {

    if (s< PID_IN_ALIGNMENT_RANGE && s > -PID_IN_ALIGNMENT_RANGE) {
      if (s < active_ki_for_alignment_range && s > -active_ki_for_alignment_range) {
        integralalign += s;
        if (integralalign > maxalignmentintegralconstant) {
          integralalign = maxalignmentintegralconstant;
        }
      }
      else{
         integralalign = 0;
      }
      errordiff_align = s - previousS;
      if (s < 0) {
        w_align = kp_align * s + kd_align * errordiff_align + ki_align * integralalign - alignment_base_w;
      } else {
        w_align = kp_align * s + kd_align * errordiff_align + ki_align * integralalign + alignment_base_w;
      }

      w_align = constrain_float(w_align, -w_limit_for_alignment, w_limit_for_alignment);
      w = w_align;
    } else {
      w = (s < 0) ? -w_limit_for_alignment : w_limit_for_alignment;
    }
    w = -w;
    previousalignsampling = HAL_GetTick();
    previousS = s;
  }

  return false;
}

#endif /* SRC_ALIGNMENT_H_ */
