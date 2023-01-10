# arduino-lighten

This repo contains the Arduino code for the hardware side of [lighten][lighten].

[lighten]: https://github.com/jcrd/lighten

# Setup

## Arduino

The following Arduino libraries are required:

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

## udev

Appropriate udev rules must be configured to access the HID device.

Create a `.rules` file in `/etc/udev/rules.d` that looks like:

```txt
SUBSYSTEM=="usb", ATTR{idVendor}=="239a", ATTR{idProduct}=="8111", MODE="0660", GROUP="plugdev", TAG+="uaccess", TAG+="udev-acl"
KERNEL=="hidraw*", ATTRS{idVendor}=="239a", ATTRS{idProduct}=="8111", MODE="0660", GROUP="plugdev", TAG+="uaccess", TAG+="udev-acl"
```

where the `idVendor` and `idProduct` attributes reflect the values found using `lsusb`:

```txt
Bus 005 Device 002: ID 239a:8111 Adafruit QT Py ESP32-S2
```

The sixth column contains the IDs in the format: `vendor:product`.

See [this section][udev] of the [hidapi Python library][hidapi] documentation for more information.

[udev]: https://pypi.org/project/hidapi/#udev-rules
[hidapi]: https://github.com/trezor/cython-hidapi

## License

This project is licensed under the MIT License (see [LICENSE](LICENSE)).
