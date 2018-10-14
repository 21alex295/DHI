#include <Wire.h>
#include<EEPROM.h>
#include <LiquidCrystal.h>
#include <avr/wdt.h>

const int pcfAddress = 0x38;
const int l1 = 0;
const int l2 = 0;
const int l3 = 0;
const int l4 = 0;
const int button = 7;

int P1, P2, P3, P4;


// Inicia variable lcd y asigna pines
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  //boa practica o disable, activase e desactivase cada segundo
  // wtd_disable();
  //wdt_enable(WDTO_1S);
  Serial.begin(9600);

  // Configura número de columnas y filas
  lcd.begin(16, 2);
  // Saca mensaje
 // lcd.print("hoal");
  // Genera tensión contraste en pin 6
  analogWrite(6, 60);

  pinMode(button, INPUT);
 /* while (digitalRead(button) == LOW) {
    wdt_reset();
  }
  if (digitalRead(button) == LOW) {
    P1 = 1;
    EEPROM.write(0, P1);
    P2 = 2;
    EEPROM.write(1, P2);
    P3 = 5;
    EEPROM.write(2, P3);
    P4 = 10;
    EEPROM.write(3, P4);
  }
  P1 = EEPROM.read(0); //recoge variable de la posicion 0
  P2 = EEPROM.read(1); //recoge variable de la posicion 1
  P3 = EEPROM.read(2); //recoge variable de la posicion 2
  P4 = EEPROM.read(3); //recoge variable de la posicion 3
  int channel = 0;
  while (true) {
    // Inicia la transimisión con el dispositivo
    Wire.beginTransmission(pcfAddress);
    // Pone a alto todos sus pines de E / S, excepto el pin channel.
    // Esto permitirá que la corriente fluya a través del LED conectado a channel.
    // Explicado en : http://www.francois-ouellet.ca/adding-pins-to-your-arduino-using-i2c-and-a-pcf8574p-chip/
    // Los leds encienden con nivel bajo en la salida.
    Wire.write(~(1 << channel));
    // Finaliza la transmisión
    Wire.endTransmission();
    delay(400);
  }*/
}


void light_leds(){ 
      
      Wire.beginTransmission(pcfAddress);
      Wire.write(~(1 << 0));
      Wire.endTransmission();
    }
}

void show_lcd(){
  lcd.clear();
  P1 = 1;
  EEPROM.write(0, P1);
  P2 = 2;
  EEPROM.write(1, P2);
  P3 = 5;
  EEPROM.write(2, P3);
  P4 = 10;
  EEPROM.write(3, P4);
  P1 = EEPROM.read(0); //recoge variable de la posicion 0
  P2 = EEPROM.read(1); //recoge variable de la posicion 1
  P3 = EEPROM.read(2); //recoge variable de la posicion 2
  P4 = EEPROM.read(3); //recoge variable de la posicion 3

  // Cursor a inicio establecido en primera linea

  lcd.setCursor(0, 0);
  lcd.print("P1: "); lcd.print(P1);
  lcd.print("    P2: "); lcd.print(P2);
  lcd.setCursor(0, 1);
  lcd.print("P3: "); lcd.print(P3);
  lcd.print("    P4: "); lcd.print(P4);
  delay(100);
}
void loop() {
  //wtd_reset();
  light_leds();
}
