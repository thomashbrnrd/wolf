/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 19:20:06 by maxisimo          #+#    #+#             */
/*   Updated: 2018/11/21 17:18:48 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static void	dda_init(t_app *app)
{
	app->deltadistx = fabs(1 / app->raydir_x);
	app->deltadisty = fabs(1 / app->raydir_y);
	if (app->raydir_x < 0)
	{
		app->stepx = -1;
		app->sidedistx = (app->rayposx - app->mapx) * app->deltadistx;
	}
	else
	{
		app->stepx = 1;
		app->sidedistx = (app->mapx + 1. - app->rayposx) * app->deltadistx;
	}
	if (app->raydir_y < 0)
	{
		app->stepy = -1;
		app->sidedisty = (app->rayposy - app->mapy) * app->deltadisty;
	}
	else
	{
		app->stepy = 1;
		app->sidedisty = (app->mapy + 1. - app->rayposy) * app->deltadisty;
	}
}

static void	dda(t_app *app)
{
	app->hit = 0;
	while (app->hit == 0)
	{
		if (app->sidedistx < app->sidedisty)
		{
			app->sidedistx += app->deltadistx;
			app->mapx += app->stepx;
			app->side = 0;
		}
		else
		{
			app->sidedisty += app->deltadisty;
			app->mapy += app->stepy;
			app->side = 1;
		}
		if (app->map[app->mapy][app->mapx] > 0)
			app->hit = 1;
	}
}

static void	raycasting_init(t_app *app, int x)
{
	app->camx = 2 * x / (double)WIN_W - 1;
	app->rayposx = app->pos.y;
	app->rayposy = app->pos.x;
	app->raydir_x = app->dir_x + app->plane_x * app->camx;
	app->raydir_y = app->dir_y + app->plane_y * app->camx;
	app->mapx = (int)app->rayposx;
	app->mapy = (int)app->rayposy;
	dda_init(app);
	dda(app);
	if (app->side == 0)
		app->dist_wall = (app->mapx - app->rayposx + (1 - app->stepx) / 2) /
			app->raydir_x;
	else
		app->dist_wall = (app->mapy - app->rayposy + (1 - app->stepy) / 2) /
			app->raydir_y;
}

void		ft_pthread(t_app *a)
{
	t_app		tab[4];
	pthread_t	t[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		ft_memcpy((void*)&tab[i], (void*)a, sizeof(t_app));
		tab[i].p.x = (WIN_W / 4) * i;
		tab[i].p.xx = (WIN_W / 4) * (i + 1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_create(&t[i], NULL, raycasting, &tab[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(t[i], NULL);
		i++;
	}
	mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
}

void		*raycasting(void *tab)
{
	t_app	a;

	a = *(t_app *)tab;
	while (a.p.x++ < a.p.xx)
	{
		raycasting_init(&a, a.p.x);
		a.lineheight = (int)(WIN_H / a.dist_wall);
		a.start = -a.lineheight / 2 + a.lookud + WIN_H / 2;
		a.end = a.lineheight / 2 + a.lookud + WIN_H / 2;
		if (a.start < 0)
			a.start = 0;
		if (a.end > WIN_H)
			a.end = WIN_H;
		a.wall_size = a.start - a.end;
		a.clr_intensity = (a.dist_wall < 1) ? 1 : 1 / a.dist_wall;
		draw_wall(a.p.x, a.start, a.end, &a);
	}
	return (tab);
}
