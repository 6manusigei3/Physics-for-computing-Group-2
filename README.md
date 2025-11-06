HEART BEAT MONITOR PROJECT

GROUP MEMBERS.
ARISTOTE ALPHONSE- BSCCS/2025/40882 
AMY SIMIYU- BSCCS/2025/39530 
BRILLIAN ANDALO -BSCCS/2025/41447 
DAVIS MANORE -BSCCS/2025/40635 
EDWIN MEITEIKINI -BSCCS/2024/44160
EMMANUEL KIPCHUMBA SIGEI -BSCCS/2025/40046
ERICSON KARANJA -BSCCS/2025/39563 
LATETIA MUMBE -BSCCS/2025/41891
LYN WANJIKU -BSCCS/2025/40726 
TINAELIS MUMBI -BSCCS/2025/ 40091


---

## Project Title  
**Heart Beat Monitor using PulseSensor and Arduino**

---

## Technical Explanation
This Arduino sketch creates a real-time heart-rate monitoring system using a PulseSensor. The sensor detects blood volume changes in the fingertip via photoplethysmography (PPG). The raw analog signal is processed to detect heartbeats, calculate BPM (beats per minute), and provide visual feedback through an LED that blinks in sync with each pulse. The system outputs both the live waveform and calculated BPM to the Serial Plotter, making it perfect for studying analog signal processing and biomedical instrumentation.

---

## Hardware Requirements
- Arduino Board (Uno/Nano/Mega)  
- PulseSensor (AMPED version)  
- LED (with 220Ω resistor) connected to digital pin 13  
- Breadboard and jumper wires  
- USB cable for power and Serial communication  

### Wiring Diagram (schematics in `/schematics/` folder)
PulseSensor:
VCC → 5V
GND → GND
SIGNAL → A0
LED:
Anode (+) → Pin 13 (via 220Ω resistor)
Cathode (-) → GND


---

## Code Overview
The sketch reads the analog signal from A0, applies threshold-based beat detection, measures inter-beat intervals (IBI) using `millis()`, and calculates BPM. A state variable prevents false triggers while the LED provides instant visual feedback.

### Key concepts demonstrated:
1. Analog Input: Reading 10-bit values from the PulseSensor  
2. Threshold-based edge detection for heartbeat events  
3. Non-blocking timing with `millis()`  
4. Real-time BPM calculation (BPM = 60000 / IBI)  
5. Serial Plotter visualization at 115200 baud  

---

## Detailed Code breakdown

### Global Variables
``
int pulsePin = A0;            // PulseSensor purple wire
int ledPin = 13;              // On-board LED
int rawValue = 0;             
int threshold = 550;          // Adjust once for your sensor
unsigned long lastBeat = 0;
int BPM = 0;
bool beat = false;




##SETUP FUNCTION

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Heart Beat Monitor warming up...");
  delay(2000);
}



##LOOP FUNCTION.

void loop() {
  rawValue = analogRead(pulsePin);

  // Plot raw signal + BPM
  Serial.print("Signal:");
  Serial.print(rawValue);
  Serial.print(",BPM:");
  Serial.println(BPM);

  // Rising edge detection
  if (rawValue > threshold && !beat) {
    digitalWrite(ledPin, HIGH);
    
    unsigned long currentTime = millis();
    unsigned long IBI = currentTime - lastBeat;
    lastBeat = currentTime;

    if (IBI > 400) {  // Ignore noise <150 BPM
      BPM = 60000 / IBI;
    }
    beat = true;
  }

  if (rawValue < threshold) {
    digitalWrite(ledPin, LOW);
    beat = false;
  }
}





##How It Works in Practice

Power On → "warming up" message appears
Place finger gently on PulseSensor (cover completely)
LED blinks with every heartbeat
Serial Plotter shows live waveform + BPM value
Typical resting BPM: 60–100


##Enhancements & Extensions

Add OLED display for standalone use
Bluetooth module for mobile app
ESP32 + Blynk dashboard
SD card logging
High/low BPM alarm


##Usage Instructions

Open Heart_Beat_Monitor.ino in Arduino IDE
Upload to board
Open Serial Plotter (Ctrl+Shift+L)
Set baud rate to 115200
Place finger on sensor → watch your heart live!



