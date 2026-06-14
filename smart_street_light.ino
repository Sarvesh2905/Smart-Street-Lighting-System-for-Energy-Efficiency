/*
  ==========================================================
  SMART STREET LIGHT - Occupancy Based Dimming (Prototype)
  ==========================================================

  PROJECT IDEA:
  Highway street lights normally stay at full brightness all
  night, wasting electricity even when no vehicle is on the
  road. This system keeps the light DIM (standby/energy-saving
  mode) by default. When a vehicle approaches and is detected
  by the sensor, the light smoothly brightens to FULL. Once the
  vehicle has passed, the light gradually fades back to dim.

  PROTOTYPE HARDWARE (small-scale demo):
    - IR Obstacle Avoidance Sensor Module -> OUT pin to Digital Pin 2
    - LED (street light)                  -> PWM Pin 9 (through resistor)

  REAL-WORLD VERSION (for actual deployment):
    Replace the basic IR module with long-range sensors such as:
      - PIR motion sensors (for general presence)
      - Microwave / Doppler radar sensors (long range, vehicle speed)
      - Laser/Time-of-Flight (ToF) distance sensors (long range, accurate)
    And replace the LED with an LED driver / relay / MOSFET
    controlling actual high-power street light fixtures.

  NOTE ON SENSOR LOGIC:
    Most basic IR obstacle sensor modules output:
      LOW  -> object/vehicle detected
      HIGH -> no object detected
    Some modules have a jumper to invert this. If your light
    behaves backwards (dims when a vehicle passes), simply
    change "== LOW" to "== HIGH" in the code below.
*/

const int IR_SENSOR_PIN = 2;      // Digital pin connected to IR sensor OUT
const int LED_PIN       = 9;      // PWM-capable pin connected to LED

const int DIM_BRIGHTNESS  = 40;    // Standby brightness (~15% of 255)
const int FULL_BRIGHTNESS = 255;   // Full brightness (100%) when vehicle detected

const unsigned long HOLD_TIME = 4000;  // Time (ms) light stays bright after vehicle leaves
const int FADE_STEP_DELAY     = 5;     // Delay (ms) per brightness step -> controls fade speed

int currentBrightness = DIM_BRIGHTNESS;
unsigned long lastDetectedTime = 0;
bool vehiclePresent = false;

void setup() {
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);

  // Start in dim/standby mode
  analogWrite(LED_PIN, DIM_BRIGHTNESS);
  Serial.println("Smart Street Light Initialized - Standby (Dim) Mode");
}

void loop() {
  int sensorState = digitalRead(IR_SENSOR_PIN);

  // Adjust this comparison if your sensor's logic is inverted
  bool vehicleDetected = (sensorState == LOW);

  if (vehicleDetected) {
    lastDetectedTime = millis();

    if (!vehiclePresent) {
      Serial.println("Vehicle detected -> Brightening to FULL");
    }
    vehiclePresent = true;

    fadeTowards(FULL_BRIGHTNESS);
  }
  else {
    // No vehicle right now - check if hold time has elapsed
    if (vehiclePresent && (millis() - lastDetectedTime >= HOLD_TIME)) {
      Serial.println("Road clear -> Dimming back to standby");
      vehiclePresent = false;
    }

    if (!vehiclePresent) {
      fadeTowards(DIM_BRIGHTNESS);
    }
  }
}

// Smoothly steps the LED brightness one unit towards the target value.
// Calling this repeatedly inside loop() creates a gradual fade effect
// instead of an abrupt jump in brightness.
void fadeTowards(int targetBrightness) {
  if (currentBrightness < targetBrightness) {
    currentBrightness++;
  } else if (currentBrightness > targetBrightness) {
    currentBrightness--;
  } else {
    return; // Already at target, nothing to do
  }

  analogWrite(LED_PIN, currentBrightness);
  delay(FADE_STEP_DELAY);
}
