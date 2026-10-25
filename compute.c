/**
 * @file compute.c
 * @brief 状態遷移およびライントレース・障害物制御ロジック
 */

#include "compute.h"
#include "global.h"

void Compute_Task(void) {

    switch (g_system_state) {

        case STATE_INIT:
            // 初期化時は compute 側での状態切り替えは行わない
            // (1周目の初期化処理を実行中)
            g_drive_cmd = DRIVE_STOP;
            break;

        case STATE_STANDBY:
            // スタンバイ中：白ボタンが押されたら(HIGH)走行モードへ移行
            g_drive_cmd = DRIVE_STOP;
            if (g_white_button == true) {
                g_system_state = STATE_RUNNING;
            }
            break;

        case STATE_RUNNING:
            // 走行モード：
            // ① 障害物判定 (4cm 〜 35cm 以内の場合はワンストップへ)
            if (g_distance_cm >= 4 && g_distance_cm <= 35) {
                g_system_state = STATE_ONESTOP;
                g_drive_cmd = DRIVE_STOP;
                break;
            }

            // ② ライントレース計算 (バイナリ値パターンに応じて駆動指示を決定)
            switch (g_line_sensor) {
                case 0b010: // 中央のみ検知：直進
                    g_drive_cmd = DRIVE_STRAIGHT;
                    break;

                case 0b100: // 左寄り：小回り右折
                    g_drive_cmd = DRIVE_RIGHT_SMALL;
                    break;

                case 0b110: // 大きく左寄り：大回り右折
                    g_drive_cmd = DRIVE_RIGHT_LARGE;
                    break;

                case 0b001: // 右寄り：小回り左折
                    g_drive_cmd = DRIVE_LEFT_SMALL;
                    break;

                case 0b011: // 大きく右寄り：大回り左折
                    g_drive_cmd = DRIVE_LEFT_LARGE;
                    break;

                case 0b000: // 線から完全に外れた場合などの復帰ロジック（必要に応じて）
                default:
                    g_drive_cmd = DRIVE_STRAIGHT;
                    break;
            }
            break;

        case STATE_ONESTOP:
            // 一時停止モード：
            // 障害物までの距離が 35cm より大きくなったら走行モードへ自動復帰
            g_drive_cmd = DRIVE_STOP;
            if (g_distance_cm > 35) {
                g_system_state = STATE_RUNNING;
            }
            break;

        case STATE_EMERGENCY:
            // 緊急停止
            g_drive_cmd = DRIVE_STOP;
            break;

        default:
            g_system_state = STATE_STANDBY;
            g_drive_cmd = DRIVE_STOP;
            break;
    }
}