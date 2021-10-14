#include <stdio.h>

#include <stdint.h>

#include <stdbool.h>

#include <stdlib.h>

#include <limits.h>

#include <stdlib.h>

typedef struct Graf {
    int ** matrix_collum;
    int length;
}graf;

graf give_graf();
int grafviz(graf * a);
int is_simple_cycle(graf * a);

int main() {
    graf gr;
    gr = give_graf();
    grafviz( & gr);
    is_simple_cycle( & gr);
    for (int i = 0; i < gr.length; i++)
        free(gr.matrix_collum[i]);
    free(gr.matrix_collum);
}
graf give_graf() {
    int length;
    int c;
    printf("Enter the number of vertices: ");
    scanf("%d", & length);
    printf("\n");
    printf("Enter the matrix:\n");
    int ** matrix_collum = malloc(sizeof(int * ) * length);
    for (int i = 0; i < length; i++)
        matrix_collum[i] = malloc(sizeof(int * ) * length);
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; ++j) {
            scanf("%d", & c);
            matrix_collum[i][j] = c;
        }
    }
    graf a;
    a.matrix_collum = matrix_collum;
    a.length = length;
    printf("\n");
    return a;
}

int grafviz(graf * a) {
    FILE * fp;
    if ((fp = fopen("graf.gv", "w")) == NULL) {
        char err[] = {
            "Error"
        };
        printf("Не удалось открыть файл\n");
        perror(err);
        return 0;
    }
    char arr[] = "graph Hellhbh {\n";
    fputs(arr, fp);
    for (int i = 0; i < a -> length; i++) {
        for (int j = i; j < a -> length; j++) {
            if ( a->matrix_collum[i][j])
                fprintf(fp, "\"%d\"--\"%d\";\n", i + 1, j + 1);
        }
    }
    fprintf(fp, "}");
    fclose(fp);
    return 0;
}

int is_simple_cycle(graf * a) {
    int i, j, prev, next, counter;
    counter = 0;
    for (int i = 0; i < a -> length; i++) {
        for (j = 0; j < a -> length; j++) {
            if ((j == i) && (a->matrix_collum[i][j] == 1))
            {
                printf("У графа петли");
                return 0;
            }
            else if (i == 0)
            {
                prev = a->length - 1;
                next = 1;
            }
            else if (i == (a->length - 1))
            {
                prev = i - 1;
                next = 0;
            }
            else
            {
                prev = i - 1;
                next = i + 1;
            }
            if (a->matrix_collum[i][j] == 1)
            {
                if (j == next)
                {
                    ++counter;
                }
                else if (j == prev);
                else
                {
                    --counter;
                }
            }
        }
    }
    if (counter == a->length)
    {
        printf("Граф - простой цикл\n");
    }
    else
    {
        printf("Граф - не простой цикл\n");
    }
    return 0;
}