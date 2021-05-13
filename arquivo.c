#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "arquivo.h"

struct dados{
	int* ramInt;
	double* ramDouble;
	int** memoriaInstrucoes;
};

Dados* criaDados(){
	Dados* dado = malloc(sizeof(Dados));
	dado->ramInt = malloc(100 * sizeof(int));
	dado->ramDouble = malloc(100 * sizeof(double));
	dado->memoriaInstrucoes = malloc(1000 * sizeof(int*));
	for (int i = 0; i < 1000; i++){
		dado->memoriaInstrucoes[i] = malloc(5 * sizeof(int));
	}
	return dado;
}

void setRam(Dados* dado){
	for (int i = 0; i < 100; i++){
		dado->ramInt[i] = 0;
	}
	for (int i = 0; i < 100; i++){
		dado->ramDouble[i] = 0.0;
	}
}

void setMemoria(Dados* dado){
	srand(time(NULL));
	for (int i = 0; i < 999; i++){
		int* vet = malloc(4 * sizeof(int));
		vet[0] = rand() % 2;
		vet[1] = rand() % 100;
		vet[2] = rand() % 100;
		vet[3] = rand() % 100;

		for (int j = 0; j < 4; j++){
			dado->memoriaInstrucoes[i][j] = vet[j];
		}

		free(vet);
	} 
	int vet[4];
	vet[0] = -1;
	vet[1] = -1;
	vet[2] = -1;
	vet[3] = -1;
	for (int j = 0; j < 4; j++){
		dado->memoriaInstrucoes[999][j] = vet[j];
	}	
	/*for (int i = 0; i < 10; i++){
		for (int j = 0; j < 4; j++){
			printf("/%d/", dado->memoriaInstrucoes[i][j]);
		}
		printf("\n");
	}*/
}

void atribuiValor(Dados* dado, int num1, int num2, int num3, int num4, int linha){
	dado->memoriaInstrucoes[linha][0] = num1;
	dado->memoriaInstrucoes[linha][1] = num2;
	dado->memoriaInstrucoes[linha][2] = num3;
	dado->memoriaInstrucoes[linha][3] = num4;
	/*for (int i = 0; i < 4; i++){
		printf(" * %d * ", dado->memoriaInstrucoes[linha][i]);
	}
	printf("\n");*/
}

void maquina(Dados* dado, int num){
	int cont = 0;
	int opcode = INT_MAX;
	int end1, end2, end3;
	int conteudoRam1, conteudoRam2;
	int soma, sub;
	int* instrucao;

	while (opcode != -1){
		instrucao = dado->memoriaInstrucoes[cont];
		/*for (int i = 0; i < 4; i++){
			printf(" / %d / ", instrucao[i]);
		}
		printf("\n");*/
		opcode = instrucao[0];
		switch(opcode){
			case 0:
				end1 = instrucao[1];
				end2 = instrucao[2];
				end3 = instrucao[3];
				conteudoRam1 = dado->ramInt[end1];
				conteudoRam2 = dado->ramInt[end2];
				soma = conteudoRam1 + conteudoRam2;
				dado->ramInt[end3] = soma;

				if (num == 0){
					printf("\n%d + %d = %d\n", conteudoRam1, conteudoRam2,soma);
				}
				break;
			case 1:
				end1 = instrucao[1];
				end2 = instrucao[2];
				end3 = instrucao[3];

				conteudoRam1 = dado->ramInt[end1];
				conteudoRam2 = dado->ramInt[end2];
				sub = conteudoRam1 - conteudoRam2;
				dado->ramInt[end3] = sub;

				if (num == 0){
					printf("\n%d - %d = %d\n", conteudoRam1, conteudoRam2, sub);
				}
				break;
			case 2:
				dado->ramInt[instrucao[2]] = instrucao[1];
				break;
		}
		cont++;
	}
}

void multiplicacao(Dados* dado, int num){
	int num1 = dado->memoriaInstrucoes[0][1];
	int num2 = dado->memoriaInstrucoes[0][2];
	int instrucao[4];

	instrucao[0] = 2;
	instrucao[1] = num1;
	instrucao[2] = 0;
	instrucao[3] = -1;
	for (int j = 0; j < 4; j++){
		dado->memoriaInstrucoes[0][j] = instrucao[j];
	}

	instrucao[0] = 2;
	instrucao[1] = 0;
	instrucao[2] = 1;
	instrucao[3] = -1;
	for (int j = 0; j < 4; j++){
		dado->memoriaInstrucoes[1][j] = instrucao[j];
	}

	for (int i = 0; i < num2; i++){
		instrucao[0] = 0;
		instrucao[1] = 0;
		instrucao[2] = 1;
		instrucao[3] = 1;
		for (int j = 0; j < 4; j++){
			dado->memoriaInstrucoes[i + 2][j] = instrucao[j];
		}
	}
	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	for (int j = 0; j < 4; j++){
		dado->memoriaInstrucoes[num2 + 2][j] = instrucao[j];
	}
	//mostraDado(dado);

	maquina(dado, 1);

	if (num == 0){
		printf("\n%d * %d = %d\n", num1, num2, dado->ramInt[1]);
	}
	dado->ramDouble[1] = (double)dado->ramInt[1];
}

void divisao(Dados* dado, int num){
	int dividendo = dado->memoriaInstrucoes[0][1];
	int divisor = dado->memoriaInstrucoes[0][2];
	int cont = 0;
	int instrucao[4];
	instrucao[0] = 2;
	instrucao[1] = dividendo;
	instrucao[2] = 0;
	instrucao[3] = -1;
	for (int j = 0; j < 4; j++){
		dado->memoriaInstrucoes[0][j] = instrucao[j];
	}

	instrucao[0] = 2;
	instrucao[1] = divisor;
	instrucao[2] = 1;
	instrucao[3] = -1;
	for (int j = 0; j < 4; j++){
		dado->memoriaInstrucoes[1][j] = instrucao[j];
	}

	instrucao[0] = -1;
	instrucao[1] = -1;
	instrucao[2] = -1;
	instrucao[3] = -1;
	for (int j = 0; j < 4; j++){
		dado->memoriaInstrucoes[2][j] = instrucao[j];
	}

	maquina(dado, 1);

	while (dado->ramInt[0] >= dado->ramInt[1]){
		instrucao[0] = 1;
		instrucao[1] = 0;
		instrucao[2] = 1;
		instrucao[3] = 0;
		for (int j = 0; j < 4; j++){
			dado->memoriaInstrucoes[0][j] = instrucao[j];
		}

		instrucao[0] = -1;
		instrucao[1] = -1;
		instrucao[2] = -1;
		instrucao[3] = -1;
		for (int j = 0; j < 4; j++){
			dado->memoriaInstrucoes[1][j] = instrucao[j];
		}

		maquina(dado, 1);

		cont++;
	}
	if (num == 0){
		printf("\n%d / %d = %d\n", dividendo, divisor, cont);
	}
	else{
		dado->ramInt[2] = cont;
	}
}

void divisaoAprox(Dados* dado){
	int dividendo = dado->memoriaInstrucoes[0][1];
	int divisor = dado->memoriaInstrucoes[0][2];
	int vet[3];
	double resultado;

	atribuiValor(dado, -1, dividendo, divisor, -1, 0);
	divisao(dado, 1);
	vet[0] = dado->ramInt[2];

	atribuiValor(dado, -1, dado->ramInt[0], 10, -1, 0);
	multiplicacao(dado, 1);

	if (dado->ramInt[1] < divisor){
		vet[1] = 0;
		atribuiValor(dado, -1, dado->ramInt[1], 10, -1, 0);
		multiplicacao(dado, 1);
		if(dado->ramInt[1] < divisor){
			vet[2] = 0;
		}
		else{
			atribuiValor(dado, -1, dado->ramInt[1], divisor, -1, 0);
			divisao(dado, 1);
			vet[2] = dado->ramInt[2];
		}
	}
	else{
		atribuiValor(dado, -1, dado->ramInt[1], divisor, -1, 0);
		divisao(dado, 1);
		vet[1] = dado->ramInt[2];
		atribuiValor(dado, -1, dado->ramInt[0], 10, -1, 0);
		multiplicacao(dado, 1);
		if (dado->ramInt[1] < divisor){
			vet[2] = 0;
		}
		else{
			atribuiValor(dado, -1, dado->ramInt[1], divisor, -1, 0);
			divisao(dado, 1);
			vet[2] = dado->ramInt[2];
		}
	}

	resultado = converteInt(vet, 1);
	dado->ramDouble[0] = resultado;

	printf("\n%d / %d eh aproximadamente %.2lf\n", dividendo, divisor, resultado);
}

void exponencial(Dados* dado){
	int num1 = dado->memoriaInstrucoes[0][1];
	int num2 = dado->memoriaInstrucoes[0][2];
	printf("*%d %d*\n", num1, num2);

	double aux = num1;
	for (int i = 0; i < num2 - 1; i++){
		atribuiValor(dado, -1, aux, num1, -1, 0);
		multiplicacao(dado, 1);
		aux = dado->ramDouble[1];
	}
	printf("\n%d ^ %d = %.0lf\n", num1, num2, aux);
}

void radiciacao(Dados* dado){
	int num1 = dado->memoriaInstrucoes[0][1];
	int aux1 = num1;
	int cont = 0;
	int temp = 1;
	int aux2, aux3;
	int temp2, temp3;
	int vet[3];
	double resultado;

	while (aux1 >= temp){
		dado->memoriaInstrucoes[0][0] = 2;
		dado->memoriaInstrucoes[0][1] = aux1;
		dado->memoriaInstrucoes[0][2] = 1;
		dado->memoriaInstrucoes[0][3] = -1;

		dado->memoriaInstrucoes[1][0] = 2;
		dado->memoriaInstrucoes[1][1] = temp;
		dado->memoriaInstrucoes[1][2] = 2;
		dado->memoriaInstrucoes[1][3] = -1;

		dado->memoriaInstrucoes[2][0] = -1;
		dado->memoriaInstrucoes[2][1] = -1;
		dado->memoriaInstrucoes[2][2] = -1;
		dado->memoriaInstrucoes[2][3] = -1;

		maquina(dado, 1);

		dado->memoriaInstrucoes[0][0] = 1;
		dado->memoriaInstrucoes[0][1] = 1;
		dado->memoriaInstrucoes[0][2] = 2;
		dado->memoriaInstrucoes[0][3] = 7;

		dado->memoriaInstrucoes[1][0] = -1;
		dado->memoriaInstrucoes[1][1] = -1;
		dado->memoriaInstrucoes[1][2] = -1;
		dado->memoriaInstrucoes[1][3] = -1;

		maquina(dado, 1);

		aux1 = dado->ramInt[7];

		temp += 2;

		cont++;
	}
	//printf("1-cont = %d\n", cont);
	dado->ramInt[10] = cont;

	atribuiValor(dado, -1, aux1, 100, -1, 0);
	multiplicacao(dado, 1);
	aux2 = dado->ramInt[1];
	atribuiValor(dado, -1, cont, 20, -1, 0);
	multiplicacao(dado, 1);
	aux3 = dado->ramInt[1];
	aux3++;

	cont = 0;
	while (aux2 >= aux3){
		dado->memoriaInstrucoes[0][0] = 2;
		dado->memoriaInstrucoes[0][1] = aux2;
		dado->memoriaInstrucoes[0][2] = 1;
		dado->memoriaInstrucoes[0][3] = -1;

		dado->memoriaInstrucoes[1][0] = 2;
		dado->memoriaInstrucoes[1][1] = aux3;
		dado->memoriaInstrucoes[1][2] = 2;
		dado->memoriaInstrucoes[1][3] = -1;

		dado->memoriaInstrucoes[2][0] = -1;
		dado->memoriaInstrucoes[2][1] = -1;
		dado->memoriaInstrucoes[2][2] = -1;
		dado->memoriaInstrucoes[2][3] = -1;

		maquina(dado, 1);

		dado->memoriaInstrucoes[0][0] = 1;
		dado->memoriaInstrucoes[0][1] = 1;
		dado->memoriaInstrucoes[0][2] = 2;
		dado->memoriaInstrucoes[0][3] = 7;

		dado->memoriaInstrucoes[1][0] = -1;
		dado->memoriaInstrucoes[1][1] = -1;
		dado->memoriaInstrucoes[1][2] = -1;
		dado->memoriaInstrucoes[1][3] = -1;

		maquina(dado, 1);

		aux2 = dado->ramInt[7];

		aux3 += 2;

		cont++;
	}
	//printf("2-cont = %d\n", cont);
	dado->ramInt[11] = cont;

	atribuiValor(dado, -1, aux2, 100, -1, 0);
	multiplicacao(dado, 1);
	aux2 = dado->ramInt[1];
	atribuiValor(dado, -1, dado->ramInt[10], 10, -1, 0);
	multiplicacao(dado, 1);
	temp2 = dado->ramInt[1];

	dado->memoriaInstrucoes[0][0] = 2;
	dado->memoriaInstrucoes[0][1] = temp2;
	dado->memoriaInstrucoes[0][2] = 1;
	dado->memoriaInstrucoes[0][3] = -1;

	dado->memoriaInstrucoes[1][0] = 2;
	dado->memoriaInstrucoes[1][1] = dado->ramInt[11];
	dado->memoriaInstrucoes[1][2] = 2;
	dado->memoriaInstrucoes[1][3] = -1;

	dado->memoriaInstrucoes[2][0] = -1;
	dado->memoriaInstrucoes[2][1] = -1;
	dado->memoriaInstrucoes[2][2] = -1;
	dado->memoriaInstrucoes[2][3] = -1;

	maquina(dado, 1);

	dado->memoriaInstrucoes[0][0] = 0;
	dado->memoriaInstrucoes[0][1] = 1;
	dado->memoriaInstrucoes[0][2] = 2;
	dado->memoriaInstrucoes[0][3] = 1;

	dado->memoriaInstrucoes[1][0] = -1;
	dado->memoriaInstrucoes[1][1] = -1;
	dado->memoriaInstrucoes[1][2] = -1;
	dado->memoriaInstrucoes[1][3] = -1;

	maquina(dado, 1);

	temp3 = dado->ramInt[1];
	atribuiValor(dado, -1, temp3, 20, -1, 0);
	multiplicacao(dado, 1);
	aux3 = dado->ramInt[1] + 1;
	//printf("//%d %d//\n", aux2, aux3);

	cont = 0;
	while (aux2 >= aux3){
		dado->memoriaInstrucoes[0][0] = 2;
		dado->memoriaInstrucoes[0][1] = aux2;
		dado->memoriaInstrucoes[0][2] = 1;
		dado->memoriaInstrucoes[0][3] = -1;

		dado->memoriaInstrucoes[1][0] = 2;
		dado->memoriaInstrucoes[1][1] = aux3;
		dado->memoriaInstrucoes[1][2] = 2;
		dado->memoriaInstrucoes[1][3] = -1;

		dado->memoriaInstrucoes[2][0] = -1;
		dado->memoriaInstrucoes[2][1] = -1;
		dado->memoriaInstrucoes[2][2] = -1;
		dado->memoriaInstrucoes[2][3] = -1;

		maquina(dado, 1);

		dado->memoriaInstrucoes[0][0] = 1;
		dado->memoriaInstrucoes[0][1] = 1;
		dado->memoriaInstrucoes[0][2] = 2;
		dado->memoriaInstrucoes[0][3] = 7;

		dado->memoriaInstrucoes[1][0] = -1;
		dado->memoriaInstrucoes[1][1] = -1;
		dado->memoriaInstrucoes[1][2] = -1;
		dado->memoriaInstrucoes[1][3] = -1;

		maquina(dado, 1);

		aux2 = dado->ramInt[7];

		aux3 += 2;

		cont++;
	}
	//printf("3-cont = %d\n", cont);
	dado->ramInt[12] = cont;

	vet[0] = dado->ramInt[10];
	vet[1] = dado->ramInt[11];
	vet[2] = dado->ramInt[12];

	resultado = converteInt(vet, 1);

	printf("\nA raiz quadrada de %d eh %.2lf\n", num1, resultado);
}

void pa(Dados* dado){
	int num1 = dado->memoriaInstrucoes[0][1];
	int num2 = dado->memoriaInstrucoes[0][2];
	int num3 = dado->memoriaInstrucoes[0][3];

	int aux = num1;
	//printf("%d %d %d\n", num1, num2, num3);

	printf("\n * %d * ", aux);

	for (int i = 1; i < num3; i++){
		dado->memoriaInstrucoes[0][0] = 2;
		dado->memoriaInstrucoes[0][1] = aux;
		dado->memoriaInstrucoes[0][2] = 0;
		dado->memoriaInstrucoes[0][3] = -1;
		//printf("//%d//\n", dado->ramInt[1]);

		dado->memoriaInstrucoes[1][0] = 2;
		dado->memoriaInstrucoes[1][1] = num2;
		dado->memoriaInstrucoes[1][2] = 1;
		dado->memoriaInstrucoes[1][3] = -1;
		//printf("//%d//\n", dado->ramInt[2]);

		dado->memoriaInstrucoes[2][0] = 0;
		dado->memoriaInstrucoes[2][1] = 0;
		dado->memoriaInstrucoes[2][2] = 1;
		dado->memoriaInstrucoes[2][3] = 4;

		dado->memoriaInstrucoes[3][0] = -1;
		dado->memoriaInstrucoes[3][1] = -1;
		dado->memoriaInstrucoes[3][2] = -1;
		dado->memoriaInstrucoes[3][3] = -1;

		maquina(dado, 1);

		aux = dado->ramInt[4];
		printf(" * %d * ", aux);
	}
	printf("\n");
}

void pg(Dados* dado){
	int num1 = dado->memoriaInstrucoes[0][1];
	int num2 = dado->memoriaInstrucoes[0][2];
	int num3 = dado->memoriaInstrucoes[0][3];

	int aux = num1;

	printf("\n * %d * ", aux);

	for (int i =1; i < num3; i++){
		atribuiValor(dado, -1, aux, num2, -1, 0);
		multiplicacao(dado, 1);
		aux = dado->ramInt[1];
		printf(" * %.0lf * ", (double)aux);
	}
	printf("\n");
}

void fatorial(Dados* dado){
	int num1 = dado->memoriaInstrucoes[0][1];
	int aux = num1;
	int aux2 = 1;

	for (int i = num1; i > 0; i--){
		dado->memoriaInstrucoes[0][0] = 2;
		dado->memoriaInstrucoes[0][1] = aux2;
		dado->memoriaInstrucoes[0][2] = 0;
		dado->memoriaInstrucoes[0][3] = -1;
		//printf("%d\n", dado->ramInt[0]);

		dado->memoriaInstrucoes[1][0] = 2;
		dado->memoriaInstrucoes[1][1] = aux;
		dado->memoriaInstrucoes[1][2] = 1;
		dado->memoriaInstrucoes[1][3] = -1;
		//printf("%d\n", dado->ramInt[1]);

		dado->memoriaInstrucoes[2][0] = -1;
		dado->memoriaInstrucoes[2][1] = -1;
		dado->memoriaInstrucoes[2][2] = -1;
		dado->memoriaInstrucoes[2][3] = -1;

		maquina(dado, 1);

		atribuiValor(dado, -1, dado->ramInt[0], dado->ramInt[1], -1, 0);
		multiplicacao(dado, 1);
		aux2 = dado->ramInt[1];
		aux--;
	}

	printf("\n%d! eh igual a %d\n", num1, aux2);
}

double converteInt(int* vet, int sinal){
    char vetor[4];
    double aux;
    double num;
    /*for (int i = 0; i < 3; i++){
         printf("*%d*", vet[i]);
    }*/
    //printf("\n");
    sprintf(vetor, "%d.%d%d", vet[0], vet[1], vet[2]);
    //printf("%s\n", vetor);
    num = atof(vetor);
    //printf("%.2lf\n", num);
    if (sinal == -1){      
        for (int i = 0; i < 2; i++){
            aux -= num;
        }
        return aux;
    }
    return num;
}

void liberaDados(Dados* dado){
	free(dado->ramInt);
	free(dado->ramDouble);
	for (int i = 0; i < 10; i++){
		free(dado->memoriaInstrucoes[i]);
	}
	free(dado->memoriaInstrucoes);
	free(dado);
}

void mostraDado(Dados* dado){
	/*for (int i = 0; i < 100; i++){
		printf("/%d/", dado->ram[i]);
	}*/
	printf("\n");
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 5; j++){
			printf("&%d&\n", dado->memoriaInstrucoes[i][j]);
		}
		printf("\n");
	}
}

void escolha(Dados* dado){
	int num1, num2, num3;
	int opcao = dado->memoriaInstrucoes[0][0]; 
	switch(opcao){
		case(0):
			printf("\nAte a proxima!\n");
			break;
		case(1):
			printf("Digite os numeros que deseja somar: ");
			scanf("%d %d", &num1, &num2);
			atribuiValor(dado, 2, num1, 0, -1, 0);
			atribuiValor(dado, 2, num2, 1, -1, 1);
			atribuiValor(dado, 0, 0, 1, 2, 2);
			atribuiValor(dado, -1, -1, -1, -1, 3);
			maquina(dado, 0);
			break;
		case(2):
			printf("Digite os numeros que deseja subtrair: ");
			scanf("%d %d", &num1, &num2);
			atribuiValor(dado, 2, num1, 0, -1, 0);
			atribuiValor(dado, 2, num2, 1, -1, 1);
			atribuiValor(dado, 1, 0, 1, 2, 2);
			atribuiValor(dado, -1, -1, -1, -1, 3);
			maquina(dado, 0);
			break;
		case(3):
			printf("Digite os numeros que deseja multiplicar: ");
			scanf("%d %d", &num1, &num2);
			atribuiValor(dado, -1, num1, num2, -1, 0);
			multiplicacao(dado, 0);
			break;
		case(4):
			printf("Digite os numeros que deseja dividir: ");
			scanf("%d %d", &num1, &num2);
			atribuiValor(dado, -1, num1, num2, -1, 0);
			divisao(dado, 0);
			break;
		case(5):
			printf("Digite os numeros que deseja dividir: ");
			scanf("%d %d", &num1, &num2);
			atribuiValor(dado, -1, num1, num2, -1, 0);
			divisaoAprox(dado);
			break;
		case(6):
			printf("Digite a base e o expoente: ");
			scanf("%d %d", &num1, &num2);
			atribuiValor(dado, -1, num1, num2, -1, 0);
			exponencial(dado);
			break;
		case(7):
			printf("Digite um numero para saber sua raiz quadrada: ");
			scanf("%d", &num1);
			atribuiValor(dado, -1, num1, -1, -1, 0);
			radiciacao(dado);
			break;
		case(8):
			printf("Digite o primeiro termo, a razao e a quantidade de termos: ");
			scanf("%d %d %d", &num1, &num2, &num3);
			atribuiValor(dado, -1, num1, num2, num3, 0);
			pa(dado);
			break;
		case(9):
			printf("Digite o primeiro termo, a razao e a quantidade de termos: ");
			scanf("%d %d %d", &num1, &num2, &num3);
			atribuiValor(dado, -1, num1, num2, num3, 0);
			pg(dado);
			break;
		case(10):
			printf("Digite um numeo para saber seu fatorial: ");
			scanf("%d", &num1);
			atribuiValor(dado, -1, num1, -1, -1, 0);
			fatorial(dado);
			break;
	}
}