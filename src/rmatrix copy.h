#pragma once


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Button2.h>
#include <helpers.h>
#include <constants.h>


class rMatrix
{
    private: 
        static Adafruit_SSD1306 display;
        static Button2 button;

        static String instructions[NUM_INSTRUCTIONS][2];

        static const String menuItems[NUM_MENU_ITEMS] = {"EFFECT", "PALETTE", "BRIGHTNESS", "SPEED", "INTENSITY"};

        static int currentMenuIndex;
        static bool menuItemSelected;

        static int effect;
        static int palette;
        static int brightness;
        static int speed;
        static int intensity;


    public:
        static void setDisplay(Adafruit_SSD1306 oled)
        {
            display = oled;

            rMatrix::instructions = {
                    {"1 CLICK", "FOR NEXT"}, 
                    {"2 CLICKS", "FOR PREV"}, 
                    {"LONG CLICK", "TO CONFIRM"}};

            currentMenuIndex = 0;
            menuItemSelected = false;

            effect = DEFAULT_EFFECT;
            palette = DEFAULT_PALETTE;
            brightness = DEFAULT_BRIGHTNESS;
            speed = DEFAULT_SPEED;
            intensity = DEFAULT_INTENSITY;
        }

        static Adafruit_SSD1306 getDisplay()
        {
            return display;
        }

        static void setButton(Button2 btn)
        {
            button = btn;
        }

        static Button2 getButton()
        {
            return button;
        }

        static void playIntro();
        static void drawMenu();
        static void displayValuePage(int value, int maxValue);

        static void moveSelection(bool incrementing);
        static void sendSingleClick(Button2 &btn);
        static void sendDoubleClick(Button2 &btn);
        static void sendLongClick(Button2 &btn);
};

