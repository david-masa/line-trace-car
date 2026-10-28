//A/DコンバータMCP3802用関数

extern unsigned short  Mcp3208RW(int ssNo, unsigned char adcChannel);



//D/AコンバータMCP4922用関数

extern int Mcp4922Write(int ssNo, unsigned char dacCh, unsigned short dacCode); 



//温度センサADT7410用関数

extern double Adt7410Read(int fd);



//LCD AQM1602用関数

extern int LcdSetup(int fd);

extern int LcdWriteChar(int fd, char c);

extern int LcdNewline(int fd);

extern int LcdClear(int fd);

extern int LcdWriteString(int fd, char *s);



//センサー関数

#include <wiringPi.h> 

#include <wiringPiI2C.h> 



#define LCD_ADR 0x3e 

#define LCD_IR 0x00



#define SEN_RIGHT 4 

#define SEN_CENTER 5 

#define SEN_LEFT 6



int ReadSens(void){

	int sensors = 0;

	sensors = digitalRead(SEN_LEFT) * 4 + digitalRead(SEN_CENTER) * 2 + digitalRead(SEN_RIGHT);

	return sensors;

}



void Sens2Lcd(int fd, int sensors){

	int ac7 = 0x80;

	

	wiringPiI2CWriteReg8(fd, LCD_IR, ac7 + 0x00);

	if(sensors & 0x04){

		LcdWriteChar(fd, '1');

	}

	else{

		LcdWriteChar(fd, '0');

	}

	

	wiringPiI2CWriteReg8(fd, LCD_IR, ac7 + 0x07);

	if(sensors & 0x02){

		LcdWriteChar(fd, '1');

	}

	else{

		LcdWriteChar(fd, '0');

	}

	

	wiringPiI2CWriteReg8(fd, LCD_IR, ac7 + 0x0f);

	if(sensors & 0x01){

		LcdWriteChar(fd, '1');

	}

	else{

		LcdWriteChar(fd, '0');

	}

}



//モーター関数

#define MOT_RIGHT2 22

#define MOT_RIGHT1 23

#define MOT_LEFT2 24

#define MOT_LEFT1 25



void TurnRight(void){

	digitalWrite(MOT_RIGHT2, LOW);

	digitalWrite(MOT_RIGHT1, HIGH);

	digitalWrite(MOT_LEFT2, HIGH);

	digitalWrite(MOT_LEFT1, LOW);

}



void TurnLeft(void){

	digitalWrite(MOT_RIGHT2, HIGH);

	digitalWrite(MOT_RIGHT1, LOW);

	digitalWrite(MOT_LEFT2, LOW);

	digitalWrite(MOT_LEFT1, HIGH);

}



void RightForward(void){

	digitalWrite(MOT_RIGHT2, LOW);

	digitalWrite(MOT_RIGHT1, HIGH);

	digitalWrite(MOT_LEFT2, LOW);

	digitalWrite(MOT_LEFT1, LOW);

}

	

void RightReverse(void){

	digitalWrite(MOT_RIGHT2, HIGH);

	digitalWrite(MOT_RIGHT1, LOW);

	digitalWrite(MOT_LEFT2, LOW);

	digitalWrite(MOT_LEFT1, LOW);

}



void LeftForward(void){

	digitalWrite(MOT_RIGHT2, LOW);

	digitalWrite(MOT_RIGHT1, LOW);

	digitalWrite(MOT_LEFT2, LOW);

	digitalWrite(MOT_LEFT1, HIGH);

}



void LeftReverse(void){

	digitalWrite(MOT_RIGHT2, LOW);

	digitalWrite(MOT_RIGHT1, LOW);

	digitalWrite(MOT_LEFT2, HIGH);

	digitalWrite(MOT_LEFT1, LOW);

}



void Forward(void){

	digitalWrite(MOT_RIGHT2, LOW);

	digitalWrite(MOT_RIGHT1, HIGH);

	digitalWrite(MOT_LEFT2, LOW);

	digitalWrite(MOT_LEFT1, HIGH);

}



void Reverse(void){

	digitalWrite(MOT_RIGHT2, HIGH);

	digitalWrite(MOT_RIGHT1, LOW);

	digitalWrite(MOT_LEFT2, HIGH);

	digitalWrite(MOT_LEFT1, LOW);

}



void Stop(void){

	digitalWrite(MOT_RIGHT2, LOW);

	digitalWrite(MOT_RIGHT1, LOW);

	digitalWrite(MOT_LEFT2, LOW);

	digitalWrite(MOT_LEFT1, LOW);

}



void Breake(void){

	digitalWrite(MOT_RIGHT2, HIGH);

	digitalWrite(MOT_RIGHT1, HIGH);

	digitalWrite(MOT_LEFT2, HIGH);

	digitalWrite(MOT_LEFT1, HIGH);

}



void LcdClrMsg(int fd, char *s){

	LcdClear(fd);

	LcdWriteString(fd, s);

}



//距離計関数

#define GP2Y0E03_ADR 0x40

#define GP2Y0E03_DIS_U 0x5e

#define GP2Y0E03_DIS_L 0x5f



int ReadDistance(int fd2){

	int disU8bit, disL4bit, dis12bit;

	disU8bit = wiringPiI2CReadReg8(fd2, GP2Y0E03_DIS_U);

	disL4bit = wiringPiI2CReadReg8(fd2, GP2Y0E03_DIS_L );

	dis12bit = (disU8bit << 4) | disL4bit;

	dis12bit = dis12bit >> 6;

	return dis12bit;

}

