#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define ROTATE_SERVO_PIN 9
//position to set for servo to be idle
#define NOZZLE_IDLE_POS 90

Servo nozzleRotateServo;

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

  nozzleRotateServo.attach(ROTATE_SERVO_PIN);
  nozzleRotateServo.write(NOZZLE_IDLE_POS);
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(TransferData));
    // REST OF THE RECIEVER CODE

  }
}

//generally speed var shouldn't be a value that can be controlled with the controller. This make the driver's life easier
//speed var should be tuned and manually coded in to the driver's preference
void rotateNozzle(int direction, int speed){
  //speed variable to control how fast the servo continously spins (would make the var a float but map returns longs)
  speed = map(speed, 0, 100, 0, 90);
  //-1 = CCW,  0 = idle, 1 = CW
  switch(direction){
    case -1:
      nozzleRotateServo.write(NOZZLE_IDLE_POS + speed);
      break;
    case 0:
      nozzleRotateServo.write(NOZZLE_IDLE_POS);
      break;
    case 1:
      nozzleRotateServo.write(NOZZLE_IDLE_POS - speed);
      break;
  }
}