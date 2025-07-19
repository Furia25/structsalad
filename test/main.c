/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:40:09 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/19 19:04:57 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include <stdio.h>
#include <string.h>
void print_entry(unsigned long key, void *val)
{
	(void)key;
	printf(" -> %s\n", (char *)val);
}

void free_str(void *val)
{
	free(val);
}

int	main(void)
{
	t_hashmap *map;

	map = hashmap_new(8, 0.8, free_str, (unsigned long (*)(void *))murmur3_hash);
	if (!map)
	{
		fprintf(stderr, "Erreur d'allocation de la hashmap\n");
		return (EXIT_FAILURE);
	}

	// INSERTIONS
	map->add(map, "bonjour", strdup("zizi"));
	map->add(map, "caca", strdup("pipi"));
	map->add(map, "chien", strdup("ouaf"));
	map->add(map, "chat", strdup("miaou"));
	map->add(map, "oiseau", strdup("cui-cui"));
	map->add(map, "bovin", strdup("meuh"));
	map->add(map, "cheval", strdup("hiiiii"));
	map->add(map, "requin", strdup("shaaark"));
	map->add(map, "canard", strdup("coincoin"));
	map->add(map, "licorne", strdup("magique"));
	map->add(map, "dragon", strdup("brûle"));
	map->add(map, "poule", strdup("cot-cot"));
	map->add(map, "pigeon", strdup("roucoule"));
	map->add(map, "tortue", strdup("lente"));
	map->add(map, "lama", strdup("crachat"));

	// ACCÈS
	char *val1 = (char *)map->get(map, "bonjour")->value;
	char *val2 = (char *)map->get(map, "chat")->value;
	char *val3 = (char *)map->get(map, "dragon")->value;

	printf("bonjour = %s\n", val1);
	printf("chat    = %s\n", val2);
	printf("dragon  = %s\n", val3);

	// ÉCRASEMENT DE VALEUR
	map->add(map, "chat", strdup("ronron")); // écrase "miaou"
	char *val_chat = (char *)map->get(map, "chat")->value;
	printf("chat aprés écrasement = %s\n", val_chat);

	// SUPPRESSION
	map->remove(map, "caca");
	map->remove(map, "chien");
	map->remove(map, "cheval");

	t_hash_entry *deleted1 = map->get(map, "caca");
	t_hash_entry *deleted2 = map->get(map, "chien");
	t_hash_entry *deleted3 = map->get(map, "cheval");

	if (!deleted1) printf("caca supprimé\n");
	if (!deleted2) printf("chien supprimé\n");
	if (!deleted3) printf("cheval supprimé\n");

	// AJOUT APRÈS SUPPRESSION
	map->add(map, "chien", strdup("wouf again"));

	// ITERATION
	printf("\n--- Contenu complet de la map ---\n");
	map->iter(map, print_entry);

	// TEST DE REMPLACEMENT AVEC LA MÊME CLÉ
	map->add(map, "poule", strdup("œuf"));
	printf("\nAprès remplacement de 'poule' :\n");
	map->iter(map, print_entry);

	// LIBÉRATION
	map->free(map, true);

	return (EXIT_SUCCESS);
}