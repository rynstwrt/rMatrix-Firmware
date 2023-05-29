#if __cplusplus >= 201703L
    #define register 
#endif


#include <constants.h>
#include <FastLED.h>


class rMatrixFX
{
    private:
        CRGB leds[NUM_LEDS];

        int effectIndex = DEFAULT_EFFECT;
        int paletteIndex = DEFAULT_PALETTE;
        int brightness = DEFAULT_BRIGHTNESS * VALUE_STEP;
        int speed = DEFAULT_SPEED * VALUE_STEP;

        bool changeHappened = false;

        int colorStep = floor(255 / NUM_LEDS);

        unsigned long ledTimer = millis();
        int ledIndex = 0;
        bool ledBoolean = false;


        // Palette values
        const TProgmemRGBPalette16* palettes[NUM_PALETTES] = {
                &RainbowColors_p, &CloudColors_p, &LavaColors_p, 
                &OceanColors_p, &ForestColors_p, &RainbowStripeColors_p, 
                &PartyColors_p, &HeatColors_p};


        // Pointers to all the effect functions.
        typedef void (rMatrixFX::*FXFunction)();
        FXFunction effectFunctions[NUM_EFFECTS] = {&rMatrixFX::effect1, 
                &rMatrixFX::effect2, &rMatrixFX::effect3, &rMatrixFX::effect4};
 

    public:
        rMatrixFX();

        void resetEffect()
        {
            FastLED.clear();
            FastLED.show();
            
            ledTimer = millis();
            ledIndex = 0;
            ledBoolean = false;
        }

        void setEffect(int fx)
        {
            effectIndex = fx;
            resetEffect();
        }

        void setPalette(int p)
        {
            paletteIndex = p;
            resetEffect();
        }

        void setBrightness(int bri)
        {
            brightness = bri * VALUE_STEP;
            FastLED.setBrightness(brightness);
        }

        void setSpeed(int s)
        {
            speed = s * VALUE_STEP;
        }

        void update();

        void effect1();
        void effect2();
        void effect3();
        void effect4();
};