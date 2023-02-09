/*
Programa para simular funcion dunha fiestra movil de maneira simplificada. 
O pulsador acciona o motor de subida o ser premido. Unha segunda pulsacion
fai que se accione o motor de baixada. O percorrido dura 7 segundos.Mentres 
os motores están accionados, deben responder ao accionamento do pulsador
(responsive).

Entrada: Pulsador (dixital)
Saidas: Rele (2x dixital)

Autor: Manuel Dominguez
Data: 2 Febreiro de 2023
*/

#define motorArriba 12
#define motorAbaixo 11
#define pulsador     7

int estado = 1;       // o valor é un numero enteiro, pode ser 0,1,2,3 ...
int contador = 0;    // contador para o numero de impulsos do motor


void setup() {
  pinMode(motorArriba, OUTPUT);
  pinMode(motorAbaixo, OUTPUT);
  pinMode(pulsador, INPUT);
  
  Serial.begin(9600); //velocidade sincronismo das comunicacions
}


void loop() {
  //lectura do pulsador
  if(digitalRead(pulsador)) {
    estado= (++estado) % 4; // Actuaizacion do estado para estar entre 0 e 3.
    contador = 100;
    while(digitalRead(pulsador)) {
      delay(20);
      }
    }
  // fin lectura do pulsador
  
  Serial.print("valor do contador: ");
  Serial.println(contador);
  Serial.print("  |  Estado: ");
  Serial.println(estado);
   
  // Accionamento dos motores
  if(contador > 0) {           // Conta número de impulsos ao motor
    if(estado == 0 ) {
      digitalWrite(motorArriba,LOW);
      digitalWrite(motorAbaixo, HIGH);
      delay(70);
      contador --;
  }
   else if (estado == 2) {
     digitalWrite(motorArriba, HIGH);
     digitalWrite(motorAbaixo, LOW);
     delay(70);
     contador --;
   } 
    else {
      digitalWrite(motorArriba, LOW);
     digitalWrite(motorAbaixo,LOW);
     delay(70);
     contador --;
      
    }
  }
  else {           //Se non está o motor accionado, espera 100 ms
    digitalWrite(motorArriba, LOW);
     digitalWrite(motorAbaixo,LOW);
    // Fin de accionamento de motores
     }
    
    delay(70);
                  
}
     
     
     
