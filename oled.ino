#include <U8x8lib.h>

U8X8_SSD1309_128X64_NONAME2_SW_I2C oled(OledPin::SCL, OledPin::SDA);

void initOled() {
  oled.begin();
}

void disp(char s[]) {
  oled.clear();
  oled.setFont(u8x8_font_8x13_1x2_f);
  oled.print(s);
}
