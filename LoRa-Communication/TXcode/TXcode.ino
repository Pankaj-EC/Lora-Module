#include <SPI.h>
#include <RadioLib.h>

#define NSS_PIN 10   // Chip select pin
#define BUSY_PIN 2   // Busy pin
#define RESET_PIN 9  // Reset pin

SX1262 radio = new Module(NSS_PIN, BUSY_PIN, RESET_PIN);

void setup() {
  Serial.begin(9600);

  // Initialize the radio module
  while (!radio.begin()) {
    Serial.println(F("LoRa initialization failed!"));
    delay(2000);
  }

  // Set LoRa frequency to 868 MHz, Spreading Factor to 12, Bandwidth to 125 kHz
  radio.setFrequency(868E6);
  radio.setSpreadingFactor(12);
  radio.setRxBandwidth(125000);

  Serial.println(F("LoRa initialization successful!"));
}

void loop() {
  char message[] = "Hello, LoRa!"; // Message to send
  radio.transmit(message, sizeof(message));
  Serial.println(F("Message sent: Hello, LoRa!"));

  delay(5000); // Send message every 5 seconds
}
