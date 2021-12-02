#include <stdio.h>

#include <stdint.h>

#include <stdbool.h>

#include <stdlib.h>

#include <limits.h>

#include <stdlib.h>

typedef struct Graf {
    int ** matrix_collum;
    int length;
}
graf;

graf give_graf();
int grafviz(graf * a);
graf TakeGraf();
void VertDelete(graf * a, int NumbOfVertex);
void GrafSort(graf * a);

int main() {
    int VerNumb;
    graf gr;
    gr = TakeGraf();
    printf("Какую вершину нужно удалить?\n");
    scanf("%d", & VerNumb);
    VertDelete( & gr, VerNumb);
    grafviz( & gr);
    GrafSort( & gr);
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
    int len = a -> length;
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
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            if (a -> matrix_collum[i][j])
                fprintf(fp, "\"%d\"--\"%d\";\n", i + 1, j + 1);
            else
                fprintf(fp, "\"%d\";\n", i + 1);
        }
    }
    fprintf(fp, "}");
    fclose(fp);
    return 0;
}
graf TakeGraf() {
    FILE * fp;
    if ((fp = fopen("graf.txt", "r")) == NULL) {
        char err[] = {
            "Error"
        };
        printf("Не удалось открыть файл\n");
        perror(err);
        exit(-1);
    }
    int length;
    int c;
    fscanf(fp, "%d", & length);
    int ** matrix_collum = malloc(sizeof(int * ) * length);
    for (int i = 0; i < length; i++)
        matrix_collum[i] = malloc(sizeof(int * ) * length);
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; ++j) {
            fscanf(fp, "%d", & c);
            matrix_collum[i][j] = c;
        }
    }
    graf a;
    a.matrix_collum = matrix_collum;
    a.length = length;
    fclose(fp);
    return a;

    fclose(fp);
}
void VertDelete(graf * a, int NumbOfVertex) {
    if (NumbOfVertex != 0) {
        int numb = NumbOfVertex - 1;
        a -> length--;
        if (NumbOfVertex != a -> length) {
            for (int i = numb; i < a -> length; i++)
                a -> matrix_collum[i] = a -> matrix_collum[i + 1];
            for (int i = 0; i < a -> length; i++)
                for (int j = numb; j < a -> length; j++)
                    a -> matrix_collum[i][j] = a -> matrix_collum[i][j + 1];
        }
    }
}
void GrafSort(graf * a) {
    int counter = 0;
    int mass[a -> length];
    int arr[a -> length];
    for (int i = 0; i < a -> length; i++) {
        for (int j = 0; j < a -> length; j++) {
            if (a -> matrix_collum[i][j])
                counter++;
        }
        arr[i] = i + 1;
        mass[i] = counter;
        counter = 0;
    }
    int newElement, location, number;

    for (int i = 1; i < a -> length; i++) {
        newElement = mass[i];
        number = arr[i];
        location = i - 1;
        while (location >= 0 && mass[location] > newElement) {
            mass[location + 1] = mass[location];
            arr[location + 1] = arr[location];
            location = location - 1;

        }
        mass[location + 1] = newElement;
        arr[location + 1] = number;
    }
    printf("Номера отсортированных вершин нового графа:\n")
    for (int i = 0; i < a -> length; i++)
        printf("%d ", arr[i]);
    printf("\n");
}