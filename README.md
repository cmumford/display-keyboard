# Display Keyboard

This project is the hardware design and software for a USB keyboard with an
integrated touch display.

Hardware features:

* Mechanical keys.
* [FeatherS2](https://unexpectedmaker.com/shop/feathers2-esp32-s2). This is a
  [ESP32-S2](https://www.espressif.com/sites/default/files/documentation/esp32-s2_datasheet_en.pdf)
  based embedded development board.
* 2.8" LCD capacitive [touch display](https://www.adafruit.com/product/2770).
* 0.91" vertical [OLED display](https://www.aliexpress.com/item/32672229793.html)
  for volume display.
* Volume control knob.

The FeatherS2 conforms to the [Adafruit Feather](https://www.adafruit.com/feather)
requirements, and allows for the possibility of replacing that MCU with another
Feather with little (if any) PCB rework.

## Hardware Design

Design is done in [KeyCad](https://kicad.org/). Files are located in
the [pcb](pcb) directory.

## Software Requirements

* [ESP-IDF](https://docs.espressif.com/)
* [VS Code extensions](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/vscode-setup.html)
  (optional)

## Getting Code

```sh
git clone https://github.com/BigMumf/display-keyboard.git
./make.py submodules
```

**Note**: Because this project makes use of new features (USB) of the ESP32-S2
          it requires a version of ESP-IDF more recent than v4.2. At present
          this means the "master" branch of esp-idf.

## Building

Configuration (GPIO pins, etc.) is stored in the sdkconfig file. This is
set using menuconfig as so:

```sh
./make.py config
```

Build and flash to the attached ESP32-S2 device as so:

```sh
. $HOME/esp/esp-idf/export.sh # only do this once
./make.py build && ./make.py flash
```
