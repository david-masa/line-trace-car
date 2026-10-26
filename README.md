要求仕様書
https://github.com/david-masa/line-trace-car/blob/main/01_%E8%A6%81%E6%B1%82%E4%BB%95%E6%A7%98%E6%9B%B8.pdf


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
