/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:54:23 by thbernar          #+#    #+#             */
/*   Updated: 2018/10/22 14:03:01 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf3d.h"

static int	ft_close(t_app *app)
{
	free(app->fname);
	free(app->map);
	free(app);
	exit(0);
	return (0);
}

static int	ft_key_press(int key, t_app *app)
{
	if (key == 13)
		app->mv_up = 1;
	else if (key == 1)
		app->mv_down = 1;
	else if (key == 2)
		app->mv_right = 1;
	else if (key == 0)
		app->mv_left = 1;
	else if (key == 123)
		app->rt_left = 1;
	else if (key == 124)
		app->rt_right = 1;
	else if (key == 53)
		exit(0);
	return (0);
}

static int	ft_key_release(int key, t_app *app)
{
	if (key == 13)
		app->mv_up = 0;
	else if (key == 1)
		app->mv_down = 0;
	else if (key == 2)
		app->mv_right = 0;
	else if (key == 0)
		app->mv_left = 0;
	else if (key == 123)
		app->rt_left = 0;
	else if (key == 124)
		app->rt_right = 0;
	return (0);
}

static void	ft_rotate(t_app *a)
{
	if (a->rt_right == 1)
	{
		a->oldDirX = a->dirX;
		a->dirX = a->dirX * cos(-0.05) - a->dirY * sin(-0.05);
		a->dirY = a->oldDirX * sin(-0.05) + a->dirY * cos(-0.05);
		a->oldPlaneX = a->planeX;
		a->planeX = a->planeX * cos(-0.05) - a->planeY * sin(-0.05);
		a->planeY = a->oldPlaneX * sin(-0.05) + a->planeY * cos(-0.05);
	}
	if (a->rt_left == 1)
	{
		a->oldDirX = a->dirX;
		a->dirX = a->dirX * cos(0.05) - a->dirY * sin(0.05);
		a->dirY = a->oldDirX * sin(0.05) + a->dirY * cos(0.05);
		a->oldPlaneX = a->planeX;
		a->planeX = a->planeX * cos(0.05) - a->planeY * sin(0.05);
		a->planeY = a->oldPlaneX * sin(0.05) + a->planeY * cos(0.05);
	}
}

static int	ft_move(t_app *a)
{
	if (a->mv_up == 1)
	{
		if (a->map[(int)(a->pos.x + a->dirX * a->ms)][(int)(a->pos.y)] == 0)
			a->pos.y += a->dirX * a->ms;
		if (a->map[(int)(a->pos.x)][(int)(a->pos.y + a->dirY * a->ms)] == 0)
			a->pos.x += a->dirY * a->ms;
	}
	if (a->mv_down == 1)
	{
		if (a->map[(int)(a->pos.x - a->dirX * a->ms)][(int)(a->pos.y)] == 0)
			a->pos.y -= a->dirX * a->ms;
		if (a->map[(int)(a->pos.x)][(int)(a->pos.y - a->dirY * a->ms)] == 0)
			a->pos.x -= a->dirY * a->ms;
	}
	if (a->mv_left == 1)
	{
		if (a->map[(int)(a->pos.x + a->dirX * a->ms)][(int)(a->pos.y)] == 0)
			a->pos.x += a->dirX * a->ms;
		if (a->map[(int)(a->pos.x)][(int)(a->pos.y + a->dirY * a->ms)] == 0)
			a->pos.y += a->dirY * a->ms;
	}
	if (a->mv_right == 1)
	{
		if (a->map[(int)(a->pos.x - a->dirX * a->ms)][(int)(a->pos.y)] == 0)
			a->pos.x -= a->dirX * a->ms;
		if (a->map[(int)(a->pos.x)][(int)(a->pos.y - a->dirY * a->ms)] == 0)
			a->pos.y -= a->dirY * a->ms;
	}
	ft_rotate(a);
	raycasting(a);
	//draw_minimap(a, 0, 0);
	return (0);
}

int			main(int ac, char **av)
{
	t_app	app;

	(void)ac;
	app.fname = av[1];
	ft_app_init(&app);
	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, app.winsize.x, app.winsize.y, "Wolf3D");
	raycasting(&app);
	mlx_hook(app.win, 2, (1L << 0), ft_key_press, &app);
	mlx_hook(app.win, 3, (1L << 1), ft_key_release, &app);
	mlx_hook(app.win, 17, (1L << 17), ft_close, &app);
	mlx_loop_hook(app.mlx, ft_move, &app);
	mlx_loop(app.mlx);
	return (0);
}
