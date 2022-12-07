#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#define I2C_SDA  47
#define I2C_SCL  48
#define buz      35
LiquidCrystal_I2C  lcd(0x27, 16, 2);

//Rede para conexão Web
const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";
const char* PARAM_MENSAGEM = "mensagem";

//Minha página será servida na Rede. Com o porta 8080;
AsyncWebServer server(80);

//HTML com CSS (Página que será servida.)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Exerc Fessor Adré</title>
</head>
<body style="display: flex; justify-items: auto; justify-content: center;">
    <form action="/get">
        <div style="border-style: dashed; padding: 10px;">
            <label>Digite a sua mensagem<br>
            <input type="text" name="mensagem" required>
            </label>
            <button type="submit">LCD</button>
        </div>
    </form>
</body>
</html>
)rawliteral";


void setup() {
  Serial.begin(115200);
//Iniciando Variávies do Buzzer e do LCD
  pinMode(buz, OUTPUT);
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();
  lcd.print("Bem-Vindo");

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    lcd.setCursor(0, 1);
    Serial.println("Connecting to WiFi..");
    lcd.print("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  lcd.clear();
  Serial.print("IP: "); Serial.println(WiFi.localIP());
  lcd.print("IP LocalHost: ");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());  


   // Servidor rodando, servindo a página
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  //API que faz um requisição Get
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    request->send_P(200, "text/html", index_html);
    if (request->hasParam(PARAM_MENSAGEM)) {
      inputMessage = request->getParam(PARAM_MENSAGEM)->value();
      lcd.clear();
      Serial.print("Mensagem: ");
      Serial.println(inputMessage);
      lcd.print("Mensagem: ");
      lcd.setCursor(0, 1);
      lcd.print(inputMessage);
      tone(buz, 500, 1000);
      delay(2000);
      lcd.clear();
      lcd.print("Digite no HTML");
      };
    });
  server.begin();
}

void loop() {
}
