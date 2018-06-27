/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_piece.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:29:12 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/09 13:29:13 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/includes/filler.h"

static int		add_cords(t_fdata *piece, int i, int j, int pieces)
{
	if (!(piece->x = ft_realloc_mod(piece->x,\
	sizeof(int) * (pieces + 1), sizeof(int) * (pieces - 1))))
		return (-1);
	piece->x[pieces - 1] = j;
	if (!(piece->y = ft_realloc_mod(piece->y,\
	sizeof(int) * (pieces + 1), sizeof(int) * (pieces - 1))))
		return (-1);
	piece->y[pieces - 1] = i;
	return (0);
}

int				get_piece_cords(t_fdata *piece)
{
	int i;
	int j;
	int pieces;

	i = 0;
	pieces = 0;
	piece->x = NULL;
	piece->y = NULL;
	while (piece->piece[i] != 0)
	{
		j = 0;
		while (piece->piece[i][j] != '\0')
		{
			if (piece->piece[i][j] == '*')
			{
				pieces++;
				if (add_cords(piece, i, j, pieces) == -1)
					return (-1);
				piece->arr_size = pieces;
			}
			j++;
		}
		i++;
	}
	return (0);
}

static _Bool	zero_exist(t_fdata *data, _Bool mode)
{
	int	i;

	i = data->arr_size;
	while (i--)
	{
		if (mode && (data->x)[i] == 0)
			return (1);
		else if (!mode && (data->y)[i] == 0)
			return (1);
	}
	return (0);
}

static void		decrement(t_fdata *data, _Bool mode)
{
	int	i;

	i = data->arr_size;
	while (i--)
	{
		if (mode)
			((data->x)[i])--;
		else
			((data->y)[i])--;
	}
}

int				cords_init_position(t_fdata *data)
{
	data->zero_point[0] = 0;
	data->zero_point[1] = 0;
	while (!zero_exist(data, 1))
	{
		((data->zero_point)[0])--;
		decrement(data, 1);
	}
	while (!zero_exist(data, 0))
	{
		((data->zero_point)[1])--;
		decrement(data, 0);
	}
	return (0);
}
