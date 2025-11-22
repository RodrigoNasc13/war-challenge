#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <time.h> 


// Struct Territorio
// Armazena as informações de cada território do jogo WAR
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios
// Recebe um ponteiro para o vetor de territórios e a quantidade

void cadastrarTerritorios(Territorio* territorios, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Cadastro do Território %d\n", i + 1);
        
        printf("Nome do território: ");
        scanf(" %[^\n]", territorios[i].nome);
        
        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);
        
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n");
    }
}

// Função para exibir todos os territórios cadastrados
// Utiliza ponteiro para percorrer o vetor de territórios
void exibirTerritorios(Territorio* territorios, int quantidade) {
    printf("\nTerritórios cadastrados\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }
}

// Função para simular ataque entre territórios
// Recebe ponteiros para o território atacante e defensor
// Usa números aleatórios para simular dados de batalha
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== INICIANDO ATAQUE ===\n");
    printf("Atacante: %s (Cor: %s, Tropas: %d)\n", 
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (Cor: %s, Tropas: %d)\n", 
           defensor->nome, defensor->cor, defensor->tropas);
    
    // Simula rolagem de dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("\nDado do Atacante: %d\n", dadoAtacante);
    printf("Dado do Defensor: %d\n", dadoDefensor);
    
    // Verifica o resultado do ataque
    if (dadoAtacante > dadoDefensor) {
        printf("\n>>> ATACANTE VENCEU! <<<\n");
        
        // Transfere metade das tropas do atacante para o defensor
        int tropasTransferidas = atacante->tropas / 2;
        
        // Atualiza o território defensor
        strcpy(defensor->cor, atacante->cor);  // Muda a cor do exército
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("O território %s agora pertence ao exército %s!\n", 
               defensor->nome, defensor->cor);
    } else {
        printf("\n>>> DEFENSOR RESISTIU! <<<\n");
        
        // Atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
        
        printf("O território %s continua com o exército %s!\n", 
               defensor->nome, defensor->cor);
    }
    
    printf("\nResultado pós-ataque\n");
    printf("Atacante %s: %d tropas\n", atacante->nome, atacante->tropas);
    printf("Defensor %s: %d tropas (Cor: %s)\n", 
           defensor->nome, defensor->tropas, defensor->cor);
}

// Função para liberar memória alocada dinamicamente
void liberarMemoria(Territorio* territorios) {
    free(territorios);
    printf("\nMemória liberada com sucesso!\n");
}

int main() {
    // Configura codificação UTF-8 para Windows
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    // Inicializa gerador de números aleatórios
    srand(time(NULL));
    
    int quantidadeTerritorios;
    
    printf("-- JOGO WAR - SISTEMA DE COMBATE --\n\n");
    
    // Solicita a quantidade de territórios
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &quantidadeTerritorios);
    
    // Validação básica
    if (quantidadeTerritorios < 2) {
        printf("É necessário pelo menos 2 territórios para jogar!\n");
        return 1;
    }
    
    // Alocação dinâmica de memória para os territórios
    Territorio* territorios = (Territorio*)calloc(quantidadeTerritorios, sizeof(Territorio));
    
    // Verifica se a alocação foi bem-sucedida
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    
    printf("\n");
    
    // Cadastra os territórios
    cadastrarTerritorios(territorios, quantidadeTerritorios);
    
    // Exibe os territórios cadastrados
    exibirTerritorios(territorios, quantidadeTerritorios);
    
    // Loop de ataques
    char continuar;
    do {
        int indiceAtacante, indiceDefensor;
        
        printf("\n-- REALIZAR ATAQUE --\n");
        
        // Seleciona território atacante
        printf("Escolha o território atacante (1 a %d): ", quantidadeTerritorios);
        scanf("%d", &indiceAtacante);
        indiceAtacante--;  // Ajusta para índice do array (0-based)
        
        // Validação do índice atacante
        if (indiceAtacante < 0 || indiceAtacante >= quantidadeTerritorios) {
            printf("Território inválido!\n");
            continue;
        }
        
        // Seleciona território defensor
        printf("Escolha o território defensor (1 a %d): ", quantidadeTerritorios);
        scanf("%d", &indiceDefensor);
        indiceDefensor--;  // Ajusta para índice do array (0-based)
        
        // Validação do índice defensor
        if (indiceDefensor < 0 || indiceDefensor >= quantidadeTerritorios) {
            printf("Território inválido!\n");
            continue;
        }
        
        // Valida se não está atacando a si mesmo
        if (indiceAtacante == indiceDefensor) {
            printf("Não é possível atacar o mesmo território!\n");
            continue;
        }
        
        // Valida se não está atacando território da mesma cor
        if (strcmp(territorios[indiceAtacante].cor, territorios[indiceDefensor].cor) == 0) {
            printf("Não é possível atacar um território da mesma cor!\n");
            continue;
        }
        
        // Valida se o atacante tem tropas suficientes
        if (territorios[indiceAtacante].tropas < 2) {
            printf("O atacante precisa de pelo menos 2 tropas para atacar!\n");
            continue;
        }
        
        // Executa o ataque
        atacar(&territorios[indiceAtacante], &territorios[indiceDefensor]);
        
        // Exibe estado atual dos territórios
        exibirTerritorios(territorios, quantidadeTerritorios);
        
        // Pergunta se deseja continuar
        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
        
    } while (continuar == 's' || continuar == 'S');
    
    // Libera a memória alocada
    liberarMemoria(territorios);
    
    printf("\nObrigado por jogar WAR!\n");
    
    return 0;
}