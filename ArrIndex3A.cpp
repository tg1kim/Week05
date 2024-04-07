#include <stdio.h>

#define	N1	9
#define	N2	8
#define	N3	7
#define	N4	6
#define DIM	4
#pragma warning (disable: 4326 4996 6031)

void main()
{
	int B[N1][N2][N3][N4];
	int arNdx[DIM], arSize[DIM] = {N1, N2, N3, N4};

	for (int i = 0; i < arSize[0]; i++)
		for (int j = 0; j < arSize[1]; j++)
			for (int k = 0; k < arSize[2]; k++)
				for (int l = 0; l < arSize[3]; l++)
					B[i][j][k][l] = i * 1000 + j * 100 + k * 10 + l;
	int IsOK = true;
	while (IsOK) {
		int nValue;
		printf("index> ");
		for (int i = 0; i < DIM && IsOK; i++) {
			scanf("%d", arNdx + i);
			if (i == 0 && arNdx[i] < 0)
				IsOK = false;
		}
		if (IsOK) {
			int Aij(int A[], int nDim, int arNdx[], int arSize[], int &nValue);
			if (Aij((int *)B, DIM, arNdx, arSize, nValue))
				printf("A[%d][%d][%d][%d] = %d(%d)\n",
					arNdx[0], arNdx[1], arNdx[2], arNdx[3], 
					B[arNdx[0]][arNdx[1]][arNdx[2]][arNdx[3]], nValue);
			else
				printf("���� ����, ....\n");
			putchar('\n');
		}
	}
	printf("Bye, ....\n\n");
}

int Aij(int A[], int nDim, int arNdx[], int arSize[], int &nValue)
{	// ������ �����̸� nValue�� ���� �����ϰ� T/F�� ��ȯ�Ѵ�.
	// �˴ٽ��� ������ ���� ���� �޶����� ������, ��� for loop�� ����Ͽ� ���� ����϶�.
	// 						;; nSize = arSize[0] * arSize[1] * arSize[2] * arSize[3]
	// arNdx[0] * nSize +	;; nSize = arSize[1] * arSize[2] * arSize[3]
	// arNdx[1] * nSize +	;; nSize = arSize[2] * arSize[3]
	// arNdx[2] * nSize +	;; nSize = arSize[3]
	// arNdx[3] * nSize		;; nSize = 1
	int nSize = 1;
	for (int i = 0; i < nDim; i++)	// �迭�� ��ü ũ�⸦ ���
		nSize *= arSize[i];
	int nNdx = 0;
	for (int i = 0; i < nDim; i++) {
		if (arNdx[i] < 0 || arNdx[i] >= arSize[i])
			return false;
		nSize /= arSize[i];			// ũ�⸦ �� ������ ���δ�
		nNdx += arNdx[i] * nSize;
	}
	nValue = A[nNdx];
	return true;
}