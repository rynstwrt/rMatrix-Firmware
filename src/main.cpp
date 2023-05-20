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

#define MENU_FONT_SIZE 1
#define MENU_PADDING 10
#define MENU_SPACING 3

#define VALUE_FONT_SIZE 2

#define DEFAULT_EFFECT 0
#define NUM_EFFECTS 10

#define DEFAULT_PALETTE 0
#define NUM_PALETTES 10

#define DEFAULT_BRIGHTNESS 255
#define MAX_BRIGHTNESS 255

#define DEFAULT_SPEED 255
#define MAX_SPEED 255

#define DEFAULT_INTENSITY 128
#define MAX_INTENSITY 255

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String menuItems[] = {"EFFECT", "PALETTE", "BRIGHTNESS", "SPEED", "INTENSITY"};
int numMenuItems = 5;
int currentMenuIndex = 0;
bool menuItemSelected = false; // TODO:

int effect = DEFAULT_EFFECT;
int palette = DEFAULT_PALETTE;
int brightness = DEFAULT_BRIGHTNESS;
int speed = DEFAULT_SPEED;
int intensity = DEFAULT_INTENSITY;

int* getCenterTextCoords(String text, bool isIntro)
{
    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(text.c_str(), 0, 0, &x, &y, &w, &h);

    int* coords = new int[2];
    coords[0] = (SCREEN_WIDTH - w) / 2;
    coords[1] = (isIntro ? SCREEN_HEIGHT + h : SCREEN_HEIGHT - h) / 2;
    return coords;
}

void intro(String text)
{
    display.clearDisplay();
    display.setFont(&INTRO_FONT);
    display.setTextSize(INTRO_FONT_SIZE);

    int* coords = getCenterTextCoords(text, true);
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
    display.setFont(NULL);
    display.setTextSize(MENU_FONT_SIZE);

    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(menuItems[0].c_str(), 0, 0, &x, &y, &w, &h);

    int yPos = MENU_PADDING;
    for (int i = 0; i < numMenuItems; ++i)
    {
        display.setCursor(MENU_PADDING, yPos);
        
        String text = (i == currentMenuIndex) ? ">" + menuItems[i] : menuItems[i];
        display.print(text);
        yPos += h + MENU_SPACING;
    }

    display.display();
}

void displayValue(int value, int maxValue)
{
    display.clearDisplay();
    display.setTextSize(VALUE_FONT_SIZE);

    String text = String(value) + "/" + maxValue;
    int* coords = getCenterTextCoords(text, false);
    display.setCursor(coords[0], coords[1]);
    delete[] coords;
    display.println(text);

    display.display();
}

void onRotate(bool incrementing)
{
    if (!menuItemSelected)
    {
        (incrementing) ? ++currentMenuIndex : --currentMenuIndex;
        if (currentMenuIndex == numMenuItems) 
            currentMenuIndex = 0;
        else if (currentMenuIndex < 0)
            currentMenuIndex = numMenuItems - 1;
        createMenu();
    }
    else 
    {
        switch(currentMenuIndex)
        {
            case 0:
                (incrementing) ? ++effect : --effect;
                effect %= NUM_EFFECTS + 1;
                displayValue(effect, NUM_EFFECTS);
                break;
            case 1:
                (incrementing) ? ++palette : --palette;
                palette %= NUM_PALETTES + 1;
                displayValue(palette, NUM_PALETTES);
                break;
            case 2: 
                (incrementing) ? ++brightness : --brightness;
                brightness %= MAX_BRIGHTNESS + 1;
                displayValue(brightness, MAX_BRIGHTNESS);
                break;
            case 3:
                (incrementing) ? ++speed : --speed;
                speed %= MAX_SPEED + 1;
                displayValue(speed, MAX_SPEED);
                break;
            case 4:
                (incrementing) ? ++intensity : --intensity;
                intensity %= MAX_INTENSITY + 1;
                displayValue(intensity, MAX_INTENSITY);
                break;
        }
    }
}

void onClick()
{
    menuItemSelected = !menuItemSelected;

    if (menuItemSelected)
    {
        switch(currentMenuIndex)
        {
            case 0:
                displayValue(effect, NUM_EFFECTS);
                break;
            case 1:
                displayValue(palette, NUM_PALETTES);
                break;
            case 2: 
                displayValue(brightness, MAX_BRIGHTNESS);
                break;
            case 3:
                displayValue(speed, MAX_SPEED);
                break;
            case 4:
                displayValue(intensity, MAX_INTENSITY);
                break;
        }
    }
    else 
    {
        createMenu();
    }
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
    onRotate(true);
    delay(1000);
    onClick();
    onRotate(true);
    delay(1000);
    onClick();
    delay(1000);
}