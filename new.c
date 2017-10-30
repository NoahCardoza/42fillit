
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

#define BIT(i) (1 << i)
#define TET_BIT(row, col) (BIT(((row*4) + col)))

char	g_board[110][110];
char	g_smallest[110][110];
char	g_tet[27];
int		g_blk[] = {B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,BA,BB,BC,BD,BE,BF,BG,BH,BI}; // norm
// int		g_size = 110; // norm
int g_size = 11;


#include <stdio.h>
#include <string.h>
#include <unistd.h>

int		set_tet(int bin)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 19)
		if (bin == g_blk[i++])
			break;
	if (i == 19)
		return (-1);
	j = 0;
	while (g_tet[j] != -1)
		j++;
	g_tet[j] = i - 1;
	return (0);
}

int		convert(int bin)
{
	while (bin <= 0b0000111111111111)
		bin = bin << 4;
	while ((bin & 0b1000100010001000) == 0)
	{
		bin = ((bin & 0b1111000000000000) << 1) + (bin & 0b0000111111111111);
		bin = ((bin & 0b0000111100000000) << 1) + (bin & 0b1111000011111111);
		bin = ((bin & 0b0000000011110000) << 1) + (bin & 0b1111111100001111);
		bin = ((bin & 0b0000000000001111) << 1) + (bin & 0b1111111111110000);
	}
	return (bin);
}

int		to_bin(char buff[21])
{
	int		val;
	int		i;

	i = -1;
	val = 0;
	while (i++ < 20)
		if (i == 20 && (buff[i] == '\n' || buff[i] == '\0'))
			return (convert(val));
		else if (i == 20)
			return (-1);
		else if (i != 0 && (i + 1) % 5 == 0 && buff[i] == '\n')
			continue;
		else if (i != 0 && (i + 1) % 5 == 0)
			return (-1);
		else if (buff[i] == '.')
			val *= 2;
		else if (buff[i] == '#')
		{
			val *= 2;
			val += 1;
		}
		else
			return (-1);
	return (-1);
}

/*
int		main(void)
{
	int i, j;
	// init g_tet
	i = 0;
	while (i < 27)
		g_tet[i++] = -1;

	// init g_board
	i = 0;
	while (i < 110)
	{
		j = 0;
		while (j < 110)
			g_board[i][j++] = 0;
		i++;
	}

	char buff[21];
   	strcpy(buff, "....\n.##.\n.##.\n....\n"); // 2
	printf("set_tet(to_bin(buff)): %d\n", set_tet(to_bin(buff)));

   	strcpy(buff, "....\n.##.\n.##.\n..#.\n"); // junk
	printf("set_tet(to_bin(buff)): %d\n", set_tet(to_bin(buff)));

   	strcpy(buff, "....\n.##.\n.##.\n.."); // junk
	printf("set_tet(to_bin(buff)): %d\n", set_tet(to_bin(buff)));

   	strcpy(buff, "....\n.#..\n.#..\n.##.\n"); // 12
	printf("set_tet(to_bin(buff)): %d\n", set_tet(to_bin(buff)));
	// print g_tet
	i = 0;
	while (g_tet[i] != -1)
		printf("%d\n", (int)g_tet[i++]);
	return (0);
}
*/

int		get_board_size()
{
	int		size;
	int		i;

	size = 1;
	while (42)
	{
		i = 0;
		while (i < size + 1)
			if (g_board[size][i++] > 0)
				break;
		if (i != size + 1)
		{
			size++;
			continue;
		}
		i = 0;
		while (i < size + 1)
			if (g_board[i++][size] > 0)
				break;
		if (i != size + 1)
		{
			size++;
			continue;
		}
		return (size);
	}
}

void	print_board()
{
	int		r;
	int		c;

	r = 0;
	while (r < g_size)
	{
		// put g_board or g_smallest for debug
		c = 0;
		while (c < g_size)
		{
			write(1, (g_board[r][c] ? &g_board[r][c] : "."), 1);
			c++;
		}
		r++;
		write(1, "\n", 1);
	}
}

int		get_block_index() {
	return (0);
}

void	put_mask(int teti)
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

void unplace(int row, int col, int teti)
{
	int r;
	int c;
	int btet;
	btet = g_blk[g_tet[teti]];
	r = 4;
	while (--r >= 0 && (c = 4))
		while (--c >= 0)
			if (TET_BIT(r, c) & btet)
				g_board[3 - r + row][3 - c + col] = 0;
}

int place_if(int row, int col, int teti)
{
	int r;
	int c;
	int btet;
	int tet;
	btet = g_blk[g_tet[teti]];
	tet = g_blk[g_tet[teti]];
	r = 4;
	while (--r >= 0 && (c = 4))
		while (--c >= 0)
			if (TET_BIT(r, c) & btet && g_board[3 - r + row][3 - c + col])
				return (0);
	r = 4;
	while (--r >= 0 && (c = 4))
		while (--c >= 0)
			if (TET_BIT(r, c) & btet)
				g_board[3 - r + row][3 - c + col] = 65 + teti;
	return (1);
}


int bruticus(int teti)
{
	int row = 0;
	int col = 0;
	while (row < 110)
	{
		while (col < 110)
		{
			if (place_if(row, col, teti))
			{
				if (get_board_size() <= g_size)
				{
					if (g_tet[teti + 1] == -1); // if we are at the last tet in the stack
						// if square is smaller, copy board to smallest board g_var
					// else
						// bruticus(teti + 1);
				}
				unplace(row, col, teti);
			}
			col++;
		}
		row++;
	}
	return (0);
}

int main()
{
	g_tet[0] = 0;
	g_tet[1] = 0;

	printf("%d\n", place_if(0,0,0));
	printf("%d\n", place_if(1,1,1));

	print_board();
	printf("%d\n", get_board_size());
	// put_mask(0);
	// put_mask(1);
	// put_mask(2);
	// put_mask(3);
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
