#define FASTLED_INTERNAL

#include <constants.h>
#include <FastLED.h>


class rMatrixFX
{
    private:
        CRGB leds[NUM_LEDS];

        int effect = DEFAULT_EFFECT;
        int palette = DEFAULT_PALETTE;
        int brightness = DEFAULT_BRIGHTNESS * VALUE_STEP;
        int speed = DEFAULT_SPEED * VALUE_STEP;
        int intensity = DEFAULT_INTENSITY * VALUE_STEP;

        bool changeHappened = false;

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
            effect = fx;
        }

        void setPalette(int p)
        {
            palette = p;
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