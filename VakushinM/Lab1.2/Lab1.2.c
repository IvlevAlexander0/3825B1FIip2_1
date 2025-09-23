/*
���� ��������� �����. ��� ���� ��������� ������ �1, �2 ����� � ��������� �������������
������ (������, �����, �����, ����, ����) ����������:
1) ����� �� ������ �� ���� ��� ������� �� �1 � �2?
2) ���� ���, ����� �� ��� ������� �����-�� �� ��������� �����? ���� �����, ������� �� ������.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

void main() {
	int x1, y1, x2, y2, piece;


	printf("Enter the coordinates of the K1\n");		//���� � �������� ��������� ������ ������
	scanf("%d%d", &x1, &y1);
	if ((x1 < 1) || (x1 > 8) || (y1 < 1) || (y1 > 8)) {
		printf("Incorrect input\n");
		return(-1);
	}
	printf("Enter the coordinates of the K2\n");		//���� � �������� ��������� ������ ������
	scanf("%d%d", &x2, &y2);
	if ((x2 < 1) || (x2 > 8) || (y2 < 1) || (y2 > 8)) {
		printf("Incorrect input\n");
		return(-1);
	}
	if ((x1 == x2) && (y1 == y2)) {			//�������� ������ �� ����������
		printf("K1 and K2 match");
		return(-1);
	}
	printf("Enter the chess piece's number:\n1) King\n2) Queen\n3) Rook\n4) Bishop\n5) Knight\n");	//���� ������ ������
	scanf("%d", &piece);

	int dx = fabs(x2 - x1);	//����������� �� x
	int dy = fabs(y2 - y1);	//����������� �� y
	int i = 0;	//��������� ��� ������ �����
	int firstPiece = piece;	//���������� �� ������, ���� ��������� ������ �� ����� ������� ���
	int possibleMoves = 0;	//���������� �� ������, ���� �� ���� �� ����� �� ����� ������� ���

	do {
		switch (piece) {
		case 1:									//�������� ���� ��� ������
			if ((dx <= 1) && (dy <= 1)) {
				if (i == 0) {
					printf("Move is possible\n");
					i = 6;
				}
				else {
					printf("King\n");
					possibleMoves++;
				}
			}
			else if (i == 0) {
				printf("Move is impossible for King\nMove is possible for:\n");
			}
			break;
		case 2:												//�������� ���� ��� ��������
			if (((x1 == x2) || (y1 == y2)) || (dx == dy)) {
				if (i == 0) {
					printf("Move is possible\n");
					i = 6;
				}
				else {
					printf("Queen\n");
					possibleMoves++;
				}
			}
			else if (i == 0) {
				printf("Move is impossible for Queen\nMove is possible for:\n");
			}
			break;
		case 3:									//�������� ���� ��� �����
			if ((x1 == x2) || (y1 == y2)) {
				if (i == 0) {
					printf("Move is possible\n");
					i = 6;
				}
				else {
					printf("Rook\n");
					possibleMoves++;
				}
			}
			else if (i == 0) {
				printf("Move is impossible for Rook\nMove is possible for:\n");
			}
			break;
		case 4:					//�������� ���� ��� �����
			if (dx == dy) {
				if (i == 0) {
					printf("Move is possible\n");
					i = 6;
				}
				else {
					printf("Bishop\n");
					possibleMoves++;
				}
			}
			else if (i == 0) {
				printf("Move is impossible for Bishop\nMove is possible for:\n");
			}
			break;
		case 5:									//�������� ���� ��� ����
			if (((dx == 2) && (dy == 1)) || ((dx == 1) && (dy == 2))) {
				if (i == 0) {
					printf("Move is possible\n");
					i = 6;
				}
				else {
					printf("Knight\n");
					possibleMoves++;
				}
			}
			else if (i == 0) {
				printf("Move is impossible for Knight\nMove is possible for:\n");
			}
			break;
		default:
			printf("Incorrect input\n");	//��������� ��� ������������ ����� ������ ������
			i = 6;
			break;
		}

		i++;
		if (i == firstPiece) {  //������� ������, ����������� � ������ �������� �����
			i++;
		}
		piece = i;
	} while (i < 6);
	if ((possibleMoves == 0) && (i != 7)) {	//������� (i != 7) �� �������� ������� ������ �����, ���� ����� ������ ��� ����� ����������� ��� ���� ������ ������ ����� ������� ���
		printf("No one\n");	//��������� � ������, ���� �� ���� �� ����� �� ����� ������� ���
	}
}