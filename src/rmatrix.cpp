#include <rmatrix.h>


/**
 * Default constructor for rMatrix. Initializes the Adafruit_SSD1306
 * display variable.
*/
rMatrix::rMatrix() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}


/**
* Get the coordinates that would place printed text to the OLED
* in the center of the screen.
* 
* @param display The SSD1306 used by the rMatrix instance.
* @param text The text to measure the size of.
* @param isIntro Whether this function is called from the intro function or not.
*  A 2-element pointer array of the X and Y coordinates.
*/
int* rMatrix::getCenterTextCoords(String text, bool isIntro)
{
    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(text.c_str(), 0, 0, &x, &y, &w, &h);

    int* coords = new int[2];
    coords[0] = (SCREEN_WIDTH - w) / 2;
    coords[1] = (isIntro ? SCREEN_HEIGHT + h : SCREEN_HEIGHT - h) / 2;
    return coords;
}


/**
 * Runs the intro sequence upon boot.
 */
void rMatrix::playIntro()
{
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE); 
    display.setFont(&INTRO_FONT);
    display.setTextSize(INTRO_FONT_SIZE);

    String nameText = "rMatrix";
    int* coords = getCenterTextCoords(nameText, true);
    display.setCursor(coords[0], coords[1]);
    delete[] coords;

    display.println(nameText);
    bool inverted = false;
    for (int i = 0; i < 5; ++i)
    {
        display.display();
        delay(INTRO_FLASH_DELAY);
        display.invertDisplay(inverted);
        inverted = !inverted;
    }

    delay(INTRO_FLASH_FINISH_DELAY);
    display.setFont(INSTRUCTIONS_FONT);
    display.setTextSize(INSTRUCTIONS_FONT_SIZE);

    for (int i = 0; i < NUM_INSTRUCTIONS; ++i)
    {
        display.clearDisplay();
        String* textParts = instructions[i];

        for (int j = 0; j < 2; ++j)
        {
            String text = textParts[j];
            int* coords = getCenterTextCoords(text, false);
            int y = (j == 0) ? coords[1] : display.getCursorY() + MENU_SPACING / 3;
            display.setCursor(coords[0], y);
            display.println(text);
        }

        display.display();
        delay(INTRO_INSTRUCTIONS_DELAY);  
    }
}


/**
 * Displays the selection menu with the menu item selected.
*/
void rMatrix::drawMenu()
{
    display.clearDisplay();
    display.setFont(MENU_FONT);
    display.setTextSize(MENU_FONT_SIZE);

    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(menuItems[0].c_str(), 0, 0, &x, &y, &w, &h);

    int yPos = MENU_SCREEN_PADDING;
    for (int i = 0; i < NUM_MENU_ITEMS; ++i)
    {
        display.setCursor(MENU_SCREEN_PADDING, yPos);
        
        String text = (i == currentMenuIndex) ? ">" + menuItems[i] : menuItems[i];
        display.print(text);
        yPos += h + MENU_SPACING;
    }

    display.display();
}


/**
 * Displays the values for each menu item in the center of the screen.
 * 
 * @param value The value to display in the center of the screen.
 * @param maxValue The max that value can be.
*/
void rMatrix::displayValuePage(int value, int maxValue)
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


/**
 * Called when the button is pressed once or twice. Either changes the 
 * selected menu item or changes the value for the selected menu item.
 * 
 * @param incrementing If the rotary encoder was turned clockwise or not.
*/
void rMatrix::moveSelection(bool incrementing)
{
    if (!menuItemSelected)
    {
        (incrementing) ? ++currentMenuIndex : --currentMenuIndex;
        if (currentMenuIndex == NUM_MENU_ITEMS) 
            currentMenuIndex = 0;
        else if (currentMenuIndex < 0)
            currentMenuIndex = NUM_MENU_ITEMS - 1;
        drawMenu();
    }
    else 
    {
        switch(currentMenuIndex)
        {
            case 0:
                (incrementing) ? ++effect : --effect;
                effect %= NUM_EFFECTS + 1;
                displayValuePage(effect, NUM_EFFECTS);
                break;
            case 1:
                (incrementing) ? ++palette : --palette;
                palette %= NUM_PALETTES + 1;
                displayValuePage(palette, NUM_PALETTES);
                break;
            case 2: 
                (incrementing) ? ++brightness : --brightness;
                brightness %= MAX_BRIGHTNESS + 1;
                displayValuePage(brightness, MAX_BRIGHTNESS);
                break;
            case 3:
                (incrementing) ? ++speed : --speed;
                speed %= MAX_SPEED + 1;
                displayValuePage(speed, MAX_SPEED);
                break;
            case 4:
                (incrementing) ? ++intensity : --intensity;
                intensity %= MAX_INTENSITY + 1;
                displayValuePage(intensity, MAX_INTENSITY);
                break;
        }
    }
}


/**
 * Called when the button is short clicked. Moves the selected menu 
 * item or the value of a menu item forward.
*/
void rMatrix::onShortClick()
{
    Serial.println("short click");
    moveSelection(true);
}


/**
 * Called when the button is long clicked. Confirms the currently
 * selected item in the menu system.
*/
void rMatrix::onLongClick()
{
    Serial.println("long click");

    menuItemSelected = !menuItemSelected;

    if (menuItemSelected)
    {
        switch(currentMenuIndex)
        {
            case 0:
                displayValuePage(effect, NUM_EFFECTS);
                break;
            case 1:
                displayValuePage(palette, NUM_PALETTES);
                break;
            case 2: 
                displayValuePage(brightness, MAX_BRIGHTNESS);
                break;
            case 3:
                displayValuePage(speed, MAX_SPEED);
                break;
            case 4:
                displayValuePage(intensity, MAX_INTENSITY);
                break;
        }
    }
    else 
    {
        drawMenu();
    }
}


/**
 * Function called every update that checks for short and long clicks.
 * Short click detected -> rMatrix::onShortClick()
 * Long click detected -> rMatrix::onLongClick()
*/
void rMatrix::detectButtonClicks()
{

}


/**
 * The setup function. Initializes the OLED, plays the intro, and
 * then displays the menu.
*/
void rMatrix::setup()
{
    Serial.begin(SERIAL_SPEED);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Loop forever
    }

    playIntro();
    drawMenu();
}


/**
 * The loop function.
*/
void rMatrix::loop()
{
}