/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nocardoz <nocardoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 20:28:22 by nocardoz          #+#    #+#             */
/*   Updated: 2017/09/22 20:34:41 by nocardoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char **shape_new()
{
	char 	**shape;

	shape = (char**)malloc(4 * sizeof(char*));
	shape[0] = ft_strnew(3);
	shape[1] = ft_strnew(3);
	shape[2] = ft_strnew(3);
	shape[3] = ft_strnew(3);
	return (shape);
}

char *map_line(char *line)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (line[i] == '.')
			line[i] = 0;
		else if (line[i] == '#')
			line[i] = 1;
		else
			raise(E_INVALID_MAP);
		i++;
	}
	return (line);
}

void map_print(char **map)
{
	char i;
	char j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ft_putchar('0' + map[i][j]);
		ft_putchar('\n');
	}
}

void map_lstprint(t_list *map)
{
	map_print((char**)map->content);
	ft_putchar('\n');
}

void	map_read(char const *file)
{
	int		fd;
	int		line;
	int		ret;
	char	*buff;
	t_list	*shapes;

	buff = ft_strnew(3);
	line = 0;
	fd = open(file, O_RDONLY);
	shapes = ft_lstnew(shape_new(), 4 * sizeof(char*));
	while ((ret = read(fd, buff, (++line % 5 ? 5 : 1))) && (ret == 5 || ret == 1))
	{
		if (ret == 5)
			ft_memcpy(((char**)ft_lstindex(shapes, line / 5)->content)[(line % 5) - 1], map_line(buff), 4);
		else if (ret == 1)
			ft_lstindex(shapes, (line / 5) - 1)->next = ft_lstnew(shape_new(), 4 * sizeof(char*));
	}
	if ((line % 5))
		raise(E_INVALID_MAP);
	ft_lstiter(shapes, &map_lstprint);
}
