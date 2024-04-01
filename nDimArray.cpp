#include <stdio.h>

#pragma warning(disable: 4326 4996 6031)

#define N		7
#define	Size	10000000							// 10�� N��

void main()
{
	int  DefineArray(int arDesc[]);
	void InitArray(int A[], int arDesc[]);
	int  ReadIndex(int arDesc[]);
	void PrintIndex(int arDesc[]);
	int  Aij(int A[], int arDesc[], int &nValue, int &nErrNdx);

	static int Arr[Size];
	int arDesc[2 * N + 1];									// �迭 ������
	printf("-1�� �Է��ϸ� �ߴ��ϰ� ���� �ܰ�� �Ѿ��.\n\n");
	int nDim, nVal, nErrNdx;
	while (1) {
		if ((nDim = DefineArray(arDesc)) <= 0)				// �迭�� ������ �а� �迭�� ����
			break;
		InitArray(Arr, arDesc);								// ���ǵ� ������� �ʱ�ȭ
		while (1) {
			if (ReadIndex(arDesc) == false)					// �迭�� ���ε��� �Է�
				break;
			PrintIndex(arDesc);
			if (Aij(Arr, arDesc, nVal, nErrNdx))			// ���ο� �����ϴ� �迭�� ��
				printf(" = %d", nVal);						// �ش� ������ �迭 ��
			else
				printf(" : %d��° ���ο���", nErrNdx);
			printf("\n\n");
		}
		putchar('\n');
	}
	printf("Bye, ....\n\n");
}

void InitArray(int A[], int arDesc[])
{	// ���ǵ� �迭�� ���� ���� ���ο� ���߾� �ʱ�ȭ �Ѵ�.
	int nCtr = 1;
	int nDim = arDesc[0];								// �迭�� ����
	int *arNdx = arDesc + 1;							// �� ������ ���ε�
	int *arBound = arDesc + nDim + 1;					// �� ������ ũ���
	for (int i = 0; i < nDim; i++)
		nCtr *= arBound[i];								// �迭�� ũ�⸦ ���
	for (int i = 0; i < nCtr; i++) {
		int nBase = 1, nSize = 1, nValue = 0;
		for (int j = nDim - 1; j >= 0; j--) {
			arNdx[j] = (i / nSize) % arBound[j];		// �� ������ ����
			nValue += arNdx[j] * nBase;					// �� ���ο� �����ϴ� ��
			nSize *= arBound[j];
			nBase *= 10;
		}
		A[i] = nValue;									// �迭�� �ʱ�ȭ
	}
}

int DefineArray(int arDesc[])
{	// �迭�� ������ �� ������ ũ�⵵ �Է¹޾� �迭�� ������ ��ȯ�Ѵ�(����: -1)
	printf("�迭�� ���Ӱ� �����մϴ�.\n");
	printf("�迭�� ����(-1, 1 ~ 7) ? ");
	int nDim;
	scanf("%d", &nDim);
	if (nDim < 0 || nDim > 7)
		return false;
	arDesc[0] = nDim;
	printf("\n%d���� �迭�� ũ�⸦ �Է��մϴ�.\n", nDim);
	int *arBound = arDesc + nDim + 1;					// �� ������ ũ���
	for (int i = 0; i < nDim; i++) {
		int OK;
		do {
			printf("int A");
			for (int j = 0; j < i; j++)
				printf("[%d]", arBound[j]);
			printf("[?]");
			for (int j = i + 1; j < nDim; j++)
				printf("[ ]");
			printf(" (-1, 2 ~ 10) ? ");
			scanf("%d", arBound + i);					// �� ������ ũ�� �Է�
			OK = arBound[i] >= 2 && arBound[i] <= 10;	// ������ ũ�� üũ
		} while (OK == false);
	}
	printf("\n\t���ǵ� �迭: int A");
	for (int i = 0; i < nDim; i++)						// ���ǵ� �迭�� ���
		printf("[%d]", arBound[i]);
	printf(";\n\t�˻��� �迭�� ������ �Է��մϴ�.\n\n");
	return nDim;
}

int ReadIndex(int arDesc[])
{	// �迭 �����ڿ� ���� �� ������ �Է��Ͽ� T/F�� ��ȯ�Ѵ�.
	int nDim = arDesc[0];								// �迭�� ����
	int *arNdx = arDesc + 1;							// �� ������ ���ε�
	int *arBound = arDesc + nDim + 1;					// �� ������ ũ���
	for (int i = 0; i < nDim; i++) {					// �� ������ ������ �Է�
		printf("\tA");
		for (int j = 0; j < i; j++)
			printf("[%d]", arNdx[j]);
		printf("[?]");
		for (int j = i + 1; j < nDim; j++)
			printf("[ ]");
		printf(" (-1, 0 ~ %d) ? ", arBound[i] - 1);		// ������ ����
		scanf("%d", arNdx + i);							// ���� �Է�
		if (arNdx[i] < 0)								// ������ �����̸�
			return false;								// �ߴ�
	}
	return  true;
}

void PrintIndex(int arDesc[])
{
	int nDim = arDesc[0];								// �迭�� ����
	int *arNdx = arDesc + 1;							// �� ������ ���ε�
	printf("\tA");
	for (int i = 0; i < nDim; i++)						// �迭�� �� ������ ���
		printf("[%d]", arNdx[i]);
}

int Aij(int A[], int arDesc[], int &nValue, int &nErrNdx)
{	// �迭 �����ڿ� �ִ� ���ο� �ش��ϴ� ���Ҹ� nValue�� �����ϰ� T/F�� ��ȯ�Ѵ�.
	// ���ο� ������ ������ nErrNdx�� ���� ��ȣ�� �ִ´�.
	// ������� [1][2][30][4]���� 30�� �����̸� ���ʿ��� 0���� ���� 2�̹Ƿ� ErrNdx = 2�� �ȴ�.
	// arDesc�� ���� ArrIndex4���� ��� �Ű����� nDim, nNdx, nBound�� ������� ���� ���̴�.
	// arDesc[0]: �迭�� ����(n)[nDim]
	// arDesc[1]  ~  arDesc[n]:  �迭 �� ������ ����[nNdx]
	// arDesc[n+1] ~ arDesc[2n]: �迭 �� ������ ũ��[nBound]
	return true;
}