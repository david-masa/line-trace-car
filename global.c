/**
 * @file global.c
 * @brief グローバル変数の実体定義および初期値の設定
 */

#include "global.h"

// -----------------------------------------------------------------
// グローバル変数の実体定義（ここでメモリが確保される）
// -----------------------------------------------------------------

// ① システム状態：起動時は必ず STATE_INIT (0) から
SystemState_t g_system_state = STATE_INIT;

// ② 駆動指示値：安全のため停止状態で初期化
DriveCmd_t g_drive_cmd = DRIVE_STOP;

// ③ ラインセンサーパターン：初期状態は 0b000 (全消灯/未検知)
uint8_t g_line_sensor_pattern = 0b00000000;

// ④ その他の共通管理変数
uint8_t g_system_flags = 0;