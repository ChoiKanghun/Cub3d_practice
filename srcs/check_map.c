/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchoi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:10:58 by kchoi             #+#    #+#             */
/*   Updated: 2020/10/27 17:10:59 by kchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_left(t_info *info, int i, int j)
{
	while (info->map[i][j] == ' ')
		j++;
	if (info->map[i][j] != '1')
		return (exit_error(info));
	return (1);
}

int	check_map_top(t_info *info)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(info->map[0]))
	{
		if (!(info->map[0][i] == ' ' || info->map[0][i] == '1'))
			return (exit_error(info));
		i++;
	}
	return (1);
}

int	check_map_right(t_info *info, int i, int j)
{
	if (info->map[i][j - 1] != '1')
		return (exit_error(info));
	return (1);
}

int	check_map_bottom(t_info *info, int i)
{
	int	j;

	j = 0;
	while (j < (int)ft_strlen(info->map[i]))
	{
		if (!(info->map[i][j] == ' ' || info->map[i][j] == '1'))
			return (exit_error(info));
		j++;
	}
	return (1);
}

int	check_map_middle(t_info *info, int i, int j)
{
	if (i > 0 && i < info->map_height - 1)
	{
		if (info->map[i - 1][j] == ' ' || info->map[i + 1][j] == ' ')
			if (info->map[i][j] != ' ' && info->map[i][j] != '1')
				return (exit_error(info));
	}
	if (j > 0 && j < info->map_width)
	{
		if (info->map[i][j - 1] == ' ' || info->map[i][j + 1] == ' ')
			if (info->map[i][j] != ' ' && info->map[i][j] != '1')
				return (exit_error(info));
	}
	return (1);
}
