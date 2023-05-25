#pragma once


// OLED DEFINITIONS
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C

// FONT DEFINITIONS
#define INTRO_FONT FreeSansBold9pt7b
#define INTRO_FONT_SIZE 2
#define INSTRUCTIONS_FONT NULL
#define INSTRUCTIONS_FONT_SIZE 2
#define MENU_FONT NULL
#define MENU_FONT_SIZE 1
#define MENU_SCREEN_PADDING 10
#define MENU_SPACING 3
#define VALUE_FONT_SIZE 2

// INTRO DEFINITIONS
#define INTRO_FLASH_DELAY 150
#define INTRO_FLASH_FINISH_DELAY 650
#define INTRO_INSTRUCTIONS_DELAY 1100

// MENU VALUE DEFINITIONS
#define DEFAULT_EFFECT 0
#define NUM_EFFECTS 4
#define DEFAULT_PALETTE 0
#define NUM_PALETTES 10

#define NUM_INSTRUCTIONS 2
#define NUM_MENU_ITEMS 5

#define MAX_SHOWN_VALUE 9
#define VALUE_STEP ceil(255 / MAX_SHOWN_VALUE)

#define DEFAULT_BRIGHTNESS MAX_SHOWN_VALUE - 1
#define MAX_BRIGHTNESS MAX_SHOWN_VALUE

#define DEFAULT_SPEED MAX_SHOWN_VALUE - 1
#define MAX_SPEED MAX_SHOWN_VALUE

#define DEFAULT_INTENSITY (MAX_SHOWN_VALUE - 1) / 2
#define MAX_INTENSITY MAX_SHOWN_VALUE

// LED DEFINITIONS
#define LED_PIN 2
#define NUM_LEDS 128
#define LED_TYPE WS2812B
#define LED_COLOR_ORDER GRB

// BUTTON DEFINITIONS
#define BUTTON_PIN 14
#define BUTTON_DEBOUNCE 50
#define BUTTON_LONG_PRESS_THRESHOLD 300

// MISCELLANEOUS DEFINITIONS
#define SERIAL_SPEED 115200

// EFFECT DEFINITIONS
#define FX1_DEBOUNCE 200