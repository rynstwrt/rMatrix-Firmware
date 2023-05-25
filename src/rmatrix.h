#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <constants.h>
#include <rmatrixfx.h>


class rMatrix
{
    private: 
        rMatrixFX rFX;

        Adafruit_SSD1306 display;

        unsigned long buttonTimer = 0;
        bool buttonActive = false;
        bool longPressActive = false;
        unsigned long lastDebounceTime = millis();

        String instructions[NUM_INSTRUCTIONS][2] = {
                    {"SHORT CLCK", "FOR NEXT"}, 
                    {"LONG CLCK", "TO CONFIRM"}};
        String menuItems[NUM_MENU_ITEMS] = {"EFFECT", "PALETTE", "BRIGHTNESS", "SPEED", "INTENSITY"};

        int currentMenuIndex = 0;
        bool menuItemSelected = false;

        int effect = DEFAULT_EFFECT;
        int palette = DEFAULT_PALETTE;
        int brightness = DEFAULT_BRIGHTNESS;
        int speed = DEFAULT_SPEED;
        int intensity = DEFAULT_INTENSITY;


    public:
        rMatrix();

        int* getCenterTextCoords(String text, bool isIntro);

        void playIntro();
        void drawMenu();
        void displayValuePage(int value, int maxValue);

        void moveSelection(bool incrementing);

        void onShortClick();
        void onLongClick();
        void detectButtonClicks();

        void setup();
        void loop();
};

