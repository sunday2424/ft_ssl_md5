/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junpark <junpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:11:11 by junpark           #+#    #+#             */
/*   Updated: 2019/10/03 03:33:18 by junpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	handle_flag(char *str, t_ssl *ssl)
{
	int	i;

	i = 1;
	ssl->flag.p = 0;
	ssl->flag.q = 0;
	ssl->flag.r = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'p')
			ssl->flag.p = 1;
		else if (str[i] == 'q')
			ssl->flag.q = 1;
		else if (str[i] == 'r')
			ssl->flag.r = 1;
		if (ssl->flag.r && ssl->flag.q)
			ssl->flag.r = 0;
		i++;
	}
}

int		get_command(char *av)
{
	int		i;
	char	*cmd;

	i = 0;
	while (ssl_dpt[i].command)
	{
		if (ft_strcmp(ssl_dpt[i].command, av) == 0)
		{
			cmd = ft_strdup(ssl_dpt[i].command);
			break ;
		}
		i++;
	}
	if (ft_strcmp(cmd, av) != 0)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", av);
		ft_printf("Standard	commands:\n\n");
		ft_printf("Message Digest commands:\nmd5\nsha256\n\n");
		ft_printf("Cipher commands:\n");
	}
	return (i);
}

int		main(int ac, char **av)
{
	t_ssl	ssl;
	int		i;

	if (ac < 2)
	{
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
		exit(0);
	}
	ssl.dp = ssl_dpt[get_command(av[1])];
	i = 2;
	while (av[i] && (av[i][0] == '-') && av[i][1] != 's')
	{
		handle_flag(av[i], &ssl);
		i++;
	}
	if (ssl.dp.command)
		handle_input(i, ac, av, &ssl);
	return (0);
}
