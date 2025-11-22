#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>


// Struct Territorio
// Armazena as informações de cada território do jogo WAR
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Configura a localização para português brasileiro (suporte a acentuação)
    setlocale(LC_ALL, "pt_BR.UTF-8");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    // Declaração de um vetor para armazenar 5 territórios
    Territorio territorios[5];
    
    printf("Sistema de cadastro de territórios\n\n");
    
    // Laço para cadastro dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do Território %d\n", i + 1);
        
        // Entrada do nome do território
        printf("Nome do território: ");
        scanf(" %[^\n]", territorios[i].nome);
        
        // Entrada da cor do exército
        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);
        
        // Entrada da quantidade de tropas
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n");
    }
    
    // Exibição dos dados cadastrados
    printf("\nTerritórios cadastrados\n\n");
    
    // Percorre o vetor e exibe as informações de cada território
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }
    
    return 0;
}