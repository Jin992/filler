/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:07:03 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/09 13:07:05 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/includes/filler.h"

static int		check_up(t_fdata *data, int *i, int *j, char marker)
{
	if (*i > 0 && data->map[*i][*j] == '.' && data->map[*i - 1][*j] == marker)
	{
		data->map[*i][*j] = (marker + 1);
		return (1);
	}
	return (0);
}

static int		check_down(t_fdata *data, int *i, int *j, char marker)
{
	if (*i < data->row - 1 && data->map[*i][*j] == '.'
		&& data->map[*i + 1][*j] == marker)
	{
		data->map[*i][*j] = (marker + 1);
		return (1);
	}
	return (0);
}

static int		check_right(t_fdata *data, int *i, int *j, char marker)
{
	if (data->map[*i][*j] == '.' && data->map[*i][*j + 1] == marker)
	{
		data->map[*i][*j] = (marker + 1);
		return (1);
	}
	return (0);
}

static int		check_left(t_fdata *data, int *i, int *j, char marker)
{
	if (*j > 0)
		if (data->map[*i][*j] == '.' && data->map[*i][*j - 1] == marker)
		{
			data->map[*i][*j] = (marker + 1);
			return (1);
		}
	return (0);
}

int				enemy_marker(char marker, t_fdata *data)
{
	int i;
	int j;
	int paste;

	i = -1;
	paste = 0;
	while (data->map[++i] != 0)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (check_up(data, &i, &j, marker) == 1)
				paste++;
			if (check_down(data, &i, &j, marker) == 1)
				paste++;
			if (check_right(data, &i, &j, marker) == 1)
				paste++;
			if (check_left(data, &i, &j, marker) == 1)
				paste++;
			j++;
		}
	}
	if (paste > 0)
		enemy_marker(marker + 1, data);
	return (0);
}
