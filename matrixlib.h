#ifndef MATRIX_LIB
#define MATRIX_LIB

// Matrix of double values
typedef struct DOUBLE_MATRIX {
    unsigned sizeY;
    unsigned sizeX;
    double **cell;
} DOUBLE_MATRIX;

// Allocate memory for matrix and fill it by zero
void set_double_size(DOUBLE_MATRIX *matrix, unsigned sizeX, unsigned sizeY);

// Clear memory
void destroy_double_matrix(DOUBLE_MATRIX *matrix);

// Sum two matrix el by el and return result
DOUBLE_MATRIX summarize_double_matrix(DOUBLE_MATRIX *matrix1, DOUBLE_MATRIX *matrix2);

// Multiply two matrix
DOUBLE_MATRIX multiply_double_matrix(DOUBLE_MATRIX *matrix1, DOUBLE_MATRIX *matrix2);

// Fill by random values
void fill_double_random(DOUBLE_MATRIX *matrix);

// Fill by random integer values
void fill_double_random_int_range(DOUBLE_MATRIX *matrix, int min, int max);

// Заполнение значениями от пользователя
void fill_double_scanf(DOUBLE_MATRIX *matrix);

// Add a number to all elements
void add_double_value(DOUBLE_MATRIX *matrix, double value);

// Multiply matrix on scalar
void scalar_double_matrix(DOUBLE_MATRIX *matrix, double value);

// Add value to all diagonal elements
void regularization_double_matrix(DOUBLE_MATRIX *matrix, double value);

// Swaps lines
void replace_strokes_double(DOUBLE_MATRIX *matrix, unsigned fr, unsigned to);

// Multiply values in stroke
void multiply_double_stroke(DOUBLE_MATRIX *matrix, unsigned stroke, double value);

// Multiply and add to stroke
void stroke_double_mult_add(DOUBLE_MATRIX *matrix, unsigned fr, unsigned to, double value);

// Return submatrix
DOUBLE_MATRIX get_submatrix(DOUBLE_MATRIX *matrix, unsigned frX, unsigned frY, unsigned toX, unsigned toY);

void gaus_method(DOUBLE_MATRIX *matrix);





// Print double matrix
void print_double_matrix(DOUBLE_MATRIX *matrix);

#endif
