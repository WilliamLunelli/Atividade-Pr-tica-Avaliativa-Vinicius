#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* ============================================================
   FUNÇÕES AUXILIARES
   ============================================================ */

/* Imprime todos os elementos de um array */
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* Troca os valores de dois ponteiros */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Copia o array original para que cada algoritmo use os mesmos dados */
void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

/* ============================================================
   ALGORITMOS DE ORDENAÇÃO
   ============================================================ */

/*
 * Bubble Sort — O(n²)
 * Compara pares adjacentes e os troca até o array estar ordenado.
 * Simples, porém ineficiente para arrays grandes.
 */
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

/*
 * Selection Sort — O(n²)
 * A cada iteração, encontra o menor elemento e o coloca na posição correta.
 */
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

/*
 * Insertion Sort — O(n²) no pior caso, O(n) se já ordenado
 * Insere cada elemento na posição correta dentro da parte já ordenada.
 * Eficiente para arrays pequenos ou quase ordenados.
 */
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/*
 * Shell Sort — entre O(n log n) e O(n²) dependendo da sequência de gaps
 * Melhoria do Insertion Sort: ordena elementos distantes antes dos adjacentes,
 * reduzindo o número de movimentações necessárias.
 */
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

/* -------- Quick Sort -------- */

/*
 * Particiona o array em torno de um pivô.
 * Elementos menores ficam à esquerda, maiores à direita.
 * Retorna o índice final do pivô.
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

/*
 * Quick Sort — O(n log n) médio, O(n²) pior caso
 * Divide o array recursivamente usando um pivô.
 * Na prática, um dos mais rápidos para dados aleatórios.
 */
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* -------- Merge Sort -------- */

/*
 * Intercala duas metades ordenadas de volta no array original.
 */
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

/*
 * Merge Sort — O(n log n) garantido
 * Divide o array ao meio recursivamente e intercala as partes ordenadas.
 * Estável e previsível, porém usa memória extra.
 */
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/* ============================================================
   FUNCT PRINCIPAL
   ============================================================ */

int main() {
    int n;
    printf("Digite o tamanho do array: ");
    scanf("%d", &n);

    int *original = (int *)malloc(n * sizeof(int));
    int *testArr  = (int *)malloc(n * sizeof(int));

    /* Preenche o array com valores aleatórios entre 0 e 9999 */
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        original[i] = rand() % 10000;

    int choice;
    do {
        printf("\n=== MENU DE ORDENACAO ===\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Quick Sort\n");
        printf("5. Merge Sort\n");
        printf("6. Shell Sort\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 6) {
            copyArray(original, testArr, n);

            /* Exibe o array apenas se for pequeno o suficiente */
            if (n <= 20) {
                printf("Original: ");
                printArray(testArr, n);
            }

            /* Mede o tempo de execução do algoritmo escolhido */
            clock_t start = clock();
            switch (choice) {
                case 1: bubbleSort(testArr, n);          break;
                case 2: selectionSort(testArr, n);       break;
                case 3: insertionSort(testArr, n);       break;
                case 4: quickSort(testArr, 0, n - 1);   break;
                case 5: mergeSort(testArr, 0, n - 1);   break;
                case 6: shellSort(testArr, n);           break;
            }
            clock_t end = clock();

            if (n <= 20) {
                printf("Ordenado: ");
                printArray(testArr, n);
            }

            double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f segundos\n", time_taken);
        }

    } while (choice != 0);

    free(original);
    free(testArr);
    return 0;
}
