#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
#include "Adafruit_TinyUSB.h"

#define DELAY 1000

#define SDA 41
#define SCL 40
#define WIRE Wire1

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);

uint8_t const desc_hid_report[] = {TUD_HID_REPORT_DESC_GENERIC_INOUT(64)};
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, true);

int sensor = 0;
char buffer[64];

void configure(void)
{
  tsl.setGain(TSL2591_GAIN_MED);
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
}

void setup(void)
{
  Wire.begin(SDA, SCL);
  usb_hid.begin();

  if (tsl.begin())
  {
    sensor = 1;
    configure();
  }

  while (!TinyUSBDevice.mounted())
    delay(1);
}

void report(double d)
{
  dtostrf(d, 0, 2, buffer);
  usb_hid.sendReport(0, buffer, strlen(buffer));
}

void sense(void)
{
  sensors_event_t ev;
  tsl.getEvent(&ev);

  if ((ev.light == 0) |
      (ev.light > 4294966000.0) |
      (ev.light < -4294966000.0))
  {
    /* If event.light = 0 lux the sensor is probably saturated */
    /* and no reliable data could be generated! */
    /* if event.light is +/- 4294967040 there was a float over/underflow */
    report(-2);
    return;
  }

  report(ev.light);
}

void loop(void)
{
  if (sensor)
    sense();
  else
    report(-1);

  delay(DELAY);
}
