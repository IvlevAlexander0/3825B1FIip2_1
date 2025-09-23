/*
Дана шахматная доска. Для двух различных клеток К1, К2 доски и выбранной пользователем
фигуры (король, ферзь, ладья, слон, конь) определить:
1) Может ли фигура за один ход перейти из К1 в К2?
2) Если нет, могут ли это сделать какие-то из остальных фигур? Если могут, вывести их список.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

void main() {
	int x1, y1, x2, y2, piece;


	printf("Enter the coordinates of the K1\n");		//Ввод и проверка координат первой клетки
	scanf("%d%d", &x1, &y1);
	if ((x1 < 1) || (x1 > 8) || (y1 < 1) || (y1 > 8)) {
		printf("Incorrect input\n");
		return(-1);
	}
	printf("Enter the coordinates of the K2\n");		//Ввод и проверка координат второй клетки
	scanf("%d%d", &x2, &y2);
	if ((x2 < 1) || (x2 > 8) || (y2 < 1) || (y2 > 8)) {
		printf("Incorrect input\n");
		return(-1);
	}
	if ((x1 == x2) && (y1 == y2)) {			//Проверка клеток на совпадение
		printf("K1 and K2 match");
		return(-1);
	}
	printf("Enter the chess piece's number:\n1) King\n2) Queen\n3) Rook\n4) Bishop\n5) Knight\n");	//Ввод номера фигуры
	scanf("%d", &piece);

	int dx = fabs(x2 - x1);	//Перемещение по x
	int dy = fabs(y2 - y1);	//Перемещение по y
	int i = 0;	//Перменная для работы цикла
	int firstPiece = piece;	//Переменная на случай, если выбранная фигура не может сделать ход
	int possibleMoves = 0;	//Переменная на случай, если ни одна из фигур не может сделать ход

	do {
		switch (piece) {
		case 1:									//Проверка хода для короля
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
		case 2:												//Проверка хода для королевы
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
		case 3:									//Проверка хода для ладьи
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
		case 4:					//Проверка хода для слона
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
		case 5:									//Проверка хода для коня
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
			printf("Incorrect input\n");	//Сообщение при некорректном вводе номера фигуры
			i = 6;
			break;
		}

		i++;
		if (i == firstPiece) {  //Пропуск фигуры, проверенной в первой итерации цикла
			i++;
		}
		piece = i;
	} while (i < 6);
	if ((possibleMoves == 0) && (i != 7)) {	//Условие (i != 7) не позволит вывести лишний текст, если номер фигуры был введён некорректно или если первая фигура может сделать ход
		printf("No one\n");	//Выводится в случае, если ни одна из фигур не может сделать ход
	}
}