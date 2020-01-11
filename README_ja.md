# Auto-Pokemon-Breeder
Forked from [progmem/Switch-Fightstick](https://github.com/progmem/Switch-Fightstick)

[English](./README.md) / [日本語](./README_ja.md)

ポケモン厳選をサポートするツールです。  
全自動で卵を孵化させることができます。

## 要件

### ハードウェア/ソフトウェア

- Arduino UNO R3 もしくは [shinyquagsire23/Switch-Fightstick's README](https://github.com/shinyquagsire23/Switch-Fightstick/blob/master/README.md) を参考にしてください。
- USBケーブル A-B
- Nintendo Switch
- ポケットモンスター ソード・シールド

### どうぐ/ポケモン

- ロトム自転車
- まるいおまもり
- 「ほのおのからだ」の特性を持つポケモン（セキタンザン、シャンデラなど）

## ビルド方法

- HatchEggs.hex のビルド

  ```sh
  $ sudo apt-get install git make gcc-avr avr-libc
  $ git clone https://github.com/Almtr/Switch-Fightstick.git
  $ cd Switch-Fightstick
  $ git clone https://github.com/abcminiuser/lufa.git
  ```

  1ボックス（30匹のポケモン）分の卵を孵化させたい場合

  ```sh
  $ make
  ```

  3ボックス（90匹のポケモン）分の卵を孵化させたい場合

  ```sh
  $ make hatch-eggs BOX_NUMBER=3
  ```

  最大の32ボックス（960匹のポケモン）分の卵を孵化させたい場合

  ```sh
  $ make hatch-eggs BOX_NUMBER=32
  ```

- Arduino UNO R3 への書き込み  
  [Updating the Atmega8U2 and 16U2 on an Uno or Mega2560 using DFU](https://www.arduino.cc/en/Hacking/DFUProgramming8U2) を参考にしてください。

## 使い方

1. メニューの「ポケモン」アイコンを左上に移動してください。 
1. インターネットから切断してください。
1. ボックスの中身を空にしてください。
1. 「ほのおのからだ」の特性を持つポケモン（と1つのタマゴ）をてもちに入れてください。
1. ワイルドエリアの預かり屋まで移動してください。
1. Arduino UNO R3 と Nintendo Switch を接続してください。

## デモ

[![](https://img.youtube.com/vi/oXnQt_Mbyzk/0.jpg)](https://www.youtube.com/watch?v=oXnQt_Mbyzk)  
https://www.youtube.com/watch?v=oXnQt_Mbyzk

## ダウンロード

https://github.com/Almtr/Switch-Fightstick/releases からダウンロードしてください。

## （オプション）その他モジュール

### トーナメント周回用モジュール

  トーナメントを自動で周回するためのモジュールです。  
  このモジュールを使用するには、「loop-tournament」を指定してコンパイルしてください。

  ```sh
  $ make clean       # 既に他のモジュールをコンパイルしていた場合は、このコマンドを実行してください。
  $ make loop-tournament
  ```
  
  使い方:  
  1. 技を1つだけ覚えたポケモン1匹をてもちに入れてください（例：「アイアンヘッド」のみを覚えたザシアン）。
  1. シュートスタジアムの受付前まで移動してください。
  1. Arduino UNO R3 と Nintendo Switch を接続してください。
  
  参考:  
  [【剣盾】トーナメント自動周回](http://niwaka-syndrome.blog.jp/archives/20509394.html)

### バトルタワー周回用モジュール

  バトルタワーを周回するためのモジュールです。  
  このモジュールを使用するには、「loop-battle-tower」を指定してコンパイルしてください。

  ```sh
  $ make clean       # 既に他のモジュールをコンパイルしていた場合は、このコマンドを実行してください。
  $ make loop-battle-tower
  ```

  使い方:  
  1. バトルタワー用のチームをレンタルしてください（チームID: 0000-0006-15Y4-3R）
  1. レンタルしたチームでシングルバトルに参加してください。
  1. Arduino UNO R3 と Nintendo Switch を接続してください。

  参考:  
  - [Twitter - sug@r@satoon_sugar: 1,000勝超えたのでメモ...](https://twitter.com/satoon_sugar/status/1208248084653674496)
  - [Twitter - sug@r@satoon_sugar: 周回開始前に、使用するチームが選ばれるようにしておく。...](https://twitter.com/satoon_sugar/status/1208253657470226432)

### ポケモンリリース用モジュール 

  ポケモンを自動で逃がすためのモジュールです。  
  このモジュールを使用するには、「release-pokemons」を指定してコンパイルしてください。

  ```sh
  $ make clean       # 既に他のモジュールをコンパイルしていた場合は、このコマンドを実行してください。
  $ make release-pokemons
  ```
  
  使い方:  
  1. 逃がしたいポケモン30匹が入ったボックスを開いてください。
  1. Bボタンを連打して、すべて閉じてください。
  1. Arduino UNO R3 と Nintendo Switch を接続してください。

### Aボタン連打用モジュール 

  Aボタンを連打するモジュールです。  
  このモジュールを使用するには、「repeat-a」を指定してコンパイルしてください。

  ```sh
  $ make clean       # 既に他のモジュールをコンパイルしていた場合は、このコマンドを実行してください。
  $ make repeat-a
  ```

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
