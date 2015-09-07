#include "celestix_lcd.h"

#define CELESTIX_VENDOR_ID 0x0CB6
#define CELESTIX_PRODUCT_ID 0x0002

#define HID_DIAL_REPORT_ID 1
#define HID_DIAL_KEY_REPORT_CMD 2


#define HID_LCD_REPORT_ID 2
#define HID_LCD_REPORT_SIZE 89
#define HID_LCD_WRITE_LINE_CMD 0x28

int clx_lcd_write_line(hid_device *dev, unsigned char line_num, const char* text)
{
  int res;
  unsigned char buf[88];
  
  buf[0] = HID_LCD_REPORT_ID;
  buf[1] = 0;
  buf[2] = 0;
  buf[3] = line_num;
  buf[4] = HID_LCD_WRITE_LINE_CMD;
  buf[5] = 0;
  buf[6] = 0;
  buf[7] = 0;
  
  strncpy((char *)buf+8, text, 40);

  // Pad with spaces up to 40 chars
  int i;
  for(i = 8 + strlen(text); i < (8 + 40); i++)
  {
    buf[i] = 0x20;
  }

  res = hid_write(dev, buf, 88);
  return res;
}

void clx_lcd_clear(hid_device *dev)
{
  clx_lcd_write_line(dev, 0, "");
  clx_lcd_write_line(dev, 1, "");
}

int clx_dial_wait_key(hid_device *dev, int milliseconds)
{
  unsigned char buf[10];
  int res = 0;
  res = hid_read_timeout(dev, buf, 9, milliseconds);
  if (res == 3 && buf[0] == HID_DIAL_REPORT_ID && buf[1] == HID_DIAL_KEY_REPORT_CMD)
  {
    res = buf[2];
  }
  return res;
}

void clx_init(hid_device *dev)
{
  dev = hid_open(CELESTIX_VENDOR_ID, CELESTIX_PRODUCT_ID, NULL);
}

void clx_close(hid_device *dev)
{
  hid_close(dev);
}
