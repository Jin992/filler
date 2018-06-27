/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_cords.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:20:35 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/09 13:20:37 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/includes/filler.h"

int		shift_x_cord(t_fdata *data)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (i < data->arr_size)
		if (data->x[i++] >= data->col - 2)
		{
			while (j < data->arr_size)
				data->x[j++] -= data->x_shift;
			data->x_shift = 0;
			return (1);
		}
	while (k < data->arr_size)
		data->x[k++]++;
	data->x_shift++;
	return (0);
}

int		shift_y_cord(t_fdata *data)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (i < data->arr_size)
	{
		if (data->y[i++] > data->row - 2)
			return (1);
	}
	while (k < data->arr_size)
		data->y[k++]++;
	data->y_shift++;
	return (0);
}

void	init_cords(t_fdata *data)
{
	data->x_shift = 0;
	data->y_shift = 0;
	data->decision_x = NULL;
	data->decision_y = NULL;
	data->decisions_cnt = 0;
}
