/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_methods.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:18:50 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/19 17:36:49 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include <stdint.h>

static void	swap(t_hash_entry *a, t_hash_entry *b)
{
	t_hash_entry	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	hashmap_resize(t_hashmap *self, size_t new_size)
{
	t_hash_entry	*new_table;
	t_hash_entry	*old_table;
	size_t			old_size;
	size_t			index;

	if (new_size == 0 || new_size > SIZE_MAX / 2)
		return (0);
	new_table = ft_calloc(new_size, sizeof(t_hash_entry));
	if (!new_table)
		return (0);
	old_table = self->table;
	old_size = self->size;
	self->table = new_table;
	self->size = new_size;
	self->count = 0;
	index = 0;
	while (index < old_size)
	{
		if (old_table[index].status == OCCUPIED)
			hashmap_insert(self, old_table[index].key, old_table[index].value);
		index++;
	}
	free(old_table);
	return (1);
}

static void	prcs(unsigned long key, size_t i,
				t_hash_entry last, t_hashmap *map)
{
	void	*old_value;

	while (1)
	{
		if (map->table[i].status == EMPTY || map->table[i].status == TOMBSTONE)
		{
			if (map->table[i].status == TOMBSTONE && map->table[i].value)
				map->val_free(map->table[i].value);
			map->table[i] = last;
			map->count++;
			return ;
		}
		if (map->table[i].status == OCCUPIED && map->table[i].key == key)
		{
			old_value = map->table[i].value;
			map->val_free(old_value);
			map->table[i] = last;
			return ;
		}
		if (last.probe_distance > map->table[i].probe_distance)
			swap(&last, &map->table[i]);
		last.probe_distance++;
		i = (i + 1) & (map->size - 1);
	}
}

int	hashmap_insert(t_hashmap *self, unsigned long key, void *value)
{
	size_t			pos;
	t_hash_entry	last;

	if (!self)
		return (0);
	if (!value)
		return (0);
	if ((double)(self->count + 1) / self->size >= self->charge_factor)
		if (!self->resize(self, self->size << 1))
			return (0);
	pos = key & (self->size - 1);
	last = (t_hash_entry){.key = key, .value = value, \
		.status = OCCUPIED, .probe_distance = 0};
	prcs(key, pos, last, self);
	return (1);
}

t_hash_entry	*hashmap_search(t_hashmap *self, void *key)
{
	unsigned long	key_v;
	size_t			pos;
	size_t			dist;

	key_v = self->hash(key);
	dist = 0;
	pos = key_v & (self->size - 1);
	while (self->table[pos].status != EMPTY)
	{
		if (self->table[pos].status != TOMBSTONE)
			if (self->table[pos].key == key_v)
				return (&self->table[pos]);
		if (dist > self->table[pos].probe_distance)
			return (NULL);
		pos = (pos + 1) & (self->size - 1);
		dist++;
	}
	return (NULL);
}
