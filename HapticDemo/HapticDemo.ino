// ___ Using a Cirque 02-000620-00 Arduino board with Haptic Reactor___
// This demonstration application is built to work with a Teensy 3.1/3.2 but it can easily be adapted to
// work with other Arduino-based systems.
// This application drives the haptic reactor via a small NPN transistor.
// The resonant frequency of our haptic reactor is 160Hz.

//  Pinnacle TM040040 with Arduino
//  Hardware Interface
//  GND
//  +3.3V
//  Haptic NPN transistor base - pin 6

#define HAPTIC_PIN  6

IntervalTimer hapticTimer;

void setup() 
{
  pinMode(HAPTIC_PIN, OUTPUT);
}

// Sweep through 50ms pulses, from 40Hz to 800Hz in 40Hz increments
void loop() 
{
  for(uint32_t freq = 40; freq < 800; freq += 40)
  {
    hapticPulse(freq, 50);
    delay(100);
  }
}

// Create a pulse at <freq> for <duration> milliseconds
void hapticPulse(uint16_t freq, uint16_t duration)
{
  hapticStart(freq);
  delay(duration);
  hapticStop();
}

// Toggles the haptic drive transistor every time it's called
void hapticTimerInterrupt()
{
  if(digitalRead(HAPTIC_PIN))
  {
    digitalWrite(HAPTIC_PIN, LOW);
  }
  else
  {
    digitalWrite(HAPTIC_PIN, HIGH);
  }
}

// Start driving the haptic at <freq> Hz
void hapticStart(uint32_t freq)
{
  // Call the hapticTimerInterrupt function every <2,000,000 / freq> milliseconds (half period)
  hapticTimer.begin(hapticTimerInterrupt, 500000 / freq);
}

// Stop driving the haptic
void hapticStop(void)
{
  hapticTimer.end();
  digitalWrite(HAPTIC_PIN, LOW);  // Don't waste power through the haptic device
}
