/*
Programa para simular funcion dunha fiestra movil de maneira simplificada. 
O proceso comeza en estado PARADO. No momento que pulsamos o botón a xanela comeza a subir (estado motorArriba), esta acción vai durar
7 segundos, a non ser que realice unha nova pulsación e me volva levar a paro. Outra pulsación fará que a xanela comece a baixar durante 7 segundos (estado motorAbaixo).
Unha nova pulación levaríanos a estado de Paro e así sucesivamente. 

Entrada: Pulsador (dixital)
Saidas: Rele (2x dixital)

Autor: Manuel Dominguez
Data: 9 Febreiro de 2023
*/

#define motorArriba 12          //Aquí indicámolle a Arduíno que a acción motorArriba está definida no pin 12
#define motorAbaixo 11          //Aquí indicámolle a Arduíno que a acción motorArriba está definida no pin 11
#define pulsador     7          //Aquí indicámolle a Arduíno que a acción pulsador está definida no pin 7

int estado = 1;       // o valor é un numero enteiro, pode ser 0,1,2,3 ... xa que van ser os estados: 0-Baixada, 1-Paro, 2-Subida, 3-Paro. Modificamos este parámetro porque en términos Booleanos só hai 2 estados. 0 e 1.
int contador = 0;    // contador para o numero de impulsos do motor; modificamos este parámetro para que o monitor serie non conte mentras non premamos o botón.


void setup() {              // Aquí configuramos os pins do Arduíno, en entradas e saídas; tamén definimos a velocidade de sincronismo das comunicacións   
                          
  
  pinMode(motorArriba, OUTPUT);     // Aquí explicámolle a Arduíno que o pin motorArriba é unha saída
  pinMode(motorAbaixo, OUTPUT);     // Aquí explicámolle a Arduíno que o pin motorabaixo é unha saída
  pinMode(pulsador, INPUT);         // Aquí explicámolle a Arduíno que o pin pulsador é unha entrada
  
  Serial.begin(9600);               //velocidade sincronismo das comunicacions
}


void loop() {             // Esta parte é na que se executa o código "bucle"
  
                         //Inicio lectura do pulsador
  
  if(digitalRead(pulsador)) {          // Aquí escribimos unha condición (if), na que dicimos " si a lectura dixital (pulsador)" está activa, pasen as seguintes accións:
    estado= (++estado) % 4;            // Actualización do estado para estar entre 0 e 3, no que temos 4 estados; motorArriba(2),paro(1 e 3), motorAbaixo(0).. Empregamos a suma e a división entre catro para obter números inferiores a 4 e así poder pasar sucesivamente dun estado a outro.
    contador = 100;                    // O contador que vai leer as veces se repite o bucle e comeza en 100 
    while(digitalRead(pulsador)) {     // Mentras que o pulsador é premido, e se lee a súa entrada dixital, o arduíno debe agardar esperando 20 milisegundos
      delay(20);
      }
    }
  
                          // fin lectura do pulsador
  
                          // aplicamos comandos para monitonear os estados
  
  Serial.print("valor do contador: ");      // Esta función (serial.print) serve para que o Arduíno imprima valores, ou o que escriba se vai escrito entre " ", neste caso queremos que escriba no monitor "valor do contador" 
  Serial.println(contador);                 // Esta función (serial.println) serve para que o Arduíno inserte un salto de liña e escriba o que poñamos, neste caso o valor "contador", asociado a print.ln que comeza en 100
  Serial.print("  |  Estado: ");            // Aquí xa saltou de liña , e definimos " | Estado " para que así poña iso literalmente na nova liña
  Serial.println(estado);                   // Aquí atribúe o valor (estado) ao escrito na liña anterior , que será 0, 1, 2, 3 en función se prememos ou non o botón
   
                          // Accionamento dos motores
  
  if(contador > 0) {          // Conta número de impulsos ao motor + aplica a condición "if" (si), o contador é maior ca 0 faga as seguintes instruccións:
    if(estado == 0 ) {       // Aplica condición "if" (si); o estado do contador "compara" (==) o valor do estado e en función delo actúa en consecuencia comezando a contar
      digitalWrite(motorArriba,LOW);            // Indica que a saída dixital "motorArriba" non se active (LOW); é un enclavamento
      digitalWrite(motorAbaixo, HIGH);          // Indica que a saída dixital "motorAbaixo" se active (HIGH); Esta modificación está feita porque o estado inicial é 1 e ao premer vai pasar ao 2 ao sumar unha unidade ao contador no que a xanela comeza a subir
      delay(70);                                // Agarda 70 milisegundos
      contador --;                              // Contador resta unha unidade
  }
   else if (estado == 2) {        // Comandos "else"+"if" nos que lle dicimos que se o estado non é cero pero si é 2 realice as seguintes accións  
     digitalWrite(motorArriba, HIGH);             // Indica que a saída dixital "motor arriba" se active (HIGH)
     digitalWrite(motorAbaixo, LOW);              // Indica que a saída dixital "motor abaixo" se active (LOW)
     delay(70);                                   // Esperar 70 milisegundos
     contador --;                                 // Contador resta unha unidade
   } 
    else {        // Comando "Else" no que di que si o estado é distinto a 0 ou 2 os motores paren e o contador conte de 100 a 0
      digitalWrite(motorArriba, LOW);            // Indica que a saída dixital "motorArriba" non se active (LOW)
     digitalWrite(motorAbaixo,LOW);             // Indica que a saída dixital "motorAbaixo" non se active (LOW)
     delay(70);                                 // Esperar 70 milisegundos   
     contador --;                               // Contador resta unha unidade
      
    }
  }
       
  // Esta última parte xa non é necesaria porque sería repetir o comando "else" anterior
  
  //else {           //Se non está o motor accionado, espera 100 ms
   // digitalWrite(motorArriba, LOW);
    // digitalWrite(motorAbaixo,LOW);
    // Fin de accionamento de motores
     //}
    
   // delay(70);
                  
}
     
     
     
