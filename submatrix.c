#include <stdio.h>
#include <stdlib.h>

#define NMIN 1
#define NMAX 100
#define MMIN 1
#define MMAX 100

int main()
{
	unsigned short n, m, **s, i, j, i1, j1, i2, j2, i1max, j1max, i2max, j2max, suma, smax, dim;

	char c;

	FILE *fin = fopen("submatrix.in", "r");

	if (!fin) { printf("Eroare fisier submatrix.in\n"); return 1; }

	fscanf(fin, "%hu %hu", &n, &m);

	if (n < NMIN || n > NMAX) { printf("Eroare valoare n\n"); return 2; }

	if (m < MMIN || m > MMAX) { printf("Eroare valoare m\n"); return 3; }

	s = (unsigned short**)calloc(n+1, sizeof(unsigned short*));

	for (i = 0; i <= n; i++) s[i] = (unsigned short*)calloc(m+1, sizeof(unsigned short));

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			fscanf(fin, " %c", &c);

			s[i][j] = s[i][j-1] + s[i-1][j] - s[i-1][j-1] + (c-'0');
		}
	}
	
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= m; j++)
			printf("%hu ", s[i][j]);

		printf("\n");
	}

	fclose(fin);

	for (smax = 0, i1 = 1; i1 <= n; i1++) {
		for (j1 = 1; j1 <= m; j1++) {
			for (i2 = i1; i2 <= n; i2++) {
				for (j2 = j1; j2 <= m; j2++) {
					suma = s[i2][j2] - s[i2][j1-1] - s[i1-1][j2] + s[i1-1][j1-1];
					dim = (j2-j1+1)*(i2-i1+1);

					if (suma == dim && suma > smax) {
						smax = suma;

						i1max = i1;
						j1max = j1;
						i2max = i2;
						j2max = j2;
					}
				}
			}
		}
	}
	
	FILE *fout = fopen("submatrix.out", "w");
	
	fprintf(fout, "%hu\n%hu %hu %hu %hu", smax, i1max, j1max, i2max, j2max);

	fclose(fout);

	for (i = 0; i <= n; i++) free(s[i]);

	free(s);

	return 0;
}
// scor 100
