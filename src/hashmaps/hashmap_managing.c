/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_managing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:38:05 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/19 18:56:53 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft.h"

t_hashmap	*hashmap_new(int power, double chargefactor,
				void (*val_free)(void *), unsigned long (*hash)(void *key))
{
	t_hashmap	*result;

	result = ft_calloc(1, sizeof(t_hashmap));
	if (!result)
		return (NULL);
	result->size = 1 << power;
	result->table = ft_calloc(result->size + 1, sizeof(t_hash_entry));
	if (!result->table)
	{
		free(result);
		return (NULL);
	}
	result->count = 0;
	result->charge_factor = chargefactor;
	result->hash = hash;
	result->val_free = val_free;
	result->resize = hashmap_resize;
	result->add = hashmap_add;
	result->get = hashmap_search;
	result->iter = hashmap_iterate;
	result->free = hashmap_free;
	result->remove = hashmap_remove;
	return (result);
}

void	hashmap_free(t_hashmap *self, bool content)
{
	if (!self)
		return ;
	if (content)
		hashmap_free_content(self);
	if (self->table)
		free(self->table);
	free(self);
}

void	hashmap_free_content(t_hashmap *self)
{
	size_t	index;

	if (self->table == NULL)
		return ;
	index = 0;
	while (index < self->size)
	{
		if (self->table[index].status == OCCUPIED)
			self->val_free(self->table[index].value);
		index++;
	}
}
