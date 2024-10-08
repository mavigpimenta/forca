#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VIDAS 6
#define MAX_PALAVRA 50
#define MAX_LINHA 100

int chute();
void inicio();
void gerarPalavra();
void printPalavra();
void append(char *s, char c);

char palavraEscolhida[MAX_PALAVRA];
char chutes[50] = "";

void gerarPalavra() {
    FILE *file = fopen("palavras.txt", "r");
    if (file == NULL) {
        perror("Não foi possível abrir o arquivo de palavras");
        exit(EXIT_FAILURE);
    }

    char linha[MAX_LINHA];
    int count = 0;
    while (fgets(linha, sizeof(linha), file)) {
        count++;
    }

    fseek(file, 0, SEEK_SET);

    int randomIndex = rand() % count;
    for (int i = 0; i <= randomIndex; i++) {
        fgets(linha, sizeof(linha), file);
        if (i == randomIndex) {
            linha[strcspn(linha, "\n")] = 0; 
            strcpy(palavraEscolhida, linha);
        }
    }

    fclose(file);
}

void inicio() {
    printf("/****************/\n");
    printf("/ Jogo da Forca */\n");
    printf("/****************/\n\n");
}

int chute() {
    char letra;
    printf("\n\nDigite seu chute: ");
    scanf(" %c", &letra);

    append(chutes, letra);

    for (int l = 0; l < strlen(palavraEscolhida); l++) {
        if (letra == palavraEscolhida[l]) {
            return 1;
        }
    }
    return 0;
}

void append(char *s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len + 1] = '\0';
}

void printPalavra() {
    for (int i = 0; i < strlen(palavraEscolhida); i++) {
        int verificar = 0;

        for (int j = 0; j < strlen(chutes); j++) {
            if (palavraEscolhida[i] == chutes[j]) {
                verificar = 1;
            }
        }

        if (verificar) {
            printf("%c", palavraEscolhida[i]);
        } else {
            printf("_");
        }
    }
}

void fim(int ganhou) {
    if (ganhou) {
        printf("\nParabéns, você ganhou!\n\n");
        printf("A palavra era **%s**\n\n", palavraEscolhida);

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

    } else {
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavraEscolhida);

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

int verificar() {
    int ganhou;

    for (int k = 0; k < strlen(palavraEscolhida); k++) {
        ganhou = 0;

        for (int m = 0; m < strlen(chutes); m++) {
            if (palavraEscolhida[k] == chutes[m]) {
                ganhou = 1;
            }
        }

        if (ganhou == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    srand(time(NULL));
    inicio();

    int erros = 0, valor;

    gerarPalavra();

    while (erros < VIDAS) {
        printf("Vidas: %i\n\n", VIDAS - erros);
        printPalavra();
        valor = chute();

        if (valor)
            puts("\nEssa letra está presente na palavra...");
        else {
            puts("\nEssa letra NÃO está presente na palavra...");
            erros++;
        }

        if (verificar()) {
            fim(1);
            break;
        }
    }

    if (valor == 0)
        fim(0);

    return 0;
}
