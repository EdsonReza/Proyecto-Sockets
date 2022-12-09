#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void generaGrafica(char *nombre, int v[], int tam);
void transformarVector(float vector[], int v[], int tam);
void mostrarVector(float v[], int tam);
void mostrarVectorI(int v[], int tam);

/**
 * @brief 
 * Genera una imagen bmp o mapa de bits
 * @param nombre Nombre del archivo bmp
 * @param v vector para generar la grafiaca
 * @param tam tamanio del vector
 */
inline void generaGrafica(char *nombre, int v[], int tam)
{

    FILE *arch;

    int numFilas = tam + (tam - 1); // numero de renglones
    int bp = 60;

    // Medidas tamaño de la imagen
    int width = 100;            // ancho de la imagen
    int height = bp * numFilas; // alto de la imagen

    int blanco = 255;
    int negro = 0;
    remove(nombre);
    arch = fopen(nombre, "a");

    if (arch == NULL)
    {
        printf("No se pudo abrir el archivo");
        return;
    }

    fprintf(arch, "P2\n");

    fprintf(arch, "%d %d\n", width, height); // Se genera la imagen con las medidas establecidas
    int color = blanco;
    int rec = 0;
    for (int i = 0; i < numFilas; i++)
    {
        if (i % 2 == 0)
        {

            color = blanco;
            for (int ancho = 0; ancho < bp; ancho++)
            {
                for (int j = 0; j < v[rec]; j++)
                {
                    fprintf(arch, "%d\n", blanco);
                }
                color = negro;
                for (int k = v[rec]; k < width; k++)
                { 
                    fprintf(arch, "%d\n", negro);
                }
            }
            rec++;
        }
        else
        {
            color = negro;
            for (int ancho = 0; ancho < bp; ancho++)
            {
                for (int e = 0; e < width; e++)
                {
                    fprintf(arch, "%d\n", negro);
                }
            }
        }
    }
    fclose(arch);
}
inline void transformarVector(float vector[], int v[], int tam)
{

    for (int i = 0; i < tam; i++)
    {
        v[i] = vector[i] * 10;
    }
}

inline void mostrarVector(float vector[], int tam)
{
    printf("\nVector: \n");
    for (int i = 0; i < tam; i++)
    {
        printf("|%.1f", vector[i]);
    }
}

inline void mostrarVectorI(int v[], int tam)
{
    printf("\nVector: \n");
    for (int i = 0; i < tam; i++)
    {
        printf("|%d", v[i]);
    }
}