/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_place.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:24:42 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/09 13:24:44 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/includes/filler.h"

static int	find_origin(t_fdata *data)
{
	int i;
	int j;

	i = 0;
	while (data->piece[i] != 0)
	{
		j = 0;
		while (data->piece[i][j] != '\0')
		{
			if (data->piece[i][j] == '*')
				break ;
			j++;
		}
		if (data->piece[i][j] == '*')
			break ;
		i++;
	}
	data->origin_y = i;
	data->origin_x = j;
	return (0);
}

int			best_place(t_fdata *data)
{
	int i;
	int index;
	int min;
	int tmp;

	min = 2147483647;
	i = 0;
	index = 0;
	data->origin_y = 0;
	data->origin_x = 0;
	find_origin(data);
	while (i < data->decisions_cnt)
	{
		if ((tmp = (unsigned char)data->map[data->decision_y[i]\
			+ data->origin_y][data->decision_x[i] + data->origin_x]) < min)
		{
			min = tmp;
			index = i;
		}
		i++;
	}
	data->decision_x[0] = data->decision_x[index];
	data->decision_y[0] = data->decision_y[index];
	return (0);
}

int			transform_mapl(t_fdata *data)
{
	int		i;
	int		j;
	char	marker;
	char	enemy;

	i = -1;
	enemy = 'X';
	marker = '1';
	if (data->player == 'X')
		enemy = 'O';
	while (data->map[++i] != 0)
	{
		j = -1;
		while (data->map[i][++j] != '\0')
		{
			if (data->map[i][j] == enemy
				|| data->map[i][j] == enemy + ('a' - 'A'))
				data->map[i][j] = marker;
			if (data->map[i][j] == data->player
				|| data->map[i][j] == data->player + ('a' - 'A'))
				data->map[i][j] = '.';
		}
	}
	enemy_marker('1', data);
	return (0);
}
