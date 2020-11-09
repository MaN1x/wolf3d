/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:49:08 by mjoss             #+#    #+#             */
/*   Updated: 2020/07/17 20:37:34 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int					swap(t_list *lst, char **line)
{
	size_t	l;
	char	*tmp;

	l = ft_strlen(lst->content);
	if (ft_strlen(lst->content) == 0)
		return (0);
	if (ft_strchr(lst->content, '\n'))
		l = ft_strlen(lst->content) - ft_strlen(ft_strchr(lst->content, '\n'));
	if (!(*line = ft_strnew(l)))
		return (-1);
	ft_memcpy(*line, lst->content, l);
	if (l == ft_strlen(lst->content))
	{
		free(lst->content);
		if (!(lst->content = ft_strnew(0)))
			return (-1);
	}
	else
	{
		tmp = ft_strnew(ft_strlen(ft_strchr(lst->content, '\n')));
		ft_strcpy(tmp, &ft_strchr(lst->content, '\n')[1]);
		free(lst->content);
		lst->content = tmp;
	}
	return (1);
}

int					wrline(t_list *lst, char **line)
{
	int			rd;
	char		*buf;
	char		*tmp;

	rd = 0;
	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	while (!ft_strchr(lst->content, '\n') &&
		(rd = read(lst->content_size, buf, BUFF_SIZE)) > 0)
	{
		if (!(tmp = ft_strjoin(lst->content, buf)))
		{
			free(buf);
			return (-1);
		}
		free(lst->content);
		lst->content = tmp;
		ft_bzero(buf, BUFF_SIZE);
	}
	if (rd < 0)
		return (rd);
	free(buf);
	return (swap(lst, line));
}

static t_list		*ft_lstnewfd(int fd)
{
	t_list	*tmp;

	if (!(tmp = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!(tmp->content = ft_strnew(0)))
		return (NULL);
	tmp->content_size = fd;
	tmp->next = NULL;
	return (tmp);
}

static t_list		*findfd(t_list *lst, int fd)
{
	while (lst)
	{
		if (lst->content_size == (size_t)fd)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int					get_next_line(int fd, char **line)
{
	static t_list	*fd_list = NULL;
	t_list			*currentfd;

	if (fd < 0 || !line)
		return (-1);
	if (!fd_list && !(fd_list = ft_lstnewfd(fd)))
		return (-1);
	if ((currentfd = findfd(fd_list, fd)))
		return (wrline(currentfd, line));
	else
	{
		currentfd = ft_lstnewfd(fd);
		ft_lstadd(&fd_list, currentfd);
		return (wrline(currentfd, line));
	}
}
