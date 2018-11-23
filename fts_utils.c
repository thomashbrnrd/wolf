/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:04:48 by thbernar          #+#    #+#             */
/*   Updated: 2018/11/23 17:29:11 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_rgb_to_hex(t_color c)
{
	return (((c.r & 0xff) << 16) + ((c.g & 0xff) << 8) + (c.b & 0xff));
}

void	ft_put_pxl_to_img(t_app *a, t_color c, int x, int y)
{
	int hex_clr;

	hex_clr = ft_rgb_to_hex(c);
	ft_memcpy(a->img_data + 4 * WIN_W * y + x * 4, &hex_clr, sizeof(int));
}

void	ft_put_circle_to_img(t_app *a, t_circle *c)
{
	put_pxl_to_img(a, c->xc + c->x, c->yc - c->y, 0xFF0000);
	put_pxl_to_img(a, c->xc - c->x, c->yc - c->y, 0xFF0000);
	put_pxl_to_img(a, c->xc + c->x, c->yc + c->y, 0xFF0000);
	put_pxl_to_img(a, c->xc - c->x, c->yc + c->y, 0xFF0000);
	put_pxl_to_img(a, c->xc + c->y, c->yc - c->x, 0xFF0000);
	put_pxl_to_img(a, c->xc - c->y, c->yc - c->x, 0xFF0000);
	put_pxl_to_img(a, c->xc + c->y, c->yc + c->x, 0xFF0000);
	put_pxl_to_img(a, c->xc - c->y, c->yc + c->x, 0xFF0000);
	if (c->d > 0)
	{
		c->y--;
		c->d -= 8 * c->y;
	}
	c->x++;
	c->d = c->d + 8 * c->x + 4;
}

void	ft_import_textures(t_app *a)
{
	//printf("1\n");
	bmp_loadfile(&a->textures[0], "textures/earth.bmp");
	//exit(0);
	//printf("2\n");
	bmp_loadfile(&a->textures[1], "textures/greystone.bmp");
	//printf("3\n");
	bmp_loadfile(&a->textures[2], "textures/redbrick.bmp");
	//printf("4\n");
	bmp_loadfile(&a->textures[3], "textures/wood.bmp");
	//printf("5\n");
	bmp_loadfile(&a->textures[4], "textures/glass.bmp");
	//printf("6\n");
	bmp_loadfile(&a->textures[5], "textures/mossy.bmp");
	//printf("7\n");
	bmp_loadfile(&a->textures[6], "textures/colorstone.bmp");
	//printf("8\n");
	bmp_loadfile(&a->textures[7], "textures/nebula.bmp");
	//printf("9\n");
	//bmp_loadfile(&a->textures[8], "textures/death.bmp");
	//printf("10\n");
}

void	ft_put_bmp_to_img(t_app *a, t_bmp bmp, int x, int y)
{
	t_coord p;
	t_color	c;

	p.x = 0;
	p.y = 0;
	while (p.y < bmp.height * bmp.scale)
	{
		p.x = 0;
		while (p.x < bmp.width * bmp.scale)
		{
			c = get_pixel_color(&bmp, p.x / bmp.scale, p.y / bmp.scale);
			ft_put_pxl_to_img(a, c, x + p.x, y + p.y);
			p.x++;
		}
		p.y++;
	}
}
