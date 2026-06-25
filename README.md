# ESP32 UART NeoPixel Control

## 概要

2台のESP32をUART通信で接続し、送信側の光センサーの値に応じて受信側のNeoPixel LEDを制御するシステムを作成しました。

光センサーが一定値を超えた場合は「ON」、下回った場合は「OFF」をUART経由で送信し、受信側でLEDの点灯・消灯を行います。

## 解説動画
https://youtube.com/shorts/8J1rCqYr5aY?feature=share

## システム構成

光センサー → ESP32(送信側) → UART → ESP32(受信側) → NeoPixel

## 使用技術

* ESP32 DevKitC-32E
* Arduino IDE
* UART通信 (Serial2)
* Adafruit NeoPixel
* 光センサー
* C++

## 動作内容

送信側

* 光センサーの値を取得
* 閾値を超えた場合は「ON」を送信
* 閾値を下回った場合は「OFF」を送信

受信側

* UARTでデータを受信
* 「ON」でNeoPixelを点灯
* 「OFF」でNeoPixelを消灯

## 学んだこと

* UART通信の基本的な仕組み
* TX/RX配線の接続方法
* UART受信バッファと available() の役割
* read() によるデータ取得
* 文字列比較時の改行コード(\r, \n)の扱い
* センサー値を利用したデバイス制御

## 今後の改善

* 状態変化時のみ送信して通信量を削減
* RGBカラー制御への対応
* センサー値そのものを送信
* JSON形式によるデータ通信
* OLED表示機能の追加
