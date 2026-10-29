/* task_1_modulename_main.c
 * LineTraceCar
 * 		by Team.A
 * custom:	gcc -Wall *.c -o app -lwiringPi -lpthread -g -O0 /home/pi/MyApp/LIB/libMyPi.a
 * org:		gcc -Wall -o "%e" "%f" -lwiringPi -lpthread -g -O0
 * Geanyのオプションの"%e"は実行ファイル名, "%f"はソースファイル名のこと
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>			///文字列操作
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>	///I2C用(wiringPi)
//#include "../MyHeadder.h"	///
#include "../LIB/MyPi.h"	///Lib関連
#include "Global.h"			///

#include <unistd.h>         //usleep
#include <math.h>           //pow

#define BUZZER  18		//GPIO18をBUZZERと定義
#define CLK  19200000	//RasoberryPi内部クロック Hz
#define RANGE   100		//PWM range

#define OL  3	//1 オクターブ下
#define OC  4 	//中央のオクターブ
#define OH  5 	//1 オクターブ上

#define REST    0	//休符
#define DO      1   //ド 
#define DOS     2   //ド#
#define RE      3   //レ
#define RES     4   //レ# 
#define MI      5   //ミ
#define FA      6   //ファ 
#define FAS     7   //ファ#
#define SO      8   //ソ
#define SOS     9   //ソ#
#define RA      10  //ラ  
#define RAS     11  //ラ#  
#define SI      12  //シ  

/*　デバッグ用なのでコメントアウト中
#define  DEBUG		// マクロ定義により#ifdef #endifで挟まれた命令が有効になります。
					// 命令を無効にする場合は、このマクロ定義をコメント文にしてビルドします。*/
//#define DEBUG_RUN
//#define DEBUG_ObstBuzzer




/* プロトタイプ宣言 */
void g(int oct, int solfa, int length); //1音を発生する関数
void PlayMusic(void);	//走行開始前の音楽再生
int PlayObstacleBuzzer(void);	//障害物検知後のブザー再生


int task_5_sound_main(void)
{
	static int MusicPlayComplete = 0;	//0:初期値・再生中 1:再生完了。走行開始時に使用。
	//Switch構文内では宣言できないとコンパイルエラーが出たため、ここで宣言
        
	switch (gsmSys_mode_state)
	{
	case  SM_INIT:
		printf("DEBUG PRINT gsmSys_mode_state == %d\n", gsmSys_mode_state);
		///初期化処理完了後に、初期化完了フラグを立ててください。
		
		wiringPiSetupGpio();  		    //BCMのGPIO番号を使用
		pinMode(BUZZER, PWM_OUTPUT);    //BUZZERをPWM出力に設定
		pwmSetRange(RANGE);             //階調の設定
		pwmSetMode(PWM_MODE_MS);        //信号波形モードの設定
		
		
		break;
	case  SM_WAIT:
	
		break;
	case  SM_RUNNING:
		if (MusicPlayComplete == 0){	
			PlayMusic();
			printf("RUNNING: Drive_inst = %d\n", giSys_Motor_drive_inst);
			MusicPlayComplete = 1;
			
		
		}
		break;
	case  SM_ONESTOP:
		if (PlayObstacleBuzzer() == 1) {			
			printf("DEBUG: Buzzer finished\n");
		}
		printf("DEBUG PRINT gsmSys_mode_state == %d\n", gsmSys_mode_state);
		break;
	case  SM_EMER:
		///終了時処理完了後に、初期化完了フラグを落としてください。
		break;

	default:;
		break;
	
	}
	

    return EXIT_SUCCESS;
    
}



void PlayMusic(void){
	int i;
	int oct,solfa;
	int bpm = 120;      //楽譜のテンポ(Beats Per Minute) 
	int qN = 60000/bpm; //4分音符(quarter note) の長さ(ミリ秒)
	int musicNo;
	int music[][3] = {  //さくらさくらの曲
		{OC,RA,qN},
		{OC,RA,qN},
		{OC,SI,qN*2},
		{OC,RA,qN},
		{OC,RA,qN},
		{OC,SI,qN*2},
/*
		{OC,RA,qN},
		{OC,SI,qN},
		{OH,DO,qN},
		{OC,SI,qN},
		{OC,RA,qN},
		{OC,SI,qN/2},
		{OC,RA,qN/2},
		{OC,FA,qN*2},
	
		{OC,MI,qN},
		{OC,DO,qN},
		{OC,MI,qN},
		{OC,FA,qN},
		{OC,MI,qN},
		{OC,MI,qN/2},
		{OC,DO,qN/2},
		{OL,SI,qN*2},
		{OC,RA,qN},
		{OC,SI,qN},
		{OH,DO,qN},
		{OC,SI,qN},

		{OC,RA,qN},
		{OC,SI,qN/2},
		{OC,RA,qN/2},
		{OC,FA,qN*2},
		{OC,MI,qN},
		{OC,DO,qN},
		{OC,MI,qN},
		{OC,FA,qN},
		{OC,MI,qN},
		{OC,MI,qN/2},
		{OC,DO,qN/2},
		{OL,SI,qN*2},

		{OC,RA,qN},
		{OC,RA,qN},
		{OC,SI,qN*2},
		{OC,RA,qN},
		{OC,RA,qN},
		{OC,SI,qN*2},
		{OC,MI,qN},
		{OC,FA,qN},
		{OC,SI,qN/2},
		{OC,RA,qN/2},
		{OC,FA,qN},
		{OC,MI,qN*2},
*/
		{OC,REST,qN},    //曲の最後は休止符を挿入して音を止める
	};

/*	GPIOの初期化をSM_INITへ移行。
 * 音楽再生PlayMusicと障害物ブザーPlayObstacleBuzzerの両方で使うため。
 * 
	wiringPiSetupGpio();        //BCMのGPIO番号を使用

	pinMode(BUZZER, PWM_OUTPUT);    //BUZZERをPWM出力に設定
	pwmSetRange(RANGE);             //階調の設定
	pwmSetMode(PWM_MODE_MS);        //信号波形モードの設定

*/
	printf("CLK %d¥n",CLK);
	musicNo = sizeof music/((sizeof music[0][0])*3); //配列の要素数(音符)の計算
	#ifdef DEBUG
	printf("musicNo = %d¥n",musicNo);
	#endif


	for(i=0; i<musicNo; i++){   //音符の最初から最後まで再生
	#ifdef DEBUG
		printf("%d  ",i+1);
	#endif
		printf("OKOKOK\n");
		oct = music[i][0];      //オクターブの取得
		solfa =  music[i][1];   //階名の取得
		qN = music[i][2];       //音の長さの取得
		g(oct,solfa,qN);        //1音を再生
	}
		
		usleep(1000);           //CPU使用率の抑制のため
			
}

int PlayObstacleBuzzer(void)
{
    static unsigned int startTime = 0;
    static int playing = 0;

    if (playing == 2) {
        return 0;   // 再生完了後は何もしない
    }

    if (playing == 0) {
        int f = 1000;
        int divisor;
        int value;

        divisor = CLK / (f * RANGE);
        value = RANGE / 2;

        pwmSetClock(divisor);
        pwmWrite(BUZZER, value);

        startTime = millis();
        playing = 1;

        return 0;
    }

    if ((unsigned int)(millis() - startTime) >= 1000) {
        pwmWrite(BUZZER, 0);
        playing = 2;

        return 1;   // 完了通知は1回だけ
    }

    return 0;
}
		

/*****************************************************
 関数名  void g(int oct, int solfa, int length)
 引数    oct     3:1オクターブ下,4:中央,5:1オクターブ上
		solfa   0:休符,1:ド,2:ド#,3:レ,4:レ#,5:ミ,6:ファ,
				7:ファ#,8:ソ,9:ソ#,10:ラ,11:ラ#,12:シ
		length　時間の長さ 単位ms
 戻り値  なし
 概要   引数で指定された音名または休符を発生する。
 *****************************************************/
void g(int oct, int solfa, int length){
	int d = 0;      //指数 式6-101
	int f = 0;      //周波数
	int divisor;    //分周値 pwmSetClock関数の引数
	int value;      //tON時間 pwmWrite関数の引数
		if(solfa !=0){         //休符以外の場合、音名の周波数を計算
			d = solfa - 10;    //引数solfaから式6-101の変数dに変換する
			if (oct == OL){    //1オクターブ下のとき
				d -= 12;
			}
			if(oct == OH){     //1オクターブ上のとき
				d+=12;
			}
			f = 440 * pow(2,(double)d/12)+0.5;  //べき乗計算のpow関数
			divisor = CLK / (f*RANGE);          //divisorを求める。
			pwmSetClock(divisor);               //内部クロックの分周の設定
			value = RANGE/2;    //デューティ比50%
		}else{
			value = 0;          //休符、valueを0にして、音を止めます
		}
	#ifdef DEBUG
		printf("d = %d, f = %d¥n",d,f);
	#endif
	pwmWrite(BUZZER, value); //length(ms) だけ音を出力
	delay(length);
}
