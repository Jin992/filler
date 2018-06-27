/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:52:35 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/09 11:52:42 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/includes/filler.h"

static char		**make_map(char **map, char **line, size_t row)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if ((map = ft_new_str_arr(map, row)) == NULL)
		return (NULL);
	while (i < row)
	{
		free(*line);
		get_next_line(0, line);
		if (!(tmp = ft_strchr(*line, ' ')))
		{
			free(*line);
			return (NULL);
		}
		if ((map[i++] = ft_strdup(tmp + 1)) == NULL)
			return (NULL);
	}
	free(*line);
	return (map);
}

static void		get_payer(char **line, char *player)
{
	if (ft_strncmp("$$$ exec", *line, 8) == 0)
	{
		if (ft_strcmp("$$$ exec p1 : [./earteshc.filler]", *line) == 0)
			*player = 'O';
		else
			*player = 'X';
	}
}

char			**get_map(char **line, char *player, t_fdata *data)
{
	char		**map;

	map = NULL;
	while (get_next_line(0, line) == 1)
	{
		get_payer(line, player);
		if (ft_strncmp(*line, "Plateau", 7) == 0)
		{
			data->row = (int)ft_atoi(*(line) + 7);
			if (data->row >= 100)
				data->col = (int)ft_atoi(*(line) + 12);
			else
				data->col = (int)ft_atoi(*(line) + 10);
			free(*line);
			get_next_line(0, line);
			break ;
		}
		free(*line);
	}
	return (make_map(map, line, (size_t)data->row));
}

static char		**make_piece(char **piece, char **line, size_t row)
{
	size_t i;

	i = 0;
	if ((piece = ft_new_str_arr(piece, row)) == NULL)
		return (NULL);
	while (i < row)
	{
		get_next_line(0, line);
		if ((piece[i++] = ft_strdup(*line)) == NULL)
			return (NULL);
		free(*line);
	}
	return (piece);
}

char			**get_piece(char **line)
{
	size_t		row;
	char		**piece;

	piece = NULL;
	row = 0;
	while (get_next_line(0, line) == 1)
	{
		if (ft_strncmp(*line, "Piece", 5) == 0)
		{
			row = (size_t)ft_atoi(*(line) + 5);
			free(*line);
			break ;
		}
		free(*line);
	}
	return (make_piece(piece, line, row));
}
