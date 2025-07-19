/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:45:28 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/19 16:45:31 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long	murmur3_hash(char *str)
{
	unsigned long	hash;
	unsigned long	c;
	int				i;

	hash = 0x811c9dc5;
	i = 0;
	while (str[i] != '\0')
	{
		c = (unsigned long)str[i];
		hash ^= c;
		hash *= 0x5bd1e995;
		hash ^= hash >> 15;
		i++;
	}
	return (hash);
}
