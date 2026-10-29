#include <stdio.h>
#include <stdlib.h>
#include <string.h>				///文字列操作
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>		///I2C用(wiringPi)
///#include "../MyHeadder.h"	///
#include "../LIB/MyPi.h"		///Lib関連
#include "Global.h"				///


#include "task_2_sensor_main.h"	///これを、実際の名称にする

//ボタン
#define SW_RED		17
#define SW_WHITE	27

//フォトセンサ
#define SEN_RIGHT	4
#define SEN_CENTER	5
#define SEN_LEFT	6


const int inGpio[5] = {SW_RED, SW_WHITE, SEN_RIGHT, SEN_CENTER, SEN_LEFT};

int ReadSens(void);
int ReadDistance(int fd2);
int fd2 = 0;

int task_2_sensor_main(void)
{
	int i;		//初期化用
		
	/*bool*/ gbSys_Btn_wht_state = 0;	//白ボタン（初期化後、発進ボタン）
    /*bool*/ gbSys_Btn_red_state = 0;	//赤ボタン（緊急停止ボタン）
    	
    	
	switch (gsmSys_mode_state)
	{
	case  SM_INIT:
			
		printf("DEBUG PRINT SysState == %d\n", gsmSys_mode_state);
		///初期化処理完了後に、初期化完了フラグを立ててください。
		
		wiringPiSetupGpio();
	
	for(i = 0; i < 5; i++){
		pinMode(inGpio[i], INPUT);
	}
	
	for(i = 0; i < 5; i++){
		pullUpDnControl(inGpio[i], PUD_DOWN);
	}	
		
		fd2 = wiringPiI2CSetup(DST_S_ADR);
													
		break;
	
		
	case  SM_WAIT:

		gbSys_Btn_wht_state = digitalRead(SW_WHITE);
		
		gbSys_Btn_red_state = digitalRead(SW_RED);
		
	
		break;


	case  SM_RUNNING:
	
		gbSys_Btn_wht_state = digitalRead(SW_WHITE);
		
		gbSys_Btn_red_state = digitalRead(SW_RED);
			
		giSys_DistSnsr_dist_value = ReadDistance(fd2);	//距離センサ（２進数）
		
		giSys_LineSnsr_line_state = ReadSens();			//フォトセンサ
		
		
		break;


	case  SM_ONESTOP:
		
		giSys_DistSnsr_dist_value = ReadDistance(fd2);	//距離センサ（２進数）
		
		giSys_LineSnsr_line_state = ReadSens();		//フォトセンサ
		
		gbSys_Btn_red_state = digitalRead(SW_RED);
		
		break;


	case  SM_EMER:
		printf("DEBUG PRINT  SysState == %d\n", gsmSys_mode_state);
		///終了時処理完了後に、初期化完了フラグを落としてください。
		
			
		gbSys_Btn_red_state = digitalRead(SW_RED);
			
	
		break;


	default:;
		break;
	
	
	}
	
    return EXIT_SUCCESS;
    
}


int ReadSens(void){					//センサの２進数処理
	int i;
	int sensors = 0;
	
	i = digitalRead(SEN_RIGHT);
	if(i == 1){sensors = 1;}
	
	i = digitalRead(SEN_CENTER);
	if(i == 1){sensors += 2;}
	
	i = digitalRead(SEN_LEFT);
	if(i == 1){sensors += 4;}
	
	return sensors;
}	

int ReadDistance(int fd2){			//距離センサ（cm変換）
	int disU8bit, disL4bit, dis12bit;
	disU8bit = wiringPiI2CReadReg8(fd2, DST_S_RU1);
	disL4bit = wiringPiI2CReadReg8(fd2, DST_S_RL1);
	dis12bit = (disU8bit << 4) | disL4bit;
	
	dis12bit = dis12bit >> 6;
	printf("kyori [%d]\n", dis12bit);

	return dis12bit;
}
