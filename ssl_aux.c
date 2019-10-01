 #include "ft_ssl.h"

void	handle_data(int ac, t_ssl *ssl)
{
	char	*command;
	char	*buff;

	if ((ac == 2 || ssl->flag.p) && get_next_line(0, &buff) > 0)
	{
		command = ft_strjoin(buff, "\n");
		if(ssl->flag.p)
			ft_printf("%s", command);
		ssl->dp.function(command);
		write(1, "\n", 1);
		free(command);
		free(buff);
	}
}

void	read_param(char **av, int i, t_ssl *ssl)
{
	int		j;
	char	*cmd;

	cmd = ft_strdup(ssl->dp.command);
	j = 0;
	while (cmd[j] != '\0')
	{
		cmd[j] = ft_toupper(cmd[j]);
		j++;
	}
	if (!(ssl->flag.q && ssl->flag.r))
		ft_printf("%s (\"%s\") = ", cmd, av[i + 1]);
	ssl->dp.function(av[i + 1]);
	if (ssl->flag.r)
		ft_printf(" \"%s\"\n", av[i + 1]);
	if (ssl->flag.s && !ssl->flag.r)
		write(1, "\n", 1);
	free(cmd);
}

void	read_file(int fd, char **av, int i, t_ssl *ssl)
{
	// int		fd;
	// int		j;
	char	*tmp;
	// char	*input;

	if (get_next_line(fd, &tmp) > 0)
		read_file_sub1(av, i, tmp, ssl);
	else
		ft_printf("No such a file or directory\n");
	if (av[i + 1] != '\0')
		while (av[i + 1] != '\0')
		{
			if (av[i + 1][1] == 's')
				ft_printf("ft_ssl: %s: -s: No such file or directory\n",
					ssl->dp.command);
			else
				ft_printf("ft_ssl: %s: %s: No such file or directory\n",
					ssl->dp.command, av[i + 1]);
			i++;
		}
	close(fd);
}

void	read_file_sub1(char **av, int i, char *tmp, t_ssl *ssl)
{
	int		j;
	char	*input;

	input = ft_strjoin(tmp, "\n");
	free(tmp);
	tmp = ft_strdup(ssl->dp.command);
	j = 0;
	while (tmp[j] != '\0')
	{
		tmp[j] = ft_toupper(tmp[j]);
		j++;
	}
	if (ssl->flag.q && !ssl->flag.r)
		ft_printf("%s (%s) = ", tmp, av[i]);
	ssl->dp.function(input);
	if (ssl->flag.r)
		ft_printf(" %s", av[i]);
	write(1, "\n", 1);
	free(input);
	free(tmp);
}

void	handle_input(int i, int ac, char **av, t_ssl *ssl)
{
	int		fd;
	// char	*cmd;

	handle_data(ac, ssl);
	while (av[i])
	{
		if (ft_strcmp(av[i], "-s") == 0)
			read_param(av, i, ssl);
		else if ((fd = open(av[i], O_RDONLY)) > 0)
		{
			read_file(fd, av, i, ssl);
			break ;
		}
		i++;
	}
}