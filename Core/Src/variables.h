/*
 * variables.h
 *
 *  Created on: Apr 19, 2025
 *      Author: Harsh
 */

char Rx_data[20];
char Ar_data[29];
char Mp_data[3];
#ifndef SRC_VARIABLES_H_
#define SRC_VARIABLES_H_

#include "stdio.h"
#include <stdbool.h>
#include "string.h"

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
int multi = 2;
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
//const char*
char disString[8];
char angleString[8];
// float kp1 = 1.2;
// float kp2 = 1.2;
// float kp3 = 1.6;
// float kd1 = 0.1;
// float kd2 = 0.18;
// float kd3 = 0.1;

float kp1 = 0.3;
float kp2 = 0.3;
float kp3 = 0.4;
float kd1 = 0.04;
float kd2 = 0.09;
float kd3 = 0.05;
//float kp1 = 0.4;
//float kp2 = 0.8;
//float kp3 = 0.6;
//float kd1 = 0.04;
//float kd2 = 0.04;
//float kd3 = 0.1;
float bpbno1 = 0.45;
float kpbno2 = 0.8;
float kpbno3 = 0.4;
float kdbno1 = 0.01;
float kdbno2= 0.01;
float kdbno3 = 0.01;
float errorbno =0;
float previouserrorbno =0;
uint32_t prevviousmillisbno =0;

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
float kp_align = 0.0215;
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
float Z_Val = 0;
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

#define pistonDown_Port GPIOB
#define pistonDown_Pin GPIO_PIN_4

#define dirPort_d GPIOD
#define dirPin_d GPIO_PIN_0


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
float kdLower = 0.0;
float kdUpper = 0.0;
float kiLower = 0.0001;
float kiUpper = 0.0001;
bool flag_amkette=true;
int baseLower = 0;
int baseUpper = 0;
float ARdistance = 1;
int a =0;
bool Rotors_flag = 0;
bool isthreepointer = true;

//Autolocomote
float target_auto = 7;
float err_auto=0;
float Kp_auto=0.1;
float Kd_auto=0;
float Ki_auto=0;
float prev_dis_auto=0;


// DRIBBLING



// int max_d = 100;
// int min_d = 0;
// //// ---------r2-------////
// long integral = 0;
// unsigned long prevmillis_d = 0;
// int dPistonPin = 0;
// bool win_flag = 1;
// // Pin Definitions
// #define pot A11
// #define LS A12
// #define proxy A14
// #define extendUpper 29
// #define retractUpper 31
// #define extendLower 25
// #define retractLower 27
// #define dir_d 32
// #define pwmpin_d 10
// bool firstrun = false;
// long p =0;
// // Control flags
// int pwm_dribble=0;
 int  fOperation = 0;
// String Loco,Com,str;
// // control variables
// float kp_d = 0;
// float kd_d = 0.00;
// int derivative_d = 0;
// int basepwm_d = 170;
// int pwm_d = 0;
//
// int setpoint_d = 0;
// int potval = 0;
// float output_d = 0;
// float aberror_d = 0;
// long error_d = 0;
// int prevErr_d = 0;
// unsigned long controlmillis1 = 0;
// unsigned long controlmillis2 = 0;
// int controlInter = 10;
// // Timing Variables
 bool f_dribble = false;
 int temp_pot = 0;
// int error_pot = 0;
// Character Input
// char x = 'S';


//picking
//functions
void pickup();

void dalay(int);

int interval_d = 50;

#define var 1450
#define madhe 1777
#define khali 3600
int integral_d = 0;
long integral = 0;
unsigned long prevmillis_d = 0;

// Pin Definitions
int check=0;

// flags
bool f_pickup = true;
int f_op = 0;
int count = 0;
int potval = 0;
int dribble_sp = var;
int pwm_dribble = 0;
float kp_d = 70;
float kd_d = 15;
float ki_d = 10;
int basepwm_d = 50;
float output_d = 0;
float aberror_d = 0;
int error_d = 0;
int prevErr_d = 0;
//picking end
float radiann = 0;

#endif /* SRC_VARIABLES_H_ */
