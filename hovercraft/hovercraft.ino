#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte address[6] = "00001";

struct TransferData {
  bool fan1_state;
  bool fan2_state;
  // the reason its "signed" is because of bug in c++ with +ve int reassigned to -ve int
  signed int servo_direction_right; // -1 means left, 0 means idle, +1 means right
  float throttle; // 0.01 to 1.00 as throttle
};

TransferData data; // Create an empty Var

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(TransferData))
    // REST OF THE RECIEVER CODE

  }
}
