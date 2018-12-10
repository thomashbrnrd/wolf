/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:54:23 by thbernar          #+#    #+#             */
/*   Updated: 2018/12/08 15:43:43 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	sprites_load(t_app *a)
{
	bmp_loadfile(&a->sprites[2], "sprites/thomas.bmp");
	bmp_loadfile(&a->weapon.sprite, "sprites/ak47.bmp");
	a->sprites[2].p.x = 4.5;
	a->sprites[2].p.y = 1.5;
}

void	sprites_init(t_app *a, t_spr *s)
{
	s->spr_x = a->sprites[2].p.y - a->pos.y;
	s->spr_y = a->sprites[2].p.x - a->pos.x;
	s->invdet = 1.0 / (a->plane_x * a->dir_y - a->dir_x * a->plane_y);
	s->change_x = s->invdet * (a->dir_y * s->spr_x - a->dir_x * s->spr_y);
	s->change_y = s->invdet * (-a->plane_y * s->spr_x + a->plane_x * s->spr_y);
	s->screenx = (int)((WIN_W / 2) * (1 + s->change_x / s->change_y));
	s->height = abs((int)(WIN_H / (s->change_y)));
	s->start_y = -s->height / 2 + WIN_H / 2;
	s->start_y = (s->start_y < 0) ? 0 : s->start_y;
	s->end_y = s->height / 2 + WIN_H / 2;
	s->end_y = (s->end_y >= WIN_H) ? WIN_H - 1 : s->end_y;
	s->width = abs((int)(WIN_H / (s->change_y)));
	s->start_x = -s->width / 2 + s->screenx;
	s->start_x = (s->start_x < 0) ? 0 : s->start_x;
	s->end_x = s->width / 2 + s->screenx;
	s->end_x = (s->end_x >= WIN_W) ? WIN_W - 1 : s->end_x;
	s->stripe = s->start_x;
}

void	sprites_draw(t_app *a)
{
	t_color		color;
	t_spr		s;

	sprites_init(a, &s);
	while (s.stripe < s.end_x)
	{
		s.texx = (int)(256 * (s.stripe - (-s.width / 2 + s.screenx))
				* a->sprites[2].width / s.width) / 256;
		if (s.change_y > 0 && s.stripe > 0 && s.stripe < WIN_W && s.change_y < a->zbuffer[s.stripe])
		{
			s.y = s.start_y;
			while (s.y < s.end_y)
			{
				s.d = (s.y) * 256 - WIN_H * 128 + s.height * 128;
				s.texy = ((s.d * a->sprites[2].height) / s.height) / 256;
				color = get_pixel_color(&a->sprites[2], s.texx, s.texy);
				s.clr = ft_rgb_to_hex(color);
				ft_memcpy(a->img_data + 4 * WIN_W * s.y + s.stripe * 4,
						&s.clr, sizeof(int));
				s.y++;
			}
		}
		s.stripe++;
	}
}
