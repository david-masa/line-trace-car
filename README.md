<img width="800" height="600" alt="PXL_20261028_032808331" src="https://github.com/user-attachments/assets/7937a963-3bea-45c5-8a67-4b5349f236f9" />
## 概要
Raspberry Pi を使用した自律走行ロボットです。<br>
3個のラインセンサでラインを検出し、モータを制御して走行します。<br>
距離センサで障害物との距離を測定します。<br>
障害物が35cm以下に近づくとモータを停止します。<br>

## 動作(個人開発コードの動作)
白色スイッチを押すと走行を開始します。<br>
ラインセンサの状態に応じて前進・後退・左右の進行方向補正を行います。<br>
ラインの状態変化に応じて左右に旋回します。<br>
障害物が35cm以下になると停止し、距離が35cmより長くなると走行制御に戻ります。<br>
距離は LCD に表示されます。<br>

動作ビデオ
<img width="720" height="405" alt="1030" src="https://github.com/user-attachments/assets/cbe50030-6045-4bba-9807-b8ba4a468576" />

## 全体回路図
<img width="1024" height="726" alt="ライントレースカー＿全体回路図" src="https://github.com/user-attachments/assets/436096e9-5113-4c67-98f8-805accc2e34c" />


## センサ回路図
<img width="1024" height="726" alt="ライントレースカー＿センサ回路図" src="https://github.com/user-attachments/assets/a2bdc3db-99d9-42b2-b49d-14b29cf30fd8" />

## 注意事項
本納品物は、開発時に機能ごとに分割した複数のソースファイルで構成されています。<br>
ビルド時にこれらのファイルを1つのファイルに結合し、納品用のファイルを生成しています。<br>
そのため、開発用ファイルが複数存在しますが、正常な構成となります。<br>

ビルドコマンドを下記のcustomに変更する必要があります。<br>
またコマンドを実行”Execute”を　sudo "./app"　に変更してください。<br>

LineTraceCar<br>
		by Team.A<br>
custom:	gcc -Wall *.c -o app -lwiringPi -lpthread -g -O0 /home/pi/MyApp/LIB/libMyPi.a -lm<br>
org:		gcc -Wall -o "%e" "%f" -lwiringPi -lpthread -g -O0<br>
Geanyのオプションの"%e"は実行ファイル名, "%f"はソースファイル名のこと<br>


## 基本部品一覧
| 部品記号 | 品名 | 値・型式 | メーカー | 個数 | 秋月型番 | 備考 |
|---|---|---|---|---:|---|---|
| BZ1 | 圧電サウンダ | PKM17EPP-4001-B0 | 村田製作所 | 1 | P-04119 | |
| C1-C3 | 電解コンデンサ | 220u/10V UVR1A221MED | ニチコン | 3 | P-03179 | 互換 P-03179、2.5mm幅 |
| C4,C5 | セラミックコンデンサ | 0.1u/50V RDER72E104K2K1H03B | 村田製作所 | 2 | P-10147 | |
| CN1 | ピンソケット | FH-2x20SG | Useconn Electronics | 1 | C-00085 | メス40ピン、ラズパイ用 |
| CN2 | ピンヘッダ | XG4C-1034 | Useconn Electronics | 1 | C-10903 | オス10ピン、L型センサ用 |
| CN3 | ターミナルブロック | TB112-2-2-U-1 | Alphaplus | 2 | P-01309 | メス2ピン、モータ用 |
| CN4 | ピンソケット | FH150-1x5SG | Useconn Electronics | 2 | C-10397 | メス5ピン、LCD用 |
| CN5 | ピンヘッダ | 1x4 (4P) | Useconn Electronics | 1 | C-03950 | 4ピン、距離センサ用、10個入り |
| CN6 | DCジャック | MJ-179P | マル信無線電機 | 1 | C-00077 | Φ2.1mm |
| IC1,IC2 | モータ駆動IC | TA7291P | 東芝 | 2 | I-02001 | 廃番 (Discontinued) |
| JP1 | ピンヘッダ | PH-1X3SG 1x3 (3P) | Useconn Electronics | 1 | C-03949 | 3ピン、マイクロサーボ用、10個入り |
| LED1 | 赤色LED | OSR5JA3Z74A | OptoSupply | 1 | I-11577 | 直径3mm |
| R1 | カーボン抵抗1/4W | 390Ω CF25J390RB | FAITHFUL LINK | 1 | R-25391 | 100本入り |
| R2 | カーボン抵抗1/4W | 4.7kΩ RD25S 4K7 | SHIH HAO Electronics | 1 | R-25472 | 100本入り |
| SW1 | トグルスイッチ | 2MS1-T1-B4-VS2-Q | Cosland | 1 | P-00300 | |
| SW2 | タクトスイッチ | DTS-6-V | Cosland | 1 | P-03648 | 赤 |
| SW3 | タクトスイッチ | DTS-6-V | Cosland | 1 | P-03646 | 白 |
| VR1 | 可変抵抗器 | 50k 3386K-EY5-503TR | SUNTAN TECHNOLOGY | 1 | P-06112 | 青色 |
| TP1 | チェック端子 | TEST-1(BK) | Kang Yang Hardware | 1 | P-07591 | 黒色 |
| — | マイクロサーボ | SG-90 | Tower Pro Pte Ltd | 1 | M-08761 | |
| — | 距離センサ | GP2Y0E03 | シャープ | 1 | I-07547 | ハーネス付き、片端要加工 |
| — | コネクタ用ハウジング 4pin | 2226A-04 | Neltron Industrial | 1 | C-12153 | GP2Y0E03用 |
| — | ケーブル用コネクタ | 2226TG | Neltron Industrial | 4 | C-12160 | GP2Y0E03用、圧着端子 |
| CN4 | 分割ロングピンソケット（メス） | FHU-1x40SG-R 1x40 (40P)・赤 | Useconn Electronics | 2 | 110299 | LCDゲタ用、4pin、1段に使用 |
| CN4 | 丸ピンIC用ソケット（シングル10P） | 6604S-10 1x10 | Neltron Industrial | 3 | 100674 | LCDゲタ用、4pin、2～4段に使用 |
| — | 丸ピンIC用ソケット（シングル10P） | 6604S-10 1x10 | Neltron Industrial | 2 | 100674 | モータ駆動IC用、10pin |

## センサ基板 部品一覧
| 部品記号 | 品名 | 値・型式 | メーカー | 個数 | 秋月型番 | 備考 |
|---|---|---|---|---:|---|---|
| IC1 | シュミットトリガ入り6回路インバーター | TC74HC14AF | 東芝 | 1 | I-10589 | 5個入り |
| OC1-OC3 | フォトリフレクタ | LBR-127HLD | Letex Technology | 3 | P-04500 | |
| R1,R4,R7 | チップ角形抵抗 | 100Ω<br>RK73B2BTTD101J | KOA | 3 | — | 10個入り、せんごくネット |
| R2,R5,R8 | チップ角形抵抗 | 270Ω<br>RK73B2BTTD271J | KOA | 3 | — | 10個入り、せんごくネット |
| R3,R6,R9 | チップ角形抵抗 | 390Ω<br>RK73B2BTTD391J | KOA | 3 | — | 10個入り、せんごくネット |
| VR1-VR3 | 半固定抵抗 | 10kΩ<br>3362P-1-103LF | Bourns | 3 | P-03277 | |
| D1 | 緑色LED | OSG5TA3Z74A | OptoSupply | 1 | I-11635 | 直径3mm |
| D2 | 黄色LED | OSY5JA3Z74A | OptoSupply | 1 | I-11639 | 直径3mm |
| D3 | 赤色LED | OSR5JA3Z74A | OptoSupply | 1 | I-11577 | 直径3mm |
| X1 | ピンヘッダ | XG4C-1031 | Useconn Electronics | 1 | C-13635 | オス10ピン、トップ型、センサ用 |

## シャーシ・駆動系・その他部品
| 部品記号 | 品名 | 値・型式 | メーカー | 個数 | 秋月型番 | 備考 |
|---|---|---|---|---:|---|---|
| — | 電池ボックス（リード線付） | 単3形×4本 | COMFORRTABLE ELECTRONIC | 1 | P-02671 | |
| — | 2.1mm標準DCプラグ | MP-121M | マル信無線電機 | 1 | C-00091 | |
| — | エネループ単3形4本パック | BK-3MCD/4H | パナソニック | 1 | — | 1台あたり4本使用 |
| — | ユニバーサルプレート | Item No. 70098 | タミヤ | 1 | — | 1台あたり1枚使用、160×60mm |
| — | ダブルギヤボックス（左右独立4速タイプ） | Item No. 70168 | タミヤ | 1 | — | |
| — | セラミックコンデンサ | 0.1µF / 50V<br>RDER72E104K2K1H03B | 村田製作所 | 2 | P-10147 | ダブルギヤボックスのモータ端子に加工 |
| — | ボールキャスター（2セット入り） | Item No. 70144 | タミヤ | 1 | — | 1台あたり1個使用 |
| — | スポーツタイヤセット（56mm径） | Item No. 70111 | タミヤ | 1 | — | 廃番、Item No. 69916で代用可 |
| — | ナット | M3 | — | 4 | — | |
| — | プラネジ | M3×5mm | — | 8 | — | |
| — | 両メネジスペーサー | 20mm<br>AS-320 | 廣杉計器 | 2 | — | センサ基板とユニバーサルプレートの固定用 |
| — | 両メネジスペーサー | 30mm<br>AS-330 | 廣杉計器 | 2 | — | 駆動基板とRaspberry Pi本体の固定用 |
| — | オネジメネジスペーサー | 10mm<br>BS-310E | 廣杉計器 | 4 | — | 駆動基板とユニバーサルプレートの固定用 |
| — | 2×5（10P）フラットケーブル | DG01032-0019-01 | Herwell Asia | 1 | 106972 | 駆動基板とセンサ基板の接続用 |
| — | ケーブルタイ | TRCV-200SSW | TRUSCO | 1 | — | 距離センサをサーボに固定 |
| — | マジックテープ | — | — | 1 | — | 電池ボックスをプレートに取り付けるために使用 |


<img width="600" height="800" alt="PXL_20261028_032824848" src="https://github.com/user-attachments/assets/41345b9c-fd9c-48dd-ba38-6c480c41cdf3" />
<img width="800" height="600" alt="PXL_20261028_032803098" src="https://github.com/user-attachments/assets/dbeaae13-5179-4b53-b1ea-5d8c26e2537a" />
<img width="800" height="600" alt="PXL_20261028_032758891" src="https://github.com/user-attachments/assets/e5cfc16c-91a7-4227-9be8-6b9ebd8b8c61" />
<img width="800" height="600" alt="PXL_20261028_032753005" src="https://github.com/user-attachments/assets/dc25ce61-2cdb-443a-a3ed-54ae5fd2bf6f" />
<img width="800" height="600" alt="PXL_20261028_032746993" src="https://github.com/user-attachments/assets/25eb8dbf-162b-4ec4-b27f-7b603e3900ec" />
<img width="800" height="600" alt="PXL_20261028_021001096" src="https://github.com/user-attachments/assets/affbcde4-454c-4a89-9621-e08a6454d5af" />
<img width="800" height="600" alt="PXL_20261028_020954164" src="https://github.com/user-attachments/assets/e5201b4c-9f83-46a5-84d0-fc166ba1c41d" />

