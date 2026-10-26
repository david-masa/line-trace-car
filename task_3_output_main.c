/* task_3__main.c
 * LineTraceCar
 * 		by Team.A
 * custom:	gcc -Wall *.c -o app -lwiringPi -lpthread -g -O0 /home/pi/MyApp/LIB/libMyPi.a
 * org:		gcc -Wall -o "%e" "%f" -lwiringPi -lpthread -g -O0
 * Geanyのオプションの"%e"は実行ファイル名, "%f"はソースファイル名のこと
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>				///文字列操作
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>		///I2C用(wiringPi)
///#include "../MyHeadder.h"	///
#include "../LIB/MyPi.h"		///Lib関連
#include "Global.h"				///

#include "task_3_output_main.h"	///これを、実際の名称にする


#define SERVO 13

#define MOT_RIGHT2 22
#define MOT_RIGHT1 23
#define MOT_LEFT2 24
#define MOT_LEFT1 25

#define T 100

const int outGpio[4] = {MOT_RIGHT1, MOT_RIGHT2, MOT_LEFT1, MOT_LEFT2};

void Stop(void);
void Forward(void);
void RightForward(void);
void LeftForward(void);
void Reverse(void);
void TurnRight(void);
void TurnLeft(void);

int task_3_output_main(void)
{
    int i;
	int tOn = 0;
	int pwmRange = 200;
	
	printf("SysState = %d, Drive_inst = %d\n",
           gsm_SysState, giDrive_inst);

	switch (gsm_SysState)
	{
		case SM_INIT:
			printf("DEBUG PRINT SysState == %d\n", gsm_SysState);

			wiringPiSetupGpio();

			/* モータGPIO初期化 */
			for (i = 0; i < 4; i++) {
				pinMode(outGpio[i], OUTPUT);
			}

			/* モータPWM初期化 */
			for (i = 0; i < 4; i++) {
				softPwmCreate(outGpio[i], 0, T);
			}

			/* サーボ初期化 */
			pinMode(SERVO, OUTPUT);
			softPwmCreate(SERVO, tOn, pwmRange);
			
			softPwmWrite(SERVO, 8);
			delay(1000);
			softPwmWrite(SERVO, 24);
			delay(1000);
			softPwmWrite(SERVO, 15);
			delay(1000);

			/* TODO: 初期化完了フラグを設定 */
			break;

		case SM_WAIT:
			/* 待機中は停止 */
			Stop();
			break;

		case SM_RUNNING:
		printf("RUNNING: Drive_inst = %d\n", giDrive_inst);
			/* 駆動指示値に応じてモータ制御 */
			switch (giDrive_inst)
			{
			case 0:
				Stop();
				break;

			case 1:
				LittleForward();
				break;

			case 2:
				Forward();
				break;

			case 3:
				LittleRightForward();
				break;

			case 4:
				RightForward();
				break;

			case 5:
				LittleLeftForward();
				break;

			case 6:
				LeftForward();
				break;

			case 7:
				Reverse();
				break;

			case 8:
				Stop();
				break;

			default:
				/* 不正な駆動指示値は停止 */
				Stop();
				break;
			}
			break;

		case SM_ONESTOP:
			/* 通常停止 */
			Stop();
			break;

		case SM_EMER:
			printf("DEBUG PRINT SysState == %d\n", gsm_SysState);

			/* 緊急停止 */
			Stop();
			break;

		default:
			/* 不明な状態でも停止 */
			Stop();
			break;
	}
    return EXIT_SUCCESS; 
}

void Stop(void){

	softPwmWrite(MOT_RIGHT2, 100);
	softPwmWrite(MOT_RIGHT1, 100);
	softPwmWrite(MOT_LEFT2, 100);
	softPwmWrite(MOT_LEFT1, 100);

}

void LittleForward(void){

	softPwmWrite(MOT_RIGHT2, 0);
	softPwmWrite(MOT_RIGHT1, 30);
	softPwmWrite(MOT_LEFT2, 0);
	softPwmWrite(MOT_LEFT1, 30);

	softPwmWrite(SERVO,14);

}

void Forward(void){

	softPwmWrite(MOT_RIGHT2, 0);
	softPwmWrite(MOT_RIGHT1, 100);
	softPwmWrite(MOT_LEFT2, 0);
	softPwmWrite(MOT_LEFT1, 100);

	softPwmWrite(SERVO,14);

}

void RightForward(void){

	softPwmWrite(MOT_RIGHT2, 0);
	softPwmWrite(MOT_RIGHT1, 30);
	softPwmWrite(MOT_LEFT2, 0);
	softPwmWrite(MOT_LEFT1, 100);

	softPwmWrite(SERVO,10);

}

void LittleRightForward(void){

	softPwmWrite(MOT_RIGHT2, 0);
	softPwmWrite(MOT_RIGHT1, 60);
	softPwmWrite(MOT_LEFT2, 0);
	softPwmWrite(MOT_LEFT1, 100);

	softPwmWrite(SERVO,10);

}

void LeftForward(void){

	softPwmWrite(MOT_RIGHT2, 0);
	softPwmWrite(MOT_RIGHT1, 100);
	softPwmWrite(MOT_LEFT2, 0);
	softPwmWrite(MOT_LEFT1, 30);

	softPwmWrite(SERVO,18);

}

void LittleLeftForward(void){

	softPwmWrite(MOT_RIGHT2, 0);
	softPwmWrite(MOT_RIGHT1, 100);
	softPwmWrite(MOT_LEFT2, 0);
	softPwmWrite(MOT_LEFT1, 60);

	softPwmWrite(SERVO,18);

}

void Reverse(void){

	softPwmWrite(MOT_RIGHT2, 30);
	softPwmWrite(MOT_RIGHT1, 0);
	softPwmWrite(MOT_LEFT2, 30);
	softPwmWrite(MOT_LEFT1, 0);

	softPwmWrite(SERVO,14);

}

void TurnRight(void){

	softPwmWrite(MOT_RIGHT2, 0);
	softPwmWrite(MOT_RIGHT1, 100);
	softPwmWrite(MOT_LEFT2, 100);
	softPwmWrite(MOT_LEFT1, 0);

	softPwmWrite(SERVO,22);

}

void TurnLeft(void){

	softPwmWrite(MOT_RIGHT2, 100);
	softPwmWrite(MOT_RIGHT1, 0);
	softPwmWrite(MOT_LEFT2, 0);
	softPwmWrite(MOT_LEFT1, 100);

	softPwmWrite(SERVO,7);

}

