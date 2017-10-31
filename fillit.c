/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayip <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:23:23 by ayip              #+#    #+#             */
/*   Updated: 2017/10/30 18:29:05 by ayip             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define G_BLK
#include "fillit.h"

void	clear_board(void)
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

int		convert(int bin)
{
	while (bin <= 0b0000111111111111)
		bin = bin << 4;
	while ((bin & 0b1000100010001000) == 0)
		bin = bin << 1;
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
			val = val * 2 + 1;
		else
			return (-1);
	return (-1);
}

int		get_board_size(void)
{
	int		size;
	int		i;

	size = 1;
	while (42)
	{
		i = 0;
		while (i < MAX - size)
			if (g_board[size][i++] > 0)
				break ;
		if (i != MAX - size)
			size++;
		if (i != MAX - size)
			continue;
		i = 0;
		while (i < MAX - size)
			if (g_board[i++][size] > 0)
				break ;
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
