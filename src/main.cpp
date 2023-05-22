#include <rmatrix.h>
#include <constants.h>


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
rMatrix rMtrx(display);


void setup()
{
    rMtrx.setup();
}


void loop()
{
    rMtrx.loop();
}