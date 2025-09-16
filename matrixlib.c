#include "matrixlib.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h> // fabsf

// Получение случайного числа
int rand_int_in_range(int min, int max)
{
    if (min > max) {
        fprintf(stderr,
                "Error: rand_int_in_range called with min=%d, max=%d\n",
                min, max);
        exit(1);
    }
    int range = max - min + 1;
    return (int)(rand() % range) + min;
}

// =========================================================
// Выделение памяти и освобождение
// =========================================================

// Создание матрицы размером sizeY × sizeX и обнуление
void set_double_size(DOUBLE_MATRIX *matrix, unsigned sizeX, unsigned sizeY) {
    matrix->cell = malloc(sizeof(double*) * sizeX);
    if (!matrix->cell) {
        perror("malloc");
        exit(1);
    }
    for (unsigned x = 0; x < sizeX; x++) {
        matrix->cell[x] = malloc(sizeof(double) * sizeY);
        if (!matrix->cell[x]) {
            perror("malloc");
            exit(1);
        }
    }
    matrix->sizeX = sizeX;
    matrix->sizeY = sizeY;

    for (unsigned y = 0; y < sizeY; y++) {
        for (unsigned x = 0; x < sizeX; x++) {
            matrix->cell[x][y] = 0.0f;
        }
    }
}

// Очистка памяти
void destroy_double_matrix(DOUBLE_MATRIX *matrix) {
    if (!matrix->cell) return;
    for (unsigned x = 0; x < matrix->sizeX; x++) {
        free(matrix->cell[x]);
    }
    free(matrix->cell);
    matrix->cell = NULL;
    matrix->sizeX = matrix->sizeY = 0;
}

// =========================================================
// Печать
// =========================================================
void print_double_matrix(DOUBLE_MATRIX *matrix) {
    for (unsigned y = 0; y < matrix->sizeY; y++) {
        for (unsigned x = 0; x < matrix->sizeX; x++) {
            printf("%10.6f ", matrix->cell[x][y]);
        }
        printf("\n");
    }
}

// =========================================================
// Базовые операции
// =========================================================

// Сложение матриц
DOUBLE_MATRIX summarize_double_matrix(DOUBLE_MATRIX *matrix1, DOUBLE_MATRIX *matrix2) {
    if (matrix1->sizeX != matrix2->sizeX || matrix1->sizeY != matrix2->sizeY) {
        fprintf(stderr, "summarize_double_matrix: incompatible sizes\n");
        exit(1);
    }
    DOUBLE_MATRIX tmp;
    set_double_size(&tmp, matrix1->sizeX, matrix1->sizeY);

    for (unsigned y = 0; y < matrix1->sizeY; y++) {
        for (unsigned x = 0; x < matrix1->sizeX; x++) {
            tmp.cell[x][y] = matrix1->cell[x][y] + matrix2->cell[x][y];
        }
    }
    return tmp;
}

// Умножение матриц
DOUBLE_MATRIX multiply_double_matrix(DOUBLE_MATRIX *matrix1, DOUBLE_MATRIX *matrix2) {
    if (matrix1->sizeX != matrix2->sizeY) {
        fprintf(stderr, "multiply_double_matrix: incompatible sizes\n");
        exit(1);
    }
    unsigned outSizeY = matrix1->sizeY;
    unsigned outSizeX = matrix2->sizeX;

    DOUBLE_MATRIX tmp;
    set_double_size(&tmp, outSizeX, outSizeY);

    for (unsigned y = 0; y < outSizeY; y++) {
        for (unsigned x = 0; x < outSizeX; x++) {
            double acc = 0.0f;
            for (unsigned w = 0; w < matrix1->sizeX; w++) {
                acc += matrix1->cell[w][y] * matrix2->cell[x][w];
            }
            tmp.cell[x][y] = acc;
        }
    }
    return tmp;
}

// Заполнение случайными числами [0;1]
void fill_double_random(DOUBLE_MATRIX *matrix) {
    srand((unsigned)time(NULL));
    for (unsigned y = 0; y < matrix->sizeY; y++) {
        for (unsigned x = 0; x < matrix->sizeX; x++) {
            matrix->cell[x][y] = (double)rand() / (double)RAND_MAX * 100;
        }
    }
}

// Заполнение случайными числами [0;1]
void fill_double_random_int_range(DOUBLE_MATRIX *matrix, int min, int max) {
    srand((unsigned)time(NULL));
    for (unsigned y = 0; y < matrix->sizeY; y++) {
        for (unsigned x = 0; x < matrix->sizeX; x++) {
            matrix->cell[x][y] = rand_int_in_range(min, max);
        }
    }
}

// Заполнение значениями от пользователя
void fill_double_scanf(DOUBLE_MATRIX *matrix) {
    for (unsigned y = 0; y < matrix->sizeY; y++) {
        for (unsigned x = 0; x < matrix->sizeX; x++) {
            scanf("%lf ", &matrix->cell[x][y]);
        }
    }
}

// Добавить константу ко всем элементам
void add_double_value(DOUBLE_MATRIX *matrix, double value) {
    for (unsigned y = 0; y < matrix->sizeY; y++) {
        for (unsigned x = 0; x < matrix->sizeX; x++) {
            matrix->cell[x][y] += value;
        }
    }
}

// Умножить все элементы на скаляр
void scalar_double_matrix(DOUBLE_MATRIX *matrix, double value) {
    for (unsigned y = 0; y < matrix->sizeY; y++) {
        for (unsigned x = 0; x < matrix->sizeX; x++) {
            matrix->cell[x][y] *= value;
        }
    }
}

// Добавить значение к диагональным элементам
void regularization_double_matrix(DOUBLE_MATRIX *matrix, double value) {
    if (matrix->sizeX != matrix->sizeY) {
        fprintf(stderr, "regularization_double_matrix: matrix must be square\n");
        exit(1);
    }
    for (unsigned i = 0; i < matrix->sizeX; i++) {
        matrix->cell[i][i] += value;
    }
}

// =========================================================
// Операции над строками
// =========================================================

// Переставить строки
void replace_strokes_double(DOUBLE_MATRIX *matrix, unsigned fr, unsigned to) {
    for (unsigned x = 0; x < matrix->sizeX; x++) {
        double tmp = matrix->cell[x][fr];
        matrix->cell[x][fr] = matrix->cell[x][to];
        matrix->cell[x][to] = tmp;
    }
}

// Умножить строку на число
void multiply_double_stroke(DOUBLE_MATRIX *matrix, unsigned stroke, double value) {
    for (unsigned x = 0; x < matrix->sizeX; x++) {
        matrix->cell[x][stroke] *= value;
    }
}

// row_to += row_fr * value
void stroke_double_mult_add(DOUBLE_MATRIX *matrix, unsigned fr, unsigned to, double value) {
    for (unsigned x = 0; x < matrix->sizeX; x++) {
        matrix->cell[x][to] += matrix->cell[x][fr] * value;
    }
}

// Получить подматрицу
DOUBLE_MATRIX get_submatrix(DOUBLE_MATRIX *matrix, unsigned frX, unsigned frY, unsigned toX, unsigned toY) {
    if (frX > toX || frY > toY || toX >= matrix->sizeX || toY >= matrix->sizeY) {
        fprintf(stderr, "get_submatrix: invalid indices\n");
        exit(1);
    }
    unsigned newW = toX - frX + 1;
    unsigned newH = toY - frY + 1;
    DOUBLE_MATRIX tmp;
    set_double_size(&tmp, newW, newH);
    for (unsigned y = 0; y < newH; y++) {
        for (unsigned x = 0; x < newW; x++) {
            tmp.cell[x][y] = matrix->cell[x + frX][y + frY];
        }
    }
    return tmp;
}

// Метод Гаусса
// Умеет только в квадратные матрицы (ну в смысле дополненные)
void gaus_method(DOUBLE_MATRIX *matrix) {
    int element_k = 0;

    // Прямой ход - сверху вниз
    while ((element_k < matrix->sizeX) && (element_k < matrix->sizeY)) {
        //printf("Before iteration:\n");
        //print_double_matrix(matrix);

        //printf("Replace strokes:\n");
        if (fabs(matrix->cell[element_k][element_k]) <= 0.000001) {
            // Ищем строку где элемент в этом столбце не равен 0 и меняем их местами
            for (unsigned y = element_k+1; y < matrix->sizeY; y++) {
                if (fabs(matrix->cell[element_k][y]) > 0.000001) {
                replace_strokes_double(matrix, y, element_k);
                }
            }
        }
        //print_double_matrix(matrix);

        //printf("Recalc matrix:\n");
        // Пересчитываем матрицу по формуле прямоугольником
        if (element_k < matrix->sizeY-1) {
            for (unsigned y = element_k+1; y < matrix->sizeY; y++) {
                for (unsigned x = element_k+1; x < matrix->sizeX; x++) {
                    matrix->cell[x/*j*/][y] = ((matrix->cell[x][y]*matrix->cell[element_k][element_k]) -
                    (matrix->cell[element_k][y]*matrix->cell[x][element_k]))/matrix->cell[element_k][element_k];
                }
            }
        }
        //print_double_matrix(matrix);

        //puts("Fill collumn by zero:");
        // Обнуляем все нижние элементы
        if (element_k<matrix->sizeY-1) {
            for (unsigned y = element_k+1; y < matrix->sizeY; y++) {
                matrix->cell[element_k][y] = 0;
            }
        }


        // Делим строку на element_k
        for (unsigned x = element_k+1; x <matrix->sizeX; x++) {
            matrix->cell[x][element_k] /= matrix->cell[element_k][element_k];
        }
        matrix->cell[element_k][element_k] /= matrix->cell[element_k][element_k];

        //print_double_matrix(matrix);
        element_k++;
        //puts("End step ---------------------------------------");
    }
        //puts("Start back walk --------------------------------");
    // Обратный ход
    element_k = matrix->sizeY-1;
    //printf("%d\n", element_k);
    while (element_k >= 0) {
        // Удаляем все ненулевые хвосты в столбце
        double current = matrix->cell[matrix->sizeX-1][element_k];
        //printf("%lf\n", current);
        for (unsigned y = element_k-1; (y >= 0) && (y != 4294967295); y--) {
            //printf("k: %d y: %d\n", element_k, y);
            matrix->cell[matrix->sizeX-1][y] -= current * matrix->cell[element_k][y];
            matrix->cell[element_k][y] = 0;
            //puts("After step:");
            //print_double_matrix(matrix);
        }
        element_k--;
        //puts("After back walk:");
        //print_double_matrix(matrix);
    }
}

