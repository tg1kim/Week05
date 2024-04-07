#include <stdio.h>

#define	N1	9
#define	N2	8
#define	N3	7
#define	N4	8
#define DIM	4
#pragma warning (disable: 4326 4996 6031)

void main()
{
	int B[N1][N2][N3][N4];
	int nArrDesc[2 * DIM + 1] = {DIM, 0, 0, 0, 0, N1, N2, N3, N4};
	int nDim = DIM;
	int *arNdx = nArrDesc + 1;
	int * arSize = nArrDesc + 1 + DIM;
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
			int Aij(int A[], int nArrDesc[], int &nValue);
			if (Aij((int *)B, nArrDesc, nValue))
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

int Aij(int A[], int nArrDesc[], int &nValue)
{	// ������ �����̸� nValue�� ���ο� ���� �迭�� ���� �����ϰ� T/F�� ��ȯ�Ѵ�.
	// �˴ٽ��� ������ ���� ���� �޶����� ������, ��� for loop�� ����Ͽ� ���� ����϶�.
	// �Ʒ��� ���� ������ ������ �Ųٷ� ����� �Ѵ�.
	// nNdx[3] * nSize +		;; nSize = 1;
	// nNdx[2] * nSize +		;; nSize = nBound[3]
	// nNdx[1] * nSize +		;; nSize = nBound[2] * nBound[3]
	// nNdx[0] * nSize			;; nSize = nBound[1] * nBound[2] * nBound[3]
	int nNdx = 0;
	int nDim = nArrDesc[0];
	int *arNdx = nArrDesc + 1;
	int * arSize = nArrDesc + 1 + nDim;
	for (int i = nDim - 1, nSize = 1; i >= 0; i--) {
		if (arNdx[i] < 0 || arNdx[i] >= arSize[i])
			return false;
		nNdx += arNdx[i] * nSize;
		nSize *= arSize[i];
	}
	nValue = A[nNdx];
	return true;
}