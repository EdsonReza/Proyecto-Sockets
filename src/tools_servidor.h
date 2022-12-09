

#ifndef TOOLS_H
#define TOOLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MEXICO 49
#define ANCHO_DE_PANTALLA 80
#define WINDOWS 1
#define LINUX 0
#define TAM_CADENA_1 100
    
    char CARACTER_HORIZONTAL = '*';
    int os = LINUX;

    int obtenerOS() {
        return os;
    }

    void limpiaPantalla() {
        if (obtenerOS() == LINUX) {
            system("clear");
        } else {
            if (obtenerOS() == WINDOWS) {
                system("cls");
            }
        }
    }

    int estaEnRangoDeNumeros(int numero) {
        if ((numero >= 48) && (numero <= 57)) {
            return 1;
        } else {
            return 0;
        }
    }

    int esPunto(int numero) {
        if (numero == 46) {
            return 1;
        } else {
            return 0;
        }
    }

    int esNumeroEnteroPositivo(char numero[]) {

        int i = 0;

        if (strlen(numero) > 0) {

            while (estaEnRangoDeNumeros(numero[i])) {
                i++;
            }

            if (i == strlen(numero)) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }


    }

    int esNumeroRealPositivo(char numero[]) {

        int i = 0, numeroDePuntos = 0;

        while (estaEnRangoDeNumeros(numero[i]) || esPunto(numero[i])) {

            i++;
            if (esPunto(numero[i])) {
                numeroDePuntos++;
            }
        }

        if (i == strlen(numero) && (numeroDePuntos < 2)) {
            return 1;
        } else {
            return 0;
        }
    }

    void llevaAPosicionDeRenglon(int x) {
        int j;
        for (j = 0; j < x; j++) {
            printf(" ");
        }
    }

    void imprimeEnCentro(char c[]) {
        int l = strlen(c);
        int ch = (int) ((ANCHO_DE_PANTALLA / 2) - l / 2);
        llevaAPosicionDeRenglon(ch);
        printf("%s", c);
    }

    void imprimeLineaHorizontal(char caracter) {
        int contador;
        for (contador = 0; contador < ANCHO_DE_PANTALLA; contador++) {
            printf("%c", caracter);
        }
        puts("");
    }

    void imprimeEspaciosHorizontal(int espacios) {
        int contador;
        for (contador = 0; contador < espacios; contador++) {
            printf(" ");
        }
    }

    void imprimeEnCentroConSalto(char c[]) {
        int l = strlen(c);
        int ch = (int) ((ANCHO_DE_PANTALLA / 2) - l / 2);
        llevaAPosicionDeRenglon(ch);
        printf("%s\n", c);
    }

    void imprimeTitulo(char titulo[]) {

        imprimeLineaHorizontal(CARACTER_HORIZONTAL);
        printf("%c", CARACTER_HORIZONTAL);
        imprimeEspaciosHorizontal((ANCHO_DE_PANTALLA / 2) - strlen(titulo) / 2 - 1);
        printf("%s", titulo);
        imprimeEspaciosHorizontal((ANCHO_DE_PANTALLA / 2) - strlen(titulo) / 2 - 1);
        printf("%c\n", CARACTER_HORIZONTAL);
        imprimeLineaHorizontal(CARACTER_HORIZONTAL);
    }

    void pausa() {
        char p[5000];
        gets(p);
    }

    void imprimePausa(void) {
        imprimeLineaHorizontal(CARACTER_HORIZONTAL);
        imprimeEnCentro("Pulse enter para continuar.");
        puts("");
        imprimeLineaHorizontal(CARACTER_HORIZONTAL);
        pausa();
        limpiaPantalla();
    }

    void imprimeMensajeDoble(char c1[], char c2[]) {
        printf("\n\n\n");
        imprimeLineaHorizontal(CARACTER_HORIZONTAL);
        imprimeEnCentroConSalto(c1);
        imprimeEnCentroConSalto(c2);
        imprimeLineaHorizontal(CARACTER_HORIZONTAL);
        printf("\n\n\n");
        imprimePausa();
    }

    void imprimeMensajeSimple(char c[]) {
        printf("\n\n\n");
        imprimeLineaHorizontal(CARACTER_HORIZONTAL);
        imprimeEnCentroConSalto(c);
        imprimeLineaHorizontal(CARACTER_HORIZONTAL);
        printf("\n\n\n");
        imprimePausa();
    }

    void imprimePantallaMensajeDoble(char titulo[], char mensaje1[], char mensaje2[]) {
        imprimeTitulo(titulo);
        imprimeMensajeDoble(mensaje1, mensaje2);
    }

    int estaEnRango(int izquierda, int derecha, int valor) {
        return valor >= izquierda && valor <= derecha;
    }

    int capturaNumeroEnteroPositivo() {

        char numero[1000];

        gets(numero);

        if (strlen(numero) > 0) {

            if (esNumeroEnteroPositivo(numero)) {

                limpiaPantalla();
                return atof(numero);
            } else {

                limpiaPantalla();
                imprimePantallaMensajeDoble("Error de caputa de datos",
                        "El dato es erroneo.",
                        "Intente nuevamente.");
                return -1;
            }
        } else {
            limpiaPantalla();
            imprimePantallaMensajeDoble("Error de caputa de datos",
                    "Este campo no puede ir vacio",
                    "Intente nuevamente.");
            return -1;
        }
    }

    float capturaNumeroRealPositivo() {

        char numero[1000];

        gets(numero);

        if (strlen(numero) > 0) {

            if (esNumeroRealPositivo(numero)) {

                limpiaPantalla();
                return atof(numero);
            } else {

                limpiaPantalla();
                imprimePantallaMensajeDoble("Error de caputa de datos",
                        "El dato es erroneo.",
                        "Intente nuevamente.");
                return -1;
            }
        } else {
            limpiaPantalla();
            imprimePantallaMensajeDoble("Error de caputa de datos",
                    "Este campo no puede ir vacio",
                    "Intente nuevamente.");
            return -1;
        }
    }

    int imprimePantallaCapturaNumeroEnteroPositivo(char titulo[], char etiqueta[]) {

        int numero;

        do {
            imprimeTitulo(titulo);
            imprimeEnCentro(etiqueta);

            numero = capturaNumeroEnteroPositivo();

            if (numero > -1) {
                return numero;
            }
        } while (1);
    }

    float imprimePantallaCapturaNumeroRealPositivo(char titulo[], char etiqueta[]) {

        float numero;

        do {
            imprimeTitulo(titulo);
            imprimeEnCentro(etiqueta);

            numero = capturaNumeroRealPositivo();

            if (numero > -1) {
                return numero;
            }
        } while (1);
    }

    void imprimeMensajeMantenimiento() {

        imprimeMensajeSimple("Temporalmente en mantenimiento ;D");
    }

    void imprimePantallaCapturaCadena(char titulo[], char etiqueta[], char *cadena) {

        imprimeTitulo(titulo);
        imprimeEnCentro(etiqueta);
        gets(cadena);
        limpiaPantalla();
    }

    void imprimeEtiquetaCapturaCadena(char etiqueta[], char cadena[]) {
        imprimeLineaHorizontal(CARACTER_HORIZONTAL);
        printf("    %s", etiqueta);
        gets(cadena);
    }

    int imprimePantallaDobleCondicion(char mensaje[]) {

        int respuesta;

        imprimeTitulo("Escoja una opcion ");
        imprimeEnCentroConSalto(mensaje);
        imprimeEnCentroConSalto("[ Si = 1   :   No = 0 ]");

        respuesta = capturaNumeroEnteroPositivo();

        if (respuesta == 1 || respuesta == 0) {
            return respuesta;
        } else {
            return imprimePantallaDobleCondicion(mensaje);
        }
    }

    int imprimeMenuIzquierda(char titulo[], char menu[], char caracterDeSalto) {

        int contador = 0, opcionG = 1, espacios = 0;
        int opcion, salto = 1;

        imprimeTitulo(titulo);

        while (contador < strlen(menu)) {

            if (salto) {
                printf("%c %d.- ", CARACTER_HORIZONTAL, opcionG);
                opcionG++;
                salto = 0;
            }

            if (menu[contador] == caracterDeSalto) {

                if (opcionG < 11) {
                    imprimeEspaciosHorizontal(ANCHO_DE_PANTALLA - 7 - espacios);
                } else {
                    imprimeEspaciosHorizontal(ANCHO_DE_PANTALLA - 8 - espacios);
                }

                printf("%c\n", CARACTER_HORIZONTAL);
                salto = 1;
                espacios = 0;

            } else {
                printf("%c", menu[contador]);
                espacios++;
            }
            contador++;
        }

        if (opcionG < 11) {
            imprimeEspaciosHorizontal(ANCHO_DE_PANTALLA - 7 - espacios);
        } else {
            imprimeEspaciosHorizontal(ANCHO_DE_PANTALLA - 8 - espacios);
        }
        puts("*");
        imprimeLineaHorizontal(CARACTER_HORIZONTAL);

        imprimeEnCentro("Escoja una opcion: ");
        opcion = capturaNumeroEnteroPositivo();
        limpiaPantalla();
        return opcion;
    }

    /*
     * Devuelve 1 si se creo correctamente
     * Devuelve 0 si no se pudo crear
     *
     * Lee un archivo de texto ya predefinido
     * sin formato
     */
    void leeArchivoTexto(char nombreArchivo[]) {
        FILE *archivo = NULL;
        char cadenaLeida[256];
        archivo = fopen(nombreArchivo, "r");

        if (archivo != NULL) {
            while (feof(archivo) == 0) {
                fgets(cadenaLeida, 256, archivo);
                printf(" %s", cadenaLeida);
                memset(cadenaLeida, 0, strlen(cadenaLeida));
            }
        }
        fclose(archivo);
    }

    int imprimeMenuBasadoEnArchivo(char nombreArchivo[], char titulo[]) {

        imprimeTitulo(titulo);
        leeArchivoTexto(nombreArchivo);
        puts("");
        imprimeLineaHorizontal(CARACTER_HORIZONTAL);
        imprimeEnCentro("Escoja una opcion: ");

        return capturaNumeroEnteroPositivo();
    }

    /**
     * Devuelve 1 si se creo correctamente
     * Devuelve 0 si no se pudo crear
     *
     * El archivo si existe se sobreescribira.
     * Si no existe se crea.
     *
     * nombreArchivo es el nombre que se le dara al
     * archivo a crear.
     */
    int creaArchivo(char nombreArchivo[]) {
        FILE *archivo = NULL;

        archivo = fopen(nombreArchivo, "w");

        if (archivo != NULL) {
            fclose(archivo);
            return 1;
        } else {
            fclose(archivo);
            return 0;
        }
    }

    /*
     * Extraen una cadena del archivo mencionado
     * en la posicion espesificada y la guarda en la
     * variable buffer.
     */
    void extraerCadenaDeArchivo(char nombreArchivo[], int posicion, char buffer[]) {
        FILE *archivo = NULL;
        int contador = 0;
        int encontrado = 0;

        archivo = fopen(nombreArchivo, "r");

        if (archivo != NULL) {
            while (feof(archivo) == 0 && encontrado != 1) {

                fgets(buffer, 200, archivo);

                if (contador == posicion) {

                    encontrado = 1;
                }
                contador++;
            }
        }
        fclose(archivo);
    }

    void insertaCadenaDeArchivo(char nombreArchivo[], char buffer[]) {
        FILE *archivo = NULL;

        archivo = fopen(nombreArchivo, "a+");

        if (archivo != NULL) {

            fputs(buffer, archivo);
            fputs("\n", archivo);
        } else {
            creaArchivo(nombreArchivo);
            insertaCadenaDeArchivo(nombreArchivo, buffer);
        }
        fclose(archivo);
    }

    /*Funcion que extre s�lo el texto sin salto de l�nea
      Recibe: cadena.-Cadena con todo el texto y salto de l�nea
              texto.- Cadena sin salto de l�nea
      texto debe ser de igual o mayor longitud que cadena
     */
    void extraeCadena(char cadena[], char texto[]) {
        int i = 0;
        while (cadena[i] != '\n') {
            texto[i] = cadena[i];
            i++;
        }
        texto[i] = '\0';
    }

    /*Convierte una cadena de min�sculas a mayusculas
      Recibe: cadena a convertir
     */
    void conversionMayus(char cadena[]) {
        int i = 0;
        while (i < strlen(cadena)) {
            cadena[i] = toupper(cadena[i]);
            i++;
        }
    }

    void borraCadena(char cadena[]) {
        memset(cadena, 0, strlen(cadena));
    }

    void convierteEnteroACadena(char cadena[], int entero) {
        borraCadena(cadena);
        sprintf(cadena, "%d", entero);
    }

    void convierteflotanteACadena(char cadena[], float flotante) {
        borraCadena(cadena);
        sprintf(cadena, "%f", flotante);
    }

    void truncaCadenaFila(char cadena[], int espacioMaximo, char buffer[]) {

        int longBuffer = strlen(buffer);

        for (int i = 0; i < espacioMaximo; i++) {

            if (i < strlen(cadena)) {
                buffer[longBuffer] = cadena[i];
            } else {
                buffer[longBuffer] = ' ';
            }
            longBuffer++;
        }
    }


#ifdef __cplusplus
}
#endif

#endif /* TOOLS_H */
