#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _Point {
	int xPos;
	int yPos;
} Ptr;

typedef struct _Rectangle {
	Ptr* p1;
	Ptr* p2;
} Rec;

Ptr* ptrInit(int, int);
Rec* recInit(Ptr*, Ptr*);
int recArea(Rec*);
int bigXPos(Rec*);
int smallXPos(Rec*);
int bigYPos(Rec*);
int smallYPos(Rec*);
int Test(Rec*, Rec*);





int main() {
	int pos[8];
	int i, j;
	Ptr* ptr[4];
	Rec* rec[2];

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 2; j++)
			scanf("%d", &pos[j]);
		j = 1;
		ptr[i] = ptrInit(pos[j - 1], pos[j]);
	}

	for (i = 0; i < 2; i++)
		rec[i] = recInit(ptr[i * 2], ptr[(i * 2) + 1]);
	printf("%d\n", testResult(rec[0], rec[1]));

	return 0;
}





Ptr* ptrInit(int x1, int y1) {				// �� ����
	Ptr* p1 = (Ptr*)malloc(sizeof(Ptr));
	p1->xPos = x1;
	p1->yPos = y1;
	return p1;
}

Rec* recInit(Ptr* p1, Ptr* p2) {			// �簢�� ����
	if (p1->xPos == p2->xPos || p1->yPos == p2->yPos)
		return NULL;
	else {
		Rec* r1 = (Rec*)malloc(sizeof(Rec));
		r1->p1 = p1;
		r1->p2 = p2;
		return r1;
	}
}

int recArea(Rec* r1) {						// �簢�� ���� ��ȯ
	int x = bigXPos(r1) - smallXPos(r1);
	int y = bigYPos(r1) - smallYPos(r1);
	return x*y;
}

int bigXPos(Rec* r) {						// �� �� �� ū �� x��ǥ ��ȯ
	if (r->p1->xPos > r->p2->xPos)
		return r->p1->xPos;
	else
		return r->p2->xPos;
}

int smallXPos(Rec* r) {						// �� �� �� ���� �� x��ǥ ��ȯ
	if (r->p1->xPos < r->p2->xPos)
		return r->p1->xPos;
	else
		return r->p2->xPos;
}

int bigYPos(Rec* r) {						// �� �� �� ū �� y��ǥ ��ȯ
	if (r->p1->yPos > r->p2->yPos)
		return r->p1->yPos;
	else
		return r->p2->yPos;
}

int smallYPos(Rec* r) {						// �� �� �� ���� �� y��ǥ ��ȯ
	if (r->p1->yPos < r->p2->yPos)
		return r->p1->yPos;
	else
		return r->p2->yPos;
}

int testResult(Rec* r1, Rec* r2) {
	if (r1 == NULL || r2 == NULL)		// �簢���� �ƴ� ������ ��� ���� 0 ��ȯ
		return 0;
	int finX;
	int finY;
	int inGap[4];
	int testX1 = bigXPos(r1) - smallXPos(r2);
	int testX2 = bigXPos(r2) - smallXPos(r1);
	int testY1 = bigYPos(r1) - smallYPos(r2);
	int testY2 = bigYPos(r2) - smallYPos(r1);

	inGap[0] = bigXPos(r1) - bigXPos(r2);
	inGap[1] = bigYPos(r1) - bigYPos(r2);
	inGap[2] = smallXPos(r1) - smallXPos(r2);
	inGap[3] = smallYPos(r1) - smallYPos(r2);

	if ((inGap[0] >= 0 && inGap[2] <= 0 && inGap[1] <= 0 && inGap[3] >= 0) ||
		(inGap[0] <= 0 && inGap[2] >= 0 && inGap[1] >= 0 && inGap[3] <= 0)) {		// ���ڰ� ��� �Ǵ� T���
		int lengthX1 = bigXPos(r1) - smallXPos(r1);
		int lengthX2 = bigXPos(r2) - smallXPos(r2);
		int lengthX = lengthX1 < lengthX2 ? lengthX1 : lengthX2;

		int lengthY1 = bigYPos(r1) - smallYPos(r1);
		int lengthY2 = bigYPos(r2) - smallYPos(r2);
		int lengthY = lengthY1 < lengthY2 ? lengthY1 : lengthY2;

		return lengthX * lengthY;

	}

	if (testX1 > 0 && testX2 > 0 && testY1 > 0 && testY2 > 0) {		// ��ġ�ų� ���ο� �����ϴ� ���
		finX = testX1 <= testX2 ? testX1 : testX2;
		finY = testY1 <= testY2 ? testY1 : testY2;
		int area = finX * finY;

		if (inGap[0] * inGap[1] * inGap[2] * inGap[3] < 0) {
			for (int i = 0; i < 4; i++) {							//  �簢���� �� �����̸� ������ �����ִ� ���
				int sum = 0;
				int count = 0;
				for (int j = 0; j < 4; j++) {
					sum = inGap[i] * inGap[j];
					if (sum < 0)
						count++;
					if (count == 3) {
						if (i % 2 == 1) {
							int lengthY1 = bigYPos(r1) - smallYPos(r1);
							int lengthY2 = bigYPos(r2) - smallYPos(r2);
							int lengthY = lengthY1 < lengthY2 ? lengthY1 : lengthY2;

							return finX * lengthY;
						}
						else {
							int lengthX1 = bigXPos(r1) - smallXPos(r1);
							int lengthX2 = bigXPos(r2) - smallXPos(r2);
							int lengthX = lengthX1 < lengthX2 ? lengthX1 : lengthX2;

							return finY * lengthX;
						}
					}
				}
			}
		}
		if ((area >= recArea(r1) || area >= recArea(r2))) 	//	���ο� �����ϴ� ���
			return recArea(r1) < recArea(r2) ? recArea(r1) : recArea(r2);
		return area;										// �̿��� ��� ���
	}
	else
		return 0;											// �簢�� �� ���� ��ġ�� �ʴ� ���
}