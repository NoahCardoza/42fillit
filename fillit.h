/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noahcardoza <noahcardoza@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 19:46:06 by nocardoz          #+#    #+#             */
/*   Updated: 2017/10/30 19:08:33 by noahcardoza      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <unistd.h>

/*
** B0   B1   B2   B3   B4
** #... #### ##.. .#.. #...
** #... .... ##.. ###. ##..
** #... .... .... .... #...
** #... .... .... .... ...
**
** B5   B6   B7   B8   B9
** ###. .#.. #... ##.. ###.
** .#.. ##.. ###. #... ..#.
** .... .#.. .... #... ....
** .... .... .... .... ....
**
** BA   BB   BC   BD   BE
** .#.. ..#. #... ###. ##..
** .#.. ###. #... #... .#..
** ##.. .... ##.. .... .#..
** .... .... .... .... ....
**
** BF   BG   BH   BI
** .##. #... ##.. .#..
** ##.. ##.. .##. ##..
** .... .#.. .... #...
** .... .... .... ....
*/

# define B0 0b1000100010001000
# define B1 0b1111000000000000
# define B2 0b1100110000000000
# define B3 0b0100111000000000
# define B4 0b1000110010000000
# define B5 0b1110010000000000
# define B6 0b0100110001000000
# define B7 0b1000111000000000
# define B8 0b1100100010000000
# define B9 0b1110001000000000
# define BA 0b0100010011000000
# define BB 0b0010111000000000
# define BC 0b1000100011000000
# define BD 0b1110100000000000
# define BE 0b1100001000100000
# define BF 0b0110110000000000
# define BG 0b1000110001000000
# define BH 0b1100011000000000
# define BI 0b0100110010000000

# define BIT(i) (1 << i)
# define TET_BIT(row, col) (BIT(((row*4) + col)))
# define MAX 26
# define NUMBLK 19

# ifndef G_BLK
#  define G_BLK
int		g_blk[] = {B0, B1, B2, B3, B4, B5, B6, B7, B8, B9,
	BA, BB, BC, BD, BE, BF, BG, BH, BI};

# endif

char	g_board[MAX][MAX];
char	g_board_cpy[MAX][MAX];
char	g_smallest[MAX][MAX];
char	g_tet[MAX];
int		g_size;
int		g_fd;

int		set_tet(int bin);
void	clear_board();
int		to_bin(char buff[21]);
int		get_board_size();
void	print_board(char board[MAX][MAX]);

#endif
