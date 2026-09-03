#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if (argc > 2){
	printf("Invalid number of arguments.\n");
	printf("Correct use: %s --filename\n", argv[0]);
	return 1;
    }


    FILE *arquivo = fopen(argv[1], "r");


    int FITA = 100;
    int caractere;
    int celulas[100];
    int pont = 0;
    int counter = 0;
    char codigo[10000];
    int len = 0; //comprimento do código brainfuck
    int input;


    //inicializacao da fita
    for (int i = 0; i < FITA; i++){
	celulas[i] = 0;
    }
    
    //caso o arquivo não exista
    if(arquivo == NULL) {
	printf("File does not exist.\n");
	return 2;
    }
    
    char buffer[256];

    while((caractere = fgetc(arquivo)) != EOF && len < 10000 - 1){
	codigo[len++] = (char)caractere;
    }
    codigo[len] = '\0';

    fclose(arquivo);

   while (counter < len) {
	int caractere_atual = codigo[counter];


	if(caractere_atual == '+'){
	    celulas[pont] = (celulas[pont] + 1) % 256;
	}else if(caractere_atual == '-'){
	    celulas[pont] = (celulas[pont] - 1 + 256) % 256;

	}else if(caractere_atual == '>'){
	    if (pont < FITA - 1){
		pont ++;
	    }

	}else if(caractere_atual == '<'){
	    if (pont > 0){
		pont --;
	    }
	}else if(caractere_atual == ':'){
	    printf("%i", celulas[pont]);
	}

	else if(caractere_atual == '.'){
	    printf("%c", celulas[pont]);
	}

	else if(caractere_atual == ','){

	    if(scanf("%d", &input) != 1){
		input = 0; 	
	    }
	    int c;
	    while ((c = getchar()) != '\n' && c != EOF);
	    
	    celulas[pont] = (input % 256 + 256) % 256;
	}

	else if(caractere_atual == '['){
	    if (celulas[pont] == 0){
	        int aninhamento = 1;
		    while (aninhamento > 0 && counter < len) {
		    counter++;
		    if (codigo[counter] == '[') aninhamento++;
		    if (codigo[counter] == ']') aninhamento--;
	        }
	    }
	}

	else if(caractere_atual == ']'){
	    if (celulas[pont] != 0){
	        int aninhamento = 1;
		    while (aninhamento > 0 && counter > 0) {
		    counter--;
		    if (codigo[counter] == '[') aninhamento--;
		    if (codigo[counter] == ']') aninhamento++;
	        }
	    }
	}

	counter++;

    }
    

    printf("\n");

    return 0;

}
