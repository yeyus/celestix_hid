#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"

#define DIAL_PUSH 58
#define DIAL_RIGHT 59
#define DIAL_LEFT 60

#ifdef __cplusplus
extern "C"{
#endif  
int clx_lcd_write_line(hid_device *dev, unsigned char line_num, const char* text);
void clx_lcd_clear(hid_device *dev);
int clx_dial_wait_key(hid_device *dev, int milliseconds);
void clx_init(hid_device *dev);
void clx_close(hid_device *dev);
#ifdef __cplusplus
}
#endif
