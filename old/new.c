
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
#define MAX 26

char	g_board[MAX][MAX];
char	g_board_cpy[MAX][MAX];
char	g_smallest[MAX][MAX];
char	g_tet[MAX];
int		g_blk[] = {B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,BA,BB,BC,BD,BE,BF,BG,BH,BI};
int		g_size;
int		g_fd;

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int		set_tet(int bin)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < MAX)
		if (bin == g_blk[i++])
			break;
	if (i == MAX)
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

int		get_board_size()
{
	int		size;
	int		i;

	size = 1;
	while (42)
	{
		i = 0;
		while (i < MAX - size)
			if (g_board[size][i++] > 0)
				break;
		if (i != MAX - size)
		{
			size++;
			continue;
		}
		i = 0;
		while (i < MAX - size)
			if (g_board[i++][size] > 0)
				break;
		if (i != MAX - size)
		{
			size++;
			continue;
		}
		return (size);
	}
}

void	print_board(char board[MAX][MAX])
{
	int		r;
	int		c;

	r = 0;
	while (r < g_size)
	{
		c = 0;
		while (c < g_size)
		{
			write(1, (board[r][c] ? &board[r][c] : "."), 1);
			c++;
		}
		r++;
		write(1, "\n", 1);
	}
}

void	put_mask(int teti)
{
	int		i;
	int		j;
	int		tet;

	i = 3;
	tet = g_blk[teti];
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

void	unplace(int row, int col, int teti)
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

int		place_if(int row, int col, int teti)
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
		{
			// (3 - r + row <= g_size && 3 - c + col <= g_size)
			// printf("(%d, %d) : [%d]\n", 3 - r + row, 3 - c + col, g_size);
			if (TET_BIT(r, c) & btet && ((3 - r + row >= g_size || 3 - c + col >= g_size) || g_board[3 - r + row][3 - c + col]))
				return (0);
		}
	r = 4;
	while (--r >= 0 && (c = 4))
		while (--c >= 0)
			if (TET_BIT(r, c) & btet)
				g_board[3 - r + row][3 - c + col] = 65 + teti;
	return (1);
}

void	board_copy()
{
	int row;
	int col;

	row = 0;
	while (row < MAX)
	{
		col = -1;
		while (++col < MAX)
		{
			g_board_cpy[row][col] = g_board[row][col];
		}
		row++;
	}
}


void	bruticus(int teti)
{
	int row;
	int col;
	int size;

	row = 0;
	while (row < g_size)
	{
		col = 0;
		while (col < g_size)
		{
			if (place_if(row, col, teti))
			{
				if ((size = get_board_size()) < g_size)
				{
					if (g_tet[teti + 1] == -1) // if we are at the last tet in the stack
					{
						g_size = size;
						print_board(g_board);
						printf("copying\n");
						board_copy();
					}
					else
						bruticus(teti + 1);
				}
				// else
				// {
				// 	unplace(row, col, teti);
				// 	col  = !++row;
				// 	continue ;
				// }
				unplace(row, col, teti);
			}
			col++;
		}
		row++;
	}
}

int		bruticus2(int teti)
{
	int row;
	int col;
	int size;

	row = 0;
	while (row < g_size)
	{
		col = 0;
		while (col < g_size)
		{
			if (place_if(row, col, teti))
			{
				if (g_tet[teti + 1] == -1) // if we are at the last tet in the stack
				{
					print_board(g_board);
					return (1);
				}
				else
					return(bruticus2(teti + 1));
			}
			col++;
		}
		row++;
	}
	return (0);
}

void	clear_board()
{
	int		i;
	int		j;

	i = 0;
	while (i < MAX)
	{
	    j = 0;
	    while (j < MAX)
	        g_board[i][j++] = 0;
	    i++;
	}
}

int		parse()
{
	int		i;
	char	buff[21];

	while ((buff[20] = '\n'))
	{
		i = read(g_fd, buff, 21);
		if (i != 21 && i != 20)
			return (1);
		if (set_tet(to_bin(buff)) == -1)
			return (1);
		if (i == 20)
		{
			if (read(g_fd, buff, 21) == 0)
				break;
			else
				return (1);
		}
	}
	g_size = 1;
	while (g_size++)
	{
		clear_board();
		if (bruticus2(0))
			break;
	}
	return (0);
}

int		main(int ac, char **av)
{
	int		i;

	if (ac != 2)
		return (write(1, "error\n", 6));
	g_fd = open(av[1], O_RDONLY);
	if (g_fd < 1)
		return (write(1, "error\n", 6));
	i = 0;
	while (i < 27)
	    g_tet[i++] = -1;
	clear_board();
	if (parse())
		return (write(1, "error\n", 6));
	return (0);
}
