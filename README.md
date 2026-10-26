要求仕様書
[01_要求仕様書.pdf](https://github.com/user-attachments/files/33943015/01_.pdf)


要件定義書
[要件定義書.docx](https://github.com/user-attachments/files/33942983/default.docx)

基本設計書
[03_基本設計書 (仮）.docx](https://github.com/user-attachments/files/33942986/03_.docx)


###グローバル変数

g_system_state（システム状態：Init / Standby / Running / Onestop）

g_drive_cmd（駆動指示値：直進、左右小・大回り、停止）

g_line_sensor（ライントレース用のバイナリ値 / 例: 0b000）

g_distance_cm（距離センサー値 / 4〜50cm、範囲外の63など）

(※もしスタンバイからランニングへ移行する際に使うなら) g_white_button など、白ボタンの押下状態を保持する変数1つ
