要求仕様書
https://github.com/david-masa/line-trace-car/blob/main/%E8%A6%81%E6%B1%82%E4%BB%95%E6%A7%98%E6%9B%B8.pdf

要件定義書
https://github.com/david-masa/line-trace-car/blob/main/%E8%A6%81%E4%BB%B6%E5%AE%9A%E7%BE%A9%E6%9B%B8.pdf

基本設計書
https://github.com/david-masa/line-trace-car/blob/main/%E5%9F%BA%E6%9C%AC%E8%A8%AD%E8%A8%88%E6%9B%B8.pdf

詳細設計書

単体テスト

結合テスト

システムテスト

受け入れテスト


## 部品一覧

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
