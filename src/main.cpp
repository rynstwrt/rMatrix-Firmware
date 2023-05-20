#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define OLED_ADDR 0x3C

#define INTRO_FONT FreeSansBold9pt7b
#define INTRO_FONT_SIZE 2

#define MENU_FONT FreeSans9pt7b
#define MENU_FONT_SIZE 1
#define MENU_SPACING 15
#define MENU_PADDING 10

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String menuItems[] = {"EFFECT", "PALETTE", "LIGHT", "SPEED", "INTENSITY"};
int numMenuItems = 5;
int currentMenuIndex = 0;
bool menuItemSelected = false; // TODO:


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
    // display.setFont(&INTRO_FONT);
    display.setTextSize(INTRO_FONT_SIZE);

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

void createMenu()
{
    display.clearDisplay();
    display.setTextSize(MENU_FONT_SIZE);

    int y = MENU_PADDING;
    for (int i = 0; i < numMenuItems; ++i)
    {
        display.setCursor(MENU_PADDING, y);
        
        String text = (i == currentMenuIndex) ? ">" + menuItems[i] : menuItems[i];
        display.print(text);
        y += MENU_SPACING;
    }

    display.display();
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
    
    intro("rMatrix");    
    createMenu();
}

void loop()
{
    // createMenu();
}