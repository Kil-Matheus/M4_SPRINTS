#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// Pinos do Led RGB
#define azul 5
#define verde 7
#define vermelho 16

//Botões dos jogadores
#define p2 38
#define p1 39

//Variáveis
int rando;
int ponto_p1 = 0;
int ponto_p2 = 0;
int i = 0;
bool already_pressed = false;

//Definições do Wi-Fi
const char *ssid = "inteli.kil";      //Digite o nome da sua rede aqui
const char *password = "kilmatheus";  //Digite a senha da rede, deve conter no mínimo 8 caractéres se não dá erro.
WebServer server(80);

//Função Led
void red() {
  digitalWrite(vermelho, HIGH);
}

void green() {
  digitalWrite(verde, HIGH);
}

void blue() {
  digitalWrite(azul, HIGH);
}

//Função resetar cores
void reset() {
  digitalWrite(azul, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, LOW);
}

//Função Pontuação
void pontuacao_p1() {
  if (already_pressed == false) {
    if (rando == 1) {
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

void pontuacao_p2() {
  if (already_pressed == false) {
    if (rando == 1) {
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
void game_end() {
  if (ponto_p1 > ponto_p2) {
    Serial.println("O Vencedor foi o Player 1");
    Serial.println("Com um total de pontos de "), Serial.print(ponto_p1);
  } else {
    Serial.println("O Vencedor foi o Player 2");
    Serial.println("Com um total de pontos de "), Serial.print(ponto_p2);
  }
}

//Programa Principal
int main() {
  bool status_p1 = digitalRead(p1);
  bool status_p2 = digitalRead(p2);
  // for(i=0; i<=10; i++){
  // while(contador <=10 || finish != 0){
  rando = rand() % 2;
  if (rando == 0) {
    red();
    delay(2000);
    reset();
  }
  if (rando == 1) {
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
  Serial.begin(115200);
  pinMode(azul, OUTPUT);      //Define a variável azul como saída
  pinMode(verde, OUTPUT);     //Define a variável verde como saída
  pinMode(vermelho, OUTPUT);  //Define a variável vermelho como saída
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  attachInterrupt(p1, pontuacao_p1, RISING);
  attachInterrupt(p2, pontuacao_p2, RISING);

  WiFi.softAP(ssid, password);  // remova "password" caso não queria que o Wi-Fi tenha senha
  IPAddress ESP_IP = WiFi.softAPIP();
  Serial.print("Wi-Fi: ");
  Serial.println(ssid);
  Serial.print("IP: ");  // O IP que aparecer aqui coloque no navegador para acessar a página web do ESP32 que será criada logo abaixo.
  Serial.println(ESP_IP);
  server.begin();
  Serial.println("Servidor Iniciado.");
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.on("/p1", handleOn);
  server.on("/p2", handleOff);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void handleRoot() {
  String html = "";
  html += "<!DOCTYPE html>";
  html += "<html lang='pt-br'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta http-equiv='X-UA-Compatible' content='IE=edge'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<meta http-equiv='refresh' content= 1>";
  html += "<title>Reflexo</title>";
  html += "</head>";
  html += "<body style='display: flex; align-items: center; justify-content: center;'>";
  html += "<div style='width: 70%; border-style: dashed; text-align: center; margin-top: 100px; padding: 20px;'>";
  html += "<div style='border-style: dashed; text-align: center; padding: 20px; font-size: 80px; float: left;' id='bloco1'>";
  html += ponto_p1;
  html += "</div>";
  html += "<div style='border-style: dashed; text-align: center; padding: 20px; font-size: 80px; float: right;'id='bloco3'>";
  html += ponto_p2;
  html += "</div>";
  html += "<div style='border-style: dashed; text-align: center; padding: 20px; font-size: 60px; width: 40%; margin-left: auto; margin-right: auto; margin-top: 4%;' id='bloco2'></div>";
  html += "</div>";
  html += "</body>";
  html += "</html>";
  server.send(200, "text/html", html);
}
void handleOn() {

  handleRoot();
}
void handleOff() {

  handleRoot();
}
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
void loop() {
  main();
  server.handleClient();
  delay(2);
}