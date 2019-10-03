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
	char	*cmd;

	cmd = ft_strdup(ssl->dp.command);
	cmd = ft_strupcase(cmd);
	if (!(ssl->flag.q && ssl->flag.r))
		ft_printf("%s (\"%s\") = ", cmd, av[i + 1]);
	ssl->dp.function(av[i + 1]);
	if (ssl->flag.r)
		ft_printf(" \"%s\"\n", av[i + 1]);
	if (ssl->flag.s && !ssl->flag.r)
		write(1, "\n", 1);
	free(cmd);
}

void	read_file(int fd, char *file, t_ssl *ssl)
{
	char	*tmp;
	char	*input;

	if (reader(fd, &tmp) >= 0)
	{
		input = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = ft_strdup(ssl->dp.command);
		tmp = ft_strupcase(tmp);
		if (!ssl->flag.q && !ssl->flag.r)
			ft_printf("%s (%s) = ", tmp, file);
		ssl->dp.function(input);
		if (ssl->flag.r)
			ft_printf(" %s", file);
		write(1, "\n", 1);
		free(input);
		free(tmp);
	}
	else
		ft_printf("No such a file or directory\n");
	close(fd);
}

void	handle_input(int i, int ac, char **av, t_ssl *ssl)
{
	int		fd;

	handle_data(ac, ssl);
	while (av[i])
	{
		if (ft_strcmp(av[i], "-s") == 0)
			read_param(av, i, ssl);
		else if ((fd = open(av[i], O_RDONLY)) > 0)
			read_file(fd, av[i], ssl);
		else
			if (av[i + 1] != '\0')
			{
				if (av[i + 1][1] == 's')
					ft_printf("ft_ssl: %s: -s: No such file or directory\n",
						ssl->dp.command);
				else
					ft_printf("ft_ssl: %s: %s: No such file or directory\n",
						ssl->dp.command, av[i + 1]);
			}
		i++;
	}
}