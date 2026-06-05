#include <Arduino.h>

/**
 * SPWM Generation using ESP32 DAC
 * Logic: Compares a 50Hz Sine reference wave with a 2kHz Sawtooth carrier wave.
 * When Sine >= Sawtooth, output HIGH (255); otherwise, LOW (0).
 */

const int dacPin = 25; // ESP32 DAC pin

// Signal Frequencies
const float freqSine = 50.0;  // Fundamental frequency (50Hz)
const float freqSaw  = 2000.0; // Switching frequency (2kHz)

// Timing management
unsigned long sampleInterval = 25; // Microseconds between samples
unsigned long lastSampleTime = 0;
float sinAmplitude = 0.909;        // Amplitude scaling factor

void setup() {
  // Initialize DAC if necessary (default on ESP32 is usually fine)
}

void loop() {
  unsigned long currentTime = micros();

  // Non-blocking sampling loop
  if (currentTime - lastSampleTime >= sampleInterval) {
    lastSampleTime = currentTime;
    
    // Time variable in seconds
    float t = currentTime / 1000000.0;

    // 1. Generate Sine Wave: Normalized 0 to 1, then scaled by amplitude
    float sineWave = ((sin(2.0 * PI * freqSine * t) + 1.0) / 2.0) * sinAmplitude;

    // 2. Generate Sawtooth Wave: Frequency based on mod operator
    float sawtoothWave = fmod(t, 1.0 / freqSaw) * freqSaw;

    // 3. SPWM Comparison Logic: The core switching signal
    int dacOutput = (sineWave >= sawtoothWave) ? 255 : 0;

    // 4. Output to Hardware
    dacWrite(dacPin, dacOutput);
  }
}