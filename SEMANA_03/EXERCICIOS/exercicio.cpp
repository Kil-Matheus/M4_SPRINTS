
int binario(int valor)
//8126 há 64
{  int resultado;
    while (valor != 0)
    {
        resultado += ( valor % 2 == 0 ? 0 : 1 );
        valor /= 2;
    }
    Serial.println(resultado);
    return 0;