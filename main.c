/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:23:41 by ayip              #+#    #+#             */
/*   Updated: 2017/10/30 18:48:32 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#include <stdio.h>
int		set_tet(int bin)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < NUMBLK)
		if (bin == g_blk[i++])
			break ;
	if (i == NUMBLK)
		return (-1);
	j = 0;
	while (g_tet[j] != -1)
		if (++j >= MAX)
			return (-1);
	g_tet[j] = i - 1;
	return (0);
}

int		place_if(int row, int col, int teti)
{
	int		r;
	int		c;
	int		btet;
	int		tet;

	btet = g_blk[(int)g_tet[teti]];
	tet = g_blk[(int)g_tet[teti]];
	r = 4;
	while (--r >= 0 && (c = 4))
		while (--c >= 0)
		{
			if (TET_BIT(r, c) & btet && ((3 - r + row >= g_size
				|| 3 - c + col >= g_size) || g_board[3 - r + row][3 - c + col]))
				return (0);
		}
	r = 4;
	while (--r >= 0 && (c = 4))
		while (--c >= 0)
			if (TET_BIT(r, c) & btet)
				g_board[3 - r + row][3 - c + col] = 65 + teti;
	return (1);
}

int		bruticus2(int teti)
{
	int		row;
	int		col;

	row = 0;
	while (row < g_size)
	{
		col = 0;
		while (col < g_size)
		{
			if (place_if(row, col, teti))
			{
				if (g_tet[teti + 1] == -1)
				{
					print_board(g_board);
					return (1);
				}
				else
					return (bruticus2(teti + 1));
			}
			col++;
		}
		row++;
	}
	return (0);
}

int		parse(void)
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
			break ;
	}
	while (g_size++)
	{
		clear_board();
		if (bruticus2(0))
			break ;
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
	g_size = 1;
	if (parse())
		return (write(1, "error\n", 6));
	return (0);
}
