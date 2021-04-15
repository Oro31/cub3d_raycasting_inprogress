/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:06:15 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/05 11:15:31 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_maplimites(t_all *vars, int *x, int *y)
{
        int     j;
        int     xmax;

        j = 0;
        while (vars->map.box[j])
                j++;
        if (*y / 64 > j)
                *y = (j - 1) * 64;
        else if (*y / 64 < 0)
                *y = 0;
        xmax = ft_lenmax_mpline(vars->map.box);
        if (*x / 64 < 0)
                *x = 0;
        else if (*x / 64 > xmax)
                *x = (xmax - 1) * 64;
}

float	ft_onlyvert_intersect(t_all *vars, float angle)
{
	int	y;
	int	x;
	int	signe;
	float	tmp;
	float	len;

	printf("onlyvert : angle = %f \n", angle);
	signe = 1;
	if (angle == (M_PI / 2))
		signe = -1;
	y = vars->map.cam.posy + signe;
	x = vars->map.cam.posx;
	while (vars->map.box[y][x] == '0')
		y += signe;
	tmp = pow((vars->map.cam.posx * 64) + 32 - (x * 64), 2) +
		pow((vars->map.cam.posy * 64) + 32 - (y * 64), 2);
	len = sqrt(tmp);
	return (len);
}

float	ft_onlyhor_intersect(t_all *vars, float angle)
{
	int	x;
	int	y;
	int	signe;
	float	tmp;
	float	len;

	printf("onlyvert : angle = %f \n", angle);
	signe = 1;
	if (angle == M_PI)
		signe = -1;
	x = vars->map.cam.posx + signe;
	y = vars->map.cam.posy;
	while (vars->map.box[y][x] == '0')
		x += signe;
	tmp = pow((vars->map.cam.posx * 64) + 32 - (x * 64), 2) +
		pow((vars->map.cam.posy * 64) + 32 - (y * 64), 2);
	len = sqrt(tmp);
	return (len);
}

float	ft_len_closest_wall(t_all *vars, float angle, int *xdm, int i)
{
	float	x;
	float	y;

	while (angle < 0)
		angle += 2 * M_PI;
	while (angle > (2 * M_PI))
		angle -= 2 * M_PI;
	if (angle == (M_PI / 2) || angle == (3 * M_PI / 2))
	{
		xdm[i] = 32;
		return (ft_onlyvert_intersect(vars, angle));
	}
	else if (angle == 0 || angle == M_PI)
	{
		xdm[i] = 32;
		return (ft_onlyhor_intersect(vars, angle));
	}
	x = ft_hor_intersect(vars, angle, xdm, i);
	y = ft_vert_intersect(vars, angle, xdm , i);
	if (x >= y)
	{
		printf("vert intersect closest y/64 =  %d \n", (int)(y / 64));
		return (y);
	}
	else
	{
		printf("hor intersect closest x/64 =  %d \n", (int)(x / 64));
		return (x);
	}
}

void	ft_find_walls(t_all *vars, float *wall, int *xdm)
{
	int	i;
	float	a;
	float	fov;

	a = (M_PI / 3) / vars->rsl.w;
	fov = ft_dir_to_fov(vars->map.cam.dir);
	i = 0;
	while (i < vars->rsl.w)
	{
		wall[i] = ft_len_closest_wall(vars,
				(fov + (M_PI / 6)) - (i * a), xdm, i);
		printf("wall[%d] = %f \n", i, wall[i]);
		i++;
	}
}
