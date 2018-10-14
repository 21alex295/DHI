#include <avr/sleep.h>
#include <MsTimer2.h>
//SerialParseInt -> devolve os valores que se
//lle envian ao serial cun int (20:20:20 devolve cada numero por separado
volatile int segundos = 0;
volatile int minutos = 0;
volatile int horas = 0;

volatile int segundosAux = 0;
volatile int minutosAux = 0;
volatile int horasAux = 0;

const int ledRojo  = 10;
const int ledVerde = 5;
const int boton    = 3;

bool alt = true;
int input;

void wakeUpNow() {

}

//Invirte que led esta iluminado mediante un bool
void alternarLed(bool alt) {
  digitalWrite(ledRojo, alt);
  digitalWrite(ledVerde, !alt);
}


/*POn o arduino en modo power down. Cando cambia o estado do boton asociado ao pin 3 
(INT1, primeiro parámetro do attach interrupt) despértase*/

void sleepNow() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(1, reloxo, CHANGE);
  sleep_mode();
  sleep_disable();
  detachInterrupt(1);
}

/*Función que fai avanzar ao reloxo segundo a segundo*/
void reloxo() {
  //Alternar leds
  alt = !alt;
  alternarLed(alt);

  //Funcion de reloxo
  segundos++;
  if (segundos > 59) {
    segundos = 0;
    minutos++;
  }
  if (minutos > 59) {
    minutos = 0;
    horas++;
  }
  if (horas > 23) {
    horas = 0;
  }

  Serial.print(horas);
  Serial.print(":");
  Serial.print(minutos);
  Serial.print(":");
  Serial.println(segundos);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(boton, INPUT);

  
  Serial.begin(9600);

  //Config do timer.Indicaselle a funcion que se chama e cada canto tempo
  MsTimer2::set(1000, reloxo);
  MsTimer2::start();

  //Config da interrupción. parametro do medio = func a executar cando pase
  attachInterrupt(1, wakeUpNow, CHANGE);  

}

void loop() {
  //pór reloxo en hora
  /*Entra no if cada vez que se envia algo ao serial. Se non estaria lendo 
  continuamente*/
  if (Serial.available() > 1) { 
    horasAux = Serial.parseInt();
    minutosAux = Serial.parseInt();
    segundosAux = Serial.parseInt();
    
    /*Se se sae do rango, pon o arduino en modo sleep*/
    if ((horasAux > 23) || (minutosAux > 59) || (segundosAux > 59)) {
      Serial.println("Paso a modo power-down");
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledVerde, LOW);
      delay(100); //provoca erros se non se esperan uns milisegundos
      sleepNow();
    } else if ((horas > 0) || (minutos > 0) || (segundos > 0)) {
      horas = horasAux;
      minutos = minutosAux;
      segundos = segundosAux;
    }
  }
}






