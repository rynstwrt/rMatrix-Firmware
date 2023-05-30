#if __cplusplus > 199711L 
    #define register
#endif

#include <Arduino.h>
#include <rmatrixfx.h>


/*=====================================================*/
/*------------------ CLASS FUNCTIONS ------------------*/
/*=====================================================*/
/**
 * The default constructor of rMatrixFX
*/
rMatrixFX::rMatrixFX() 
{ 
    FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
    FastLED.clear();
    FastLED.show();
}


/**
 * Called continuously. 
 * Where the logic for each effect occurs.
*/
void rMatrixFX::update()
{
    FastLED.setBrightness(brightness);

    FXFunction func = effectFunctions[effectIndex];
    (this->*func)();
}


/*=============================================*/
/*------------------ EFFECTS ------------------*/
/*=============================================*/
/**
 * The first effect. 
 * Solid.
*/
void rMatrixFX::effect1()
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        leds[i] = ColorFromPalette(*palettes[paletteIndex], colorStep * i);
    }
    FastLED.show();
}


/**
 * The second effect. 
 * Blink effect.
*/
void rMatrixFX::effect2()
{
    if (millis() - ledTimer > FX2_DEBOUNCE)
    {
        ledBoolean = !ledBoolean;

        if (ledBoolean)
        {
            for (int i = 0; i < NUM_LEDS; ++i)
            {
                leds[i] = ColorFromPalette(*palettes[paletteIndex], colorStep * i);
            }
        }
        else 
        {
            FastLED.clear();
        }

        FastLED.show();
        ledTimer = millis();
    }
}


/**
 * The third effect.
 * Theater chase
*/
void rMatrixFX::effect3()
{
    if (millis() - ledTimer > FX3_DEBOUNCE)
    {
        ledBoolean = !ledBoolean;

        FastLED.clear();
        for (int i = 0; i < NUM_LEDS; ++i)
        {
            if (i % 2 == 0 && ledBoolean)
            {
                leds[i] = ColorFromPalette(*palettes[paletteIndex], colorStep * i);
            }
            else if (i % 2 != 0 && !ledBoolean)
            {
                leds[i] = ColorFromPalette(*palettes[paletteIndex], colorStep * i);
            }
        }

        FastLED.show();
        ledTimer = millis();
    }
}


/**
 * The fourth effect.
 * Fill up with color then fill up with black.
*/
void rMatrixFX::effect4()
{
    if (millis() - ledTimer > FX4_DEBOUNCE)
    {
        if (!ledBoolean)
        {
            leds[ledIndex] = ColorFromPalette(*palettes[paletteIndex], colorStep * ledIndex);
        }
        else 
        {
            leds[ledIndex] = CRGB::Black;
        }

        FastLED.show();
        
        ++ledIndex;
        if (ledIndex == NUM_LEDS)
        {
            ledIndex = 0;
            ledBoolean = !ledBoolean;
        }

        ledTimer = millis();
    }
}