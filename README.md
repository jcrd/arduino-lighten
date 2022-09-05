# arduino-lighten

This repo contains the Arduino code for the hardware side of [lighten][lighten].

[lighten]: https://github.com/jcrd/lighten

It requires the following libraries:

- [Adafruit TSL2591 library](https://github.com/adafruit/Adafruit_TSL2591_Library)
- [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor)
- [Adafruit TinyUSB](https://github.com/adafruit/Adafruit_TinyUSB_Arduino) (The board used should have [built-in support][support] for this library)

[support]:  https://github.com/adafruit/Adafruit_TinyUSB_Arduino#cores-with-built-in-support

[This tutorial](https://learn.adafruit.com/adafruit-tsl2591/wiring-and-test#install-adafruit-tsl2591-library-2980796) explains how to set up the first two.

The **TinyUSB** library can be installed similarly:
> In the Arduino IDE menus, go to Sketch -> Include Library -> Manage Libraries, then search for and install Adafruit TinyUSB.

Now clone the **arduino-lighten** repo:

```sh
git clone https://github.com/jcrd/arduino-lighten.git
```

Open the `arduino-lighten.ino` file in the Arduino IDE and upload it to the board.

## License

This project is licensed under the MIT License (see [LICENSE](LICENSE)).
