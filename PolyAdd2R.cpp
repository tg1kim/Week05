#include <stdio.h>

#define MAX_TERM 100
#pragma warning(disable: 4326 4996 6031)

typedef int Polynomial[2 * (MAX_TERM + 1)];	// Polynomial: 다항식을 정의한다

void main()
{
	Polynomial polyA = { 6, 3, -1, 2, -2, 1, 0, -1, };				// 끝 표시, (계수, 지수)
	Polynomial polyB = { 5, 4, -1, 2, 2, 1, 8, 0, 0, -1, };
	Polynomial polyC;
	void InitPolynomial(Polynomial A);
	bool InputPolynomial(Polynomial A, const char* szMsg);
	void OutputPolynomial(Polynomial A, const char* szMsg);
	bool CheckPolynomial(Polynomial A);
	bool Attach(Polynomial aPoly, int nCoef, int nExpon);
	bool AddPolynomial(Polynomial A, Polynomial B, Polynomial C);
	bool SubPolynomial(Polynomial A, Polynomial B, Polynomial C);
	void SimpleMulPolynomial(Polynomial A, int nCoef, int nExpon, Polynomial B);
	bool MultiplyPolynomial(Polynomial A, Polynomial B, Polynomial C);
	CheckPolynomial(polyA);
	CheckPolynomial(polyB);
	int bContinue = true;
	while (bContinue) {
		int nFtn;
		printf("1: A, 2: B, 3: Add, 4: Sub, 5: Simple, 6: Mul, 7: pr ? ");
		scanf("%d", &nFtn);
		switch (nFtn) {
		case 1:
			if (InputPolynomial(polyA, "A") == 0)					// 다항식 A를 입력한다.
				printf("Input Error\n");
			break;
		case 2:
			if (InputPolynomial(polyB, "B") == 0)					// 다항식 B를 입력한다.
				printf("Input Error\n");
			break;
		case 3:
			InitPolynomial(polyC);									// C를 초기화한다.
			if (AddPolynomial(polyA, polyB, polyC))					// 더한다.
				OutputPolynomial(polyC, "C(X) = ");					// C를 출력한다.
			break;
		case 4:
			InitPolynomial(polyC);									// C를 초기화한다.
			if (SubPolynomial(polyA, polyB, polyC))					// 뺀다.
				OutputPolynomial(polyC, "C(X) = ");					// C를 출력한다.
			break;
		case 5:
			InitPolynomial(polyC);									// C를 초기화한다.
			SimpleMulPolynomial(polyA, polyB[0], polyB[1], polyC);	// 한 항을 곱한다.
			OutputPolynomial(polyC, "C(X) = ");						// C를 출력한다.
			polyC[1] = -1, polyC[2 * MAX_TERM + 1] = -2;			// C를 초기화한다.
			SimpleMulPolynomial(polyB, polyA[0], polyA[1], polyC);	// 한 항을 곱한다.
			OutputPolynomial(polyC, "C(X) = ");						// C를 출력한다.
			break;
		case 6:
			InitPolynomial(polyC);									// C를 초기화한다.
			if (MultiplyPolynomial(polyA, polyB, polyC))			// 곱한다.
				OutputPolynomial(polyC, "C(X) = ");					// C를 출력한다.
			break;
		case 7:
			OutputPolynomial(polyA, "A(X) = ");						// A를 출력한다.
			OutputPolynomial(polyB, "B(X) = ");						// B를 출력한다.
			break;
		default:
			bContinue = false;
		}
		putchar('\n');
	}
	printf("Bye, ....\n\n");
}

void InitPolynomial(Polynomial A)
{
	A[1] = -1, A[2 * MAX_TERM + 1] = -2;
}

bool Attach(Polynomial aPoly, int nCoef, int nExpon)
{	// 저장할 공간이 있는지 조사하여 한 항을 끝에 저장하고 T/F를 반환한다.
	if (aPoly[1] == -2)										// 끝, 메모리	 부족
		return false;
	if (aPoly[1] == -1) {									// 공간이 있으면
		aPoly[0] = nCoef, aPoly[1] = nExpon;				// 계수, 지수
		return (aPoly[3] != -2 && (aPoly[3] = -1), true);	// 끝을 표시
	}
	return Attach(aPoly + 2, nCoef, nExpon);
}

bool AddPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	// 두 다항식 A, B를 더하여 다항식 C에 저장하고 T/F를 반환한다.
	if (A[1] == -1 && B[1] == -1)
		return true;
	int nNdxA = 0, nNdxB = 0, nCoef, nExpon;
	if (A[1] > B[1])
		(nCoef = A[0], nExpon = A[1], nNdxA = 2);
	else if (A[1] == B[1])
		(nCoef = A[0] + B[0], nExpon = A[1], nNdxA = 2, nNdxB = 2);
	else
		(nCoef = B[0], nExpon = B[1], nNdxB = 2);
	if (nCoef && Attach(C, nCoef, nExpon) == false)
		return false;
	return AddPolynomial(A + nNdxA, B + nNdxB, C + (nCoef ? 2 : 0));
}

bool SubPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	// 다항식 A에서 다항식 B를 빼서 다항식 C에 저장하고 T/F를 반환한다.
	if (A[1] == -1 && B[1] == -1)
		return true;
	int nNdxA = 0, nNdxB = 0, nCoef, nExpon;
	if (A[1] > B[1])
		(nCoef = A[0], nExpon = A[1], nNdxA = 2);
	else if (A[1] == B[1])
		(nCoef = A[0] - B[0], nExpon = A[1], nNdxA = 2, nNdxB = 2);
	else
		(nCoef = -B[0], nExpon = B[1], nNdxB = 2);
	if (nCoef && Attach(C, nCoef, nExpon) == false)
		return false;
	return SubPolynomial(A + nNdxA, B + nNdxB, C + (nCoef ? 2 : 0));
}

void SimpleMulPolynomial(Polynomial A, int nCoef, int nExpon, Polynomial B)
{	// 다항식 A와 한 항을 곱하여 다항식 B에 저장한다.
	if (A[1] == -1)
		return;
	Attach(B, A[0] * nCoef, A[1] + nExpon);
	return SimpleMulPolynomial(A + 2, nCoef, nExpon, B + 2);
}

#define	ALGORITHM	3

bool MultiplyPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	// 두 다항식 A, B를 곱하여 다항식 C에 저장하고 T/F를 반환한다.
#if ALGORITHM == 1

	if (A[1] < 0)
		return true;
	Polynomial C1, C2;
	InitPolynomial(C1), InitPolynomial(C2);					// C1, C2를 초기화한다.
	SimpleMulPolynomial(B, A[0], A[1], C1);
	return MultiplyPolynomial(A + 2, B, C2) && AddPolynomial(C1, C2, C);

#elif ALGORITHM == 2

	if (B[1] < 0)
		return true;
	Polynomial C1, C2;
	InitPolynomial(C1), InitPolynomial(C2);					// C1, C2를 초기화한다.
	SimpleMulPolynomial(A, B[0], B[1], C1);
	return MultiplyPolynomial(A, B + 2, C2) && AddPolynomial(C1, C2, C);

#else

	Polynomial C1, C2, C3;
	InitPolynomial(C3);										// C를 초기화한다.
	int nNdxA = 0;
	while (A[nNdxA + 1] >= 0) {
		InitPolynomial(C1);									// C1을 초기화한다.
		SimpleMulPolynomial(B, A[nNdxA], A[nNdxA + 1], C1);
		InitPolynomial(C2);									// C2를 초기화한다.
		if (AddPolynomial(C, C1, C2) == false)
			return false;
		InitPolynomial(C);									// C2를 초기화한다.
		SimpleMulPolynomial(C2, 1, 0, C);					// C2를 C로 복사한다.
		nNdxA += 2;
	}
	return true;

#endif
}

bool CheckPolynomial(Polynomial aPoly)
{	// 다항식이 올바른지 체크
	int bRight = true;
	int nExpon, nPrvExpon = aPoly[1] + 1;
	for (int i = 0; i <= 2 * MAX_TERM; i += 2) {
		nExpon = aPoly[i + 1];
		if (nExpon == -1)
			return bRight;
		if (aPoly[i] == 0) {									// 계수가 0인지 체크
			fprintf(stderr, "%d 번째 항의 계수가 0 입니다.\n", i / 2 + 1);
			bRight = false;
		}
		if (nExpon < 0 || nExpon >= nPrvExpon) {				// 지수가 양수이면서 내림차순
			fprintf(stderr, "%d 번째 항의 지수가 잘못 되었습니다.\n", i / 2 + 1);
			bRight = false;
		}
		nPrvExpon = nExpon;
	}
	return false;
}

bool InputPolynomial(Polynomial aPoly, const char* szMsg)
{	// 다항식을 입력
	int nCtr;
	fprintf(stderr, "%s 다항식을 입력합니다.\n", szMsg);
	do {
		fprintf(stderr, "항의 갯수는 ? ");
		scanf("%d", &nCtr);
	} while (nCtr < 0);
	if (nCtr > MAX_TERM) {
		fprintf(stderr, "항이 너무 많습니다.\n");
		return false;
	}
	nCtr *= 2;
	int nNdx;
	for (nNdx = 0; nNdx < nCtr; nNdx += 2) {
		fprintf(stderr, "%d 번째 항의 계수는 ? ", nNdx / 2 + 1);
		scanf("%d", &aPoly[nNdx]);
		fprintf(stderr, "%d 번째 항의 지수는 ? ", nNdx / 2 + 1);
		scanf("%d", &aPoly[nNdx + 1]);
	}
	aPoly[nNdx + 1] = -1;	/* 끝을 표시한다 */
	return CheckPolynomial(aPoly);
}

void OutputPolynomial(Polynomial aPoly, const char* szMsg)
{	// 다항식을 출력
	printf(szMsg);
	if (aPoly[1] == -1)
		putchar('0');
	else {
		for (int i = 0; aPoly[i + 1] >= 0; i += 2) {
			int nCoeff = aPoly[i];					// 계수
			int nExpon = aPoly[i + 1];				// 지수
			char cSign = '+';
			if (nCoeff < 0) {						// +/- 준비
				cSign = '-';
				nCoeff = - nCoeff;
			}
			if (i || cSign == '-')					// 첫 항이 양수일 경우만 제외
				if (i == 0 && cSign == '-')			// 첫 항이 음수
					printf("-");
				else
					printf(" %c ", cSign);			// 부호 출력
			if (nCoeff != 1 || nExpon == 0)
				printf("%d", nCoeff);				// 계수 출력
			if (nExpon > 0) {
				putchar('X');
				if (nExpon > 1)
					printf("^%d", nExpon);			// 지수 출력
			}
		}
	}
	putchar('\n');
}

