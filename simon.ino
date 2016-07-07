#include <Wire.h>
#include <rgb_lcd.h>

const int buttonPinUn = 2;
const int buttonPinDeux = 3;
const int buttonPinTrois = 4;
const int buttonPinQuatre = 5;
boolean valButtonUn;
boolean valButtonDeux;
boolean valButtonTrois;
boolean valButtonQuatre;
int led[100] = {1};
int button[100] = {};
int score;

rgb_lcd lcd;

void setup() {
  //LCD
  lcd.begin(16, 2);
  lcd.setRGB(30, 30, 200);
  lcd.print("START");
  //Serial
  Serial.begin(9600);
  //Boutons
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  //Leds
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  randomSeed(analogRead(0));
  Serial.println("--------------");
}

void loop() {
  Serial.println("START");
  for (int i = 0; i <= 100; i++) {
    if (led[i] == 1 || led[i] == 2 || led[i] == 3 || led[i] == 4) {
      
      resetButton();
      delay(500);
      lowLed();
      while (valButtonUn + valButtonDeux + valButtonTrois + valButtonQuatre == 0) {
        
        valButtonUn = !digitalRead(2);
        valButtonDeux = !digitalRead(3);
        valButtonTrois = !digitalRead(4);
        valButtonQuatre = !digitalRead(5);

        if (led[1]==NULL){
          lcd.setRGB(random(1,200), random(1,200), random(1,200));
          delay(150);
        }
        
      }

      if (valButtonUn == 1) {
        button[i] = 1;
        digitalWrite(6, HIGH);
        buzzerPlay(261, 300);
        resetButton();
      }

      if (valButtonDeux == 1) {
        button[i] = 2;
        digitalWrite(7, HIGH);
        buzzerPlay(330, 300);
        resetButton();
      }

      if (valButtonTrois == 1) {
        button[i] = 3;
        digitalWrite(8, HIGH);
        buzzerPlay(392, 300);
        resetButton();
      }

      if (valButtonQuatre == 1) {
        button[i] = 4;
        digitalWrite(9, HIGH);
        buzzerPlay(523, 300);
        resetButton();
      }

      if (button[i] == led[i]) {
        Serial.print("ok, ");
      } else {
        Serial.println("nope.");
        buzzerPlay(261, 100);
        buzzerPlay(180, 100);
        buzzerPlay(100, 100);
        nonValide();
        break;
      }
    } else {
      buzzerPlay(261, 100);
      buzzerPlay(330, 100);
      buzzerPlay(392, 100);
      buzzerPlay(523, 100);
      valide(i);
      break;
    }
  }
}

void resetButton() {
  valButtonUn = 0;
  valButtonDeux = 0;
  valButtonTrois = 0;
  valButtonQuatre = 0;
}

void lowLed() {
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void highLed() {
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void buzzerPlay(int note, int duree) {
  tone(10, note);
  delay(duree);
  noTone(10);
}

void valide(int valIterateur) {
  score++;
  lcd.setRGB(30, 30, 200);
  lcd.setCursor(0, 0);
  lcd.print("score: ");
  lcd.print(score);
  int derniereValeur = random(1, 5);
  led[valIterateur] = derniereValeur;
  Serial.println("VALIDE");
  Serial.print("on rajoute ");
  Serial.println(derniereValeur);
  for (int i = 0; i <= 3; i++) {
    highLed();
    delay(100);
    lowLed();
    delay(100);
  }

  for (int i = 0; i <= 100; i++) {
    if (led[i] == 1 || led[i] == 2 || led[i] == 3 || led[i] == 4) {
      delay(100);
      if (led[i] == 1) {
        digitalWrite(6, HIGH);
        buzzerPlay(261, 500);
        digitalWrite(6, LOW);
      }
      if (led[i] == 2) {
        digitalWrite(7, HIGH);
        buzzerPlay(330, 500);
        digitalWrite(7, LOW);
      }
      if (led[i] == 3) {
        digitalWrite(8, HIGH);
        buzzerPlay(392, 500);
        digitalWrite(8, LOW);
      }
      if (led[i] == 4) {
        digitalWrite(9, HIGH);
        buzzerPlay(523, 500);
        digitalWrite(9, LOW);
      }
    } else {
      break;
    }
  }
}

void nonValide() {
  Serial.println("NON VALIDE");
  Serial.print("score = ");
  Serial.println(score);
  delay(500);
  asm volatile (" jmp 0"); // http://www.xappsoftware.com/wordpress/2013/06/24/three-ways-to-reset-an-arduino-board-by-code/
}
