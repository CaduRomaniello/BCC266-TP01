#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arquivo.h"

int main(){
	int opcao;
	Dados* dado = criaDados();
	setRam(dado);
	setMemoria(dado);
	//mostraDado(dado);
	//maquina(dado, 0);

	do{
		printf("\n");
		printf(" __________________________________\n");
		printf("|  __________CALCULADORA_________  |\n");
		printf("| |  __________________________  | |\n");
		printf("| | |                          | | |\n");
		printf("| | | [0]-Sair                 | | |\n");
		printf("| | | [1]-Soma                 | | |\n");
		printf("| | | [2]-Subtracao            | | |\n");
		printf("| | | [3]-Multiplicacao        | | |\n");
		printf("| | | [4]-Divisao inteira      | | |\n");
		printf("| | | [5]-Divisao aproximada   | | |\n");
		printf("| | | [6]-Exponencial          | | |\n");
		printf("| | | [7]-Radiciacao           | | |\n");
		printf("| | | [8]-P.A.                 | | |\n");
		printf("| | | [9]-P.G.                 | | |\n");
		printf("| | | [10]-Fatorial            | | |\n");
		printf("| | |__________________________| | |\n");
		printf("| |______________________________| |\n");
		printf("|__________________________________|\n");
		printf("\nDigite uma opcao valida: ");

		do{
			scanf("%d", &opcao);
			atribuiValor(dado, opcao, 0 ,0 ,0, 0);
			if (opcao < 0 || opcao > 10){
				printf("Comando invalido, digite novamente! \n");
			}
		}while (opcao < 0 || opcao > 10);
		escolha(dado);
	}while (opcao != 0);

	/*printf("Digite os numeros para multiplicacao: ");
	scanf("%d %d", &num1, &num2);
	multiplicacao(dado, num1, num2, 0);

	printf("Digite os numeros a serem divididos: ");
	scanf("%d %d", &num1, &num2);
	divisao(dado, num1, num2, 0);

	printf("Digite os numeros a serem divididos: ");
	scanf("%d %d", &num1, &num2);
	divisaoAprox(dado, num1, num2);

	printf("Digite a base e a potencia: ");
	scanf("%d %d", &num1, &num2);
	exponencial(dado, num1, num2);*/

	/*printf("Digite o numero para radiciacao: ");
	scanf("%d", &num1);
	radiciacao(dado, num1);*/

	/*printf("Digite nro inicial, razao e iteracoes: ");
	scanf("%d %d %d", &num1, &num2, &num3);
	pa(dado, num1, num2, num3);*/

	/*printf("Digite nro inicial, razao e iteracoes: ");
	scanf("%d %d %d", &num1, &num2, &num3);
	pg(dado, num1, num2, num3);	*/

	/*printf("Digite um numero: ");
	scanf("%d", &num1);
	fatorial(dado, num1);*/	

	liberaDados(dado);
	return 0;
}