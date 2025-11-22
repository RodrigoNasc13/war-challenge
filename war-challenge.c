#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <stdlib.h>  // Necessário para malloc, calloc, free, rand, srand
#include <time.h>

// Struct Territorio
// Armazena as informações de cada território do jogo WAR
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Struct Jogador
// Armazena as informações de cada jogador
typedef struct {
    char nome[30];
    char cor[10];
    char* missao;  // Missão alocada dinamicamente
} Jogador;

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

// Função para cadastrar jogadores
void cadastrarJogadores(Jogador* jogadores, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Cadastro do Jogador %d\n", i + 1);
        
        printf("Nome do jogador: ");
        scanf(" %[^\n]", jogadores[i].nome);
        
        printf("Cor do exército: ");
        scanf("%s", jogadores[i].cor);
        
        // Aloca memória para a missão
        jogadores[i].missao = (char*)malloc(200 * sizeof(char));
        
        printf("\n");
    }
}

// Função para atribuir missão sorteada ao jogador
// Recebe ponteiro para destino, vetor de missões e total de missões
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    // Sorteia uma missão aleatória
    int indice = rand() % totalMissoes;
    
    // Copia a missão sorteada para o destino usando ponteiro
    strcpy(destino, missoes[indice]);
}

// Função para exibir a missão do jogador
// Passagem por valor - apenas visualização
void exibirMissao(char* nomejogador, char* missao) {
    printf("\nMissão de %s: %s\n", nomejogador, missao);
}

// Função para verificar se a missão foi cumprida
// Retorna 1 se cumprida, 0 caso contrário
// Passagem por referência para verificação
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador) {
    // Conta territórios conquistados pelo jogador
    int territoriosConquistados = 0;
    int tropasTotais = 0;
    
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            territoriosConquistados++;
            tropasTotais += mapa[i].tropas;
        }
    }
    
    // Verifica diferentes tipos de missões
    if (strstr(missao, "Conquistar 3 territórios") != NULL) {
        return territoriosConquistados >= 3;
    } else if (strstr(missao, "Conquistar 4 territórios") != NULL) {
        return territoriosConquistados >= 4;
    } else if (strstr(missao, "Acumular 20 tropas") != NULL) {
        return tropasTotais >= 20;
    } else if (strstr(missao, "Acumular 30 tropas") != NULL) {
        return tropasTotais >= 30;
    } else if (strstr(missao, "Dominar a maioria") != NULL) {
        return territoriosConquistados > (tamanho / 2);
    }
    
    return 0;
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

// Função para liberar toda a memória alocada dinamicamente
void liberarMemoria(Territorio* territorios, Jogador* jogadores, int quantidadeJogadores) {
    // Libera as missões de cada jogador
    for (int i = 0; i < quantidadeJogadores; i++) {
        free(jogadores[i].missao);
    }
    
    // Libera o vetor de jogadores
    free(jogadores);
    
    // Libera o vetor de territórios
    free(territorios);
    
    printf("\nMemória liberada com sucesso!\n");
}

int main() {
    // Configura codificação UTF-8 para Windows
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    // Inicializa gerador de números aleatórios
    srand(time(NULL));
    
    int quantidadeTerritorios, quantidadeJogadores;
    
    printf("-- JOGO WAR - SISTEMA DE COMBATE COM MISSÕES --\n\n");
    
    // Solicita a quantidade de jogadores
    printf("Quantos jogadores vão participar? ");
    scanf("%d", &quantidadeJogadores);
    
    if (quantidadeJogadores < 2) {
        printf("É necessário pelo menos 2 jogadores para jogar!\n");
        return 1;
    }
    
    // Alocação dinâmica de memória para os jogadores
    Jogador* jogadores = (Jogador*)calloc(quantidadeJogadores, sizeof(Jogador));
    
    if (jogadores == NULL) {
        printf("Erro ao alocar memória para jogadores!\n");
        return 1;
    }
    
    // Cadastra os jogadores
    printf("\n");
    cadastrarJogadores(jogadores, quantidadeJogadores);
    
    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territórios consecutivos",
        "Conquistar 4 territórios de qualquer localização",
        "Acumular 20 tropas no total",
        "Acumular 30 tropas no total",
        "Dominar a maioria dos territórios do mapa"
    };
    int totalMissoes = 5;
    
    // Atribui missões aleatórias aos jogadores
    printf("\n=== DISTRIBUIÇÃO DE MISSÕES ===\n");
    for (int i = 0; i < quantidadeJogadores; i++) {
        atribuirMissao(jogadores[i].missao, missoes, totalMissoes);
        exibirMissao(jogadores[i].nome, jogadores[i].missao);
    }
    
    // Solicita a quantidade de territórios
    printf("\nQuantos territórios deseja cadastrar? ");
    scanf("%d", &quantidadeTerritorios);
    
    // Validação básica
    if (quantidadeTerritorios < 2) {
        printf("É necessário pelo menos 2 territórios para jogar!\n");
        liberarMemoria(NULL, jogadores, quantidadeJogadores);
        return 1;
    }
    
    // Alocação dinâmica de memória para os territórios
    Territorio* territorios = (Territorio*)calloc(quantidadeTerritorios, sizeof(Territorio));
    
    // Verifica se a alocação foi bem-sucedida
    if (territorios == NULL) {
        printf("Erro ao alocar memória para territórios!\n");
        liberarMemoria(NULL, jogadores, quantidadeJogadores);
        return 1;
    }
    
    printf("\n");
    
    // Cadastra os territórios
    cadastrarTerritorios(territorios, quantidadeTerritorios);
    
    // Exibe os territórios cadastrados
    exibirTerritorios(territorios, quantidadeTerritorios);
    
    // Loop de ataques
    char continuar;
    int turno = 0;
    int jogadorAtual = 0;
    
    do {
        turno++;
        printf("\n========== TURNO %d - Jogador: %s (%s) ==========\n", 
               turno, jogadores[jogadorAtual].nome, jogadores[jogadorAtual].cor);
        
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
        
        // Valida se o território pertence ao jogador atual
        if (strcmp(territorios[indiceAtacante].cor, jogadores[jogadorAtual].cor) != 0) {
            printf("Você só pode atacar com territórios da sua cor (%s)!\n", 
                   jogadores[jogadorAtual].cor);
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
        
        // Verifica se o jogador atual cumpriu sua missão
        if (verificarMissao(jogadores[jogadorAtual].missao, territorios, 
                           quantidadeTerritorios, jogadores[jogadorAtual].cor)) {
            printf("\n");
            printf("*********************************************\n");
            printf("*** VITÓRIA! ***\n");
            printf("O jogador %s cumpriu sua missão!\n", jogadores[jogadorAtual].nome);
            printf("Missão: %s\n", jogadores[jogadorAtual].missao);
            printf("*********************************************\n");
            break;
        }
        
        // Pergunta se deseja continuar
        printf("\nDeseja continuar jogando? (s/n): ");
        scanf(" %c", &continuar);
        
        // Passa para o próximo jogador
        jogadorAtual = (jogadorAtual + 1) % quantidadeJogadores;
        
    } while (continuar == 's' || continuar == 'S');
    
    // Libera a memória alocada
    liberarMemoria(territorios, jogadores, quantidadeJogadores);
    
    printf("\nObrigado por jogar WAR!\n");
    
    return 0;
}