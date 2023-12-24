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

  // Set the module to receive mode
  radio.startReceive();
  
  Serial.println(F("LoRa initialization successful!"));
}

void loop() {
  if (radio.available()) {
    char receivedMessage[32]; // Assuming the message won't exceed 32 bytes
    int bytesRead = radio.readData(receivedMessage, sizeof(receivedMessage));

    if (bytesRead > 0) {
      receivedMessage[bytesRead] = '\0'; // Null-terminate the received message
      Serial.print(F("Received message: "));
      Serial.println(receivedMessage);
    } else {
      Serial.println(F("Error receiving message."));
    }
  }

  delay(1000); // Wait for 1 second before checking for the next message
}
