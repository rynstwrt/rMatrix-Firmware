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
    Serial.println("1");

    if (millis() - ledTimer > FX1_DEBOUNCE)
    {
        leds[ledIndex] = ColorFromPalette(*palette, ledIndex);
        FastLED.show();
        
        ++ledIndex;
        ledTimer = millis();
    }

    if (ledIndex == NUM_LEDS)
    {
        ledIndex = 0;
        FastLED.clear();
        FastLED.show();
    }
}


/**
 * The second effect. 
 * Blink effect.
*/
void rMatrixFX::effect2()
{
    Serial.println("2");

    if (millis() - ledTimer > FX2_DEBOUNCE)
    {
        ledBoolean = !ledBoolean;

        if (ledBoolean)
        {
            for (int i = 0; i < NUM_LEDS; ++i)
            {
                leds[i] = ColorFromPalette(*palette, i);
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
    Serial.println("3");

    if (millis() - ledTimer > FX3_DEBOUNCE)
    {
        ledBoolean = !ledBoolean;

        FastLED.clear();   
        for (int i = 0; i < NUM_LEDS; ++i)
        {
            if (i % 2 == 0 && ledBoolean)
            {
                leds[i] = ColorFromPalette(*palette, i);
            }
            else if (i % 2 != 0 && !ledBoolean)
            {
                leds[i] = ColorFromPalette(*palette, i);
            }
        }

        FastLED.show();
        ledTimer = millis();
    }
}


/**
 * The fourth effect.
*/
void rMatrixFX::effect4()
{
    Serial.println("4");   
}