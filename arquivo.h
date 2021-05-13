#ifndef ARQUIVO_H
#define ARQUIVO_H

typedef struct dados Dados;

Dados* criaDados();
void setRam(Dados* dado);
void setMemoria(Dados* dado);
void atribuiValor(Dados* dado, int num1, int num2, int num3, int num4, int linha);
void maquina(Dados* dados, int num);
void multiplicacao(Dados* dado, int num);
void divisao(Dados* dado, int num);
void divisaoAprox(Dados* dado);
void exponencial(Dados* dado);
void radiciacao(Dados* dado);
void pa(Dados* dado);
void pg(Dados* dado);
void fatorial(Dados* dado);
double converteInt(int* vet, int sinal);
void liberaDados(Dados* dado);
void mostraDado(Dados* dado);
void escolha(Dados* dado);

#endif