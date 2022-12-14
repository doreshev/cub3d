/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:44:15 by doreshev          #+#    #+#             */
/*   Updated: 2022/08/31 19:49:05 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_lstfree(t_list *map)
{
	t_list	*n1;

	if (!map)
		return ;
	n1 = map;
	while (map)
	{
		if (n1->content)
			free(n1->content);
		n1->content = NULL;
		n1 = n1->next;
		free(map);
		map = n1;
	}
}

void	ft_free_addr(char **addr)
{
	int	i;

	if (addr == NULL)
		return ;
	i = 0;
	while (i < 9)
	{
		free(addr[i]);
		addr[i] = NULL;
		i++;
	}
}

void	ft_free(t_data *a)
{
	ft_lstfree(a->map);
	if (a->img)
		mlx_destroy_image(a->mlx, a->img);
	free(a->mlx);
	ft_free_addr(a->addr);
	free(a->line);
}

void	ft_error(char *s, t_data *a)
{
	ft_free(a);
	write(2, "Error\n", 6);
	ft_putstr_fd(s, 2);
	exit(EXIT_FAILURE);
}

int	ft_close(t_data *a)
{
	mlx_destroy_window(a->mlx, a->win);
	ft_free(a);
	exit(EXIT_SUCCESS);
}
