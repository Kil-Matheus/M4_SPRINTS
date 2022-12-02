using namespace std;

// Pinos do Led RGB
#define azul      5
#define verde     7
#define vermelho  16

//Botões dos jogadores
#define p2        38
#define p1        39

//Variáveis
int rando;
int ponto_p1 = 0;
int ponto_p2 = 0;
int i = 0;
bool already_pressed = false;
// int contador = 0;
// int finish = 0;

//Função Led
void red(){
  digitalWrite(vermelho, HIGH);
}

void green(){
  digitalWrite(verde, HIGH);
}

void blue(){
  digitalWrite(azul, HIGH);
}

//Função resetar cores
void reset(){
  digitalWrite(azul, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, LOW);
}

//Função Pontuação
void pontuacao_p1(){
  if(already_pressed == false){
    if(rando == 1){
      ponto_p1 += 1;
      Serial.print("O play 1 marcou: "), Serial.println(ponto_p1);
      reset();
      } else {
      Serial.println("Game Over P1");
      Serial.println("Pontuação: ");
      Serial.print("Player 1: "), Serial.println(ponto_p1);
      Serial.print("Player 2: "), Serial.println(ponto_p2);
      ponto_p1 = -10;
      ponto_p2 = 0;
      // finish = 1;
      // i = 10;
      reset();
    }
    already_pressed = true;
  }
}

void pontuacao_p2(){
  if(already_pressed == false){
    if(rando == 1){
      ponto_p2 += 1;
      Serial.print("O play 2 marcou: "), Serial.println(ponto_p2);
      reset();
    } else {
      Serial.println("Game Over P2");
      Serial.println("Pontuação: ");
      Serial.print("Player 1: "), Serial.println(ponto_p1);
      Serial.print("Player 2: "), Serial.println(ponto_p2);
      ponto_p1 = 0;
      ponto_p2 = -10;
      // i = 10;
      // finish = 1;
      reset();
    }
    already_pressed = true;
  }
}


//Fim de jogo
void game_end(){
  if(ponto_p1 > ponto_p2){
    Serial.println("O Vencedor foi o Player 1");
    Serial.println("Com um total de pontos de "), Serial.print(ponto_p1);
  } else {
    Serial.println("O Vencedor foi o Player 2");
    Serial.println("Com um total de pontos de "), Serial.print(ponto_p2);
  }
}

//Programa Principal
int main(){
  bool status_p1 = digitalRead(p1);
  bool status_p2 = digitalRead(p2);
  // for(i=0; i<=10; i++){
    // while(contador <=10 || finish != 0){
      rando = rand() % 2;
      if(rando == 0){
        red();
        delay(2000);
        reset();
      }if(rando == 1){
        green();
        // contador++;
        delay(2000);
        reset();
      }
    // }
  already_pressed = false;
  reset();
//}
  // game_end();
  delay(3000);
  // i =0;
  // finish = 0;
  return 0;
}


void setup() {
  Serial.begin(9600);
  pinMode(azul, OUTPUT);//Define a variável azul como saída
  pinMode(verde, OUTPUT);//Define a variável verde como saída
  pinMode(vermelho, OUTPUT);//Define a variável vermelho como saída
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  attachInterrupt(p1, pontuacao_p1, RISING);
  attachInterrupt(p2, pontuacao_p2, RISING);
}

void loop() {
  main();
}
