
/*
** B0
** #...
** #...
** #...
** #...
**
** B1
** ####
** ....
** ....
** ....
**
** B2
** ##..
** ##..
** ....
** ....
**
** B3
** .#..
** ###.
** ....
** ....
**
** B4
** #...
** ##..
** #...
** ....
**
** B5
** ###.
** .#..
** ....
** ....
**
** B6
** .#..
** ##..
** .#..
** ....
**
** B7
** #...
** ###.
** ....
** ....
**
** B8
** ##..
** #...
** #...
** ....
**
** B9
** ###.
** ..#.
** ....
** ....
**
** BA
** .#..
** .#..
** ##..
** ....
**
** BB
** ..#.
** ###.
** ....
** ....
**
** BC
** #...
** #...
** ##..
** ....
**
** BD
** ###.
** #...
** ....
** ....
**
** BE
** ##..
** .#..
** .#..
** ....
**
** BF
** .##.
** ##..
** ....
** ....
**
** BG
** #...
** ##..
** .#..
** ....
**
** BH
** ##..
** .##.
** ....
** ....
**
** BI
** .#..
** ##..
** #...
** ....
*/

#define B0 0b1000100010001000
#define B1 0b1111000000000000
#define B2 0b1100110000000000
#define B3 0b0100111000000000
#define B4 0b1000110010000000
#define B5 0b1110010000000000
#define B6 0b0100110001000000
#define B7 0b1000111000000000
#define B8 0b1100100010000000
#define B9 0b1110001000000000
#define BA 0b0100010011000000
#define BB 0b0010111000000000
#define BC 0b1000100011000000
#define BD 0b1110100000000000
#define BE 0b1100001000100000
#define BF 0b0110110000000000
#define BG 0b1000110001000000
#define BH 0b1100011000000000
#define BI 0b0100110010000000



int g_board[110][110]; // clean
int g_tet[27]; // clean
int g_blk[] = {B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,BA,BB,BC,BD,BE,BF,BG,BH,BI};


#include <stdio.h>

int get_block_index() {
	return (0);
}

void put_mask(int teti)
{
	int i = 3, j;
	int tet = g_blk[teti];

	while (i >= 0)
	{
		j = 3;
		while (j >= 0)
		{
			if ((1 << ((i*4) + j)) & tet)
				printf("%c", 65 + teti);
			else
				printf(".");
			j--;
		}
		printf("\n");
		i--;
	}
}

// int can_place(int x, int y, int tet)
// {
// 	int i = 0;
// 	int j = 0;

// 	while (i < 4)
// 	{
// 		while (j < 4)
// 		{

// 			j++;
// 		}
// 		i++;
// 	}
// }


// int bruticus()
// {
// 	int x = 0;
// 	int y = 0;
// 	int i = 0;
// 	while (x < 110)
// 	{
// 		while (y < 110)
// 		{
// 			if (can_place(x, y, 1))
// 			{

// 			}
// 			y++;
// 		}
// 		x++;
// 	}
// }




int main()
{
	put_mask(0);
	put_mask(1);
	put_mask(2);
	put_mask(3);
	return (0);
	// // init g_tet
	// i = 0;
	// while (i < 27)
	//     g_tet[i++] = -1;

	// // init g_board
	// i = 0;
	// while (i < 110)
	// {
	//     j = 0;
	//     while (j < 110)
	//         g_board[i][j++] = 0;
	//     i++;
	// }
	// return 0;
}