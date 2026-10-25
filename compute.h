/**
 * @file compute.h
 * @brief 計算制御モジュールの看板
 */

#ifndef COMPUTE_H_
#define COMPUTE_H_

void Compute_Task(void);

//もし各モジュールごとのヘッダーを省略したいならメイン関数のint mainの前に、プロトタイプ宣言する必要がある。
//extern void Input_Task(void);
//extern void Compute_Task(void);
//extern void Output_Task(void);

#endif /* COMPUTE_H_ */