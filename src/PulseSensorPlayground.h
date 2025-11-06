

![heart](https://raw.githubusercontent.com/WorldFamousElectronics/PulseSensorPlayground/master/extras/images/pulsesensor_amped_arduino_uno.jpg)

> **v2.1.0** – Now with less sketch-crashing, more blinky lights, and actual comments that make sense.

---

### "I just want my LED to blink with my heart" – This is for YOU.

You bought a cute little green heart sensor, watched the YouTube video, copy-pasted the example...  
and then spent 4 hours wondering why `BPM = 0` forever.

We’ve all been there. This library fixes that.

---

## Features (that actually work)

- Works with **1 sensor** or **20 sensors** (yes really)
- Auto-blinks an LED on every heartbeat (because dopamine)
- Auto-fades a PWM LED (because it's prettier)
- 500Hz sampling (that's every 2ms – medical-grade-ish)
- Hardware timer on fancy boards, software timer on your dusty Uno
- Serial Plotter ready **out of the box**
- Processing visualizer support (remember that psychedelic heart?)
- Pause/resume sampling (great for when you’re uploading new code while wearing the sensor)
- No more "ghost beats" when you breathe funny

---

## Quick Start (copy-paste this, thank me later)

```cpp
#include <PulseSensorPlayground.h>

const int PULSE_PIN = A0;
const int BLINK_PIN = 13;
const int FADE_PIN = 5;

PulseSensorPlayground pulse;  // one sensor, keeps it simple

void setup() {
  Serial.begin(115200);
  
  pulse.analogInput(PULSE_PIN);
  pulse.blinkOnPulse(BLINK_PIN);
  pulse.fadeOnPulse(FADE_PIN);
  
  pulse.begin();
}

void loop() {
  if (pulse.sawStartOfBeat()) {
    int myBPM = pulse.getBeatsPerMinute();
    Serial.println("♥ A heartbeat! BPM: " + String(myBPM));
  }
  
  delay(20); // don't hog the CPU
}
Boom. Open Serial Plotter. Watch your heart draw modern art.

All the Functions (yes, you can have more than one sensor)
cppPulseSensorPlayground pulse(3); // 3 sensors, because why not

pulse.analogInput(A0, 0);       // sensor 0 on A0
pulse.analogInput(A1, 1);       // sensor 1 on A1
pulse.blinkOnPulse(13, 0);      // LED on 13 blinks with sensor 0
pulse.fadeOnPulse(5, 1);        // PWM fade on pin 5 with sensor 1

pulse.setThreshold(550);        // tweak if you're getting noise
Useful stuff you’ll actually use:
cpppulse.getBeatsPerMinute()       // → 72
pulse.getInterBeatIntervalMs()  // → 832 (ms between beats)
pulse.isInsideBeat()            // → true when your heart is actually squeezing
pulse.getPulseAmplitude()       // → how "thumpy" the beat was
pulse.getLastBeatTime()         // → when the last beat happened (2ms resolution)

Serial Output Options
cpppulse.setSerial(Serial);                    // default
pulse.setOutputType(SERIAL_PLOTTER);        // Arduino IDE → Serial Plotter
pulse.setOutputType(PROCESSING_VISUALIZER); // for that 2015 Processing sketch we all loved
Then just call these in loop():
cpppulse.outputSample();  // every 2ms – raw signal
pulse.outputBeat();    // only on heartbeat – BPM + IBI

Pro Tips From Someone Who’s Cried Over This

Finger placement matters – too loose = noise, too tight = flatline
Green side faces skin, purple side faces the void
Use a 1K resistor on your LED or watch it burn (the LED, not your soul)
Ear clip works better than finger when you're typing
Don’t wear black nail polish – it confuses the sensor (yes really)
If BPM jumps to 200 → you probably coughed. Or died.


Supported Boards

Arduino Uno / Nano / Mega (classic)
ESP32 / ESP8266
Teensy (all of them)
Adafruit Feather nRF52
Probably your weird AliExpress board too


Memory & Timing Nerd Stuff
Uncomment these if you’re into pain:
cpp#define PULSE_SENSOR_TIMING_ANALYSIS true   // see how late your loop() is
#define PULSE_SENSOR_MEMORY_USAGE true      // cry about RAM usage

Common Errors & Fixes

























ProblemFixBPM = 0 foreverCheck wiring. Green wire → A0. Seriously.Random 300 BPMYou're moving. Sit still, weirdo."avr/interrupt.h" errorUpdate your board coreLED blinks but no BPMCall pulse.sawStartOfBeat() in loop()

Made with love by

World Famous Electronics (yes that’s their real name)
Some guy in Nairobi at 4am who just wanted his heart to control a NeoPixel strip
You, when you submit a pull request

