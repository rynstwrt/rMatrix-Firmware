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
        int intensity = DEFAULT_INTENSITY * VALUE_STEP;

        bool changeHappened = false;


        // Palette values
        TProgmemRGBPalette16 palettes[NUM_PALETTES] = {*CloudColors_p,
                *LavaColors_p, *OceanColors_p, *ForestColors_p, *RainbowColors_p,
                *RainbowStripeColors_p, *PartyColors_p, *HeatColors_p};

        TProgmemHSVPalette16* palette = &(palettes[DEFAULT_PALETTE]);


        // Pointers to all the effect functions.
        typedef void (rMatrixFX::*FXFunction)();
        FXFunction effectFunctions[NUM_EFFECTS] = {&rMatrixFX::effect1, 
                &rMatrixFX::effect2, &rMatrixFX::effect3, &rMatrixFX::effect4};

        // Effect 1 variables.
        int fx1Index = 0;
        int fx1Timer = millis();


    public:
        rMatrixFX();

        void setEffect(int fx)
        {
            effectIndex = fx;
        }

        void setPalette(int p)
        {
            paletteIndex = p;
            palette = &(palettes[paletteIndex]);
        }

        void setBrightness(int bri)
        {
            brightness = bri;
        }

        void setSpeed(int s)
        {
            speed = s;
        }

        void setIntensity(int i)
        {
            intensity = i;
        }

        void update();

        void effect1();
        void effect2();
        void effect3();
        void effect4();
};