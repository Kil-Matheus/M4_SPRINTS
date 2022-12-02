

int ponto1 = 0;
int ponto2 = 0;

AsyncWebServer server(80);

String html(){
    String html = "":
    html.concat("<head>")
    html.concat("<body>")
    html.concat("<div> Pontuação 1: ");
    html.concat(ponto1);


    return html;
}

void setup(){


    server("/", HTTP_GET, [](AsyncWebServer) *req{
        req->send(200, "html", html());
    });
}



void loop(){
    quando botao 1 for apertado{
        ponto1 +=1;
    }
    
    quando botao 2 for apertado{
        ponto2 +=1;
    }
}