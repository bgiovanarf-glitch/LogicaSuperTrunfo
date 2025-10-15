/* -----------------------------------------------------------
   Super Trunfo de Cidades - Nível Novato
Objetivo:
   - Cadastrar 2 cartas de cidades (via terminal)
   - Calcular densidade populacional (população / área)
   - Comparar um atributo escolhido no código
   - Mostrar qual carta venceu
----------------------------------------------------------- */

#include <stdio.h>
#include <string.h>

/* Tamanho máximo de texto para cidade e códigos.
   Defino constantes para facilitar manutenção. */
#define STRMAX 64

/* Aqui crio uma "struct" para guardar os dados da carta.
   Struct é tipo uma "caixinha" com vários campos. */
typedef struct {
    char estado[3];           // Ex: "RO" (2 letras + '\0')
    char codigo[8];           // Ex: "A01"
    char cidade[STRMAX];      // Ex: "Ji-Paraná"
    long populacao;           // Habitantes (número inteiro grande)
    double area;              // km² (pode ter casas decimais)
    double pib;               // PIB em bilhões (ou outro padrão)
    int pontosTuristicos;     // Quantidade (inteiro)
    double densidade;         // hab/km² = populacao / area (calculado)
} Carta;

/* Para escolher qual atributo vou comparar, crio "rótulos".
   Isso deixa o código mais legível do que usar números soltos. */
typedef enum {
    POPULACAO = 1,
    AREA      = 2,
    PIB       = 3,
    PONTOS    = 4,
    DENSIDADE = 5
} Atributo;

/* >>>>> ATRIBUTO QUE SERÁ COMPARADO <<<<<
   Exemplos: POPULACAO, AREA, PIB, PONTOS, DENSIDADE */
const Atributo ATRIBUTO_ESCOLHIDO = DENSIDADE;

/* Função auxiliar: lê uma linha de texto com espaços e tira o '\n' do final.
   Uso fgets porque scanf("%s") corta no espaço. */
void lerLinha(char *dest, int max) {
    if (fgets(dest, max, stdin) != NULL) {
        size_t n = strlen(dest);
        if (n > 0 && dest[n - 1] == '\n') {
            dest[n - 1] = '\0'; // remove a quebra de linha
        }
    }
}

/* Para misturar scanf e fgets, às vezes sobra um '\n' no buffer.
   Essa função limpa até o fim da linha. */
void limparBufferAteQuebraLinha(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descarta */ }
}

/* Função para cadastrar 1 carta.
   Eu peço os dados e guardo tudo dentro da struct passada por ponteiro. */
void cadastrarCarta(Carta *c) {
    printf("\n=== Cadastro de Carta ===\n");

    printf("Estado (UF, ex: RO): ");
    lerLinha(c->estado, sizeof(c->estado));

    printf("Codigo da carta (ex: A01): ");
    lerLinha(c->codigo, sizeof(c->codigo));

    printf("Nome da cidade: ");
    lerLinha(c->cidade, sizeof(c->cidade));

    /* Para números, uso scanf. Depois limpo o buffer para não
       atrapalhar a próxima leitura de texto. */
    printf("Populacao (habitantes): ");
    scanf("%ld", &c->populacao);
    limparBufferAteQuebraLinha();

    printf("Area (km2): ");
    scanf("%lf", &c->area);
    limparBufferAteQuebraLinha();

    printf("PIB (use o mesmo padrao para as duas, ex: em bilhoes): ");
    scanf("%lf", &c->pib);
    limparBufferAteQuebraLinha();

    printf("Pontos turisticos (quantidade): ");
    scanf("%d", &c->pontosTuristicos);
    limparBufferAteQuebraLinha();

    /* Cálculo da densidade: preciso tomar cuidado para não dividir por zero. */
    if (c->area > 0.0) {
        c->densidade = (double)c->populacao / c->area;
    } else {
        c->densidade = 0.0; // valor “neutro” se área inválida
    }
}

/* Função para exibir a carta de forma organizada. */
void exibirCarta(const Carta *c) {
    printf("\n--- Carta %s (%s) ---\n", c->codigo, c->estado);
    printf("Cidade:              %s\n", c->cidade);
    printf("Populacao:           %ld habitantes\n", c->populacao);
    printf("Area:                %.2f km2\n", c->area);
    printf("PIB:                 %.2f\n", c->pib);
    printf("Pontos Turisticos:   %d\n", c->pontosTuristicos);
    printf("Densidade:           %.2f hab/km2\n", c->densidade);
}

/* Esta função compara duas cartas com base no ATRIBUTO_ESCOLHIDO.
   Retorno:
   - 1  => carta1 venceu
   - -1 => carta2 venceu
   - 0  => empate
*/
int compararCartas(const Carta *a, const Carta *b, Atributo atr) {
    /* Eu poderia fazer um switch(atr), mas como o objetivo é treinar
       if e if-else, vou usar só ifs encadeados. */

    if (atr == POPULACAO) {
        if (a->populacao > b->populacao) return 1;
        else if (a->populacao < b->populacao) return -1;
        else return 0;
    }
    else if (atr == AREA) {
        if (a->area > b->area) return 1;
        else if (a->area < b->area) return -1;
        else return 0;
    }
    else if (atr == PIB) {
        if (a->pib > b->pib) return 1;
        else if (a->pib < b->pib) return -1;
        else return 0;
    }
    else if (atr == PONTOS) {
        if (a->pontosTuristicos > b->pontosTuristicos) return 1;
        else if (a->pontosTuristicos < b->pontosTuristicos) return -1;
        else return 0;
    }
    else if (atr == DENSIDADE) {
        /* Regra especial: densidade MENOR vence */
        if (a->densidade < b->densidade) return 1;
        else if (a->densidade > b->densidade) return -1;
        else return 0;
    }

    /* Se não cair em nada (não deveria), considero empate. */
    return 0;
}

/* Para mostrar o nome “bonitinho” do atributo comparado. */
const char* nomeAtributo(Atributo atr) {
    if (atr == POPULACAO) return "Populacao (maior vence)";
    else if (atr == AREA) return "Area (maior vence)";
    else if (atr == PIB) return "PIB (maior vence)";
    else if (atr == PONTOS) return "Pontos Turisticos (maior vence)";
    else if (atr == DENSIDADE) return "Densidade (MENOR vence)";
    return "Atributo desconhecido";
}

int main(void) {
    /* Declaro duas cartas. O usuário vai preencher cada uma. */
    Carta c1, c2;

    printf("=== Super Trunfo de Cidades (Nivel Novato) ===\n");
    printf("Atributo escolhido no codigo: %s\n", nomeAtributo(ATRIBUTO_ESCOLHIDO));

    /* Cadastro das duas cartas */
    cadastrarCarta(&c1);
    cadastrarCarta(&c2);

    /* Exibo para o usuário conferir o que foi digitado */
    printf("\n=== Cartas Cadastradas ===\n");
    exibirCarta(&c1);
    exibirCarta(&c2);

    /* Faço a comparação usando apenas if/else, lá na função compararCartas */
    int resultado = compararCartas(&c1, &c2, ATRIBUTO_ESCOLHIDO);

    /* Mostro o vencedor com base no retorno da função */
    printf("\n=== Resultado da Comparacao (%s) ===\n", nomeAtributo(ATRIBUTO_ESCOLHIDO));
    if (resultado == 1) {
        printf("Venceu a carta %s (%s) - Cidade: %s\n", c1.codigo, c1.estado, c1.cidade);
    } else if (resultado == -1) {
        printf("Venceu a carta %s (%s) - Cidade: %s\n", c2.codigo, c2.estado, c2.cidade);
    } else {
        printf("Empate!\n");
    }

    return 0; // Fim do programa
}