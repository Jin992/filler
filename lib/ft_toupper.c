/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <earteshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 14:19:51 by earteshc          #+#    #+#             */
/*   Updated: 2017/11/15 14:00:18 by earteshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (('a' <= c) && (c <= 'z'))
		return ((int)c - 32);
	return ((int)c);
}
