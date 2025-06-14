#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Stepper.h>
//requirement for this code file : (1) 28BYJ-48 Step motor X 2 (2) 3D printed rail for 28BYJ-48 Step motor X 2 (3) three-pin-button X 2 (4) ULN2003 board X2 (For step motors) (5) Bread Board (6) dupont lines (7) QAPASS Lcd for Arduino (8) Arduino 4 x 4 keypad
LiquidCrystal_I2C lcd(0x27, 16, 2); // Maybe you need to change "0x27" here
//Setting for keypad
const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// setting for step motors
const int stepsPerRev = 2048;
// motor1 → IN1:10, IN2:12, IN3:11, IN4:13 !! Notice !!
Stepper stepper1(stepsPerRev, 10, 12, 11, 13);
// motor2 → IN1:A0,  IN2:A2,  IN3:A1,  IN4:A3 !! Notice !!
Stepper stepper2(stepsPerRev, A0, A2, A1, A3);
// Notice the sequence of pin setting above, since we want our motor to spin at two directions
// password setting
const String password = "1234";
String inputStr = "";

//messenges below are to be shown on our LCD screen
const String messages[] = {
  "Hello",
  "This is a supply",
  "machine.",
  "Press yellow to",
  "get Tissue paper",
  "Press red to get",
  "Toilet cover"
};
const uint8_t MSG_COUNT = sizeof(messages) / sizeof(messages[0]);
unsigned long lastMsgTime = 0;
const unsigned long MSG_INTERVAL = 3000;
uint8_t currentMsg = 0;

void setup() {
  // initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print("Password: ");

  // set to output
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  // set the spining speed
  stepper1.setSpeed(15);
  stepper2.setSpeed(15);
}

void loop() {
  unsigned long now = millis(); // we use millis instead of delays since we don't want to disturb the detection

  if (now - lastMsgTime >= MSG_INTERVAL) {
    lastMsgTime = now;
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(messages[currentMsg]);
    currentMsg = (currentMsg + 1) % MSG_COUNT;
  }

  // detect the input
  char key = keypad.getKey();
  if (key != NO_KEY && key >= '0' && key <= '9') {
    inputStr += key;
    // show input
    lcd.setCursor(10, 1);
    for (uint8_t i = 0; i < inputStr.length(); i++) {
      lcd.print('*');
    }
    // If user push a button for a long time, it could be read twice. Delay(200) prevent this.
    delay(200);
    lastMsgTime = now;
  }

  // check the input
  if (inputStr.length() == password.length()) {
    lcd.clear();
    lcd.setCursor(0, 0);

    if (inputStr == password) {
      // if the password is right then open the safety door
      lcd.print("Right password");
      lcd.setCursor(0, 1);
      lcd.print("Pwd: ");
      lcd.print(inputStr);
      delay(1000);

      for (long i = 0; i < 10787; i++) {
        stepper1.step(-1);
        stepper2.step(1);
        delay(2);  
      }

      // We can wait for 30 seconds for our safety door to go down or push # button to do it.
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Press # to close");
      lcd.setCursor(0, 1);
      lcd.print("30s timeout");

      unsigned long startWait = millis();
      bool closed = false;
      while (millis() - startWait < 30000UL) {
        char k = keypad.getKey();
        if (k == '#') {
          closed = true;
          break;
        }
      }

      // detected button "#" pushed
      for (long i = 0; i < 10787; i++) {
        stepper1.step(1);
        stepper2.step(-1);
        delay(2);
      }

    } else {
      // Wrong password
      lcd.print("Wrong password");
    }

    delay(2000);
    inputStr = "";
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Password: ");
    lastMsgTime = millis();
  }
}
