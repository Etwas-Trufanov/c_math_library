#include "matrixlib.h"
#include <stdio.h>

int main() {
    unsigned tSizeY;
    unsigned tSizeX;

    printf("Enter size x and size y of matrix: ");
    scanf("%i %i", &tSizeX, &tSizeY);

    DOUBLE_MATRIX matrix1;

    set_double_size(&matrix1, tSizeX, tSizeY);
    
    fill_double_random_int_range(&matrix1, 1, 20);

    print_double_matrix(&matrix1);

    gaus_method(&matrix1);

    print_double_matrix(&matrix1);

    destroy_double_matrix(&matrix1);

    return 0;
}
