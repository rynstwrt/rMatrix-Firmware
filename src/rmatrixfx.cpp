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
 * The first effect. Fills up the matrix.
*/
void rMatrixFX::effect1()
{
    Serial.println("1");

    if (millis() - fx1Timer > FX1_DEBOUNCE)
    {
        leds[fx1Index] = ColorFromPalette(*palette, fx1Index);
        FastLED.show();
        
        ++fx1Index;
        fx1Timer = millis();
    }

    if (fx1Index == NUM_LEDS)
    {
        fx1Index = 0;
        FastLED.clear();
        FastLED.show();
    }
}


/**
 * The second effect.
*/
void rMatrixFX::effect2()
{
    Serial.println("2");
}


/**
 * The third effect.
*/
void rMatrixFX::effect3()
{
    Serial.println("3");
}


/**
 * The fourth effect.
*/
void rMatrixFX::effect4()
{
    Serial.println("4");   
}