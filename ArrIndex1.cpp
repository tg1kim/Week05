#include <stdio.h>

#define	SIZE	10
#pragma warning (disable: 4326 4996)

void main()
{
	int B[SIZE][SIZE][SIZE][SIZE];

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			for (int k = 0; k < SIZE; k++)
				for (int l = 0; l < SIZE; l++)
					B[i][j][k][l] = i * 1000 + j * 100 + k * 10 + l;
	while (1) {
		int i, j, k, l, nValue;
		printf("index> ");
		scanf("%d", &i);
		if (i < 0)
			break;
		scanf("%d", &j);
		scanf("%d", &k);
		scanf("%d", &l);
		int Aij(int A[], int i, int j, int k, int l, int n, int &nValue);
		if (Aij((int *)B, i, j, k, l, SIZE, nValue))
			printf("A[%d][%d][%d][%d] = %d(%d)\n", i, j, k, l, B[i][j][k][l], nValue);
		else
			printf("���� ����, ....\n");
		putchar('\n');
	}
	printf("Bye, ....\n\n");
}

int Aij(int A[], int i, int j, int k, int l, int n, int &nValue)
{	// ������ �����̸� nValue�� ���� �����ϰ� T/F�� ��ȯ�Ѵ�.
	return true;
}