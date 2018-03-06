/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:39:52 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/06 13:40:07 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef FILLER_H
#define FILLER_H

typedef struct s_fdata
{
	char	**map;
	char	**piece;
	char	player;
	int		zero_point[2];
	int		*x;
	int 	*y;
	int		arr_size;
	int		row;
	int 	col;


}				t_fdata;

#endif
