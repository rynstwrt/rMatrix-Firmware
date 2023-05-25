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
    if (changeHappened)
    {
        // TODO: set brightness, speed, intensity, effect, palette, etc
        changeHappened = false;
    }

    FastLED.setBrightness(brightness);

    FXFunction func = effectFunctions[effectIndex];
    (this->*func)();
}



/*=============================================*/
/*------------------ EFFECTS ------------------*/
/*=============================================*/
/**
 * The first effect. 
 * Fills up the matrix pixel by pixel.
*/
void rMatrixFX::effect1()
{
    if (millis() - ledTimer > FX1_DEBOUNCE)
    {
        float colorIndex = 255 * ledIndex / NUM_LEDS; 
        leds[ledIndex] = ColorFromPalette(*palettes[paletteIndex], colorIndex);
        FastLED.show();
        
        ++ledIndex;
        if (ledIndex == NUM_LEDS)
        {
            ledIndex = 0;
            FastLED.clear();
            FastLED.show();
        }

        ledTimer = millis();
    }
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
                leds[i] = ColorFromPalette(*palettes[paletteIndex], i);
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
                leds[i] = ColorFromPalette(*palettes[paletteIndex], i);
            }
            else if (i % 2 != 0 && !ledBoolean)
            {
                leds[i] = ColorFromPalette(*palettes[paletteIndex], i);
            }
        }

        FastLED.show();
        ledTimer = millis();
    }
}


/**
 * The fourth effect.
 * Rainbow.
*/
void rMatrixFX::effect4()
{
    if (millis() - ledTimer > FX4_DEBOUNCE)
    {
        for (int i = 0; i < NUM_LEDS; ++i)
        {
            leds[i] = ColorFromPalette(*palettes[paletteIndex], i + ledIndex);
        }

        ledTimer = millis();
    }
}