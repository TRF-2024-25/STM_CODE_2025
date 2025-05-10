/*
 * Autolocomotion.h
 *
 *  Created on: May 9, 2025
 *      Author: RISHI
 */
#ifndef SRC_AUTOLOCOMOTION_H_
#define SRC_AUTOLOCOMOTION_H_

void autolocomote() {
	if (!autoloco) {
		return;
	}
	if(!isardistanceset){
		currentar = ARdistance;
		isardistanceset = true;
	}

	err_auto =  targetauto - (currentar - ARdistance);
	if(abs(err_auto)<0.5){
		autoloco=false;
		return;
	}
	vy = Kp_auto * (err_auto);
	vx=0;
	prev_dis_auto = err_dis;
	locomote();

}

#endif /* SRC_AUTOLOCOMOTION_H_ */
