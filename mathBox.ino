
//Keypad setup
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','C'},
  {'4','5','6','D'},
  {'7','8','9','E'},
  {'A','0','B','F'}
};
byte rowPins[ROWS] = {38, 40, 42, 44}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {46, 48, 50, 52}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// LCD setup
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
//int backLight = 13;    // pin 13 will control the backlight

//Servo setup
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position <change to default pos
int locked_pos = 10; 
int open_pos = 10; 

//configuration variables
int num_digits = 2;
int num_args = 2;
bool add = true;
bool minus = false;
bool multiply = false;
bool divide = false;
int score = 0;
int answer = 0;
int submitted = 0

//pinouts
int digitPin0 = 1;
int digitPin1 = 3;
int argPin0 = 5;
int argPin1 = 3;
int addPin = 1;
int minusPin = 2;
int multiplyPin = 3;
int dividePin = 4;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //LCD Setup
  lcd.begin(16, 2);

  lcd.clear();                  // start with a blank screen
  lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
  
  // Print a message to the LCD.
  lcd.print("hello, world!");

  //Servo Setup
  myservo.attach(13);  // attaches the servo on pin 9 to the servo object
  //myservo.write(lockedpos);

  //random setup
  randomSeed(analogRead(0)); // change to unused pin

  //setup configuration
  //don't use pin 13 for input
  pinMode(digitpin0, INPUT);
  pinMode(digitpin1, INPUT);
  pinMode(argpin0, INPUT);
  pinMode(argpin1, INPUT);
  pinMode(addpin, INPUT);
  pinMode(minuspin, INPUT);
  pinMode(multiplypin, INPUT);
  pinMode(dividepin, INPUT);
  
  
  //read pins for configuration
  add = digitalRead(addPin);
  minus = digitalRead(minusPin);
  multiply = digitalRead(multiplyPin);
  divide = digitalRead(dividePin);

  num_digits = BitToInt(digitalRead(digitPin0),digitalRead(digitPin1));
  num_args = BitToInt(digitalRead(argPin0),digitalRead(argPin1));  
  if (num_args<2){
    num_args = 2;
    }
  
  
}

void loop() {
  //generate query
  
  
  //grab keypress
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }

  //LCD Output
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the keypressed:
  lcd.print(customKey);

}

int genQuery(int digits, int args, int add, int minus, int multiply, divide){
  for (int i = 0; i<digits;i++){
    randNumber = random(0,9)    
  }
  
  int result;
  result = x * y;
  return result;
}

int BitToInt(int pin0, int pin1){
  int result;
  result = pin0 + pin1*2;
  return result;
}
