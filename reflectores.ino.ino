#include<stdlib.h> //Para usar randomseed()

const byte pinsReflectores[] = {0, 1, 2, 3,}; //arreglo de leds
const byte numReflectores = sizeof(pinsReflectores) / sizeof(pinsReflectores[0]); //num leds
const byte sensorLuz = A2;
int flash = 750; //250 para la aplicación real
unsigned long inicio = 0;
bool iniciaNoche = 1; 

//Funciones

//encender o apagar los leds
void reflectores(bool estado) {
  for (byte i = 0; i < numReflectores; i++) {
    digitalWrite(pinsReflectores[i], estado);
  }
}

//tiempo que estarán encendidos, apagados o flasheando los reflectores
void tiempo(unsigned long modo){
  inicio = millis();
  while(millis() - inicio <= modo);
}

//Programa

  void setup(){
 
    randomSeed(millis());//genera nums aleatorios
    for(byte i = 0; i < numReflectores; i++){ //Se activan los reflectores
        pinMode(pinsReflectores[i], OUTPUT);
    }
    reflectores(LOW); //Inician los reflectores apagados
}

  void loop(){
  
  int oscuridad = analogRead(sensorLuz); // Se configura el sensor de luz
    if(oscuridad < 400 && iniciaNoche == 1){ //Si ya es de noche has esto una vez
      iniciaNoche = 0;
      for(byte i = 0; i < numReflectores; i++){ //Parpadear reflectores
          digitalWrite(pinsReflectores[i], HIGH);
          tiempo(flash);
          digitalWrite(pinsReflectores[i], LOW);
          tiempo(flash);
      }
    }

    else if(oscuridad < 400 && iniciaNoche == 0){ // Si es de noche y ya flashearon los reflectores al inicio
            reflectores(LOW); //Inician apagados
            
          //Calculos para Prueba
          //byte minuto = random(1, 10);
          //int apagado = minuto*1000;
          //int encendido = apagado/10;
        
          //Calculos para la Aplicación
          int minuto = random(30, 61);//Asignar un minuto entre 30 y 60
          unsigned long segundos = minuto*60;
          unsigned long milisegundos = segundos*1000;
          unsigned long apagado = milisegundos;
          int encendido = (apagado/500); //Tiempo encendido 
          int pausa = encendido;//Pausa entre encendido y apagado de los reflectoress
          tiempo(apagado); //Durante tiempo calculado

          for(byte i = 0; i < numReflectores; i++){ //Enciende y apaga los reflectores
            digitalWrite(pinsReflectores[i], HIGH);
            tiempo(encendido);//Durante tiempo calculado
            digitalWrite(pinsReflectores[i], LOW);
            tiempo(pausa);//Durante tiempo calculado
        }
    }

    else{ 
        if(oscuridad > 400 && iniciaNoche == 0){//Durante el dia y ya flashearon al inicio
           reflectores(LOW);//Apagados durante el dia
        } 
        iniciaNoche = 1;//inicia bandera de evento cuando ya no se cumpla la condicion anterior
   }
}