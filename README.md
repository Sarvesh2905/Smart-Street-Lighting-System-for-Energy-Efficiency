# Smart Street Lighting System for Energy Efficiency

🏆 **Recognition:** Selected among the **Top 5 in our category** — "Ideas for Vikshit Bharat S&T Hackathon", presented at the **India International Science Festival (IISF) 2024, IIT Guwahati, Assam**.

---

## 1. Problem Statement

On highways, street lights typically remain at full brightness throughout the night — regardless of whether any vehicle is actually using the road. Over long stretches of highway, this leads to massive, continuous power wastage during low-traffic hours (late nights, off-peak times).

## 2. Our Idea

Instead of an all-or-nothing system, we proposed an **occupancy-based adaptive lighting system**:

- By default, every street light stays in a **dim/standby state** — just enough for basic visibility, consuming minimal power.
- When a vehicle approaches a light's coverage zone, sensors detect it and the light **brightens to full intensity** for safe visibility.
- Once the vehicle passes and no activity is detected for a short hold period, the light **gradually dims back** to standby.

This way, full brightness is only used exactly when and where it's needed, cutting down energy consumption significantly across an entire highway stretch over a night.

## 3. How It Works

```
 [Sensor monitors road] 
        |
        v
 Vehicle detected? ----No----> Stay / fade to DIM (standby)
        |
       Yes
        |
        v
 Fade up to FULL brightness
        |
        v
 Hold brightness while vehicle is near
        |
        v
 Vehicle leaves + hold time elapses
        |
        v
 Fade back down to DIM
```

The brightness transitions are handled via PWM (Pulse Width Modulation), so the change between dim and full is a smooth fade rather than an abrupt on/off switch — closer to how real adaptive lighting systems behave.

## 4. Prototype Demonstration

For the hackathon demo, we built a small-scale working prototype using easily available components to showcase the core logic:

| Component | Role in Prototype |
|---|---|
| IR Obstacle Sensor Module | Detects "vehicle" passing by (proxy for real sensors) |
| Arduino / ESP8266 Microcontroller | Reads sensor input, controls light output |
| LED | Represents the street light, dimmed/brightened via PWM |

This was deliberately a simplified stand-in — we were transparent with the judges that **real highway deployment would require longer-range, more robust sensors**, which is outlined below.

## 5. Real-World Sensor Recommendations

For an actual highway deployment, the basic IR module would be replaced with sensors suited for outdoor, long-range, all-weather vehicle detection:

### Primary Detection Sensors
- **Microwave / Doppler Radar Sensors** (e.g., RCWL-0516, HB100) — Detect moving vehicles over several meters, work reliably in fog, dust, and rain, unaffected by ambient light.
- **LiDAR / Time-of-Flight (ToF) Sensors** (e.g., TF-Mini, VL53L1X) — Provide accurate distance measurement and can estimate vehicle speed and direction, useful for predictive "light ahead" activation.
- **Inductive Loop Sensors** — Traditional, embedded-in-road sensors used widely in traffic systems; highly reliable for detecting vehicle presence on a specific lane.
- **PIR (Passive Infrared) Sensors** — Useful for detecting pedestrians/animals near the roadside, though limited range makes them better suited as a secondary sensor.

### Supporting Sensors
- **LDR (Light Dependent Resistor) / Ambient Light Sensors** — Ensure the system only activates dimming logic at night, and stays off entirely during daylight.
- **Camera + Image Processing (advanced/future scope)** — For traffic density estimation and adaptive brightness based on traffic volume, not just presence/absence.

### Controller & Connectivity Upgrade
- **ESP32** instead of basic Arduino — built-in WiFi/Bluetooth for IoT connectivity, more processing power for handling multiple sensors.
- **LoRa modules** — For long-distance, low-power communication between street light poles spread across a highway (since WiFi range is impractical at highway scale).
- **Cloud Dashboard** (e.g., ThingSpeak, Firebase, AWS IoT) — For monitoring energy savings, sensor health, and light status across the network in real time.

### Actuation for Real Fixtures
- **PWM-based LED Drivers** — To control high-power LED street light fixtures (instead of a simple low-power LED).
- **Relay / Triac Dimmer Modules** — For dimming AC-powered light fixtures (sodium vapor / LED) safely.

## 6. Tech Stack Used

- **Hardware:** Arduino, ESP8266, IR Sensor, LED
- **Concepts:** PWM-based dimming, occupancy sensing, embedded systems, IoT

## 7. Future Scope

- Cascading activation — lights ahead of an approaching vehicle pre-brighten before it arrives, using inter-pole communication (LoRa/ESP-NOW).
- Solar-powered nodes for fully off-grid highway lighting.
- Integration with traffic management systems for accident detection and emergency response lighting.
- Data analytics dashboard to quantify real energy savings over time.

## 8. Prototype Code

See `smart_street_light.ino` for the Arduino sketch implementing the dim/bright occupancy logic described above.
