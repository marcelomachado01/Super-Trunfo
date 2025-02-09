#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CIDADES 32 // 8 estados * 4 cidades

// Estrutura para armazenar informações das cidades
typedef struct {
    char codigo[4]; // Código da cidade (Ex: "A01")
    char nome[50]; // Nome da cidade
    int populacao; // População da cidade
    float area; // Área da cidade em km²
    float pib; // PIB da cidade em bilhões
    int pontos_turisticos; // Número de pontos turísticos
    float densidade_populacional; // Calculado como população / área
    float pib_per_capita; // Calculado como PIB / população
} Cidade;

// Função para cadastrar uma nova cidade
void cadastrarCidades(Cidade cidades[], int *totalCidades) {
    if (*totalCidades >= MAX_CIDADES) { // Verifica se atingiu o limite de cidades
        printf("\nLimite de cidades atingido!\n");
        return;
    }
    
    Cidade nova;
    printf("\nDigite o código da cidade (Ex: A01, B02): ");
    scanf(" %3s", nova.codigo);
    
    printf("Nome da cidade: ");
    getchar(); // Limpa buffer do teclado
    fgets(nova.nome, sizeof(nova.nome), stdin);
    nova.nome[strcspn(nova.nome, "\n")] = '\0'; // Remove a quebra de linha do nome
    
    printf("População: ");
    scanf("%d", &nova.populacao);
    
    printf("Área (km²): ");
    scanf("%f", &nova.area);
    
    printf("PIB (em bilhões): ");
    scanf("%f", &nova.pib);
    
    printf("Número de pontos turísticos: ");
    scanf("%d", &nova.pontos_turisticos);
    
    // Cálculo das novas propriedades
    nova.densidade_populacional = nova.populacao / nova.area;
    nova.pib_per_capita = (nova.pib * 1000000000) / nova.populacao; // Convertendo PIB de bilhões para unidade monetária
    
    // Adiciona a nova cidade ao array
    cidades[*totalCidades] = nova;
    (*totalCidades)++;
    
    printf("\nCidade cadastrada com sucesso!\n");
}

// Função para listar todas as cidades cadastradas
void listarCidades(Cidade cidades[], int totalCidades) {
    if (totalCidades == 0) { // Verifica se há cidades cadastradas
        printf("\nNenhuma cidade cadastrada.\n");
        return;
    }
    
    printf("\nLista de Cidades:\n");
    for (int i = 0; i < totalCidades; i++) {
        printf("-----------------------------\n");
        printf("Código: %s\n", cidades[i].codigo);
        printf("Nome: %s\n", cidades[i].nome);
        printf("População: %d\n", cidades[i].populacao);
        printf("Área: %.2f km²\n", cidades[i].area);
        printf("PIB: %.2f bilhões\n", cidades[i].pib);
        printf("Pontos turísticos: %d\n", cidades[i].pontos_turisticos);
        printf("Densidade Populacional: %.2f hab/km²\n", cidades[i].densidade_populacional);
        printf("PIB per capita: %.2f\n", cidades[i].pib_per_capita);
    }
}

// Função para comparar duas cartas com base em um atributo escolhido
void compararCartas(Cidade c1, Cidade c2, int atributo) {
    float valor1, valor2;
    char *atributoNome;
    
    switch (atributo) {
        case 1:
            valor1 = c1.populacao;
            valor2 = c2.populacao;
            atributoNome = "População";
            break;
        case 2:
            valor1 = c1.area;
            valor2 = c2.area;
            atributoNome = "Área";
            break;
        case 3:
            valor1 = c1.pib;
            valor2 = c2.pib;
            atributoNome = "PIB";
            break;
        case 4:
            valor1 = c1.pontos_turisticos;
            valor2 = c2.pontos_turisticos;
            atributoNome = "Pontos Turísticos";
            break;
        case 5:
            valor1 = c1.densidade_populacional;
            valor2 = c2.densidade_populacional;
            atributoNome = "Densidade Populacional";
            break;
        default:
            printf("Atributo inválido!\n");
            return;
    }
    
    printf("\nComparando %s:\n", atributoNome);
    printf("%s: %.2f vs %s: %.2f\n", c1.nome, valor1, c2.nome, valor2);
    
    if (atributo == 5) {
        printf("Vencedor: %s\n", (valor1 < valor2) ? c1.nome : c2.nome);
    } else {
        printf("Vencedor: %s\n", (valor1 > valor2) ? c1.nome : c2.nome);
    }
}

// Função principal
int main() {
    Cidade cidades[MAX_CIDADES]; // Array para armazenar as cidades
    int totalCidades = 0; // Contador de cidades cadastradas
    int opcao;
    
    do {
        // Menu principal
        printf("\nSuper Trunfo - Países\n");
        printf("1. Cadastrar Cidade\n");
        printf("2. Listar Cidades\n");
        printf("3. Comparar Cartas\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        // Execução da opção escolhida pelo usuário
        switch (opcao) {
            case 1:
                cadastrarCidades(cidades, &totalCidades);
                break;
            case 2:
                listarCidades(cidades, totalCidades);
                break;
            case 3:
                if (totalCidades < 2) {
                    printf("\nÉ necessário pelo menos duas cidades para comparar!\n");
                } else {
                    int c1, c2, atributo;
                    printf("Digite o índice da primeira cidade (0 a %d): ", totalCidades - 1);
                    scanf("%d", &c1);
                    printf("Digite o índice da segunda cidade (0 a %d): ", totalCidades - 1);
                    scanf("%d", &c2);
                    printf("Escolha o atributo para comparação (1-População, 2-Área, 3-PIB, 4-Pontos Turísticos, 5-Densidade Populacional): ");
                    scanf("%d", &atributo);
                    compararCartas(cidades[c1], cidades[c2], atributo);
                }
                break;
            case 4:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 4);
    
    return 0;
}
