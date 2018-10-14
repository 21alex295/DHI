/*
 * Autor: Alejandro Fernández Luces
 * Dispositivos Hardware e Interfaces
 * 
 * Descripción: Programa que mide o tempo de reacción dun usuario de 
 * pulsar un botón cando se acende o led vermello
 *
 */

const int boton    =  3;
const int ledVerde = 5;
const int ledRojo  = 10;

const int FALSE = 0;
const int TRUE = 1;

int contador = 0;
bool invalid = FALSE;

long tiempoIni = 0;
long tiempoFin = 0;
long tiempoReaccion = 0;


/*Función que espera a que o botón estea pulsado, mediante un 
bucle infinito que é interrumpido cando se pulsa o botón. Ademais
cando o botón é pulsado, espera 50 ms para asegurarse de que a pulsación 
non é erronea.*/
void waitPulsation(int boton) {
  while (1) {
    if (digitalRead(boton) == HIGH) {
      delay(50);
    } else {
      continue;
    }
    if (digitalRead(boton) == HIGH) {
      return;
    }
    else {
      continue;
    }
  }
}

/*Cumpre a mesma función ca a anterior pero coa depulsacion*/
void waitDepulsation(int boton) {
  while (1) {
    if (digitalRead(boton) == LOW) {
      delay(50);
    } else {
      continue;
    }
    if (digitalRead(boton) == LOW) {
      return;
    }
    else {
      continue;
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(boton, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  randomSeed(analogRead(0));

}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledRojo, LOW);

  waitPulsation(boton);
  waitDepulsation(boton);

  digitalWrite(ledVerde, LOW);
  contador = random(400, 1200);

  /*Este bucle fai a función de que pase un tempo aleatorio antes 
  de que se acenda o led vermello. Se o boton se pulsa antes, reinicia 
  a función loop()*/
  while (contador >= 0) {
    delay(1);
    if (digitalRead(boton) == HIGH) {
      Serial.print("No se precipite \n");
      waitDepulsation(boton);
      return;
    }
    contador--;
  }

  digitalWrite(ledRojo, HIGH);
  
  /*Mídese o tempo dende que se acende o led vermello ata que se pulsa o botón*/
  tiempoIni = millis();
  while (digitalRead(boton) == LOW);
  tiempoFin = millis();
  digitalWrite(ledRojo, LOW);
  tiempoReaccion = tiempoFin - tiempoIni;
  
  /*Mensaxes en función do tempo de reacción*/
  if (tiempoReaccion < 100) {
    Serial.print(tiempoReaccion);
    Serial.print("ms ");
    Serial.println("ENHORBUENA! Excelentes reflejos!");
  } else if (tiempoReaccion > 200) {
    Serial.print(tiempoReaccion);
    Serial.print("ms ");
    Serial.println("Intente de nuevo");
  } else {
    Serial.print(tiempoReaccion);
    Serial.print("ms ");
    Serial.println("BIEN! Buenos reflejos");
  }
  waitDepulsation(boton);

}
