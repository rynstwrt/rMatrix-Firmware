#include <rmatrix.h>


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
rMatrix matrix;


void setup()
{
    matrix.setDisplay(display);
    matrix.setup();
}


void loop()
{
    matrix.loop();
}