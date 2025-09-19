#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// -------- Relay pins --------
const int RELAYS[3] = {4,3,2};        // White, Blue, Yellow
enum {W=0,B=1,Y=2};
const char* nameShort[3] = {"W","B","Y"};
const char* nameFull[3]  = {"White","Blue","Yellow"};

// -------- Keypad --------
const byte ROWS=4, COLS=4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {6,7,8,9};
byte colPins[COLS] = {10,11,12,13};
Keypad keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// -------- States --------
bool bulbOn[3];
bool countdownActive[3];
unsigned long endTime[3];

bool selecting = false;
bool entering = false;
bool chosen[3];
String timeDigits = "";

int showIndex = -1;
unsigned long lastLCD = 0;

// -------- LCD helpers --------
void lcdStatus() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("W:"); lcd.print(bulbOn[W]?"ON ":"OFF");
  lcd.print(" B:"); lcd.print(bulbOn[B]?"ON ":"OFF");
  lcd.setCursor(0,1);
  lcd.print("Y:"); lcd.print(bulbOn[Y]?"ON ":"OFF");
}

void lcdSelect() {
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Select bulbs");
  lcd.setCursor(0,1); lcd.print("Chosen:");
  for(int i=0;i<3;i++) if(chosen[i]) { lcd.print(nameShort[i]); lcd.print(' '); }
}

void lcdEnter() {
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Time (sec):");
  lcd.setCursor(0,1); lcd.print(timeDigits);
}

void lcdCountdown(int idx, unsigned long sec) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(nameShort[idx]); lcd.print(":OFF ");
  lcd.print(nameFull[idx]);
  lcd.setCursor(0,1);
  lcd.print("Left: "); lcd.print(sec); lcd.print(" s");
}

// -------- Countdown start --------
void startCountdown(unsigned long sec) {
  for(int i=0;i<3;i++) if(chosen[i]) {
    bulbOn[i] = false;
    digitalWrite(RELAYS[i], LOW);
    if(sec>0) {
      countdownActive[i] = true;
      endTime[i] = millis() + sec*1000UL;
    } else {
      bulbOn[i] = true;
      digitalWrite(RELAYS[i], HIGH);
      countdownActive[i] = false;
    }
    chosen[i] = false;
  }

  // pick the first active for immediate display
  showIndex = -1;
  for(int i=0;i<3;i++) if(countdownActive[i]) { showIndex = i; break; }
  if(showIndex >= 0) {
    unsigned long remain = (endTime[showIndex] - millis())/1000UL;
    lcdCountdown(showIndex, remain);   // <— show immediately
  } else lcdStatus();
}

// -------- Setup --------
void setup() {
  lcd.init(); lcd.backlight();
  for(int i=0;i<3;i++) {
    pinMode(RELAYS[i],OUTPUT);
    digitalWrite(RELAYS[i],HIGH);    // all ON initially
    bulbOn[i] = true;
  }
  lcdStatus();
}

// -------- Loop --------
void loop() {
  unsigned long now = millis();

  // check expiry
  for(int i=0;i<3;i++) {
    if(countdownActive[i] && now >= endTime[i]) {
      countdownActive[i] = false;
      bulbOn[i] = true;
      digitalWrite(RELAYS[i], HIGH);
      lcdStatus();
    }
  }

  // keypad
  char k = keypad.getKey();
  if(k) {
    if(entering) {
      if(isDigit(k) && timeDigits.length()<4) {
        timeDigits += k; lcdEnter();
      } else if(k=='D') {
        unsigned long sec = timeDigits.length()? timeDigits.toInt():0;
        entering = false; startCountdown(sec);
        timeDigits="";
      } else if(k=='#') {
        entering=false; for(int i=0;i<3;i++) chosen[i]=false; lcdStatus();
      }
    }
    else if(selecting) {
      if(k=='W'){ chosen[W]=true; lcdSelect(); }
      else if(k=='B'){ chosen[B]=true; lcdSelect(); }
      else if(k=='Y'){ chosen[Y]=true; lcdSelect(); }
      else if(k=='C'){ for(int i=0;i<3;i++) chosen[i]=false; lcdSelect(); }
      else if(k=='*'){ selecting=false; entering=true; timeDigits=""; lcdEnter(); }
      else if(k=='#'){ selecting=false; for(int i=0;i<3;i++) chosen[i]=false; lcdStatus(); }
    }
    else {
      if(k=='A'){ selecting=true; for(int i=0;i<3;i++) chosen[i]=false; chosen[W]=true; lcdSelect(); }
      else if(k=='B'){ selecting=true; for(int i=0;i<3;i++) chosen[i]=false; chosen[B]=true; lcdSelect(); }
      else if(k=='C'){ selecting=true; for(int i=0;i<3;i++) chosen[i]=false; chosen[Y]=true; lcdSelect(); }
      else if(k=='1'){ bulbOn[W]=!bulbOn[W]; digitalWrite(RELAYS[W], bulbOn[W]?HIGH:LOW); lcdStatus(); }
      else if(k=='4'){ bulbOn[B]=!bulbOn[B]; digitalWrite(RELAYS[B], bulbOn[B]?HIGH:LOW); lcdStatus(); }
      else if(k=='7'){ bulbOn[Y]=!bulbOn[Y]; digitalWrite(RELAYS[Y], bulbOn[Y]?HIGH:LOW); lcdStatus(); }
    }
  }

  // update countdown display every 500 ms
  if(showIndex>=0 && countdownActive[showIndex] && now - lastLCD >= 500) {
    lastLCD = now;
    unsigned long remain = (endTime[showIndex] > now) ? (endTime[showIndex]-now)/1000UL : 0;
    lcdCountdown(showIndex, remain);
  }
  else if(showIndex>=0 && !countdownActive[showIndex]) {
    // pick next active or go back to status
    int next=-1;
    for(int i=0;i<3;i++) if(countdownActive[i]) { next=i; break; }
    showIndex = next;
    if(showIndex<0) lcdStatus();
  }
}
