/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:04:48 by thbernar          #+#    #+#             */
/*   Updated: 2018/10/30 12:25:58 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_close(t_app *app)
{
	free(app->map);
	exit(0);
	return (0);
}

void	ft_error(char *s)
{
	ft_putstr(s);
	exit(-1);
}

int		ft_rgb_to_hex(t_color c)
{
	return (((c.r & 0xff) << 16) + ((c.g & 0xff) << 8) + (c.b & 0xff));
}

void	ft_free_strsplit(char **array)
{
	int i;

	i = 0;
	while (array	[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_put_pxl_to_img(t_app *a, t_color c, int x, int y)
{
	int hex_clr;

	hex_clr = ft_rgb_to_hex(c);
	ft_memcpy(a->img_data + 4 * WIN_W * y + x * 4, &hex_clr, sizeof(int));
}
