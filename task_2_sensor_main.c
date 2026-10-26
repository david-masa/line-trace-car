#include "Global.h"				///

#include "task_2_sensor_main.h"	///これを、実際の名称にする

int ReadSens(void);
int ReadDistance(int fd2)


int task_2_sensor_main(void)
{
	int i;		//初期化用
	int fd2;	
	int sensors = 0;
	/*bool*/ gbBtn_wht_state = 0;	//白ボタン（初期化後、発進ボタン）
    /*bool*/ gbBtn_red_state = 0;	//赤ボタン（緊急停止ボタン）
    	
    	
	switch (gsm_SysState)
	{
	case  SM_INIT:
			
		printf("DEBUG PRINT SysState == %d\n", gsm_SysState);
		///初期化処理完了後に、初期化完了フラグを立ててください。
		
		wiringPiSetupGpio();
	
	for(i = 0; i < 5; i++){
		pinMode(inGpio[i], INPUT);
	}
	
	for(i = 0; i < 5; i++){
		pullUpDnControl(inGpio[i], PUD_DOWN);
	}	
														
		break;
	
		
	case  SM_WAIT:

	do{
		gbBtn_wht_state = digitalRead(SW_WHITE);
	}while(gbBtn_wht_state == DBTN_OFF);
	
		break;


	case  SM_RUNNING:
			
		giDistSnsr_dist_value = ReadDistance(fd2);	//距離センサ（２進数）
		
		giLineSnsr_line_state = ReadSens();		//フォトセンサ
		
		break;


	case  SM_ONESTOP:
	
		giDistSnsr_dist_value = ReadDistance(fd2);	//距離センサ（２進数）
		
		giLineSnsr_line_state = ReadSens();		//フォトセンサ
		
		break;


	case  SM_EMER:
		printf("DEBUG PRINT  SysState == %d\n", gsm_SysState);
		///終了時処理完了後に、初期化完了フラグを落としてください。
		
		do{
		gbBtn_red_state = digitalRead(SW_RED);
		}while(	gbBtn_red_state == DBTN_OFF);
	
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
	disU8bit = wiringPiI2CReadReg8(fd2, GP2Y0E03_DIS_U);
	disL4bit = wiringPiI2CReadReg8(fd2, GP2Y0E03_DIS_L);
	dis12bit = (disU8bit << 4) | disL4bit;
	
	dis12bit = dis12bit >> 6;
	
	return dis12bit;
}
