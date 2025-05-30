/*
 * variables.h
 *
 *  Created on: Apr 19, 2025
 *      Author: Harsh
 */


#ifndef SRC_VARIABLES_H_
#define SRC_VARIABLES_H_

#include "stdio.h"
#include <stdbool.h>
#include "string.h"
char sendbuffer[10];
char Rx_data[20];
char Ar_data[39];
char Mp_data[3];
char rx_data[20]={'{','"','L','O','C','"',':','"','S','0','0','0','4','0','0','0','0','0','"','}'};
char rpm1s[4];
char rpm2s[4];
char rpm3s[4];
bool f_h = true;
bool f_H = true;
// Loco = "S000090100";
bool autoloco=false;
bool isardistanceset=false;
unsigned char inp = 'S';
void dalay(int d);
void recievecmd();
void encoders();
void pickup();
void powerWindow();

// bool sp_reached = false;
// bool f_power = false;
// int count = 0;
// int dribble_sp = 0;
 int prev_error_pot = 0;
// int delta =0;
unsigned long preev_ = 0;
int currPwm1 = 0;
int currPwm2 = 0;
int currPwm3 = 0;
int previousbnobeforealignment = 0;
bool previousbnobeforealignmentset = false;
int prevPwm1 = 0;
int prevPwm2 = 0;
int prevPwm3 = 0;
int adder = 2;
float alpha = 0;
//int pwm_motor[3] = { 11, 12, 44 };
//int dir_motor[3] = { 34, 36, 38 };  // 26 32 28
int pwm_motor[3] = { 11, 44, 12 };
int dir_motor[3] = { 34, 38, 36 };  // 26 32 28
int dir[3];
int basepwm[3];
int base[3];
int multi = 3.2;
bool fromlocomotion = false;
bool ballpickup = false;
float x;
float y;
float y_val;
float r = 0.076;
float err_dis =0;
float currentar=0;
float targetauto=7;
bool dirchanged1_flag = false;
bool dirchanged2_flag = false;
bool dirchanged3_flag = false;
bool isauto = false;
bool difference_big_for_acceleration = false;
//const char*
char disString[8];
char angleString[8];
//kartik
float kp1 = 0.5;//0.14
float kp2 = 0.65;// 0.31
float kp3 = 0.45;//0.4

float kd1 = 0.04;//0.0
float kd2 = 0.05;// 0.024
float kd3 = 0.03;// 0.02
bool bnoallow = 1;
//float kp1 = 0.5;//0.4;
//float kp2 = 0.45;//0.756;
//float kp3 = 0.45;//0.3;
//float kd1 = 0.04;//0.04;
//float kd2 = 0.04;//0.09;
//float kd3 = 0.055;//0.05;
// float kp1 = 1.2;
// float kp2 = 1.2;
// float kp3 = 1.6;
// float kd1 = 0.1;
// float kd2 = 0.18;
// float kd3 = 0.1;

//float kp1 = 0.5;//0.4;
//float kp2 = 0.7566;//0.756;
//float kp3 = 0.30;//0.3;
//float kd1 = 0;//0.04;
//float kd2 = 0;//0.09;
//float kd3 = 0.08;//0.05;
//float kp1 = 0.4;
//float kp2 = 0.8;
//float kp3 = 0.6;
//float kd1 = 0.04;
//float kd2 = 0.04;
//float kd3 = 0.1;
float kpbno1 = 120;
float kpbno2 = 120;
float kpbno3 = 120;
float kdbno1 = 8;
float kdbno2= 8;
float kdbno3 = 8;
float bnoerror =0;
int bno1pid =0;
int bno2pid =0;
int bno3pid =0;
float previousbnoerror =0;
int bnosetpoint =0;
uint32_t prevviousmillisbno =0;
float radiantopwm = 1075.2;
float rpmtoradian = 9.549;
float base1multiplier  = 1000;
float base2multiplier =   1030;
float base3multiplier = 960;
//float base1multiplier  = 1000;
//float base2multiplier =   990;
//float base3multiplier = 1100;
float joystickwconstant = 1.2;
int defaultcontrollerangle = 400;
float kcasew = 0.9;
float ocasew = 0.7;
int upperlimitlocomotionconstant = 65000;
float nextanglesetpointalignmentconstant = 1.6;
float alignmentinitialdeltamultiplier = 0.05;
float alignmentsetpoint =2;
int alignmentsamplingtime =20;
float active_ki_for_alignment_range = 10;
float PID_IN_ALIGNMENT_RANGE = 120;
int maxalignmentintegralconstant = 100;
float alignment_base_w = 0.2;
float w_limit_for_alignment = 2.0;
int strength_effective_for_deceleration_acceleration_constant = 30;
int decleration_acceleration_sampling = 50;
float acceleration_constant = 0.9;
float deceleration_constant = 0.95;
int max_strength_set = 100;
float prevw =0;



bool Dribble_Ext = false;

bool alignn = true;
float alignvalue=0;
int sampletime = 50;
bool nexts=0;
float initialdelta =0;
float s=0;
bool donealign =false;
float integralalign = 0;
float w_align = 0;
float kp_align = 0.0225;
float kd_align = 0.0180;
float ki_align = 0.0020;
long previousalignsampling = 0;
float previousS = 0;

float errordiff_align=0;

volatile long long previousmillis = 0;
volatile long long previousmilliss = 0;
char val[] = "";
//int rpm1 = 0;
//int rpm2 = 0;
//int rpm3 = 0;
int Z_Val = 0;
int rotationstrength = 0;
int strength = 0;
int strengthc = 0;
int strengthX = 0;
long strengthsampling = 0;
int angle = 0;
int anglec = 0;
int prevangle = 0;
double vx = 0;
double vy = 0;
double xtarget = 0;
double ytarget = 7;
double distance = 0;
double maxdistance = 0;
float d = 0.4;
float w = 0;
double pi = 3.1415;
char enco[] = "";
int16_t setpoint1 = 0;
int16_t setpoint2 = 0;
int16_t setpoint3 = 0;
int pwm1 = 0;
int pwm2 = 0;
int pwm3 = 0;
char loco = 'S', com = 'S';
char lococ;
float error1 = 0;
float error2 = 0;
float error3 = 0;
float preverror1 = 0;
float preverror2 = 0;
float preverror3 = 0;

//DynamicJsonDocument doc(512);
//DynamicJsonDocument docenc(512);
//DynamicJsonDocument doc_AR(512);
//DeserializationError err;
//DeserializationError erre;
//DeserializationError Ar_err;
//String Ardata = "";

// DRIBBLING


#define retractUpper_Port GPIOC
#define retractUpper_Pin GPIO_PIN_8

#define extendLower_Port GPIOD
#define extendLower_Pin GPIO_PIN_3

#define extendUpper_Port GPIOA
#define extendUpper_Pin GPIO_PIN_8

#define retractLower_Port GPIOD
#define retractLower_Pin GPIO_PIN_1

#define pistonUp_Port GPIOD
#define pistonUp_Pin GPIO_PIN_7

#define pistonDown_Port GPIOA
#define pistonDown_Pin GPIO_PIN_10

#define dirPort_d GPIOB
#define dirPin_d GPIO_PIN_7


volatile int rpm1 = 0;
volatile int rpm2 = 0;
volatile int rpm3 = 0;


int prev = 0;
int prev_loco = 0;




// ROTORS VARIABLES
#define user_led_1 A11
#define encoderLower 2
#define encoderUpper 3
#define DirMLower 26
#define DirMUpper 28
#define PwmMLower 8
#define PwmMUpper 7
int shootcount =0;
int sampling = 80;
volatile int Rpm_set_lower = 0;
volatile int Rpm_set_upper = 0;
int errLower = 0, preverrLower = 0, errUpper = 0, preverrUpper = 0;
volatile unsigned long count1, count2, shootmillis = 0, shootmillis2 = 0;
unsigned long prevtime = 0;
unsigned long prevtime_ = 0;
int Rpmlower = 0, Rpmupper = 0, PwmLower = 0, PwmUpper = 0, errordiffLower = 0, errordiffUpper = 0;
float kpLower = 11;
float kpUpper = 24;
//float kdLower = 0.0;
//float kdUpper = 0.0;
//float kiLower = 0.0001;
//float kiUpper = 0.0001;
bool flag_amkette=true;
int baseLower = 0;
int baseUpper = 0;
float ARdistance = 1;
int a =0;
bool Rotors_flag = 0;
bool isthreepointer = true;
int RotorsSampling=80;
int sixtythousand = 60000;
int ppr=360;
int Sixhunppr = 600;
//Autolocomote
float target_auto = 7;
float err_auto=0;
float Kp_auto=0.1;
float Kd_auto=0;
float Ki_auto=0;
float prev_dis_auto=0;


// DRIBBLING

 bool f_dribble = true;
 int pot_val = 0;


void while_delay(int);


#define var 1180
#define madhe 1300
#define khali 2950
int integral_d = 0;
unsigned long timeout_d = 0;
unsigned long prevmillis_d = 0;
int check=0;
int count = -1;
int potval = 0;
int dribble_sp = khali;
int pwm_dribble = 0;
float kp_d = 50;
float kd_d = 15;
float ki_d = 10;
int basepwm_d = 50;
float output_d = 0;
float aberror_d = 0;
int error_d = 0;
int prevErr_d = 0;
float radiann = 0;

#endif /* SRC_VARIABLES_H_ */
