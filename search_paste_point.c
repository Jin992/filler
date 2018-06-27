/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_paste_point.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:15:15 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/09 13:15:17 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/includes/filler.h"

static _Bool	check_possibility(t_fdata *data)
{
	int dot_point;
	int overlay_point;
	int i;

	dot_point = 0;
	overlay_point = 0;
	i = 0;
	while (i < data->arr_size)
	{
		if (data->map[data->y[i]][data->x[i]] == '.')
			dot_point++;
		if (data->map[data->y[i]][data->x[i]] == data->player
			|| data->map[data->y[i]][data->x[i]] == ft_tolower(data->player))
			overlay_point++;
		i++;
	}
	if (dot_point == data->arr_size - 1 && overlay_point == 1)
		return (1);
	return (0);
}

static int		write_decision(t_fdata *data)
{
	data->decisions_cnt++;
	if (!(data->decision_x = ft_realloc_mod(data->decision_x, sizeof(int) * \
	(data->decisions_cnt), sizeof(int) * (data->decisions_cnt - 1))))
		return (-1);
	data->decision_x[data->decisions_cnt - 1] = data->zero_point[0] + \
															data->x_shift;
	if (!(data->decision_y = ft_realloc_mod(data->decision_y, sizeof(int) * \
	(data->decisions_cnt), sizeof(int) * (data->decisions_cnt - 1))))
		return (-1);
	data->decision_y[data->decisions_cnt - 1] = data->zero_point[1] + \
															data->y_shift;
	return (0);
}

int				search_position(t_fdata *data)
{
	int i;

	i = 0;
	init_cords(data);
	while (i < data->row)
	{
		while (1)
		{
			if (check_possibility(data))
				if (write_decision(data) == -1)
					return (-1);
			if (shift_x_cord(data) != 0)
				break ;
		}
		if (shift_y_cord(data) != 0)
			break ;
		i++;
	}
	return (0);
}
