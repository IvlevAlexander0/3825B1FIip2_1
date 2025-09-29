//Libraries
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>


void main() {


	//Input
	//CS = Collum start  RS = Row start CE = Collum end RE = Row end
	int CS = -1;
	printf("Input STARTING position COLLUM.( A = 1 , B = 2 etc. )\n");
	scanf("%d", &CS);

	int RS = -1;
	printf("Input STARTING position ROW.\n");
	scanf("%d", &RS);

	int CE = -1;
	printf("Input ENDING position COLLUM.( A = 1 , B = 2 etc. )\n");
	scanf("%d", &CE);

	int RE = -1;
	printf("Input ENDING position ROW.\n");
	scanf("%d", &RE);

	int Piece = -1;
	printf("Input PIECE. ( Rook - 1 , Bishop - 2 , Queen - 3 , Knight - 4 , King - 5 )\n");
	scanf("%d", &Piece);


	// CD = Collum difference RD = Row difference
	int CD = abs(CE - CS);
	int RD = abs(RE - RS);


	//Enum for chess pieces for the sake of readability
	enum PIECE {
		Rook = 1,
		Bishop = 2,
		Queen = 3,
		Knight = 4,
		King = 5
	};
	
	//Input check
	if ( CS < 1 || CS > 8 || RS < 1 || RS > 8 || CE < 1 || CE > 8 || RE < 1 || RE > 8 || Piece < 1 || Piece > 5 ) {
		printf("Incorrect input, please reastart and try again.\n");
	}

	//Starting and ending positions are the same
	else if (CD == 0 && RD == 0) {
		printf("Starting and endinng positions match No piece can be in that position in one move.\n");
	}


	//Ifs and output
	else if ((CD == 2 && RD == 1) || (CD == 1 && RD == 2)) {

		if (Piece == Knight) {
			printf("Chosen piece can move to that space.\n");
		}

		else {
			printf("Knight can move to that space.\n");
		}
	}


	else if (CD == 0 || RD == 0 || CD == RD) {

		if (Piece == Queen) {
			printf("Chosen piece can move to that space.\n");
		}

		else {
			printf("Queen can move to that space.\n");
		}

		if (CD <= 1 && RD <= 1) {

			if (Piece == King) {
				printf("Chosen piece can move to that space.\n");
			}

			else {
				printf("King can move to that space.\n");
			}
		}

		if (CD == 0 || RD == 0) {

			if (Piece == Rook) {
				printf("Chosen piece can move to that space.\n");
			}

			else {
				printf("Rook can move to that space.\n");
			}
		}

		else if (CD == RD) {

			if (Piece == Bishop) {
				printf("Chosen piece can move to that space.\n");
			}

			else {
				printf("Bishop can move to that space.\n");
			}
		}
	}
	else {
		printf("No piece can reach that position in one move.\n");
	}
}