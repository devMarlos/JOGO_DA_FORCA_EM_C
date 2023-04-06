#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

// Variaveis globais
char palavra[TAMANHO_PALAVRA];
char chutes[26];
int tentativas = 0, i, j;


int main() {
	
	abertura();
	escolhePalavra();
	
	
	do{
		// começar o nosso jogo!!
		
		desenhaForca();
		chuta();
		
	}while(!acertou() && !enforcou() );
	
	if(acertou()){
		 printf("\nParabens, voce ganhou!\n\n");
		 printf("A palavra era **%s**\n\n", palavra);

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

	}else{
		printf("\nPuxa, voce foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavra);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    
	}
	
}

void abertura(){
	printf("********************\n");
	printf("*   Jogo da Forca  *\n");
	printf("********************\n");
}

void chuta(){
	// Captura um novo chute
	char chute;
	scanf(" %c", &chute);	
	chutes[tentativas] = chute;
	tentativas++;	
}

int jaChutou(char letra){
		int achou = 0;
			 
		// A letra já foi chutada ?
		for(j = 0; j < tentativas; j++){
			if(chutes[j] == letra){
				achou = 1;
				break;
			}
		}
		return achou;
}

void desenhaForca(){
	int i, erros = chutesErrados();
	
	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
	    (erros>=1?'_':' '), (erros>=1?')':' '));
	printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
	    (erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |       %c     \n", (erros>=2?'|':' '));
	printf(" |      %c %c   \n", (erros>=4?'/':' '), 
	    (erros>=4?'\\':' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");
	//Imprime a palavra secreta
	for(i = 0; i < strlen(palavra); i++){
		
	int achou = jaChutou(palavra[i]);
			
		if(achou){
			printf("%c ", palavra[i]);
		} else{
			printf("_ ");
		}
	}
	printf("\n");
}

int chutesErrados(){
	int erros = 0;
	
	for(i = 0; i < tentativas; i++){
		int existe = 0;
		for(j = 0; j < strlen(palavra); j++){
			if(chutes[i] == palavra[j]){
				existe = 1;
				break;
			}
		}
		if(!existe) erros++;
	}
	return erros;
}

int enforcou(){
	return chutesErrados() >=5;
}

int acertou(){
	for(i = 0; i < strlen(palavra); i++){
		if(!jaChutou(palavra[i])){
			return 0;
		}
	}
	return 1;
}

void adicionaPalavra() {
	char quer;
	printf("Voce deseja adicionar uma nova palavra no jogo ? (S/N)");
	scanf(" %c", &quer);
	
	if(quer == 'S'){
		char novapalavra[TAMANHO_PALAVRA];
		printf("Qual a palavra nova? ");
		scanf("%s", novapalavra);
		
		FILE* f;
		
		f = fopen("palavras.txt", "r+");
		if(f == 0){
			printf("Arquivo não lido \n\n");
			exit(1);
		}
		
		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;
		
		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);
		
		fseek(f, 0, SEEK_END);
		fprintf(f, "%s", novapalavra);
	}
}

void escolhePalavra(){
	// Função para ler arquivos 
	// utilizamos o "r" de READ - LER
	FILE* f;
	f = fopen("palavras.txt", "r");
	if( f == NULL){
		printf("Arquivo nao lido\n\n");
		exit(1);
	}
	int qtdDePalavras;
	fscanf(f, "%d", &qtdDePalavras);
	
	srand(time(0));
	int randomico = rand() % qtdDePalavras;
	
	for(i = 0; i <= randomico; i++){
		fscanf(f, "%s", palavra);
	}
	
	fclose(f);
}

