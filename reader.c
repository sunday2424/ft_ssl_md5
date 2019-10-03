/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 03:29:25 by junpark           #+#    #+#             */
/*   Updated: 2019/10/03 03:29:27 by junpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		reader(int fd, char **file)
{
	char	*buff;
	char	*str;
	char	*tmp;
	int		f;

	buff = NULL;
	str = NULL;
	while ((f = get_next_line(fd, &buff)) > 0)
	{
		if (str)
		{
			tmp = str_add(str, buff, "\n");
			free(str);
			str = ft_strdup(tmp);
			free(tmp);
		}
		else
			str = ft_strdup(buff);
		free(buff);
	}
	if (f < 0)
		return (-1);
	*file = strdup(str);
	free(str);
	return (0);
}

char	*str_add(char const *s1, char const *s2, char *c)
{
	char *res;

	if (s1 && s2 && c)
	{
		if (!(res = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(c))))
			return (NULL);
		res = ft_strcpy(res, s1);
		res = ft_strcat(res, c);
		res = ft_strcat(res, s2);
		return (res);
	}
	return (NULL);
}
