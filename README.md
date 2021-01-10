# Cosplay: Fett Display

Display module for a Boba Fett costume. Uses a 2" TFT display instead of the traditional
segment display/LED bar graph combination. The goal behind this choice was a thinner electronics
package and the ability to make some customizations not afforded by a 7-segment display.


## Components
- Adafruit FLORA v3 (ATmega32u4 Chip)
- Adafruit 2.0" 320x240 Color IPS TFT Display (ST7789 TFT Driver)


## Required Libraries
- Adafruit GFX Library
- Adafruit BusIO
- Adafruit ST7735 and ST7789 Library


## Development
1. Install `arduino-cli` if it is not yet installed.
2. Create configuration file if you have not yet created one:
    ```
    arduino-cli config init
    ```
3. Install board support for the Adafruit FLORA:
    ```
    arduino-cli config add board_manager.additional_urls https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
    arduino-cli core update-index
    arduino-cli core install adafruit:avr
    ```
4. Add dependent libraries:
    ```
    arduino-cli lib update-index
    arduino-cli lib install "Adafruit GFX Library"
    arduino-cli lib install "Adafruit BusIO"
    arduino-cli lib install "Adafruit ST7735 and ST7789 Library"
    ```

### Compile
The sketch can be compiled with make, assuming the steps in [development](#development) have been followed.

    make clean      # Delete build files
    make            # Build sketch
    make install    # Upload sketch to Adafruit FLORA


## License
Copyright (c) 2021 Winston Astrachan. Available under the terms of the MIT license.
Software libraries and utilities contained within this project are copyright their respective authors.
