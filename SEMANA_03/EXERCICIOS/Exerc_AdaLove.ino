#include <iostream>
using namespace std;

//Pinos led.
int led_4 = 6;
int led_3 = 18;
int led_2 = 9;
int led_1 = 14;

//Pinos Button;
int btn_verde = 5;
int btn_azul = 4; 

//LDR
int sensor_luz = 7;

//Buzzer
int buz = 12;

//Vetores
int leds[4]= {1,2,3,4};
int binar[4] = {0,0,0,0};
int vetor[1024];
int barulin[256];
int j =0;
int i =0;
int v =0;

  //Função LDR
  int ldr()
  {
    int valor = analogRead(sensor_luz);
    return normalizacao(valor);
  }

  //Função normalização do sensor LDR entre 0 e 15
  int normalizacao(int luz)
  {
    int valor = map(luz, 0, 4095, 15, 0);
    return valor;
  }

//Nova Binario
void binario(int bin)
{
  int res = 0;
  for(i=3; i>=0; i--){
    binar[i] = bin % 2;
    bin = bin/2;
  }
}

int main()
  {
    int valor_1 = ldr();
    int valor = ldr();
    binario(valor);
    int press = digitalRead(btn_verde);
    int press_2 = digitalRead(btn_azul);

    if(press == HIGH){
      // Serial.println(valor);
      digitalWrite(led_1, binar[0]);
      digitalWrite(led_2, binar[1]);
      digitalWrite(led_3, binar[2]);
      digitalWrite(led_4, binar[3]);
      tone(buz, 1000+(valor_1*100));
      delay(150);
      noTone(buz);
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, LOW);
      digitalWrite(led_3, LOW);
      digitalWrite(led_4, LOW);
      for(i=0 ; i<4 ; i++){
        vetor[j] = binar[i];
        j+=1;
      }
      barulin[v] = 1000+(valor_1*100);
      v += 1;
    }

    if(press_2 == HIGH){
      int l = 0;
      for(i = 0; i < j; i++){
        digitalWrite(led_1, vetor[l++]);
        digitalWrite(led_2, vetor[l++]);
        digitalWrite(led_3, vetor[l++]);
        digitalWrite(led_4, vetor[l++]);
        tone(buz, barulin[i]);
        delay(150);
        noTone(buz);        
      }
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, LOW);
      digitalWrite(led_3, LOW);
      digitalWrite(led_4, LOW);
      for(i=0; i<1024; i++){
        vetor[i]=0;
      }
      for(i=0; i<256; i++){
        barulin[i]=0;
      }
      j =0;
      v =0;
    }

  return 0;
  }
//ESP32
void setup() {
  Serial.begin(115200);
  // Serial.begin(9600);
  pinMode(led_4, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_1, OUTPUT);
  pinMode(btn_verde, INPUT_PULLUP);
  pinMode(btn_azul, INPUT_PULLUP);
  pinMode(sensor_luz, INPUT);
  pinMode(buz, OUTPUT);
}

void loop() {   
main();
}
