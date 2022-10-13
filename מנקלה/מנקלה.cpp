/*    0   1  2  3  4  5  6  7   :index
	  _______________________
 left|##| 6| 5| 4| 3| 2| 1|  |
	 |  |                 |  |
	 |__|_1|_2|_3|_4|_5|_6|##|right
*/
#include<iostream>
using namespace std;

int tests(bool,int,int**);
int distribution(int**,int);
void reset(int** chadash, int** yashan)
{
	for(int x=1; x<7; x++)
		for(int y=0; y<2; y++)
			chadash[x][y] = yashan[x][y];
	chadash[0][0] = yashan[0][0];
	chadash[7][0] = yashan[7][0];
	chadash[0][1] = yashan[0][1];
	chadash[7][1] = yashan[7][1];
}

int status(bool maslul, int big, int** board, int xy)
{
	if (xy == 71)//the stock
		return tests(maslul,big,board);
	else if(board[xy/10][xy%10] == 1)//it was empty
		return board[7][1];
	else if(board[xy/10][xy%10] > 1)
		return status(maslul, big, board, distribution(board, xy));
	else
	{
		cout<<"error!\n\n";
		return -1;
	}
}

int tests(bool maslul, int big, int** board)
{
	int** copy = new int*[8];
	for(int y=0; y<8; y++)
		copy[y] = new int[2];
	reset(copy, board);

	int xy, biggest=0, now=0;

	for (int x=1; x<7; x++)
	{
		reset(board, copy);

		if(board[x][1] > 0)
			now = status(maslul, big, board, distribution(board, x*10 + 1));
		if(now==big && maslul)
		{
			cout<<x;
			return big;
		}
		if(now > biggest)
			biggest = now;
	}

	for(int y=0; y<8; y++)
		delete[] copy[y];
	delete[] copy;

	return biggest;
}

int distribution(int** board, int index)//חלוקת תא אחד
{
	//.'מחזיר מיקום של הסיום - ספרת העשרות היא איקס, והיחידות היא וואי. כנ"ל 'אינדקס
	int i = board[index/10][index%10];
	board[index/10][index%10] = 0;
	for (; i>0; i--)
	{
		if(index%10 == 0)//top row
		{
			if(index/10 == 1)
			{
				index = 11;
				board[1][1]++;
			}
			else
			{
				index -= 10;
				board[index/10][0]++;
			}
		}
		else if(index%10 == 1)//bottom Line
		{
			if(index/10 == 7)
			{
				index = 60;
				board[6][0]++;
			}
			else
			{
				index += 10;
				board[index/10][1]++;
			}
		}
	}
	return index;
}

void main()
{
	int** board = new int*[8], biggest=0;
	for(int y=0; y<8; y++)
		board[y] = new int[2];

	//reset
	for(int x=1; x<7; x++)
		for(int y=0; y<2; y++)
			board[x][y] = 4;
	board[0][0] = 0;
	board[7][0] = 0;
	board[0][1] = 0;
	board[7][1] = 0;

	biggest = tests(0,-2,board);
	cout<<biggest<<"\nthe track from right to left: ";

	//reset
	for(int x=1; x<7; x++)
		for(int y=0; y<2; y++)
			board[x][y] = 4;
	board[0][0] = 0;
	board[7][0] = 0;
	board[0][1] = 0;
	board[7][1] = 0;
	tests(true,biggest,board);
	cout<<endl;

	system("pause");
	for(int y=0; y<8; y++)
		delete[] board[y];
	delete[] board;
}