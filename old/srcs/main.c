/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nocardoz <nocardoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 16:29:58 by nocardoz          #+#    #+#             */
/*   Updated: 2017/09/22 20:29:59 by nocardoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"



int			main(int argc, char const *argv[])
{
	int fd;

	if (argc != 2)
		write(1, "usage: fillit source_file\n", 26);
	else
		map_read(argv[1]);
	return (0);
}
