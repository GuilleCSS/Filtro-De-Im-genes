//Procesamiento de imagenes
//Autores: Guillermo Carreto Sanchez-Gustavo Nava Pintor-Samuel Soriano Chavez-Angel Miguel Sanchez Perez
//11/06/2023

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Constantes
#define MAX_LONGITUD 100
	
//Prototipos
void filtrodesenfoque(char *);
void filtroenfoque(char *);
void filtrorepujado(char *);
void filtrorealcebordes(char *);
void filtrodetectarbordes(char *);

//Funcion principal
int main(void) {
	
	//Variables
    char nombreArchivo[MAX_LONGITUD];
    int opcion;
	
	//Pedirle al usuario que imagen quiere ponerle un filtro
    printf("Ingrese el nombre del archivo PGM: ");
    scanf("%s", nombreArchivo);

	//Ciclo do-while para la aplicacion del filtro
	do{
		printf("Seleccione el filtro a aplicar:\n");
    	printf("1. Desenfoque\n");
    	printf("2. Enfocar\n");
    	printf("3. Repujado\n");
    	printf("4. Realce de bordes\n");
    	printf("5. Detector de bordes\n");
    	printf("6. Salir del editor");
    	printf("\nOpcion: ");
    	scanf("%d", &opcion);
			
			
    		switch (opcion) {
        		case 1:
            		filtrodesenfoque(nombreArchivo);
            		break;
        		case 2:
           			filtroenfoque(nombreArchivo);
            		break;
        		case 3:
            		filtrorepujado(nombreArchivo);
            		break;
        		case 4:
            		filtrorealcebordes(nombreArchivo);
            		break;
        		case 5:
        			filtrodetectarbordes(nombreArchivo);
        			break;
    			case 6: 
    				printf("\nGracias");
    		}
	}while(opcion!=6);

    return 0;
}

//Funcion para el filtro de desenfoque
void filtrodesenfoque(char* nombreArchivo) {
	
	//Variables
    FILE* archivo;
    FILE* archivoSalida;
    char encabezado[MAX_LONGITUD];
    int ancho, alto, max_valor;
    int** matriz;
    int** resultado;
	
	//Abrimos la imagen PGM
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
	
	//Se lee el encabezado
    fscanf(archivo, "%s", encabezado);
    if (strcmp(encabezado, "P2") != 0) {
        printf("El archivo no es un archivo PGM valido.\n");
        fclose(archivo);
        return;
    }
	
	//Se reconoce el ancho-alto y el maximo valor de pixeles de la imagen
    fscanf(archivo, "%d %d", &ancho, &alto);
    fscanf(archivo, "%d", &max_valor);
	
	//Se crea la matriz del ancho-alto de la imagen
    matriz = (int**)malloc(alto * sizeof(int*));
    for (int i = 0; i < alto; i++) {
        matriz[i] = (int*)malloc(ancho * sizeof(int));
    }
	
	//Se lee los datos de cada pixel en la matriz
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fscanf(archivo, "%d", &matriz[i][j]);
        }
    }

    fclose(archivo); //Cerramos el archivo
	
	//Creamos la matriz resultante con el tamaño de la imagen
    resultado = (int**)malloc(alto * sizeof(int*));
    for (int i = 0; i < alto; i++) {
        resultado[i] = (int*)malloc(ancho * sizeof(int));
        for (int j = 0; j < ancho; j++) {
            int sum = 0;
            int cont = 0;
            for (int k = i - 1; k <= i + 1; k++) {
    			for (int l = j - 1; l <= j + 1; l++) {
       				if (k >= 0 && k < alto && l >= 0 && l < ancho) {
            		sum += matriz[k][l];
            		cont++;
        			}
    			}
			}

            resultado[i][j] = sum / 9;
        }
    }
	
	//Se crea el archivo para guardar la nueva imagen
    archivoSalida = fopen("desenfoque.pgm", "w");
    if (archivoSalida == NULL) {
        printf("No se pudo crear el archivo de salida.\n");
        return;
    }
	
	//Se escribe en el archivo el encabezado, el anchi-alto y el maximo valor de pixeles
    fprintf(archivoSalida, "P2\n");
    fprintf(archivoSalida, "%d %d\n", ancho, alto);
    fprintf(archivoSalida, "%d\n", max_valor);
	
	//Imprimimos la matriz resultante en el archivo
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fprintf(archivoSalida, "%d ", resultado[i][j]);
        }
        fprintf(archivoSalida, "\n");
    }

    fclose(archivoSalida); //Se cierra el archivo nuevo
    printf("Se ha aplicado el filtro de desenfoque a la imagen.\n");

	//Liberamos la memoria utilizada
    for (int i = 0; i < alto; i++) {
        free(matriz[i]);
        free(resultado[i]);
    }
    free(matriz);
    free(resultado);
	
	return;
}

//Funcion para el filtro de enfoque
void filtroenfoque(char* nombreArchivo) {
	
	//Variables
    FILE* archivo;
    FILE* archivoSalida;
    char encabezado[MAX_LONGITUD];
    int ancho, alto, max_valor;
    int** matriz;
    int** resultado;
	
	//Abrimos la imagen PGM
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
	
	//Se lee el encabezado
    fscanf(archivo, "%s", encabezado);
    if (strcmp(encabezado, "P2") != 0) {
        printf("El archivo no es un archivo PGM valido.\n");
        fclose(archivo);
        return;
    }
	
	//Se reconoce el ancho-alto y el maximo valor de pixeles de la imagen
    fscanf(archivo, "%d %d", &ancho, &alto);
    fscanf(archivo, "%d", &max_valor);

	//Se crea la matriz del ancho-alto de la imagen
    matriz = (int**)malloc(alto * sizeof(int*));
    for (int i = 0; i < alto; i++) {
        matriz[i] = (int*)malloc(ancho * sizeof(int));
    }
	
	//Se lee los datos de cada pixel en la matriz
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fscanf(archivo, "%d", &matriz[i][j]);
        }
    }

    fclose(archivo);//Cerramos el archivo

	//Creamos la matriz resultante con el tamaño de la imagen
    resultado = (int**)malloc(alto * sizeof(int*));
    for (int i = 0; i < alto; i++) {
        resultado[i] = (int*)malloc(ancho * sizeof(int));
        for (int j = 0; j < ancho; j++) {
            if (i == 0 || j == 0 || i == alto - 1 || j == ancho - 1) {
                resultado[i][j] = matriz[i][j];
            } else {
                int sum = 5 * matriz[i][j] - matriz[i - 1][j] - matriz[i][j - 1] - matriz[i][j + 1] - matriz[i + 1][j];
                if (sum < 0) {
                    sum = 0;
                }
                if (sum > max_valor) {
                    sum = max_valor;
                }
                resultado[i][j] = sum;
            }
        }
    }
	
	//Se crea el archivo para guardar la nueva imagen
    archivoSalida = fopen("enfoque.pgm", "w");
    if (archivoSalida == NULL) {
        printf("No se pudo crear el archivo de salida.\n");
        return;
    }
	
	//Se escribe en el archivo el encabezado, el anchi-alto y el maximo valor de pixeles
    fprintf(archivoSalida, "P2\n");
    fprintf(archivoSalida, "%d %d\n", ancho, alto);
    fprintf(archivoSalida, "%d\n", max_valor);
	
	//Imprimimos la matriz resultante en el archivo
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fprintf(archivoSalida, "%d ", resultado[i][j]);
        }
        fprintf(archivoSalida, "\n");
    }

    fclose(archivoSalida);//Se cierra el archivo nuevo
    printf("Se ha aplicado el filtro de enfoque a la imagen.\n");
	
	//Liberamos la memoria utilizada
    for (int i = 0; i < alto; i++) {
        free(matriz[i]);
        free(resultado[i]);
    }
    free(matriz);
    free(resultado);
    
    return;
}

//Funcion para el filtro de repujado
void filtrorepujado(char* nombreArchivo) {

    // Variables
    FILE* archivo;
    FILE* archivoSalida;
    char encabezado[MAX_LONGITUD];
    int ancho, alto, max_valor;
    int** matriz;
    int** resultado;

    // Abrimos la imagen PGM
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Se lee el encabezado
    fscanf(archivo, "%s", encabezado);
    if (strcmp(encabezado, "P2") != 0) {
        printf("El archivo no es un archivo PGM válido.\n");
        fclose(archivo);
        return;
    }

    // Se reconoce el ancho-alto y el máximo valor de píxeles de la imagen
    fscanf(archivo, "%d %d", &ancho, &alto);
    fscanf(archivo, "%d", &max_valor);

    // Se crea la matriz del ancho-alto de la imagen
    matriz = (int**)malloc(alto * sizeof(int*));
    resultado = (int**)malloc(alto * sizeof(int*));
    for (int i = 0; i < alto; i++) {
        matriz[i] = (int*)malloc(ancho * sizeof(int));
        resultado[i] = (int*)malloc(ancho * sizeof(int));
    }

    // Se lee los datos de cada píxel en la matriz
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fscanf(archivo, "%d", &matriz[i][j]);
        }
    }

    fclose(archivo); // Se cierra el archivo
    
    int filtro[3][3] = {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}};

    // Aplicamos el filtro de repujado a cada píxel de la imagen original
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            if (i < 1 || j < 1 || i >= alto - 1 || j >= ancho - 1) {
                resultado[i][j] = matriz[i][j];
            } else {
                int suma = 0;
                
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        suma += matriz[i + k][j + l] * filtro[k + 1][l + 1];
                    }
                }
                if (suma < 0) {
                    suma = 0;
                }
                resultado[i][j] = suma;
            }
        }
    }

    // Se crea el archivo para guardar la nueva imagen
    archivoSalida = fopen("repujado.pgm", "w");
    if (archivoSalida == NULL) {
        printf("No se pudo crear el archivo de salida.\n");
        return;
    }

    // Se escribe en el archivo el encabezado, el ancho-alto y el máximo valor de píxeles
    fprintf(archivoSalida, "P2\n");
    fprintf(archivoSalida, "%d %d\n", ancho, alto);
    fprintf(archivoSalida, "%d\n", max_valor);

    // Se escribe en el archivo la matriz resultante
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fprintf(archivoSalida, "%d ", resultado[i][j]);
        }
        fprintf(archivoSalida, "\n");
    }

    fclose(archivoSalida); // Se cierra el archivo resultante
    printf("Se ha aplicado el filtro de repujado a la imagen.\n");

    // Liberamos la memoria utilizada
    for (int i = 0; i < alto; i++) {
        free(matriz[i]);
        free(resultado[i]);
    }
    free(matriz);
    free(resultado);

    return;
}

//Funcion para el filtro de realce de bordes
void filtrorealcebordes(char* nombreArchivo) {

    // Variables
    FILE* archivo;
    FILE* archivoSalida;
    char encabezado[MAX_LONGITUD];
    int ancho, alto, max_valor;
    int** matriz;
    int** resultado;

    // Abrimos la imagen PGM
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Se lee el encabezado
    fscanf(archivo, "%s", encabezado);
    if (strcmp(encabezado, "P2") != 0) {
        printf("El archivo no es un archivo PGM valido.\n");
        fclose(archivo);
        return;
    }

    // Se reconoce el ancho-alto y el maximo valor de pixeles de la imagen
    fscanf(archivo, "%d %d", &ancho, &alto);
    fscanf(archivo, "%d", &max_valor);

    // Se crea la matriz del ancho-alto de la imagen
    matriz = (int**)malloc(alto * sizeof(int*));
    for (int i = 0; i < alto; i++) {
        matriz[i] = (int*)malloc(ancho * sizeof(int));
    }

    // Se lee los datos de cada pixel en la matriz
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fscanf(archivo, "%d", &matriz[i][j]);
        }
    }

    fclose(archivo); // Se cierra el archivo

    // Creamos la matriz resultante con el tamaño de la imagen
    resultado = (int**)malloc(alto * sizeof(int*));
    for (int i = 0; i < alto; i++) {
        resultado[i] = (int*)malloc(ancho * sizeof(int));
        for (int j = 0; j < ancho; j++) {
            if (i == 0 || j == 0 || i == alto - 1 || j == ancho - 1) {
                resultado[i][j] = matriz[i][j];
            } else {
                int suma = matriz[i][j] - matriz[i - 1][j - 1];
                if (suma < 0) {
                    suma = 0;
                }
                resultado[i][j] = suma;
            }
        }
    }

    // Se crea el archivo para guardar la nueva imagen
    archivoSalida = fopen("realce_bordes.pgm", "w");
    if (archivoSalida == NULL) {
        printf("No se pudo crear el archivo de salida.\n");
        return;
    }

    // Se escribe en el archivo el encabezado, el anchi-alto y el maximo valor de pixeles
    fprintf(archivoSalida, "P2\n");
    fprintf(archivoSalida, "%d %d\n", ancho, alto);
    fprintf(archivoSalida, "%d\n", max_valor);

    // Se escribe en el archivo la matriz resultante
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fprintf(archivoSalida, "%d ", resultado[i][j]);
        }
        fprintf(archivoSalida, "\n");
    }

    fclose(archivoSalida); // Cerramos el archivo
    printf("Se ha aplicado el filtro de realce de bordes a la imagen.\n");

    // Liberamos la memoria utilizada
    for (int i = 0; i < alto; i++) {
        free(matriz[i]);
        free(resultado[i]);
    }
    free(matriz);
    free(resultado);
}

//Funcion para el filtro de detectar bordes
void filtrodetectarbordes(char* nombreArchivo) {

    // Variables
    FILE* archivo;
    FILE* archivoSalida;
    char encabezado[MAX_LONGITUD];
    int ancho, alto, max_valor;
    int** matriz;
    int** resultado;

    // Abrir el archivo PGM
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Verificar el encabezado del archivo PGM
    fscanf(archivo, "%s", encabezado);
    if (strcmp(encabezado, "P2") != 0) {
        printf("El archivo no es un archivo .PGM valido.\n");
        fclose(archivo);
        return;
    }

    // Leer las dimensiones de la imagen
    fscanf(archivo, "%d %d", &ancho, &alto);

    // Leer el valor maximo de los pixeles
    fscanf(archivo, "%d", &max_valor);

    // Crear la matriz para almacenar los datos de la imagen
    matriz = (int**)malloc(alto * sizeof(int*));
    for (int i = 0; i < alto; i++) {
        matriz[i] = (int*)malloc(ancho * sizeof(int));
    }

    // Leer los datos de los pixeles y guardarlos en la matriz
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fscanf(archivo, "%d", &matriz[i][j]);
        }
    }

    fclose(archivo);

    // Definir la máscara
    int filtro[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};

    // Aplicar el filtro de detectar bordes
    resultado = (int**)malloc(alto * sizeof(int*));
    for (int i = 0; i < alto; i++) {
        resultado[i] = (int*)malloc(ancho * sizeof(int));
        for (int j = 0; j < ancho; j++) {
            if (i == 0 || j == 0 || i == alto - 1 || j == ancho - 1) {
                resultado[i][j] = 0;
            } else {
                int suma = 0;
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        suma += matriz[i + k][j + l] * filtro[k + 1][l + 1];
                    }
                }

                resultado[i][j] = abs(suma);
                if (resultado[i][j] > max_valor) {
                    resultado[i][j] = max_valor;
                }
            }
        }
    }

    // Crear y escribir el archivo PGM de salida
    archivoSalida = fopen("detectar_bordes.pgm", "w");
    if (archivoSalida == NULL) {
        printf("No se pudo crear el archivo de salida.\n");
        return;
    }

    // Escribir el encabezado y las dimensiones en el archivo de salida
    fprintf(archivoSalida, "P2\n");
    fprintf(archivoSalida, "%d %d\n", ancho, alto);
    fprintf(archivoSalida, "%d\n", max_valor);

    // Escribir los datos de los pixeles en el archivo de salida
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fprintf(archivoSalida, "%d ", resultado[i][j]);
        }
        fprintf(archivoSalida, "\n");
    }

    fclose(archivoSalida);
    printf("\nSe ha aplicado el filtro de detectar bordes a la imagen\n\n");

    // Liberar la memoria asignada para las matrices
    for (int i = 0; i < alto; i++) {
        free(matriz[i]);
        free(resultado[i]);
    }
    free(matriz);
    free(resultado);

    return;
}

