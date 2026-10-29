/* Global.c
 * LineTraceCar
 * 		by Team.A
 * custom:	gcc -Wall *.c -o app -lwiringPi -lpthread -g -O0 /home/pi/MyApp/LIB/libMyPi.a
 * org:		gcc -Wall -o "%e" "%f" -lwiringPi -lpthread -g -O0
 * Geanyのオプションの"%e"は実行ファイル名, "%f"はソースファイル名のこと
*/

#include "Global.h"

///グローバル変数 
SM_MODE gsmSys_mode_state = SM_INIT;	///システム状態（0:SM_INIT、SM_WAIT、SM_RUNNING、SM_ONESTOP、SM_EMER）

bool gbSys_Btn_red_state;				///赤ﾎﾞﾀﾝ状態（DBTN_OFF:0、DBTN_ON:1）
bool gbSys_Btn_wht_state;				///白ﾎﾞﾀﾝ状態（DBTN_OFF:0、DBTN_ON:1）

int giSys_LineSnsr_line_state;			///ラインセンサー状態（例）L:C:R ⇒ 1:1:0 → 0b00000000 00000110）
int giSys_DistSnsr_dist_value;			///距離センサー計測距離（cm）

int giSys_Motor_drive_inst;				///駆動指示（0:即停止、1:微速直進、2:加速直進、3:前右弱、4:前右強、5:前左弱、6:前左強、7:微速後進、8:減速停止, 9TurnRight, 10: TurnLeft）

bool gbSys_Loop_f = true;				///処理継続フラグ
