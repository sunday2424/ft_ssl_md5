/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junpark <junpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:44:00 by junpark           #+#    #+#             */
/*   Updated: 2019/10/03 01:41:40 by junpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	g_md5_s[64] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

unsigned int	g_md5_k[64] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static void		md5_loop(int i, t_md5 *md5)
{
	if (0 <= i && i <= 15)
	{
		md5->f = (md5->b & md5->c) | ((~md5->b) & md5->d);
		md5->g = i;
	}
	else if (16 <= i && i <= 31)
	{
		md5->f = (md5->d & md5->b) | ((~md5->d) & md5->c);
		md5->g = (5 * i + 1) % 16;
	}
	else if (32 <= i && i <= 47)
	{
		md5->f = md5->b ^ md5->c ^ md5->d;
		md5->g = (3 * i + 5) % 16;
	}
	else
	{
		md5->f = md5->c ^ (md5->b | (~md5->d));
		md5->g = (7 * i) % 16;
	}
	md5->f = md5->f + md5->a + g_md5_k[i] + *((unsigned int *)(md5->mem[md5->g]));
	md5->a = md5->d;
	md5->d = md5->c;
	md5->c = md5->b;
	md5->b = md5->b + left_rotate(md5->f, g_md5_s[i]);
}

static void		md5_proc(int set, t_md5 *md)
{
	int i;
	int j;

	i = 0;
	while (i < 16)
	{
		j = -1;
		while (++j < 4)
			md->mem[i][j] = md->str[set * 64 + i * 4 + j];
		i++;
	}
	md->a = md->A;
	md->b = md->B;
	md->c = md->C;
	md->d = md->D;
	i = 0;
	while (i < 64)
	{
		md5_loop(i, md);
		i++;
	}
	md->A += md->a;
	md->B += md->b;
	md->C += md->c;
	md->D += md->d;
}

static void		md5_pad(char *s, t_md5 *md)
{
	int					i;
	unsigned long long	bit_len;

	md->A = 0x67452301;
	md->B = 0xefcdab89;
	md->C = 0x98badcfe;
	md->D = 0x10325476;
	bit_len = 0;
	if (s)
		md->set = (ft_strlen(s) + 8) / 64 + 1;
	else
		md->set = 1;
	md->str = (unsigned char *)malloc(64 * md->set);
	i = -1;
	while (++i < (int)(64 * md->set))
		md->str[i] = 0;
	i = -1;
	while (s && s[++i])
		md->str[i] = s[i];
	md->str[i == -1 ? 0 : i] = 1 << 7;
	bit_len = i << 3;
	i = -1;
	while (++i < 8)
		md->str[64 * md->set - 8 + i] = bit_len >> (i * 8);
}

void			md5_dpt(char *str)
{
	t_md5	md5;
	int		i;

	ft_bzero(&md5, 10);
	md5_pad(str, &md5);
	i = 0;
	while (i < (int)(md5.set))
	{
		md5_proc(i, &md5);
		i++;
	}
	rev_bits(&md5.A);
	rev_bits(&md5.B);
	rev_bits(&md5.C);
	rev_bits(&md5.D);
	ft_printf("%.8x%.8x%.8x%.8x", md5.A, md5.B, md5.C, md5.D);
	free(md5.str);
}
