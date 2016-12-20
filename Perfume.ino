#include <LiquidCrystal.h>
#include <Keypad.h>

int motorPin1 = 27;
int motorPin2 = 28;
int motorPin3 = 29;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 6, 23, 5, 22);

int x=0;
int number[3][4] = {0};

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};
byte rowPins[ROWS] = {14,15,16,17}; //connect to row pinouts 
byte colPins[COLS] = {18,19,20,21}; //connect to column pinouts
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Perfume");
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  char num;
  int Time[3] = {0};
  int curs[12][2] = {{10,0},{11,0},{13,0},{14,0},{2,1},{3,1},{5,1},{6,1},{10,1},{11,1},{13,1},{14,1}};
  char key = keypad.getKey();
  if (key != NO_KEY){
    num=key;
    if(num == 'D'){
      while(key == 'D'){
        int count[3] = {0};
        for(int i=0 ; i<3 ; i++){
          Time[i] = number[i][0]*600 + number[i][1]*60 + number[i][2]*10 + number[i][3] - 1;  
          if(Time[i] == -1)
            Time[i] = 0;
          if(Time[i] >= 6000)
            Time[i] = 5999;
        }
        for(int i=0 ; i<3 ; i++){
          number[i][0] = Time[i]/600;
          number[i][1] = (Time[i]%600)/60;
          number[i][2] = (Time[i]%60)/10;
          number[i][3] = Time[i]%10;
        }
        for(int i=0 ; i<3 ; i++)
          for(int j=0 ; j<4 ; j++){
            lcd.setCursor(curs[i*4+j][0],curs[i*4+j][1]);
            lcd.print(number[i][j]);
          }
        for(int i=0 ; i<3 ; i++)
          for(int j=0 ; j<4 ; j++){
            if(number[i][j] == 0)
              count[i]++;
          }
         Serial.print(count[0]);
         Serial.print(count[1]);
         Serial.print(count[2]);
         Serial.println();
        if(count[0] < 4)
          analogWrite(motorPin1, 128);
        else
          analogWrite(motorPin1, 0);
        if(count[1] < 4)
          analogWrite(motorPin2, 128);
        else
          analogWrite(motorPin2, 0);
        if(count[2] < 4)
          analogWrite(motorPin3, 128);
        else
          analogWrite(motorPin3, 0);
        delay(500);
        analogWrite(motorPin1, 0);  
        analogWrite(motorPin2, 0);
        analogWrite(motorPin3, 0);
        if(count[0]+count[1]+count[2] == 12)
          break;
         delay(100);
      }
    }
    else{
      if(x<12 && num!='A' && num!='B' && num!='C' ){
        lcd.setCursor(curs[x][0],curs[x][1]);
        lcd.print(num);
        if(x>=0 && x<4)
          number[0][x] = num-48;
        if(x>=4 && x<8)
          number[1][x-4] = num-48;
        if(x>=8 && x<12)
          number[2][x-8] = num-48;
        x++;
      }
      if(num == 'A')
        x = 0;
      if(num == 'B')
        x = 4;
      if(num == 'C')
        x = 8;
    }
  }
  lcd.setCursor(8,0);
  lcd.print("A:");
  lcd.setCursor(12,0);
  lcd.print(":");
  lcd.setCursor(0,1);
  lcd.print("B:");
  lcd.setCursor(4,1);
  lcd.print(":");
  lcd.setCursor(8,1);
  lcd.print("C:");
  lcd.setCursor(12,1);
  lcd.print(":");

}
