/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:07:46 by wmillett          #+#    #+#             */
/*   Updated: 2024/01/03 15:07:47 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_color_code(enum e_id id, int n, int i)
{
	t_cube	*cube;

	cube = get_cube();
	if (id == C)
	{
		if (i == 0)
			cube->c_red = n;
		if (i == 1)
			cube->c_green = n;
		if (i == 2)
			cube->c_blue = n;
	}
	if (id == F)
	{
		if (i == 0)
			cube->f_red = n;
		if (i == 1)
			cube->f_green = n;
		if (i == 2)
			cube->f_blue = n;
	}
}

void	split_color_code(char *code, enum e_id id)
{
	char	**split;
	int		i;
	int		n;

	n = 0;
	i = 0;
	split = gc_split(code, ',');
	while (split[i])
	{
		n = ft_atoi(split[i]);
		if (n > 255)
			ft_error(MORE_255);
		add_color_code(id, n, i);
		i++;
	}
	if (i != 3)
		ft_error(BAD_COLOR);
}

void	parse_color_code(char *code, enum e_id id)
{
	static int	c_count = 0;
	static int	f_count = 0;
	int			i;

	i = 0;
	if (id == C)
		c_count++;
	if (id == F)
		f_count++;
	if (c_count > 1 || f_count > 1)
		ft_error(EXISTS);
	while (code[i] && ft_isdigit(code[i]) == true)
		i++;
	if (code[i] == ',')
		i++;
	while (code[i] && ft_isdigit(code[i]) == true)
		i++;
	if (code[i] == ',')
		i++;
	while (code[i] && ft_isdigit(code[i]) == true)
		i++;
	if (code[i])
		ft_error(BAD_COLOR);
	split_color_code(code, id);
}
