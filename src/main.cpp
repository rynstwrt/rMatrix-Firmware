#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String menuItems[] = {"EFFECT", "PALETTE", "BRIGHTNESS", "SPEED", "INTENSITY"};
int numMenuItems = 5;
int currentMenuItem = 0;

int* getCenterTextCoords(String text)
{
    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(text.c_str(), 0, 0, &x, &y, &w, &h);

    int* coords = new int[2];
    coords[0] = (SCREEN_WIDTH - w) / 2;
    coords[1] = (SCREEN_HEIGHT - h) / 2;
    return coords;
}

void intro(String text)
{
    display.clearDisplay();

    int* coords = getCenterTextCoords(text);
    display.setCursor(coords[0], coords[1]);
    delete[] coords;

    display.println(text);

    bool inverted = false;
    for (int i = 0; i < 5; ++i)
    {
        display.display();
        delay(200);
        display.invertDisplay(inverted);
        inverted = !inverted;
    }

    delay(750);
}

void setup()
{
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Loop forever
    }
    Serial.println("SSD1306 initialized!");

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    intro("rMatrix");    
}

void loop()
{
    display.clearDisplay();
    display.setCursor(0, 0);

    for (int i = 0; i < numMenuItems; ++i)
    {
        String text = (i == currentMenuItem) ? "> " + menuItems[i] : menuItems[i];
        display.println(text);
    }

    display.display();
    delay(50);

    // int16_t x, y;
    // uint16_t w, h;
    // display.getTextBounds(menuItems[0], 0, 0, &x, &y, &w, &h);

    // for (int i = 0; i < numMenuItems; ++i)
    // {
    //     // display.setCursor(0, i * h);
    //     String text = (i == currentMenuItem) ? "> " + menuItems[i] : menuItems[i];
    //     display.print
    // }
}