/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:22:25 by doreshev          #+#    #+#             */
/*   Updated: 2022/08/25 19:59:29 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_img_render(t_data *a)
{
	int		i;
	char	*tmp;

	i = 64;
	tmp = a->no;
	a->no = mlx_xpm_file_to_image(a->mlx, a->no, &i, &i);
	a->addr[2] = mlx_get_data_addr(a->no, &a->bits_per_pixel[2],
			&a->line_length[2], &a->endian[2]);
	free(tmp);
	tmp = a->so;
	a->so = mlx_xpm_file_to_image(a->mlx, a->so, &i, &i);
	a->addr[3] = mlx_get_data_addr(a->so, &a->bits_per_pixel[3],
			&a->line_length[3], &a->endian[3]);
	free(tmp);
	tmp = a->we;
	a->we = mlx_xpm_file_to_image(a->mlx, a->we, &i, &i);
	a->addr[4] = mlx_get_data_addr(a->we, &a->bits_per_pixel[4],
			&a->line_length[4], &a->endian[4]);
	free(tmp);
	tmp = a->ea;
	a->ea = mlx_xpm_file_to_image(a->mlx, a->ea, &i, &i);
	a->addr[5] = mlx_get_data_addr(a->ea, &a->bits_per_pixel[5],
			&a->line_length[5], &a->endian[5]);
	free(tmp);
	if (!a->ea || !a->so || !a->we || !a->no)
	{
		write(2, "Error!\nImage file is missing or unavailable!\n", 45);
		ft_lstfree(a->map);
		free(a->mlx);
		exit(EXIT_FAILURE);
	}
}

void	ft_check_map_init(t_data *a)
{
	if (a->no == NULL)
		ft_error("Texture 'NO' not found!\n", a);
	if (a->ea == NULL)
		ft_error("Texture 'EA' not found!\n", a);
	if (a->we == NULL)
		ft_error("Texture 'WE' not found!\n", a);
	if (a->so == NULL)
		ft_error("Texture 'SO' not found!\n", a);
	if (a->c[0] < 0)
		ft_error("Ceiling colour not found!\n", a);
	if (a->f[0] < 0)
		ft_error("Floor colour not found!\n", a);
	if (!a->map)
		ft_error("Map not found!\n", a);
	if (a->player == '\0')
		ft_error("Player position not found!\n", a);
	if (a->player == 'N')
		a->pa = 90;
	else if (a->player == 'S')
		a->pa = 270;
	else if (a->player == 'E')
		a->pa = 0;
	else
		a->pa = 180;
}

void	ft_game(t_data *a)
{
	ft_check_map_init(a);
	a->pdx = cos(degree_to_radian(a->pa));
	a->pdy = -1 * sin(degree_to_radian(a->pa));
	a->mlx = mlx_init();
	ft_img_render(a);
	a->win = mlx_new_window(a->mlx, WIDTH, HEIGHT, "Cube3D");
	mlx_mouse_hide();
	mlx_hook(a->win, 17, 0, ft_close, a);
	mlx_hook(a->win, 2, 0, ft_key_hook, a);
	mlx_loop_hook(a->mlx, ft_game_start, a);
	mlx_loop(a->mlx);
}
