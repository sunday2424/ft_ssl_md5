/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junpark <junpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 02:23:11 by junpark           #+#    #+#             */
/*   Updated: 2019/07/17 15:47:52 by junpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_printf/ft_printf.h"

typedef struct	s_flags
{
	int			p;
	int			q;
	int			r;
	int			s;
}				t_flags;

typedef struct	s_dp
{
	char		*command;
	void		(*function)(char *);
}				t_dp;

typedef struct	s_ssl
{
	t_dp		dp;
	t_flags		flags;
}				t_ssl;

typedef struct	s_md
{
	unsigned int	A;
	unsigned int	B;
	unsigned int	C;
	unsigned int	D;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	f;
	unsigned int	g;
	unsigned int	set;
	unsigned char	*msg;
	unsigned char	mem[16][4];
}				t_md;

typedef struct	s_sha
{
	unsigned int	hash[8];
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	e;
	unsigned int	f;
	unsigned int	g;
	unsigned int	h;
	unsigned int	set;
	unsigned char	*msg;
	unsigned int	mem[64];
}				t_sha;

#endif
