/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_collisions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 13:56:36 by thbernar          #+#    #+#             */
/*   Updated: 2018/10/16 14:11:58 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_is_againstwall(t_app *app)
{
	if (app->map[(int)app->pos.x][(int)app->pos.y] == 0)
		return (0);
	else
		return (1);
}