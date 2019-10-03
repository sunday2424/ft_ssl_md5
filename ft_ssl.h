/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junpark <junpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 02:23:11 by junpark           #+#    #+#             */
/*   Updated: 2019/10/03 04:34:05 by junpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdio.h>
# include <fcntl.h>
# include "ft_printf/ft_printf.h"
# include "ft_printf/libft.h"

# define RIGHT_ROTATE_64BIT(n, d) ((n >> d) | (n << (64 - d)))

typedef struct	s_ssl_flag
{
	int			p;
	int			q;
	int			r;
	int			s;
}				t_ssl_flag;

/*
** p, echo STDIN to STDOUT and append the checksum to STDOUT
** q, quiet mode
** r, reverse the format of the output.
** s, print the sum of the given string
*/

typedef struct	s_dp
{
	char		*command;
	void		(*function)(char *);
}				t_dp;

typedef struct	s_ssl
{
	t_dp		dp;
	t_ssl_flag	flag;
}				t_ssl;

typedef struct	s_md5
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
	unsigned char	*str;
	unsigned char	mem[16][4];
}				t_md5;

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

typedef struct	s_sha5
{
	uint64_t		hash[8];
	uint64_t		a;
	uint64_t		b;
	uint64_t		c;
	uint64_t		d;
	uint64_t		e;
	uint64_t		f;
	uint64_t		g;
	uint64_t		h;
	uint64_t		set;
	unsigned char	*msg;
	uint64_t		mem[80];
}				t_sha5;

void			handle_flag(char *str, t_ssl *ssl);
int				get_command(char *av);

void			handle_data(int ac, t_ssl *ssl);
void			read_param(char **av, int i, t_ssl *ssl);
void			read_file(int fd, char *file, t_ssl *ssl);
int				file_reader(int fd, char **file);
char			*str_add(char const *s1, char const *s2, char *c);
void			handle_input(int i, int ac, char **av, t_ssl *ssl);

void			rev_bits(unsigned int *c);
unsigned int	left_rotate(unsigned int x, unsigned int c);
unsigned int	right_rotate(unsigned int x, unsigned int c);

int				reader(int fd, char **file);
char			*str_add(char const *s1, char const *s2, char *c);

void			md5_dpt(char *str);
void			sha256_dpt(char *str);
void			sha224_dpt(char *str);
void			sha512_dpt(char *str);
void			sha384_dpt(char *str);

static t_dp ssl_dpt[] =
{
	{"md5", md5_dpt},
	{"sha256", sha256_dpt},
	{"sha224", sha224_dpt},
	{"sha512", sha512_dpt},
	{"sha384", sha384_dpt},
	{NULL, NULL}
};

#endif
