/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:33:08 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/09 13:33:10 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/includes/filler.h"

void			*free_data(t_fdata *data)
{
	ft_free_str_arr(data->map);
	ft_free_str_arr(data->piece);
	free(data->x);
	free(data->y);
	if (data->decision_y != NULL)
		free(data->decision_y);
	if (data->decision_x != NULL)
		free(data->decision_x);
	data->piece = NULL;
	data->x = NULL;
	data->y = NULL;
	data->y_shift = 0;
	data->x_shift = 0;
	return (NULL);
}

static void		correct_answer(t_fdata *data)
{
	ft_putnbr_fd(data->decision_y[0], 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(data->decision_x[0], 1);
	ft_putstr_fd("\n", 1);
}

static void		*wrong_answer(t_fdata *data)
{
	ft_putnbr_fd(0, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(0, 1);
	ft_putstr_fd("\n", 1);
	free_data(data);
	free(data);
	return (NULL);
}

int				main(void)
{
	char	*line;
	t_fdata	*data;

	data = (t_fdata *)malloc(sizeof(t_fdata));
	while (1)
	{
		if (!(data->map = get_map(&line, &data->player, data)))
			return ((int)wrong_answer(data));
		if (!(data->piece = get_piece(&line)))
			return ((int)wrong_answer(data));
		if (get_piece_cords(data) == -1)
			return ((int)wrong_answer(data));
		cords_init_position(data);
		search_position(data);
		transform_mapl(data);
		if (data->decision_y != NULL && data->decision_x != NULL)
			best_place(data);
		if (data->decision_y == NULL || data->decision_x == NULL)
			return ((int)wrong_answer(data));
		else
			correct_answer(data);
		free_data(data);
	}
	return (0);
}
