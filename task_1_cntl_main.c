/* task_1_cntl_main.c
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

#include "task_1_cntl_main.h"	
#include "task_1_math_main.h"		///
#include "task_2_sensor_main.h"			///これを、実際の名称にする
#include "task_3_output_main.h"	///これを、実際の名称にする
#include "task_4_lcdled_main.h"	///これを、実際の名称にする
#include "task_5_sound_main.h"	///これを、実際の名称にする

int main(void)
{
	
	task_1_cntl_main();
	
	return EXIT_SUCCESS;

}

int task_1_cntl_main(void)
{
    
    while (gbSys_Loop_f)
    {
		switch (gsmSys_mode_state)
		{
		case  SM_INIT:
			printf("DEBUG PRINT SysState == %d\n", gsmSys_mode_state);
			///初期化処理完了後に、初期化完了フラグを立ててください。
			task_1_math_main();
			task_2_sensor_main();
			task_3_output_main();
			task_4_lcdled_main();
			task_5_sound_main();
			gsmSys_mode_state = SM_WAIT;
			break;
		case  SM_WAIT:
			task_1_math_main();
			task_2_sensor_main();
			task_3_output_main();
			task_4_lcdled_main();
			task_5_sound_main();
			break;

		case  SM_RUNNING:
			task_1_math_main();
			task_2_sensor_main();
			task_3_output_main();
			task_4_lcdled_main();
			task_5_sound_main();
			break;

		case  SM_ONESTOP:
			task_1_math_main();
			task_2_sensor_main();
			task_3_output_main();
			task_4_lcdled_main();
			task_5_sound_main();
			break;

		case  SM_EMER:
			task_1_math_main();
			task_2_sensor_main();
			task_3_output_main();
			task_4_lcdled_main();
			task_5_sound_main();
			printf("DEBUG PRINT  SysState == %d\n", gsmSys_mode_state);
			///終了時処理完了後に、初期化完了フラグを落としてください。
			break;

		default:;
			break;
		
		}
	}
	
    return EXIT_SUCCESS;
    
}
