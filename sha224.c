/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 03:32:36 by junpark           #+#    #+#             */
/*   Updated: 2019/10/03 03:32:38 by junpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	g_sha224_k[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,	0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,	0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,	0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,	0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,	0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,	0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,	0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,	0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,	0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,	0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

unsigned int	g_sha224_v[8] =
{
	0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
	0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
};

static void	sha224_loop(int i, t_sha *sha)
{
	unsigned int	s0;
	unsigned int	s1;
	unsigned int	ch;
	unsigned int	temp1;
	unsigned int	maj;

	s1 = right_rotate(sha->e, 6) ^ right_rotate(sha->e, 11)
		^ right_rotate(sha->e, 25);
	ch = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
	temp1 = sha->h + s1 + ch + g_sha224_k[i] + sha->mem[i];
	s0 = right_rotate(sha->a, 2) ^ right_rotate(sha->a, 13)
		^ right_rotate(sha->a, 22);
	maj = (sha->a & sha->b) ^ (sha->a & sha->c) ^ (sha->b & sha->c);
	sha->h = sha->g;
	sha->g = sha->f;
	sha->f = sha->e;
	sha->e = sha->d + temp1;
	sha->d = sha->c;
	sha->c = sha->b;
	sha->b = sha->a;
	sha->a = temp1 + s0 + maj;
}

static void	sha224_pre(int set, t_sha *sha)
{
	int				i;
	int				j;
	unsigned int	s0;
	unsigned int	s1;

	i = -1;
	while (++i < 16)
	{
		j = -1;
		sha->mem[i] = 0;
		while (++j < 4)
			sha->mem[i] += sha->msg[set * 64 + i * 4 + j] << (8 * (3 - j));
	}
	i = 15;
	while (++i < 64)
	{
		s0 = right_rotate(sha->mem[i - 15], 7) ^ right_rotate(sha->mem[i - 15], 18)
			^ (sha->mem[i - 15] >> 3);
		s1 = right_rotate(sha->mem[i - 2], 17) ^ right_rotate(sha->mem[i - 2], 19)
			^ (sha->mem[i - 2] >> 10);
		sha->mem[i] = sha->mem[i - 16] + s0 + sha->mem[i - 7] + s1;
	}
}

static void	sha224_process(int set, t_sha *sha)
{
	int i;

	sha224_pre(set, sha);
	sha->a = sha->hash[0];
	sha->b = sha->hash[1];
	sha->c = sha->hash[2];
	sha->d = sha->hash[3];
	sha->e = sha->hash[4];
	sha->f = sha->hash[5];
	sha->g = sha->hash[6];
	sha->h = sha->hash[7];
	i = -1;
	while (++i < 64)
		sha224_loop(i, sha);
	sha->hash[0] += sha->a;
	sha->hash[1] += sha->b;
	sha->hash[2] += sha->c;
	sha->hash[3] += sha->d;
	sha->hash[4] += sha->e;
	sha->hash[5] += sha->f;
	sha->hash[6] += sha->g;
	sha->hash[7] += sha->h;
}

static void	sha224_init(char *s, t_sha *sha)
{
	int			i;
	uint64_t	bit_len;

	i = -1;
	while (++i < 8)
		sha->hash[i] = g_sha224_v[i];
	sha->set = s ? (ft_strlen(s) + 8) / 64 + 1 : 1;
	sha->msg = (unsigned char *)malloc(64 * sha->set);
	i = -1;
	while (++i < (int)(64 * sha->set))
		sha->msg[i] = 0;
	i = -1;
	while (s && s[++i])
		sha->msg[i] = s[i];
	sha->msg[i == -1 ? 0 : i] = 1 << 7;
	bit_len = i << 3;
	i = -1;
	while (++i < 8)
		sha->msg[64 * sha->set - i - 1] = bit_len >> (i * 8);
}

void		sha224_dpt(char *str)
{
	t_sha	sha;
	int		set;

	sha224_init(str, &sha);
	set = -1;
	while (++set < (int)(sha.set))
		sha224_process(set, &sha);
	set = -1;
	while (++set < 7)
		ft_printf("%.8x", sha.hash[set]);
	free(sha.msg);
}
