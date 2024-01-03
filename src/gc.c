/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:07:33 by wmillett          #+#    #+#             */
/*   Updated: 2024/01/03 15:07:34 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mblock	*garbage_collector(void)
{
	static t_mblock	head = {NULL, NULL};

	return (&head);
}

void	*gc_malloc(size_t size)
{
	t_mblock	*new_mb;

	new_mb = malloc(sizeof(t_mblock) * 1);
	if (!new_mb)
	{
		gc_free_all();
		ft_putstr_fd(MALLOC_ERROR, 2);
		exit(1);
	}
	new_mb->next_mb = garbage_collector()->next_mb;
	garbage_collector()->next_mb = new_mb;
	new_mb->address = malloc(size);
	if (!new_mb->address)
	{
		gc_free_all();
		ft_putstr_fd(MALLOC_ERROR, 2);
		exit(1);
	}
	return (new_mb->address);
}

void	gc_free_all(void)
{
	t_mblock	*gc_ptr;
	t_mblock	*ptr_copy;
	t_cube		*cube;

	cube = get_cube();
	gc_ptr = garbage_collector()->next_mb;
	while (gc_ptr)
	{
		if (gc_ptr->address)
			free(gc_ptr->address);
		ptr_copy = gc_ptr;
		gc_ptr = gc_ptr->next_mb;
		free(ptr_copy);
	}
	garbage_collector()->next_mb = NULL;
	close(cube->fd);
	clear_mlx(cube->cubmlx);
}

void	gc_free(void *address)
{
	t_mblock	*gc_ptr;
	t_mblock	*ptr_copy;

	gc_ptr = garbage_collector()->next_mb;
	ptr_copy = garbage_collector();
	while (gc_ptr)
	{
		if (gc_ptr->address == address)
		{
			ptr_copy->next_mb = gc_ptr->next_mb;
			if (gc_ptr->address)
				free(gc_ptr->address);
			free(gc_ptr);
			return ;
		}
		ptr_copy = gc_ptr;
		gc_ptr = gc_ptr->next_mb;
	}
}
