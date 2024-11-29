#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Criando a função
void exit_Program();
void createDatabaseFile();

// Implementando a função abaixo
void createDatabaseFile() {
    FILE* file = fopen("database.txt", "a");
    if (file == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }
    fclose(file);
}

// Implementando a função abaixo
void exit_Program() {
    printf("Saindo do programa...\n");
    exit(0);
}