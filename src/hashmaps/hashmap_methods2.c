/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_methods2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:10:14 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/19 17:38:06 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

int	hashmap_add(t_hashmap *self, void *key, void *value)
{
	unsigned long	key_v;

	key_v = self->hash(key);
	hashmap_insert(self, key_v, value);
	return (1);
}

void	hashmap_remove(t_hashmap *self, void *key)
{
	t_hash_entry	*entry;

	entry = self->get(self, key);
	if (entry != NULL)
	{
		entry->status = TOMBSTONE;
		if (entry->value)
		{
			self->val_free(entry->value);
			entry->value = NULL;
			self->count -= 1;
		}
	}
}

void	hashmap_iterate(t_hashmap *self, 
			void (*f) (unsigned long key_v, void *value))
{
	size_t			index;
	size_t			actual_count;
	t_hash_entry	entry;

	index = 0;
	actual_count = 0;
	while (index < self->size && actual_count < self->count)
	{
		entry = self->table[index];
		if (entry.status == OCCUPIED)
		{
			f(entry.key, entry.value);
			actual_count++;
		}
		index++;
	}
}
