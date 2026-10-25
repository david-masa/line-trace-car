/**
 * @file global.h
 * @brief システム共通の型定義、定数、およびグローバル変数の宣言（看板）
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdint.h>
#include <stdbool.h>

// -----------------------------------------------------------------
// 1. システム状態の型定義 (enum)
// -----------------------------------------------------------------
typedef enum {
    STATE_INIT = 0,     // 0: 初期化状態
    STATE_STANDBY,      // 1: 待機状態
    STATE_RUNNING,      // 2: 走行状態
    STATE_ONESTOP,      // 3: 一時停止状態
    STATE_EMERGENCY     // 4: 緊急停止状態
} SystemState_t;

// -----------------------------------------------------------------
// 2. 駆動指示値の型定義 (enum)
// -----------------------------------------------------------------
typedef enum {
    DRIVE_STOP = 0,     // 停止
    DRIVE_STRAIGHT,     // 直進
    DRIVE_LEFT_SMALL,   // 小回り左折
    DRIVE_LEFT_LARGE,   // 大回り左折
    DRIVE_RIGHT_SMALL,  // 小回り右折
    DRIVE_RIGHT_LARGE   // 大回り右折
} DriveCmd_t;

// -----------------------------------------------------------------
// 3. グローバル変数の extern 宣言（実体は global.c に置く）
//extern 付き（ヘッダー / global.h）

//役割： 「あっちのファイルに本物があるから、この名前で共有して使ってね！」という共有の合言葉（看板）をみんなに配る。

//メモリは新しく作らない。

//extern なし（ソース / global.c）

//役割： 世界にたった1つだけの「本物の実体（メモリの確保と初期値の設定）」を作る。
// -----------------------------------------------------------------
// ① システム状態
extern SystemState_t g_system_state;

// ② 駆動指示値
extern DriveCmd_t g_drive_cmd;

// ③ ラインセンサーのパターン（例: 0b000 などのビット情報）
extern uint8_t g_line_sensor_pattern;

// ④ その他の共通管理変数（例: 走行フラグや汎用カウンターなど）
extern uint8_t g_system_flags;

extern bool          g_white_button;        // 白ボタン押下状態 (true/false)

#endif /* GLOBAL_H_ */