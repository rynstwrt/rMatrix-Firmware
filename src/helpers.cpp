#include <Arduino.h>
#include <constants.h>
#include <rmatrix.h>
#include <helpers.h>


/**
* Get the coordinates that would place printed text to the OLED
* in the center of the screen.
* 
* @param text The text to measure the size of.
* @param isIntro Whether this function is called from the intro function or not.
* @return A 2-element pointer array of the X and Y coordinates.
*/
int* Helpers::getCenterTextCoords(String text, bool isIntro)
{
    int16_t x, y;
    uint16_t w, h;
    rMatrix::getDisplay().getTextBounds(text.c_str(), 0, 0, &x, &y, &w, &h);

    int* coords = new int[2];
    coords[0] = (SCREEN_WIDTH - w) / 2;
    coords[1] = (isIntro ? SCREEN_HEIGHT + h : SCREEN_HEIGHT - h) / 2;
    return coords;
}