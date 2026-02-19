#include <stdio.h>   // pra usar printf
#include <stdlib.h>  // pra usar malloc e free
#include <time.h>    // pra medir tempo de execução

// função que preenche o vetor em ordem decrescente
// exemplo: tamanho = 5 → 5 4 3 2 1
void preencherDecrescente(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = tamanho - i;  // coloca os números do maior pro menor
    }
}

// Bubble Sort normal
// também conta quantas comparações e trocas foram feitas
void bubbleSort(int vetor[], int tamanho, long long *comparacoes, long long *movimentacoes) {

    for (int i = 0; i < tamanho - 1; i++) {  // controla as passadas
        for (int j = 0; j < tamanho - i - 1; j++) {  // percorre o vetor

            (*comparacoes)++;  // conta cada comparação feita

            if (vetor[j] > vetor[j + 1]) {  // se o atual for maior que o próximo
                // troca os dois
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;

                (*movimentacoes)++;  // conta a troca
            }
        }
    }
}

// Selection Sort
// procura o menor número e coloca na posição certa
void selectionSort(int vetor[], int tamanho, long long *comparacoes, long long *movimentacoes) {

    for (int i = 0; i < tamanho - 1; i++) {

        int menor = i;  // assume que o menor é o atual

        for (int j = i + 1; j < tamanho; j++) {
            (*comparacoes)++;  // conta comparação

            if (vetor[j] < vetor[menor]) {
                menor = j;  // achou um menor
            }
        }

        // se achou um menor diferente, faz a troca
        if (menor != i) {
            int temp = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = temp;

            (*movimentacoes)++;  // conta a troca
        }
    }
}

// função pra testar os algoritmos
void testarAlgoritmo(int tamanho) {

    int *vetor = malloc(tamanho * sizeof(int));  // cria vetor dinamicamente

    clock_t inicio, fim;
    double tempo;
    long long comparacoes, movimentacoes;

    // ===== Testando Bubble Sort =====
    preencherDecrescente(vetor, tamanho);  // pior caso
    comparacoes = 0;
    movimentacoes = 0;

    inicio = clock();
    bubbleSort(vetor, tamanho, &comparacoes, &movimentacoes);
    fim = clock();

    tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;

    printf("Bubble\t%d\t%.2f ms\t%lld\t%lld\n",
           tamanho, tempo, comparacoes, movimentacoes);

    // ===== Testando Selection Sort =====
    preencherDecrescente(vetor, tamanho);  // reseta o vetor
    comparacoes = 0;
    movimentacoes = 0;

    inicio = clock();
    selectionSort(vetor, tamanho, &comparacoes, &movimentacoes);
    fim = clock();

    tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;

    printf("Selection\t%d\t%.2f ms\t%lld\t%lld\n",
           tamanho, tempo, comparacoes, movimentacoes);

    free(vetor);  // libera memória
}

int main() {

    printf("Algoritmo\tTam\tTempo\tComparacoes\tTrocas\n");

    testarAlgoritmo(100);
    testarAlgoritmo(1000);
    testarAlgoritmo(10000);

    return 0;
}