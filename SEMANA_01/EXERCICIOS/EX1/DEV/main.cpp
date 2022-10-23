#include <iostream>
#include <string>

using namespace std;
// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente 
// entre dois valores mínimo e máximo e retorna esse valor

int numPorcento(int vter, int vmin, int vmax)
{
    int porcento;
	porcento = ((vter - vmin) * 100)/(vmax - vmin);

	// int p_comp = vmax - vter;
    // int s_comp = vter - vmin;

	// t1 = vmax - vmin;
	// t2 = vter - vmin;
    // if (p_comp > s_comp)
    // {   printf("O terceiro valor %d esta mais proximo do valor minimo %d, em %d porcento", vter, vmin, porcento);
    // }else if (p_comp < s_comp){
    //     printf("O terceiro valor %d esta mais proximo do valor maximo %d, em %d porcento", vter, vmax, porcento);
    // }else if (p_comp == s_comp){
    //     printf("O valor esta no meio, representando 50 porcento");
    // }
	printf("%d", porcento);
	return porcento;
}

// 2 - Faça uma função que simule a leitura de um sensor lendo o 
// valor do teclado ao final a função retorna este valor


int converteSensor(int valor, int vmin, int vmax) 
{
    // int valor;
    cout << "Digite um valor entre : " << vmin << " e " << vmax << "\n";
    scanf("%d", &valor);
    // printf("Sensor = " "%d", valor);
    return valor;   
}

// 3 - Faça uma função que armazena uma medida inteira qualquer 
// em um vetor fornecido. Note que como C não possui vetores 
// nativos da linguagem, lembre-se que você precisa passar o 
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em 
// uma área de memória fora do vetor

int insere(int novoValor, int index, int *v)
{
	int *array =v;
	array[index] = novoValor;
	return index + 1;
}


// 4 - Faça uma função que recebe um vetor com 4 posições que contém 
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção 
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a 
// segunda é esta maior distância.

char* direcaoMenorCaminho(int posicao[], int *maiorDirecao)
{	
	char* direcao[4] = {"Direita","Esquerda", "Frente", "Tras"};
	int index = 0;

	for (int i=0; i < 4; i++){
		if (posicao[i] > *maiorDirecao){
			*maiorDirecao = posicao[i];
			index = i;
		}
	}
// if (direcao[index] == "Direita"){
// 	return direcao[index];
// }
// if (direcao[index] == "Esquerda"){
// 	return direcao[index];
// }
// if (direcao[index] == "Frente"){
// 	return direcao[index];
// }
// if (direcao[index] == "Tras"){
// 	return direcao[index];
// }
    return direcao[index];
}


// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e 
// retorna verdadeiro ou falso

int leComando()
{
    int res;
    cout << "Do you want continue?: (y/n) \n";
    scanf("%c", &res);
    if(tolower(res) == 'n'){
		return res = 0;
	}
    return res = 1;
}


// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô 
// e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda", 
// "Frente", "Tras"). 
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno 
// para uma movimentação futura. 
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro 
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado 
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas 
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja 
// enviado pelo usuário. 
//
    //  Complete a função com a chamada das funções já criadas

int dirige(int *v,int maxv){
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;		
	while(dirigindo){		
		int medida = insere(medida, posAtualVetor, vetorMov);
		medida = converteSensor(medida,0,830);
		posAtualVetor = insere(medida, posAtualVetor, vetorMov);
		medida = converteSensor(medida,1,830);
		posAtualVetor = insere(medida, posAtualVetor, vetorMov);
		medida = converteSensor(medida,2,830);
		posAtualVetor = insere(medida, posAtualVetor, vetorMov);
		medida = converteSensor(medida,3,830);
		posAtualVetor = insere(medida, posAtualVetor, vetorMov);
		dirigindo = leComando();		
	}
	return posAtualVetor;
}


// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado 
// na maior distância a cada movimento
void percorre(int *v,int tamPercorrido){		
	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){

		char *direcao = direcaoMenorCaminho(&(vetorMov[i]),&maiorDir);
		printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);
	}
}

int main(int argc, char** argv) {
	int maxVetor = 100;
	int vetorMov[maxVetor*4];
	int posAtualVet = 0;
	
	posAtualVet = dirige(vetorMov,maxVetor);
	percorre(vetorMov,posAtualVet);
	
	return 0;
}