// /*
//  * The firmware for the rMatrix project, as seen on https://www.rmatrix.xyz. 
//  * 
//  * Developed by Ryan Stewart, A.K.A. Ryn.
//  * 
//  * This firmware is licensed under the 
//  * Creative Commons Attribution-NonCommercial-ShareAlike (CC-BY-NC-SA)
//  * license: http://creativecommons.org/licenses/by-nc-sa/4.0/
//  * 
//  * This firmware can be modified and distributed, but can NOT be used for
//  * commerical use. The licensing also requires that you release any 
//  * modified works of this firmware under the same license.
//  * 
//  * This firmware is distributed "as is" and without any warranty.
//  * 
//  * Check the LICENSE.md file for details about licensing.
// */
 

//  /*
//     === THE WIRING (WEMOS D1 MINI) ===
    
//     FOR THE OLED
//     ------------------------
//     OLED GND -> Wemos GND
//     OLED VCC -> Wemos 5V
//     OLED SCL -> Wemos D1 pin
//     OLED SDA -> Wemos D2 pin

//     FOR THE BUTTON
//     ------------------------
//     BUTTON + -> D5
//     BUTTON GND -> GND
//  */
 

// // INCLUDES
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <Fonts/FreeSansBold9pt7b.h>
// #include <Button2.h>
// #include <constants.h>


// // GLOBAL VARIABLES
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// const int numInstructions = 3;
// String instructions[numInstructions][2] = {
//     {"1 CLICK", "FOR NEXT"}, 
//     {"2 CLICKS", "FOR PREV"}, 
//     {"LONG CLICK", "TO CONFIRM"}};

// const int numMenuItems = 5;
// String menuItems[numMenuItems] = {"EFFECT", "PALETTE", "BRIGHTNESS", "SPEED", "INTENSITY"};
// int currentMenuIndex = 0;
// bool menuItemSelected = false;

// int effect = DEFAULT_EFFECT;
// int palette = DEFAULT_PALETTE;
// int brightness = DEFAULT_BRIGHTNESS;
// int speed = DEFAULT_SPEED;
// int intensity = DEFAULT_INTENSITY;

// Button2 button;



// /**
//  * Runs the intro sequence upon boot.
//  * 
//  * @param text The text to display for the intro sequence.
// */
// void intro()
// {
//     display.clearDisplay();
//     display.setFont(&INTRO_FONT);
//     display.setTextSize(INTRO_FONT_SIZE);

//     String rMatrix = "rMatrix";
//     int* coords = getCenterTextCoords(rMatrix, true);
//     display.setCursor(coords[0], coords[1]);
//     delete[] coords;

//     display.println(rMatrix);
//     bool inverted = false;
//     for (int i = 0; i < 5; ++i)
//     {
//         display.display();
//         delay(INTRO_FLASH_DELAY);
//         display.invertDisplay(inverted);
//         inverted = !inverted;
//     }

//     delay(INTRO_FLASH_FINISH_DELAY);
//     display.setFont(INSTRUCTIONS_FONT);
//     display.setTextSize(INSTRUCTIONS_FONT_SIZE);

//     for (int i = 0; i < numInstructions; ++i)
//     {
//         display.clearDisplay();
//         String* textParts = instructions[i];

//         for (int j = 0; j < 2; ++j)
//         {
//             String text = textParts[j];
//             int* coords = getCenterTextCoords(text, false);
//             int y = (j == 0) ? coords[1] : display.getCursorY() + MENU_SPACING / 3;
//             display.setCursor(coords[0], y);
//             delete[] coords;
//             display.println(text);
//         }

//         display.display();
//         delay(INTRO_INSTRUCTIONS_DELAY);  
//     }
// }


// /**
//  * Displays the selection menu with the menu item selected.
// */
// void createMenu()
// {
//     display.clearDisplay();
//     display.setFont(MENU_FONT);
//     display.setTextSize(MENU_FONT_SIZE);

//     int16_t x, y;
//     uint16_t w, h;
//     display.getTextBounds(menuItems[0].c_str(), 0, 0, &x, &y, &w, &h);

//     int yPos = MENU_SCREEN_PADDING;
//     for (int i = 0; i < numMenuItems; ++i)
//     {
//         display.setCursor(MENU_SCREEN_PADDING, yPos);
        
//         String text = (i == currentMenuIndex) ? ">" + menuItems[i] : menuItems[i];
//         display.print(text);
//         yPos += h + MENU_SPACING;
//     }

//     display.display();
// }


// /**
//  * Displays the values for each menu item in the center of the screen.
//  * 
//  * @param value The value to display in the center of the screen.
//  * @param maxValue The max that value can be.
// */
// void displayValue(int value, int maxValue)
// {
//     display.clearDisplay();
//     display.setTextSize(VALUE_FONT_SIZE);

//     String text = String(value) + "/" + maxValue;
//     int* coords = getCenterTextCoords(text, false);
//     display.setCursor(coords[0], coords[1]);
//     delete[] coords;
//     display.println(text);

//     display.display();
// }


// /**
//  * Called when the button is pressed once or twice. Either changes the 
//  * selected menu item or changes the value for the selected menu item.
//  * 
//  * @param incrementing If the rotary encoder was turned clockwise or not.
// */
// void moveSelection(bool incrementing)
// {
//     if (!menuItemSelected)
//     {
//         (incrementing) ? ++currentMenuIndex : --currentMenuIndex;
//         if (currentMenuIndex == numMenuItems) 
//             currentMenuIndex = 0;
//         else if (currentMenuIndex < 0)
//             currentMenuIndex = numMenuItems - 1;
//         createMenu();
//     }
//     else 
//     {
//         switch(currentMenuIndex)
//         {
//             case 0:
//                 (incrementing) ? ++effect : --effect;
//                 effect %= NUM_EFFECTS + 1;
//                 displayValue(effect, NUM_EFFECTS);
//                 break;
//             case 1:
//                 (incrementing) ? ++palette : --palette;
//                 palette %= NUM_PALETTES + 1;
//                 displayValue(palette, NUM_PALETTES);
//                 break;
//             case 2: 
//                 (incrementing) ? ++brightness : --brightness;
//                 brightness %= MAX_BRIGHTNESS + 1;
//                 displayValue(brightness, MAX_BRIGHTNESS);
//                 break;
//             case 3:
//                 (incrementing) ? ++speed : --speed;
//                 speed %= MAX_SPEED + 1;
//                 displayValue(speed, MAX_SPEED);
//                 break;
//             case 4:
//                 (incrementing) ? ++intensity : --intensity;
//                 intensity %= MAX_INTENSITY + 1;
//                 displayValue(intensity, MAX_INTENSITY);
//                 break;
//         }
//     }
// }


// /**
//  * Called when the button is clicked once. Moves the selected menu 
//  * item or the value of a menu item forward.
//  * 
//  * @param btn The button clicked.
// */
// void onSingleClick(Button2 &btn)
// {
//     Serial.println("single click");
//     moveSelection(true);
// }


// /**
//  * Called when the button is double clicked. Moves the selected
//  * menu item or the value of a menu item backward.
//  * 
//  * @param btn The button clicked.
// */
// void onDoubleClick(Button2 &btn)
// {
//     Serial.println("double click");
//     moveSelection(false);
// }


// /**
//  * Called when the button is held down. Confirms the currently
//  * selected item in the menu system.
//  * 
//  * @param btn The button clicked.
// */
// void onLongClick(Button2 &btn)
// {
//     Serial.println("long click");

//     menuItemSelected = !menuItemSelected;

//     if (menuItemSelected)
//     {
//         switch(currentMenuIndex)
//         {
//             case 0:
//                 displayValue(effect, NUM_EFFECTS);
//                 break;
//             case 1:
//                 displayValue(palette, NUM_PALETTES);
//                 break;
//             case 2: 
//                 displayValue(brightness, MAX_BRIGHTNESS);
//                 break;
//             case 3:
//                 displayValue(speed, MAX_SPEED);
//                 break;
//             case 4:
//                 displayValue(intensity, MAX_INTENSITY);
//                 break;
//         }
//     }
//     else 
//     {
//         createMenu();
//     }
// }


// /**
//  * The setup function. Initializes the OLED, plays the intro, and
//  * then displays the menu.
// */
// void setup()
// {
//     Serial.begin(SERIAL_SPEED);

//     if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
//     {
//         Serial.println(F("SSD1306 allocation failed"));
//         for (;;); // Loop forever
//     }

//     Serial.println("SSD1306 initialized!");

//     display.setTextColor(SSD1306_WHITE);
//     intro();    
//     createMenu();

//     button.begin(BUTTON_PIN, INPUT_PULLUP, false);
//     button.setLongClickTime(BUTTON_LONG_PRESS_THRESHOLD);
//     button.setDoubleClickTime(BUTTON_DOUBLE_CLICK_THRESHOLD);
//     button.setClickHandler(onSingleClick);
//     button.setDoubleClickHandler(onDoubleClick);
//     button.setLongClickDetectedHandler(onLongClick);
// }


// /**
//  * The loop function.
// */
// void loop()
// {
//     button.loop();
// }