# ESP32 UART Weather Display

ESP32を2台使用し、天気予報APIから取得した天気情報をUART通信で送信し、OLEDディスプレイに表示するIoTプロジェクトです。
![display](./img/display.jpg)

## Features

- 天気予報APIから3日分の天気を取得
- JSONデータをArduinoJsonで解析
- 天気を英語へ変換してUART送信
- ESP32間でUART通信
- OLED(SSD1306)へ表示

## Hardware

- ESP32 ×2
- SSD1306 OLED Display (128×64)

## Libraries

- ArduinoJson
- Adafruit GFX Library
- Adafruit SSD1306
- WiFi
- HTTPClient

## Project Structure

Sender ESP32
- Wi-Fi接続
- Weather API取得
- JSON解析
- UART送信

Receiver ESP32
- UART受信
- OLED表示

## API

https://weather.tsukumijima.net/

