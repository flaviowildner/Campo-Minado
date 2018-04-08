#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char convert(int n) {
	if (n >= 0 && n <= 9)
		return n + 48;
	else if (n == -1)
		return 'X';
	else
		return 0;
}

void imprimirMatriz(char **matrizView, int &nX, int &nY) {
	int i, j;
	system("clear");
	for (i = 0; i < nX; i++) {
		for (j = 0; j < nY; j++) {
			printf("|%c", matrizView[i][j]);
		}
		printf("|\n");
		for (j = 0; j < nY; j++) {
			printf(" -");
		}
		printf("\n");
	}
}

int verificarVitoria(char **matrizView, int &nX, int &nY, int nBombas) {
	int i, j;
	int count = 0;
	for (i = 0; i < nX; i++) {
		for (j = 0; j < nY; j++) {
			if (matrizView[i][j] == 32)
				count++;
		}
	}
	if (count == nBombas)
		return 1;
	else
		return 0;
}

void gerarMatriz(int **matrizPrincipal, char **matrizView, int &nX, int &nY, int &nBombas) {
	int posX, posY, i, j;
	int iAux, jAux;


	for (i = 0; i < nX; i++)
		for (j = 0; j < nY; j++)
			matrizPrincipal[i][j] = 0;

	for (i = 0; i < nX; i++)
		for (j = 0; j < nY; j++)
			matrizView[i][j] = 32;

	for (i = 0; i < nX; i++) {
		for (j = 0; j < nY; j++) {
			printf("%d ", matrizPrincipal[i][j]);
		}
		printf("\n");
	}


	for (i = 0; i < nBombas; i++) {
		posX = rand() % nX;
		posY = rand() % nY;
		if (matrizPrincipal[posX][posY] == -1)
			i--;
		else
			matrizPrincipal[posX][posY] = -1;
	}

	for (i = 0; i < nX; i++) {
		for (j = 0; j < nY; j++) {
			if (matrizPrincipal[i][j] != -1) {
				for (iAux = -1; iAux < 2; iAux++) {
					for (jAux = -1; jAux < 2; jAux++) {
						if (i + iAux >= 0 && i + iAux < nX && j + jAux >= 0 && j + jAux < nY && (matrizPrincipal[i + iAux][j + jAux] == -1)) {
							matrizPrincipal[i][j]++;
						}
					}
				}
			}
		}
	}
}


int main()
{
	int **matrizPrincipal = NULL;
	char **matrizView = NULL;
	int nBombas = 0;
	int posX, posY;
	int nX, nY;
	int run = 1;
	int runGame;
	int i, j;

	srand((unsigned)time(NULL));


		
	//RUN

	while (run == 1) {
		system("clear");
		printf("Digite o tamanho do campo em formato 'X Y': ");
		scanf("%d %d", &nX, &nY);

		do {
			system("clear");
			printf("Digite o numero de bombas: ");
			scanf("%d", &nBombas);
		} while (nBombas < 0 || nBombas > nX * nY);

		matrizPrincipal = (int **)malloc(nX * sizeof(int*));
		for (i = 0; i < nX; i++) {
			matrizPrincipal[i] = (int *)malloc(nY * sizeof(int));
		}
		matrizView = (char **)malloc(nX * sizeof(char*));
		for (i = 0; i < nX; i++) {
			matrizView[i] = (char *)malloc(nY * sizeof(char));
		}
		gerarMatriz(matrizPrincipal, matrizView, nX, nY, nBombas);
		runGame = 1;
		while (runGame == 1) {
			imprimirMatriz(matrizView, nX, nY);
			printf("Digite uma posicao: ");
			scanf("%d %d", &posX, &posY);

			if (posX >= 1 && posX <= nX && posY >= 1 && posY <= nY) {
				if (matrizPrincipal[posX - 1][posY - 1] == -1) {
					for (i = 0; i < nX; i++) {
						for (j = 0; j < nY; j++) {
							matrizView[i][j] = convert(matrizPrincipal[i][j]);
						}
					}
					imprimirMatriz(matrizView, nX, nY);
					printf("Voce Perdeu!\nJogar novamente?\n1-Sim\n2-Nao\n");
					scanf("%d", &run);
					runGame = 2;
				}
				else {
					matrizView[posX - 1][posY - 1] = convert(matrizPrincipal[posX - 1][posY - 1]);
					printf("\n");
					imprimirMatriz(matrizView, nX, nY);
					if (verificarVitoria(matrizView, nX, nY, nBombas) == 1) {
						printf("Voce ganhou!\nJogar novamente?\n1-Sim\n2-Nao\n");
						scanf("%d", &run);
						runGame = 2;
					}
				}
			}

		}
	}


    return 0;
}

