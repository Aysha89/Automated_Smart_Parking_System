#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD and Servo
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD address and dimensions
Servo myservo;  // Servo motor object

// Define pin numbers
int led1 = 10, led2 = 11, led3 = 12, led4 = 13;  // LED pins
int ir_enter = 2, ir_back = 4;  // Entry and exit IR sensor pins
int ir_car1 = 9, ir_car2 = 6, ir_car3 = 7, ir_car4 = 8;  // Car presence IR sensor pins
int servopin = 3;  // Servo control pin
int S1 = 0, S2 = 0, S3 = 0, S4 = 0;  // Parking slot occupancy flags
int slot = 4;  // Total number of parking slots

void setup() {
  Serial.begin(9600);  // Start serial communication for debugging

  // Set pin modes for sensors, LEDs, and servo
  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);
  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  myservo.attach(3);  // Attach servo to pin 3
  myservo.write(0);  // Initialize servo position (closed)
  
  // Initialize LCD display
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Car Parking ");
  lcd.setCursor(0, 1);
  lcd.print("    System");
  delay(2000);
  lcd.clear();
  
  // Calculate initial available slots
  int total = S1 + S2 + S3 + S4;
  slot = slot - total;  
}

void loop() {
  // Read IR sensors for each parking slot and control LEDs accordingly
  readSensors();
  
  // Control the entry gate when a vehicle enters
  if (digitalRead(ir_enter) == 0) {
    myservo.write(90);  // Open the gate
    slot = max(0, slot - 1);  // Decrease available slots
    delay(2000);  // Allow time for vehicle to enter
  } else {
    myservo.write(0);  // Close the gate
  }

  // Control the exit gate when a vehicle exits
  if (digitalRead(ir_back) == 0) {
    myservo.write(90);  // Open the gate
    delay(2000);  // Allow time for vehicle to exit
  }

  // Update the LCD display with current parking slot status
  updateLCD();

  // Display a message if parking is full
  if (slot == 0) {
    lcd.setCursor(0, 0);
    lcd.print("  SORRY PARKING  ");
    lcd.setCursor(0, 1);
    lcd.print("     IS FULL     ");
    delay(1500);  // Display message for 1.5 seconds
  }
}

// Function to read IR sensors and update slot occupancy
void readSensors() {
  S1 = (digitalRead(ir_car1) == 0) ? 1 : 0;  // Check if slot 1 is occupied
  S2 = (digitalRead(ir_car2) == 0) ? 1 : 0;  // Check if slot 2 is occupied
  S3 = (digitalRead(ir_car3) == 0) ? 1 : 0;  // Check if slot 3 is occupied
  S4 = (digitalRead(ir_car4) == 0) ? 1 : 0;  // Check if slot 4 is occupied
  
  // Update LEDs to indicate slot occupancy
  digitalWrite(led1, S1 ? HIGH : LOW);
  digitalWrite(led2, S2 ? HIGH : LOW);
  digitalWrite(led3, S3 ? HIGH : LOW);
  digitalWrite(led4, S4 ? HIGH : LOW);
}

// Function to update the LCD display with current slot availability
void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print(" Have Slot ");
  int total = 4 - (S1 + S2 + S3 + S4);  // Calculate available slots
  lcd.print(total);
  lcd.print("   ");

  // Display slot status for each slot
  lcd.setCursor(0, 1);
  lcd.print(S1 ? "1:F " : "1:E ");  // 'F' for full, 'E' for empty
  lcd.setCursor(4, 1);
  lcd.print(S2 ? "2:F " : "2:E ");
  lcd.setCursor(8, 1);
  lcd.print(S3 ? "3:F " : "3:E ");
  lcd.setCursor(12, 1);
  lcd.print(S4 ? "4:F " : "4:E ");
}
