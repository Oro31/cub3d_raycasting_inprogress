/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hor_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 07:46:41 by rvalton           #+#    #+#             */
/*   Updated: 2021/04/06 08:42:09 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_ne_hor_inte(t_all *vars, float angle, int *xdm, int i)
{
	int	x;
	int	y;
	float	tmp;
	float	len;
	float	a;

	a = sin(angle) / cos(angle);
	if (a < 0)
		a = a * -1;
	printf("tan(angle) = %f \n", a);
	x = (vars->map.cam.posx * 64) + 64;
	y = (vars->map.cam.posy * 64) + 32 - (32 * a);
        ft_check_maplimites(vars, &x, &y);
	while (vars->map.box[y / 64][x / 64] == '0')
	{
		x = x + 64;
		y = y - (64 * a);
		ft_check_maplimites(vars, &x, &y);
	}
	xdm[i] = y % 64;
	tmp = pow((vars->map.cam.posx * 64) + 32 - x, 2) +
		pow((vars->map.cam.posy * 64) + 32 - y, 2);
	len = sqrt(tmp);
	return (len);
}

float	ft_nw_hor_inte(t_all *vars, float angle, int *xdm, int i)
{
	int	x;
	int	y;
	float	tmp;
	float	len;
	float	a;

	a = sin(angle) / cos(angle);
	if (a < 0)
		a = a * -1;
	printf("tan(angle) = %f \n", a);
	x = (vars->map.cam.posx * 64) - 64;
	y = (vars->map.cam.posy * 64) + 32 - (96 * a);
	ft_check_maplimites(vars, &x, &y);
	while (vars->map.box[y / 64][x / 64] == '0')
	{
		x = x - 64;
		y = y - (64 * a);
		ft_check_maplimites(vars, &x, &y);
	}
	printf(" hor_inte map[%d][%d] = %c \n", (int)(y / 64), (int)(x / 64), vars->map.box[y / 64][x / 64]);
	xdm[i] = y % 64;
	tmp = pow((vars->map.cam.posx * 64) + 32 - x, 2) +
		pow((vars->map.cam.posy * 64) + 32 - y, 2);
	len = sqrt(tmp);
	return (len);
}

float	ft_sw_hor_inte(t_all *vars, float angle, int *xdm, int i)
{
	int	x;
	int	y;
	float	tmp;
	float	len;
	float	a;

	a = sin(angle) / cos(angle);
	if (a < 0)
		a = a * -1;
	x = (vars->map.cam.posx * 64) - 64;
	y = (vars->map.cam.posy * 64) + 32 + (96 * a);
	ft_check_maplimites(vars, &x, &y);
	while (vars->map.box[y / 64][x / 64] == '0')
	{
		x = x - 64;
		y = y + (64 * a);
		ft_check_maplimites(vars, &x, &y);
	}
	xdm[i] = y % 64;
	tmp = pow((vars->map.cam.posx * 64) + 32 - x, 2) +
		pow((vars->map.cam.posy * 64) + 32 - y, 2);
	len = sqrt(tmp);
	return (len);
}

float	ft_se_hor_inte(t_all *vars, float angle, int *xdm, int i)
{
	int	x;
	int	y;
	float	tmp;
	float	len;
	float	a;

	a = sin(angle) / cos(angle);
	if (a < 0)
		a = a * -1;
	x = (vars->map.cam.posx * 64) + 64;
	y = (vars->map.cam.posy * 64) + 32 + (32 * a);
	ft_check_maplimites(vars, &x, &y);
	while (vars->map.box[y / 64][x / 64] == '0')
	{
		x = x + 64;
		y = y + (64 * a);
		ft_check_maplimites(vars, &x, &y);
	}
	xdm[i] = y % 64;
	tmp = pow((vars->map.cam.posx * 64) + 32 - x, 2) +
		pow((vars->map.cam.posy * 64) + 32 - y, 2);
	len = sqrt(tmp);
	return (len);
}

float	ft_hor_intersect(t_all *vars, float angle, int *xdm, int i)
{
	float	res;
	float	fov;
	float	a;

	fov = ft_dir_to_fov(vars->map.cam.dir);
	if (fov > angle)
		a = fov - angle;
	else
		a = angle - fov;
	res = 0;
	if (angle > 0 && angle < (M_PI / 2))
		res = ft_ne_hor_inte(vars, a, xdm, i);
	else if (angle > (M_PI / 2) && angle < M_PI)
		res = ft_nw_hor_inte(vars, a, xdm , i);
	else if (angle > M_PI && angle < (3 * M_PI / 2))
		res = ft_sw_hor_inte(vars, a, xdm , i);
	else
		res = ft_se_hor_inte(vars, a, xdm , i);
	return (res);
}
