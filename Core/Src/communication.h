/*
 * communication.h
 *
 *  Created on: Apr 23, 2025
 *      Author: Harsh
 */

#ifndef SRC_COMMUNICATION_H_
#define SRC_COMMUNICATION_H_
#include "locomotion.h"
#include "variables.h"
#include "cJSON.h"
void Rxvalueslo(char *Rx_data){
  loco = Rx_data[8];
  char Rotate[4];
  strncpy(Rotate, Rx_data +9, 3);
  rotationstrength = atoi(Rotate);
  char Angle[4];
  strncpy(Angle, Rx_data +12, 3);

  //angle = (angle == 400) ? 400 : (angle + 180) % 360;
  char Strength[4];
  strncpy(Strength, Rx_data +15, 3);
  if ((int32_t)HAL_GetTick() - strengthsampling > decleration_acceleration_sampling) {
      angle = atoi(Angle);
        if(angle == 400){
            angle = prevangle;
        }
      strengthX = atoi(Strength);
      absstrengthdifferencebig(prevangle,angle,strengthX,strengthc);
      if(difference_big_for_acceleration){
	  calculatenextstrength(prevangle,&angle,&strengthX,strengthc);
      }

//      if (strengthX - strengthc >  strength_effective_for_deceleration_acceleration_constant) {
////  		strengthX -= (strengthX - strengthc) *acceleration_constant   ;
////		if((angle - Z_Val)%360 > 220 && (angle - Z_Val) < 320){
////			strengthX = strengthc + 1.5;
////		}
//	  strengthX  = strengthc + 2.5;
//	  if(prevangle != angle && angle != 400){
//	      angle = prevangle + (angle - prevangle)*0.04;
//	  }
//
//      } else if (strengthX - strengthc < - (strength_effective_for_deceleration_acceleration_constant)) {
//	  //  	strengthX -= (strengthX - strengthc)  *deceleration_constant;
////		if((angle - Z_Val)%360 > 220 && (angle - Z_Val) < 320){
////			strengthX = strengthc - 2.5;
////		}
//	  strengthX = strengthc - 3.5;
//	  if(prevangle != angle && angle != 400){
//	      angle = prevangle + (angle - prevangle)*0.04;
//	  }
//      }
      strengthc = strengthX;
      strength = strengthX;
      prevangle = angle;
      strengthsampling = HAL_GetTick();
  }
  strength  = constrain(strength,0,max_strength_set);
}

void calculatenextstrength(int prevangle, int *angle, int *strengthX, int strengthc){
  float strengthXx = *strengthX*cos(toradian(*angle));
  float strengthXy = *strengthX*sin(toradian(*angle));
  float strengthcx = strengthc*cos(toradian(prevangle));
  float strengthcy = strengthc*sin(toradian(prevangle));
  strengthXx = strengthcx + (strengthXx - strengthcx)*0.05;
  strengthXy = strengthcy + (strengthXy - strengthcy)*0.05;
  *strengthX = sqrt(strengthXx*strengthXx + strengthXy*strengthXy);
  *angle = toangle(atan2(strengthXy,strengthXx));
}

void absstrengthdifferencebig(int prevangle ,int angle,int strengthX,int strengthc){
    float strengthXx = strengthX*cos(toradian(angle));
    float strengthXy = strengthX*sin(toradian(angle));
    float strengthcx = strengthc*cos(toradian(prevangle));
    float strengthcy = strengthc*sin(toradian(prevangle));
    float distance = sqrt((strengthcx - strengthXx)*(strengthcx - strengthXx) + (strengthcy - strengthXy)*(strengthcy - strengthXy));
    if(distance>30){
	difference_big_for_acceleration = true;
    }
    else{
    difference_big_for_acceleration = false;
    }

}

void Arvalueslo(char *Ar_data){
   if(Ar_data!= NULL){
	   strncpy(disString,Ar_data +6,7);
	   strncpy(angleString,Ar_data + 20,7);
           strncpy(Mp_data,Ar_data +34,3);
	   sscanf(disString,"%f",&ARdistance);
	   sscanf(angleString,"%f",&alpha);
           sscanf(Mp_data,"%d",&Z_Val);
           if(Z_Val >= 358 && Z_Val <= 2){
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,0);
           }
           else{
               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,1);
           }
   }
}
//void Mpuvalueslo(char *Mp_data){
//	sscanf(Mp_data,"%d",&Z_Val);
//	if(Z_Val > 360){
//		Z_Val =0;
//		bnoallow = false;
//	}
//}

//int parsegargiar(char *Ar_data){
//	value *rootar = parse_json(Ar_data);
//
//}
//int parseJSAR(char *Ar_data) {
//	cJSON *rootar = cJSON_Parse(Ar_data);
//	if (!rootar) {
//		printf("Failed to parse JSON\n");
//		return -1;
//	}
//
//	cJSON *adistance = cJSON_GetObjectItem(rootar, "D");
//	cJSON *Arangle = cJSON_GetObjectItem(rootar, "A");
//	if (adistance != NULL&& cJSON_IsString(adistance)&&cJSON_IsString(Arangle)&&Arangle!=NULL) {
////		disString = adistance->valuestring;
////		angleString = Arangle->valuestring;
//		const char *Stringfordis = adistance->valuestring;
//		const char *Stringforangle = Arangle->valuestring;
//        strcpy(disString, Stringfordis);
//        strcpy(angleString, Stringforangle);
//        disString[7] = '\0';
//        angleString[7] = '\0';  // Null-terminate the string
////        printf("%s",angleString);
//        sscanf(Stringfordis,"%f",&ARdistance);
//        sscanf(Stringforangle,"%f",&alpha);
//
//
//
//	}
//	return 0;
//
//}
//int parseJS(char *Rx_data) {
//	if(Rx_data!=NULL){
//	cJSON *root = cJSON_Parse(Rx_data);
//	if (!root) {
//		printf("Failed to parse JSON\n");
//		a++;
////		return -1;
//	}
////	printf("")
//	cJSON *loc = cJSON_GetObjectItem(root, "LOC");
//	if (loc != NULL && cJSON_IsString(loc)) {
//		const char *zString = loc->valuestring;
//		loco = zString[0];
//
//		// Extract characters from index 1 to 3 (3 characters total)
//		char temp[4];  // +1 for null terminator
//		strncpy(temp, zString + 1, 3);
//		temp[3] = '\0';  // Null-terminate the string
//
//		// Convert to integer
//		rotationstrength = atoi(temp);
//		char temp2[4];
//		strncpy(temp2, zString + 4, 3);
//		temp2[3] = '\0';
//
//		angle = atoi(temp2);
//
//
//			angle = (angle == 400) ? 400 : (angle + 180) % 360;
//
//			// Serial.println(angle);
//			char temp3[4]; // For substring from index 4 to 6 (3 chars + null terminator)
//			strncpy(temp3, zString + 7, 3);
//			temp3[3] = '\0';  // Null-terminate
//
//			strengthX = atoi(temp3);
//			printf("%d",strengthX);
//			 if ((int32_t)HAL_GetTick() - strengthsampling > 30) {
//			 if (strengthX - strengthc >30) {
//			   strengthX -= (strengthX - strengthc) * 0.98;
//			 } else if (strengthX - strengthc < -30) {
//			   strengthX -= (strengthX - strengthc) * 0.85;
//			 }
//			 strengthc = strengthX;
//			strength = strengthX;
//			   strengthsampling = HAL_GetTick();
//			 }
//			 strength  = constrain(strength,0,85);
//	} else {
//		printf("Invalid or missing 'Z' field in JSON\n");
//	}
//	cJSON_Delete(root);
//	}
//	return 0;
//}

#endif /* SRC_COMMUNICATION_H_ */
