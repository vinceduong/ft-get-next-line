/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 17:53:55 by vduong            #+#    #+#             */
/*   Updated: 2018/05/02 12:04:18 by vduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*joinline(char **str1, char *str2)
{
	int		len;
	int		restlen;
	char	*line;
	char	*rest;
	char	*tmp;

	if (!*str2)
		return (NULL);
	tmp = *str1;
	len = ft_instr(str2, '\n') + 1;
	if (!(line = ft_strnew(len)))
		return (NULL);
	ft_strncpy(line, str2, len);
	*str1 = ft_strjoin(tmp, line);
	free(tmp);
	free(line);
	if (!(restlen = ft_strlen(str2 + len)))
		return (NULL);
	rest = ft_strnew(restlen);
	ft_strncpy(rest, str2 + len, restlen);
	return (rest);
}

int				get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	int				ret;
	static char		*stock;

	if (fd < 0 || fd > 10000 || !line || !(*line = ft_strnew(1)))
		return (-1);
	if (stock != NULL)
	{
		stock = joinline(line, stock);
		if (ft_strcutat(line, '\n'))
			return (1);
	}
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		stock = joinline(line, buff);
		if (ft_strcutat(line, '\n'))
			return (1);
	}
	if (ret == -1)
		return (-1);
	if (!stock && !ret && !ft_strlen(*line))
		return (0);
	return (1);
}
