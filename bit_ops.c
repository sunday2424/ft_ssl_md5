/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 03:28:46 by junpark           #+#    #+#             */
/*   Updated: 2019/10/03 03:29:03 by junpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	left_rotate(unsigned int x, unsigned int c)
{
	return ((x << c) | (x >> (32 - c)));
}

unsigned int	right_rotate(unsigned int x, unsigned int c)
{
	return ((x >> c) | (x << (32 - c)));
}

void			rev_bits(unsigned int *c)
{
	unsigned int t;

	t = 0;
	t += *c & 0xff;
	t = t << 8;
	t += (*c >> 8) & 0xff;
	t = t << 8;
	t += (*c >> 16) & 0xff;
	t = t << 8;
	t += (*c >> 24) & 0xff;
	*c = t;
}

