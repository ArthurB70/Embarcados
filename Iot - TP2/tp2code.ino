#include "Ultrasonic.h"
#include "dht.h"
#define trigPin 13
#define echoPin 12
HC_SR04 sensor_ultrasonic(13,12);
dht DHT;

const int DHTPIN =  A1;
const int led_verde = 3;
const int led_amarelo = 7;
const int led_vermelho = 6; 
float distancia_cm = 0;
float temperatura = 0;
float luz = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led_verde, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
}

void loop() {
  exec_dht11_led_vermelho();
  exec_ultrassonic_led_verde();
  exec_rele_led_amarelo();
  print_dados_coletados();
}
void exec_dht11_led_vermelho(){
  DHT.read11(DHTPIN);
  !isnan(DHT.temperature) ? temperatura = DHT.temperature: temperatura = temperatura;
  temperatura >= 30 ? digitalWrite(led_vermelho, HIGH): digitalWrite(led_vermelho,LOW);
}
void exec_ultrassonic_led_verde(){
    distancia_cm = sensor_ultrasonic.distance();
    if(distancia_cm <= 30){
      digitalWrite(led_verde, HIGH);
      delay(func_distancia_delay(distancia_cm));
      digitalWrite(led_verde, LOW);
      delay(func_distancia_delay(distancia_cm));    
      }
    distancia_cm >= 900 ? digitalWrite(led_verde, HIGH): digitalWrite(led_verde, LOW);
}
void exec_rele_led_amarelo(){
  luz = analogRead(A0);
  if(luz >= 600){
    digitalWrite(led_amarelo, LOW);
    }
   else{
    digitalWrite(led_amarelo, HIGH);
    }
  }
void print_dados_coletados(){
  Serial.print("distancia: ");
  Serial.print(distancia_cm);
  Serial.print("\ttemperatura: ");
  Serial.print(temperatura);
  Serial.print("\tLDR: ");
  Serial.print(luz);
  Serial.println();
  }
float func_distancia_delay(float distancia){
   return (25*distancia)/2;
}
