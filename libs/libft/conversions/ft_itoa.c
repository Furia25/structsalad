/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:32:30 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/24 16:11:46 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static long	ft_abs(int n)
{
	long	nb;

	nb = (long) n;
	if (nb < 0)
		return (-nb);
	return (nb);
}

char	*ft_itoa(int n)
{
	size_t	index;
	size_t	size;
	char	*result;
	long	nb;
	int		sign;

	nb = ft_abs(n);
	sign = n < 0;
	size = (ft_intlen(nb) + sign + 1);
	result = (char *)ft_calloc(size, sizeof(char));
	if (!result)
		return (NULL);
	index = size - 1;
	if (nb == 0)
		result[--index] = '0';
	while (nb != 0)
	{
		result[--index] = '0' + nb % 10;
		nb = nb / 10;
	}
	if (sign)
		result[--index] = '-';
	return (result);
}
