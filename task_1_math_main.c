#include <stdio.h>
#include <stdlib.h>
#include <string.h>				///文字列操作
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>		///I2C用(wiringPi)
///#include "../MyHeadder.h"	///
#include "../LIB/MyPi.h"		///Lib関連
#include "Global.h"				///


#include "task_1_math_main.h"	///これを、実際の名称にする

static int positionNow = 0;
static int positionOld = 0;
static unsigned int turnTime = 0;
static int turn = 0;



//ボタン
#define SW_RED		17
#define SW_WHITE	27

//フォトセンサ
#define SEN_RIGHT	4
#define SEN_CENTER	5
#define SEN_LEFT	6

int task_1_math_main(void)
{
		
	/*bool*/ gbSys_Btn_wht_state = 0;	//白ボタン（初期化後、発進ボタン）
    /*bool*/ gbSys_Btn_red_state = 0;	//赤ボタン（緊急停止ボタン）
    	
    	
	switch (gsmSys_mode_state)
	{
	case  SM_INIT:
			
		printf("DEBUG PRINT SysState == %d\n", gsmSys_mode_state);
		///初期化処理完了後に、初期化完了フラグを立ててください。
													
		break;
	
		
	case  SM_WAIT:
	
		gbSys_Btn_wht_state = digitalRead(SW_WHITE);

		if(gbSys_Btn_wht_state == 1){
			gsmSys_mode_state = SM_RUNNING;
			printf("RUNNINGに遷移しました。");
		}
		
		break;


	case  SM_RUNNING:

		if(giSys_DistSnsr_dist_value <= 35){
			gsmSys_mode_state = SM_ONESTOP;
		}

		positionNow = giSys_LineSnsr_line_state;

		if(turn == 0){
			if((positionOld == 0b010) && (positionNow == 0b100 || positionNow == 0b110)){
				turn = 1;
				turnTime = millis();
			}
			else if((positionOld == 0b010) && (positionNow == 0b001 || positionNow == 0b011)){
				turn = 2;
				turnTime = millis();
			}
		}
		
		if(turn == 1){
			giSys_Motor_drive_inst = 9;
			if((millis() - turnTime) >= 135){
				turn = 0;
				giSys_Motor_drive_inst = 0;
			}
			
		}
		else if(turn == 2){
			giSys_Motor_drive_inst = 10;
			if((millis() - turnTime) >= 135){
				turn = 0;
				giSys_Motor_drive_inst = 0;
			}
			
		}
		else{
			switch(positionNow){					
				case 0b000:
				case 0b101:
				giSys_Motor_drive_inst = 2;
				break;
				
				case 0b010:
				giSys_Motor_drive_inst = 7;
				break;

				case 0b100:
				giSys_Motor_drive_inst = 5;
				break;
				
				case 0b110:
				giSys_Motor_drive_inst = 6;
				break;

				case 0b001:
				giSys_Motor_drive_inst = 3;
				break;
				
				case 0b011:
				giSys_Motor_drive_inst = 4;
				break;

				default:
				giSys_Motor_drive_inst = 0;
				break;
			}
		}
		positionOld = positionNow;
		
		
		break;


	case  SM_ONESTOP:
		
		if(giSys_DistSnsr_dist_value > 35){
			gsmSys_mode_state = SM_RUNNING;
		}

		break;


	case  SM_EMER:
		printf("DEBUG PRINT  SysState == %d\n", gsmSys_mode_state);
		///終了時処理完了後に、初期化完了フラグを落としてください。
		
			
	
		break;


	default:;
		break;
	
	
	}
	
    return EXIT_SUCCESS;
    
}
