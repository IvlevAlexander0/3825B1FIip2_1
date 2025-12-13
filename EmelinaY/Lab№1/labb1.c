#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main() {
    // плотность будем считать как г/сm^3
    double const  tolst = 0.5;
    double const  tolbok = 1.5;
    double const  tolkr = 1.5;
    double const  toldver = 1.0;
    double const  tolpolk = 0.5;
    double const  plDSP = 0.75;
    double const  plDVP = 0.85;
    double const  plderevo = 0.6;
    double h, d, w;

    printf("calculation of cabinet weight\n");
    printf("==================\n");

    printf("Enter the height of the cabinet h (180-220 cm): ");
    scanf("%lf", &h);

    printf("Enter the cabinet depth d (50-90 cm): ");
    scanf("%lf", &d);

    printf("Enter the cabinet width w(80 - 120 cm) : ");
    scanf("%lf", &w);

    if (h < 180 || h > 220 || d < 50 || d > 90 || w < 80 || w > 120) {
        printf("Error: the parameters are outside the allowed ranges!\n");
        return 1;
    }
    double masst = h * w * tolst * plDVP;                    
    double masbok = 2 * h * d * tolbok * plDSP;              
    double maskr = 2 * w * d * tolkr * plDSP;                
    double masdver =  h * w * toldver * plderevo;
    double poslpolka = 0;
    int countpolk = 0;
    while (poslpolka <= h-40.5) {
        countpolk += 1;
        poslpolka += 40.5;
    }
    double maspolk = countpolk * (w * tolpolk * d)*plDSP;
    double sum_mas =( masst + masbok + maskr + masdver + maspolk)/1000.0;
    printf("\nCalculation results:\n");
    printf("Cabinet height: %.1f cm\n", h);
    printf("cabinet depth: %.1f cm\n", d);
    printf("cabinet width: %.1f cm\n", w);
    printf("cabinet weight : %.2f kg\n", sum_mas);
}


// Структура для хранения результатов эксперимента
typedef struct {
    int size;
    double time_m1;
    double time_m2;
} ExperimentResult;

double* multiply_m1(const double* A, const double* B, int size) {
    double* result = (double*)calloc(size * size, sizeof(double));
    if (!result) {
        printf("Ошибка выделения памяти для результата m1\n");
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            double aik = A[i * size + k];
            for (int j = 0; j < size; j++) {
                result[i * size + j] += aik * B[k * size + j];
            }
        }
    }
    return result;
}

// Функции для матрицы m2 (двумерный массив)
double** generate_m2(int size, double a, double b) {
    double** matrix = (double**)malloc(size * sizeof(double*));
    if (!matrix) {
        printf("Ошибка выделения памяти для m2\n");
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        matrix[i] = (double*)malloc(size * sizeof(double));
        if (!matrix[i]) {
            printf("Ошибка выделения памяти для строки m2\n");
            // Освобождаем уже выделенную память
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            return NULL;
        }

        for (int j = 0; j < size; j++) {
            matrix[i][j] = a + ((double)rand() / RAND_MAX) * (b - a);
        }
    }
    return matrix;
}

void print_m2(double** matrix, int size) {
    if (size > 5) {
        printf("Матрица m2 [%dx%d] (вывод пропущен для size > 5)\n", size, size);
        return;
    }

    printf("Матрица m2 [%dx%d]:\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%8.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

double** multiply_m2(double** A, double** B, int size) {
    double** result = (double**)malloc(size * sizeof(double*));
    if (!result) {
        printf("Ошибка выделения памяти для результата m2\n");
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        result[i] = (double*)calloc(size, sizeof(double));
        if (!result[i]) {
            printf("Ошибка выделения памяти для строки результата m2\n");
            for (int j = 0; j < i; j++) free(result[j]);
            free(result);
            return NULL;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            double aik = A[i][k];
            for (int j = 0; j < size; j++) {
                result[i][j] += aik * B[k][j];
            }
        }
    }
    return result;
}

// Освобождение памяти для m1
void free_m1(double* matrix) {
    free(matrix);
}

// Освобождение памяти для m2
void free_m2(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Функция проведения одного эксперимента
ExperimentResult run_experiment(int size, double a, double b, int print_matrices) {
    ExperimentResult result;
    result.size = size;

    // Генерация матриц
    double* m1_A = generate_m1(size, a, b);
    double* m1_B = generate_m1(size, a, b);
    double** m2_A =
        e_m2(size, a, b);
    double** m2_B = generate_m2(size, a, b);

    if (!m1_A || !m1_B || !m2_A || !m2_B) {
        printf("Ошибка генерации матриц для размера %d\n", size);
        result.time_m1 = result.time_m2 = 0;
        return result;
    }

    // Печать матриц если нужно
    if (print_matrices) {
        printf("\n=== Эксперимент для размера %d ===\n", size);
        printf("Матрицы m1:\n");
        print_m1(m1_A, size);
        printf("\n");
        print_m1(m1_B, size);

        printf("\nМатрицы m2:\n");
        print_m2(m2_A, size);
        printf("\n");
        print_m2(m2_B, size);
    }

    // Умножение m1 с замером времени
    clock_t start = clock();
    double* m1_result = multiply_m1(m1_A, m1_B, size);
    clock_t end = clock();
    result.time_m1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Умножение m2 с замером времени
    start = clock();
    double** m2_result = multiply_m2(m2_A, m2_B, size);
    end = clock();
    result.time_m2 = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Печать результатов если нужно
    if (print_matrices && m1_result && m2_result) {
        printf("\nРезультат умножения m1:\n");
        print_m1(m1_result, size);
        printf("\nРезультат умножения m2:\n");
        print_m2(m2_result, size);
        printf("\nВремя m1: %.6f сек, Время m2: %.6f сек\n",
            result.time_m1, result.time_m2);
    }

    // Освобождение памяти
    if (m1_result) free_m1(m1_result);
    if (m2_result) free_m2(m2_result, size);
    free_m1(m1_A);
    free_m1(m1_B);
    free_m2(m2_A, size);
    free_m2(m2_B, size);

    return result;
}

// Функция сравнения для сортировки
int compare_results(const void* a, const void* b) {
    ExperimentResult* resA = (ExperimentResult*)a;
    ExperimentResult* resB = (ExperimentResult*)b;
    return resA->size - resB->size;
}

int main() {
    srand(time(NULL));

    double a, b;
    int n_experiments;

    // Ввод параметров
    printf("Введите диапазон генерации значений (a b): ");
    scanf("%lf %lf", &a, &b);

    printf("Введите количество экспериментов (n): ");
    scanf("%d", &n_experiments);

    int* sizes = (int*)malloc(n_experiments * sizeof(int));
    if (!sizes) {
        printf("Ошибка выделения памяти для размеров\n");
        return 1;
    }

    printf("Введите %d размеров матриц:\n", n_experiments);
    for (int i = 0; i < n_experiments; i++) {
        printf("Размер %d: ", i + 1);
        scanf("%d", &sizes[i]);
    }

    // Массив для хранения результатов
    ExperimentResult* results = (ExperimentResult*)malloc(n_experiments * sizeof(ExperimentResult));
    if (!results) {
        printf("Ошибка выделения памяти для результатов\n");
        free(sizes);
        return 1;
    }

    // Проведение экспериментов
    for (int i = 0; i < n_experiments; i++) {
        int print_matrices = (sizes[i] < 5) ? 1 : 0;
        results[i] = run_experiment(sizes[i], a, b, print_matrices);
    }

    // Сортировка результатов по размеру
    qsort(results, n_experiments, sizeof(ExperimentResult), compare_results);

    // Запись результатов в файл
    FILE* file = fopen("result.txt", "w");
    if (!file) {
        printf("Ошибка открытия файла для записи\n");
    }
    else {
        fprintf(file, "Размер\tВремя m1 (сек)\tВремя m2 (сек)\n");
        for (int i = 0; i < n_experiments; i++) {
            fprintf(file, "%d\t%.6f\t%.6f\n",
                results[i].size, results[i].time_m1, results[i].time_m2);
        }
        fclose(file);
        printf("\nРезультаты сохранены в файл result.txt\n");
    }

    // Вывод результатов в консоль
    printf("\nИтоговые результаты экспериментов:\n");
    printf("Размер\tВремя m1 (сек)\tВремя m2 (сек)\n");
    for (int i = 0; i < n_experiments; i++) {
        printf("%d\t%.6f\t%.6f\n",
            results[i].size, results[i].time_m1, results[i].time_m2);
    }

    // Освобождение памяти
    free(sizes);
    free(results);

    return 0;
}
``` generat



#include <stdlib.h>

int main() {
    // Спросили у системы: "Дай место для 5 целых чисел"
    int* grades = (int*)malloc(5 * sizeof(int));

    // Проверили, дали ли место
    if (grades == NULL) {
        printf("Места нет!\n");
        return 1;
    }

    // Строим дома (заполняем)
    grades[0] = 5;
    grades[1] = 4;
    // ... и т.д.

    // ОЧЕНЬ ВАЖНО: Возвращаем землю системе!
    free(grades);

    return 0;
}



int a = 5;
int* p = &a;
*p = 15;
printf("%d", a);
return 0;
}///15

///
void mystery(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int a = 3, b = 7;
    mystery(&a, &b);
    printf("a=%d, b=%d", a, b);
}
<details> <summary>Ответ< / summary> Функция меняет значения a и b местами.Вывод: a = 7, b = 3 < / details >




fclose(file);

}