/*
 * communication.h
 *
 *  Created on: Apr 23, 2025
 *      Author: Harsh
 */

#ifndef SRC_COMMUNICATION_H_
#define SRC_COMMUNICATION_H_

#include "variables.h"
#include "cJSON.h"
int Rxvalueslo(char *Rx_data){
//	if(Rx_data!=NULL && Rx_data[1] =='{'){
		a++;
		loco = Rx_data[8];
		char Rotate[4];
		strncpy(Rotate, Rx_data +9, 3);
		rotationstrength = atoi(Rotate);
		char Angle[4];
		strncpy(Angle, Rx_data +12, 3);
		angle = atoi(Angle);
		angle = (angle == 400) ? 400 : (angle + 180) % 360;

		char Strength[4];
		strncpy(Strength, Rx_data +15, 3);
		strengthX = atoi(Strength);
		 if ((int32_t)HAL_GetTick() - strengthsampling > decleration_acceleration_sampling) {
			if (strengthX - strengthc >strength_effective_for_deceleration_acceleration_constant) {
				strengthX -= (strengthX - strengthc) * deceleration_constant;
			 } else if (strengthX - strengthc < -strength_effective_for_deceleration_acceleration_constant) {

				       if((int)(angle - Z_Val ) %360 > 140 && (int)(angle - Z_Val ) %360 < 220)

				       {
				    	   strengthX -= (strengthX - strengthc) * 0.97;
				       }
				       else
				       {

					   strengthX -= (strengthX - strengthc) *acceleration_constant;
		 	     }
			 }
		  	 strengthc = strengthX;
					strength = strengthX;
					   strengthsampling = HAL_GetTick();
					 }
					 strength  = constrain(strength,0,max_strength_set);


//	}
}

int Arvalueslo(char *Ar_data){
   if(Ar_data!= NULL){
	   strncpy(disString,Ar_data +6,7);
	   strncpy(angleString,Ar_data + 20,7);
	   sscanf(disString,"%f",&ARdistance);
	   sscanf(angleString,"%f",&alpha);
   }
}
int Mpuvalueslo(char *Mp_data){
	sscanf(Mp_data,"%d",&Z_Val);
//	Z_Val =0;
}

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
