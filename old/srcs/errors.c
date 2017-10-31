/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nocardoz <nocardoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 19:54:24 by nocardoz          #+#    #+#             */
/*   Updated: 2017/09/22 20:07:51 by nocardoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	raise(int error)
{
	if (error == E_INVALID_MAP)
		ft_putstr_fd("[ERROR] Invalid Map.\n", 2);
	exit(error);
}
