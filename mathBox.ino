
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
byte num_digits = 2;
byte num_args = 2;
byte num_seq = 1;
byte score = 0;
int answer = 0;
int submitted = 0;
byte op[4]={1,2,3,4};
int argVal[5];
byte opVal[4]={0,0,0,0};

//pinouts
byte digitPin0 = 1;
byte digitPin1 = 3;
byte argPin0 = 5;
byte argPin1 = 3;
byte seqPin0 = 5;
byte seqPin1 = 3;

byte addPin = 1;
byte minusPin = 2;
byte multiplyPin = 3;
byte dividePin = 4;


//char* lcdinitialization[] = {"Answer the question", "To open the box!", "Press A to continue..."} ; 
char line0[17];
char line1[17];

char lcdqueryscore[17] = "Tries: ";
char lcdquerytext;

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
  pinMode(digitPin0, INPUT);
  pinMode(digitPin1, INPUT);
  pinMode(argPin0, INPUT);
  pinMode(argPin1, INPUT);
  pinMode(seqPin0, INPUT);
  pinMode(seqPin1, INPUT);
  pinMode(addPin, INPUT);
  pinMode(minusPin, INPUT);
  pinMode(multiplyPin, INPUT);
  pinMode(dividePin, INPUT);
  
  
  //read pins for configuration  
  
  availableOperators(op,digitalRead(addPin),digitalRead(minusPin),digitalRead(multiplyPin),digitalRead(dividePin));//writes to op

  num_digits = BitToInt(digitalRead(digitPin0),digitalRead(digitPin1))+1; //minimum 1, offset by 1 therefore {1,2,3,4}
  
  num_args = BitToInt(digitalRead(argPin0),digitalRead(argPin1))+2; //minimum 2, offset by 2 therefore {2,3,4,5}
   
  num_seq = BitToInt(digitalRead(argPin0),digitalRead(argPin1))+1;  //minimum 1, offset by 1 therefore {1,2,3,4}
  
  
}

void loop() {
  //generate query
  
  
  //grab keypress
  //(while customKey == not press){
  //do nothing}
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
/*
  if (customKey=='B'&& score<num_seq){
    //check answer.
    //if correct score++;
    else report answer is wrong, try again
    
  }
  if (score=num_seq){
    //check answer.
    //if correct score++;
    else report answer is wrong, try again
    
  }
*/
  //LCD Output
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the keypressed:
  lcd.print(customKey);
  
  //sprintf(lcdqueryscore, “Score: %-2d”, score);
  
  //update display
  updateDisplay(); 

  

}

void genArgsVal(int argVal[], int digits, int args){      
  for (int i = 0; i<args; i++){
    argVal[i] = random(0,10*exp(digits)-1);    
  }
}

void availableOperators(byte op[], byte add, byte minus, byte multiply, byte divide){  
  op[0]*=add;
  op[1]*=minus;
  op[2]*=multiply;
  op[3]*=divide; 
}

int chooseOperator(byte op[]) {
  int selectedop=0;
  while(selectedop == 0){    
    selectedop=op[random(0,3)];
  }
  return selectedop;
}

void genOpVal(byte opVal[], byte args, byte op[]){  
    
  for (int i = 0; i<args-1; i++){
    opVal[i] = chooseOperator(op) ;  
  }  
}

int genAnswer(byte args, int argVal[], byte opVal[]){
  int answer;
  for (int j = 0; j<args-1; j++){
    if (j==0){
      answer=argVal[j];
    }
    else{
      switch(opVal[j-1]){
        case 0:
          break;
        case 1:
          answer += argVal[j];
          break;
        case 2:
          answer -= argVal[j];
          break;
        case 3:
          answer *= argVal[j];
          break;
        case 4:
          //answer /= argVal[j];
          break;
      }
    }
    
  }
  
  return answer;
}



byte BitToInt(byte pin0, byte pin1){
  //casts {00,01,10,11} to {0,1,2,3}
  int result;
  result = pin0 + pin1*2;
  return result;
}



void updateDisplay() {
   lcd.setCursor(0,0);
   lcd.print(line0);
   lcd.print(line1);
}
