# Auto-Pokemon-Breeder
Forked from [progmem/Switch-Fightstick](https://github.com/progmem/Switch-Fightstick)

[English](./README.md) / [日本語](./README_ja.md)

ポケモン厳選をサポートするツールです。  
全自動で30個の卵を孵化させることができます。

## 要件

### ハードウェア/ソフトウェア

- Arduino UNO R3 もしくは [shinyquagsire23/Switch-Fightstick's README](https://github.com/shinyquagsire23/Switch-Fightstick/blob/master/README.md) を参考にしてください。
- USB micro-b ケーブル
- Nintendo Switch
- ポケットモンスター ソード・シールド

### どうぐ/ポケモン

- ロトム自転車
- まるいおまもり
- 「ほのおのからだ」の特性を持つポケモン（セキタンザン、シャンデラなど）

## ビルド方法

- Joystick.hex のビルド

   ```
   $ apt-get install git make gcc-avr avr-libc
   $ git clone https://github.com/Almtr/Switch-Fightstick.git
   $ cd Switch-Fightstick
   $ git clone https://github.com/abcminiuser/lufa.git
   $ make
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

## 参考

- [GitHub - progmem/Switch-Fightstick](https://github.com/progmem/Switch-Fightstick)
- [GitHub - shinyquagsire23/Switch-Fightstick](https://github.com/shinyquagsire23/Switch-Fightstick)
- [GitHub - bertrandom/snowball-thrower](https://github.com/bertrandom/snowball-thrower)
- [GitHub - kidGodzilla/woff-grinder](https://github.com/kidGodzilla/woff-grinder)
- [GitHub - ebith/Switch-Fightstick](https://github.com/ebith/Switch-Fightstick)
- [Updating the Atmega8U2 and 16U2 on an Uno or Mega2560 using DFU](https://www.arduino.cc/en/Hacking/DFUProgramming8U2)
