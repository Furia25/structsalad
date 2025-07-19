/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:20:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/19 18:49:15 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>

# define HASHMAP_POWER	8
# define HASHMAP_CHARGEFACTOR	0.8

typedef enum e_hash_status
{
	EMPTY,
	TOMBSTONE,
	OCCUPIED
}	t_hash_status;

typedef struct s_hash_entry
{
	unsigned long	key;
	void			*value;
	t_hash_status	status;
	size_t			probe_distance;
}	t_hash_entry;


typedef struct s_hashmap t_hashmap;
struct s_hashmap
{
	t_hash_entry	*table;
	unsigned long	temp_key;
	size_t			size;
	size_t			count;
	double			charge_factor;
	void			(*val_free)(void *val);
	unsigned long	(*hash)(void *key);
	int				(*resize)(t_hashmap *self, size_t new_size);
	int				(*add)(t_hashmap *self, void *key, void *value);
	t_hash_entry	*(*get)(t_hashmap *self, void *key);
	void			(*free)(t_hashmap *self, bool content);
	void			(*iter)(t_hashmap *self, void (*f)(unsigned long key, void *val));
	void			(*remove)(t_hashmap *self, void *key);
};

unsigned long		murmur3_hash(char *str);

t_hashmap			*hashmap_new(int power,
						double chargefactor,
						void (*val_free)(void *),
						unsigned long (*hash)(void *key));

void				hashmap_free(t_hashmap *self, bool content);
void				hashmap_free_content(t_hashmap *self);
void				hashmap_remove(t_hashmap *self, void *key);
int					hashmap_insert(t_hashmap *self,
						unsigned long key, void *value);
t_hash_entry		*hashmap_search(t_hashmap *self, void *key);
int					hashmap_resize(t_hashmap *self, size_t new_size);
int					hashmap_add(t_hashmap *self, void *key, void *value);
void				hashmap_iterate(t_hashmap *self,
						void (*f) (unsigned long key_v, void *value));

#endif