#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define TAMANHO_VETOR 100

// Estrutura para o nó da árvore binária
typedef struct No {
    int dado;
    struct No *esquerda;
    struct No *direita;
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um valor na árvore
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->dado) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}

// Função para percorrer a árvore em pré-ordem
void percorrerPreOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dado);
        percorrerPreOrdem(raiz->esquerda);
        percorrerPreOrdem(raiz->direita);
    }
}

// O número de comparações feitas em uma lista de N elementos é, na pior das hipóteses, n(n-1)/2.
// Comparisons = 100 * (100-1) / 2 = 4950
// Função Bubble Sort
void bubbleSort(int arr[], int n, int *comparisons) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j+1]) {
                // Troca
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int numAlunos, i, ultimoDigito, somaDigitos = 0;
    long long matricula;

    setlocale(LC_ALL, "Portuguese");
    printf("Faculdade: Wyden UNIFBV\n");
    printf("Materia: Estrutura de Dados\n");
    printf("Professor: Fausto Jose Feitosa Barbosa Gominho\n");
    printf("\n\nAlunos no grupo: \n");
    printf("Thiago Henrique Batista Araujo de Souza\t| Matricula: 202303661142");
    printf("\nFernanda Araujo de Souza\t\t| Matricula: 202303445831");

    printf("\n\nDigite o numero de alunos no grupo: ");
    scanf("%d", &numAlunos);

    for (i = 0; i < numAlunos; i++) {
        printf("Digite a matricula do aluno %d: ", i + 1);
        scanf("%lld", &matricula);
        ultimoDigito = matricula % 10;
        somaDigitos += ultimoDigito;
    }

    int modulo = somaDigitos % 3;
    printf("\nResultado da operacao de modulo 3 a partir da soma do ultimo numero da matricula é: %d\n", modulo);

    // Criação de Vetor Unicos para armazenar número não repetidos e o Vetor auxiliar Usados para armazenar os número repetidos
    int unicos[TAMANHO_VETOR];
    int usados[1001] = {0};
    srand(time(NULL));

    for (i = 0; i < TAMANHO_VETOR; ) {
        int num = rand() % 1000 + 1;
        if (!usados[num]) {
            unicos[i] = num;
            usados[num] = 1;
            i++;
        }
    }

    // Exibir vetor desordenado
    printf("\nVetor desordenado:\n");
    for (i = 0; i < TAMANHO_VETOR; i++) {
        printf("%d ", unicos[i]);
    }
    printf("\n");

    // Criar a árvore binária de busca usando os números desordenados
    No* raiz = NULL;
    for (i = 0; i < TAMANHO_VETOR; i++) {
        raiz = inserir(raiz, unicos[i]);
    }

    // Percorrer a árvore em pré-ordem
    printf("\nPercurso em pre-ordem da arvore binaria:\n");
    percorrerPreOrdem(raiz);
    printf("\n");

    
    // Criação da variavel comparisons para saber o número de comparações que serão feitas com o método de ordenação escolhido
    int comparisons = 0;
    clock_t start_time = clock();
    
    // Qual tipo de ordenação será usado com base no resultado do módulo 3
    switch (modulo) {
        case 0:
            bubbleSort(unicos, TAMANHO_VETOR, &comparisons);
            break;
    }
    
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // tempo retornado em microsegundos
    double elapsed_time_sec = elapsed_time * 10000; // tempo retornado em segundos
    double elapsed_time_milisec = elapsed_time * 1000; // t empo retornado em microsegundos

    // Exibir vetor ordenado
    printf("\nVetor ordenado com o metodo Bubble Sort:\n");
    for (i = 0; i < TAMANHO_VETOR; i++) {
        printf("%d ", unicos[i]);
    }
    printf("\n\nQuantidade de Comparacoes feitas usando o método Bubble Sort: %d\n", comparisons);
    printf("\n\nTempo de execucao: %.2f segundos\n", elapsed_time_sec);
    printf("Tempo de execuçcao: %.3f milisegundos\n", elapsed_time_milisec);
    printf("Tempo de execuçcao: %f microsegundos\n", elapsed_time);

    return 0;
}
