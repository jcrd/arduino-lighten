#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
#include "Adafruit_TinyUSB.h"

#define SDA 41
#define SCL 40
#define WIRE Wire1

#define REPORT_SIZE 16

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);

uint8_t const desc_hid_report[] = {TUD_HID_REPORT_DESC_GENERIC_INOUT(REPORT_SIZE)};
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 1, true);

int sensor = 0;
char char_buf[REPORT_SIZE];

void configure(void)
{
  tsl.setGain(TSL2591_GAIN_MED);
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
}

void setup(void)
{
  Wire.begin(SDA, SCL);

  usb_hid.setReportCallback(get_report, NULL);
  usb_hid.begin();

  if (tsl.begin())
  {
    sensor = 1;
    configure();
  }

  while (!TinyUSBDevice.mounted())
    delay(1);
}

int sense(void)
{
  if (sensor == 0)
    return -1.0;

  sensors_event_t ev;
  tsl.getEvent(&ev);

  if ((ev.light == 0) |
      (ev.light > 4294966000.0) |
      (ev.light < -4294966000.0))
  {
    /* If event.light = 0 lux the sensor is probably saturated */
    /* and no reliable data could be generated! */
    /* if event.light is +/- 4294967040 there was a float over/underflow */
    return -2.0;
  }

  return ev.light;
}

uint16_t get_report(uint8_t report_id, hid_report_type_t report_type,
                    uint8_t *buffer, uint16_t reqlen)
{
  dtostrf(sense(), 0, 0, char_buf);
  int i = 0;
  for (; i < REPORT_SIZE && char_buf[i] != '\0'; i++)
    buffer[i] = (uint8_t)char_buf[i];
  return i;
}

void loop(void)
{
}
