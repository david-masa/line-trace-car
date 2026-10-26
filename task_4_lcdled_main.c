/* task_4__main.c
 * LineTraceCar
 * 		by Team.A
 * custom:	gcc -Wall *.c -o app -lwiringPi -lpthread -g -O0 /home/pi/MyApp/LIB/libMyPi.a
 * org:		gcc -Wall -o "%e" "%f" -lwiringPi -lpthread -g -O0
 * Geanyのオプションの"%e"は実行ファイル名, "%f"はソースファイル名のこと
*/
/* task_1_modulename_lcd.c
 * LineTraceCar
 * 		by Team.A
 * custom:	gcc -Wall *.c -o app -lwiringPi -lpthread -g -O0 /home/pi/MyApp/LIB/libMyPi.a
 * org:		gcc -Wall -o "%e" "%f" -lwiringPi -lpthread -g -O0
 * Geanyのオプションの"%e"は実行ファイル名, "%f"はソースファイル名のこと
*/

/*printf("%d, %d\n", LedtimeNow, LedtimeOld); デバック用
printf("%d\n", LedtimeNow - LedtimeOld);
printf("DEBUG PRINT SysState == %d\n", gsm_SysState);
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>			///文字列操作
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>	///I2C用(wiringPi)
#include "MyHeadder.h"	///
#include "/home/pi/MyApp/LIB/MyPi.h"	///Lib関連
#include "Global.h"			///
#include <stdbool.h>

// LED
#define LED_TOGGLE 800 //LEDのONOFFを切り替える時間
#define LED_EMER 200 //LEDのONOFFを切り替える時間
#define LED1 20

unsigned int LedtimeNow;
int LedtimeOld = 0;
bool led_state = true;

//LCD
#define LCD_ADR 0x3e 
int fd;
int gsm_SysStateOld;


int task_4_lcdled_main(void)
{
    printf("DEBUG PRINT SysState == %d\n", gsmSys_mode_state);
   
	switch (gsmSys_mode_state)
	{
	case  SM_INIT:
	{
		//初期化		
		wiringPiSetupGpio();
		pinMode(LED1, OUTPUT);
		digitalWrite(LED1, led_state); 
		
		fd = wiringPiI2CSetup(LCD_ADR);
		LcdSetup(fd);
		
		//LCD
		LcdClear(fd);
		LcdWriteString(fd, "INITIALIZING");
		gsm_SysStateOld = gsmSys_mode_state;
	
		///初期化処理完了後に、初期化完了フラグを立ててください。
		
	}
		break;
		
	case  SM_WAIT:
		
		
		
		LedtimeNow = millis();
		
		if(LedtimeNow > LedtimeOld + LED_TOGGLE){		
			printf("%d\n", LedtimeNow - LedtimeOld);
			digitalWrite(LED1, led_state); 
			led_state = !led_state;
			LedtimeOld = LedtimeNow; 
			printf("DEBUG PRINT SysState == %d\n", gsmSys_mode_state);
		}
		
		//LCD
		if(gsm_SysStateOld != gsmSys_mode_state) {
			LcdClear(fd);
			LcdWriteString(fd, "WAIT");
			gsm_SysStateOld = gsmSys_mode_state;
		}
				
		
		break;
		
	case  SM_RUNNING:
	
		LedtimeNow = millis(); 
		
		if(LedtimeNow > LedtimeOld + LED_TOGGLE){		
			digitalWrite(LED1, led_state); 
			led_state = !led_state;//論理反転
			LedtimeOld = LedtimeNow; 
	
		if(gsm_SysStateOld != gsmSys_mode_state) {
			LcdClear(fd);
			LcdWriteString(fd, "RUNNING");
			gsm_SysStateOld = gsmSys_mode_state;
		}
			
		break;
		
	case  SM_ONESTOP:
		LedtimeNow = millis(); 
		if(LedtimeNow > LedtimeOld + LED_TOGGLE){		
			digitalWrite(LED1, led_state); 
			led_state = !led_state;
			LedtimeOld = LedtimeNow; 
		}
		
		if(gsm_SysStateOld != gsmSys_mode_state) {
			LcdClear(fd);
			LcdWriteString(fd, "STOP");
			gsm_SysStateOld = gsmSys_mode_state;
		}
		break;
		
	case  SM_EMER:
		LedtimeNow = millis(); 
		if(LedtimeNow > LedtimeOld + LED_EMER){		
			printf("%d\n", LedtimeNow - LedtimeOld);
			digitalWrite(LED1, led_state); 
			led_state = !led_state;
			LedtimeOld = LedtimeNow; 
			printf("DEBUG PRINT  SysState == %d\n", gsmSys_mode_state);
		}
		
		
		if(gsm_SysStateOld != gsmSys_mode_state) {
				LcdClear(fd);
				LcdWriteString(fd, "EMERGENCY");
				gsm_SysStateOld = gsmSys_mode_state;
		}
		
		
		///終了時処理完了後に、初期化完了フラグを落としてください。
		
		break;

	default:;
		break;
	
	}
	
	
    return EXIT_SUCCESS;
    
}


