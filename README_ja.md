# Auto-Pokemon-Breeder
Forked from [Almtr/Switch-Fightstick](https://github.com/Almtr/Switch-Fightstick)

[English](./README.md) / [日本語](./README_ja.md)

ポケモンの育成をサポートする自動化ツール群です。

## 要件

### ハードウェア/ソフトウェア

- Arduino UNO R3 もしくは [shinyquagsire23/Switch-Fightstick's README](https://github.com/shinyquagsire23/Switch-Fightstick/blob/master/README.md) を参考にしてください。
- USBケーブル A-B
- Nintendo Switch
- ポケットモンスター ソード・シールド

## ビルド環境準備(ubuntu)

  ```sh
  $ sudo apt-get install git make gcc-avr avr-libc
  $ git clone https://github.com/smd877/Switch-Fightstick
  $ cd Switch-Fightstick
  $ git clone https://github.com/abcminiuser/lufa.git
  ```

- hexファイルの Arduino UNO R3 への書き込み  
  [Updating the Atmega8U2 and 16U2 on an Uno or Mega2560 using DFU](https://www.arduino.cc/en/Hacking/DFUProgramming8U2) を参考にしてください。

## マジカル交換自動化

### ビルド方法

  1ボックス（30匹のポケモン）分マジカル交換したい場合

  ```sh
  $ make magical-trade
  ```

  3ボックス（90匹のポケモン）分マジカル交換したい場合

  ```sh
  $ make magical-trade BOX_NUMBER=3
  ```

### 使い方

1. 設定で「話の速さ」を速いにしてください。
1. 設定で「ニックネーム登録」をしないにしてください。
1. インターネットに接続してください。
1. ボックスに空きがない(30匹が交換できる)状態にしてください。
1. 図鑑が完成していることを前提に時間を組んでいます。(図鑑登録の時間を入れていません)※後述
1. どこでもいいのでポケモンセンターの中に移動してください。
1. Arduino UNO R3 と Nintendo Switch を接続してください。

### 交換まで時間がかかる場合は

  Module/MagicalTrade.c の 「TradeStart」メソッドの「case 4800」でおよそ交換開始後30秒程度で交換完了と判断して次の操作に移ります。
  「case 4800」の4800を調整することで交換完了判断のタイミング変更ができます。

### 図鑑がまだ完成していない場合は

  Module/MagicalTrade.c の 「TradeFinish」メソッドの「case 2850」でおよそ交換完了後2,3秒程度で次の操作に移ります。
  「case 1000 ... 1999」の1999と「case 2850」の2850を調整することで図鑑追加のアクションに対応できます。


## ボックスに余った卵を孵化するだけ自動化

### ビルド方法

  1ボックス（30匹のポケモン）分孵化したい場合

  ```sh
  $ make only-hatch-eggs
  ```

  3ボックス（90匹のポケモン）分孵化したい場合

  ```sh
  $ make only-hatch-eggs BOX_NUMBER=3
  ```

### 使い方

1. 設定で「話の速さ」を速いにしてください。
1. 設定で「ニックネーム登録」をしないにしてください。
1. ボックスを卵で埋めてください。
1. 「ほのおのからだ」の特性を持つポケモン1匹だけをてもちに入れてください。
1. ワイルドエリアの預かり屋まで移動してください。
1. ポケモンボックスを開いた状態(左上の卵に赤カーソルが当たっている状態)にしてください。
1. Arduino UNO R3 と Nintendo Switch を接続してください。


## 新時渡り式ポケジョブ自動化

### ビルド方法

  経験値を上げたい場合

  ```sh
  $ make poke-job
  ```

  H - S (か経験値)を上げたい場合

  ```sh
  $ make poke-job TARGET_NUM=6
  
  // TARGET_NUM=6 : ＨＰ
  // TARGET_NUM=5 : こうげき
  // TARGET_NUM=4 : ぼうぎょ
  // TARGET_NUM=3 : とくこう
  // TARGET_NUM=2 : とくぼう
  // TARGET_NUM=1 : すばやさ
  // TARGET_NUM=0 : 経験値
  ```

### 使い方

※ 新時渡り(レイドバトルによる日付変更ペナルティの回避)を利用した自動化です。利用する場合は自己責任でお願いします。

1. 新時渡りによりペナルティ回避状態にしてください。
1. 何月でもいいので1日にしてください。
1. 何時でもいいので0分にしてください。
1. 設定で「話の速さ」を速いにしてください。
1. 左上のポケモンボックスに対象ポケモン1匹だけを配置してください。
1. ロトミの前まで移動してください。
1. Arduino UNO R3 と Nintendo Switch を接続してください。

最大25回試行したら止まります。(新時渡りで1日と2分進めて確実にポケジョブを完了にするため。)


## 努力値振り分け自動化

### ビルド方法

  以下を実行

  ```sh
  $ make give-effort EFFORT_H=0 EFFORT_A=0 EFFORT_B=44 EFFORT_C=212 EFFORT_D=0 EFFORT_S=252

  // 0は省略しても大丈夫です↓こんなのもok
  // $ make give-effort EFFORT_B=44 EFFORT_C=212 EFFORT_S=252
  ```

### 使い方

※ 新時渡り(レイドバトルによる日付変更ペナルティの回避)を利用した自動化です。利用する場合は自己責任でお願いします。

1. 新時渡りによりペナルティ回避状態にしてください。
1. 何月でもいいので1日にしてください。
1. 何時でもいいので0分にしてください。
1. 設定で「話の速さ」を速いにしてください。
1. 左上のポケモンボックスに対象ポケモン1匹だけを配置してください。
1. ロトミの前まで移動してください。
1. Arduino UNO R3 と Nintendo Switch を接続してください。
1. H→A→B→C→D→S の順に努力値を振っていきます。(510の範囲チェックとかはやってないので自己責任で)

## ダウンロード

https://github.com/smd877/Switch-Fightstick/releases からダウンロードしてください。

## 他モジュールについて

Fork元を参照してください。
https://github.com/Almtr/Switch-Fightstick

以下モジュールがあります。

- 卵孵化トーナメント周回用モジュール
- トーナメント周回用モジュール
- トーナメント周回用モジュール
- バトルタワー周回用モジュール
- ポケモンリリース用モジュール 
- Aボタン連打用モジュール 

## 参考

- [GitHub - progmem/Switch-Fightstick](https://github.com/progmem/Switch-Fightstick)
- [GitHub - shinyquagsire23/Switch-Fightstick](https://github.com/shinyquagsire23/Switch-Fightstick)
- [GitHub - bertrandom/snowball-thrower](https://github.com/bertrandom/snowball-thrower)
- [GitHub - kidGodzilla/woff-grinder](https://github.com/kidGodzilla/woff-grinder)
- [GitHub - ebith/Switch-Fightstick](https://github.com/ebith/Switch-Fightstick)
- [Updating the Atmega8U2 and 16U2 on an Uno or Mega2560 using DFU](https://www.arduino.cc/en/Hacking/DFUProgramming8U2)
- [【剣盾】トーナメント自動周回](http://niwaka-syndrome.blog.jp/archives/20509394.html)
- [Twitter - sug@r@satoon_sugar: 1,000勝超えたのでメモ...](https://twitter.com/satoon_sugar/status/1208248084653674496)
- [Twitter - sug@r@satoon_sugar: 周回開始前に、使用するチームが選ばれるようにしておく。...](https://twitter.com/satoon_sugar/status/1208253657470226432)
