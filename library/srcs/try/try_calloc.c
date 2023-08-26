/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_calloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:27:58 by tterao            #+#    #+#             */
/*   Updated: 2023/08/26 15:50:39 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include "stdlib.h"
#include <limits.h>
#include <stdint.h>

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*casted_s;
	size_t			i;

	casted_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		casted_s[i] = '\0';
		i++;
	}
}

void	*try_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count != 0 && (SIZE_MAX / count) < size)
		return (try_calloc(0, 0));
	ptr = try_malloc(count * size);
	ft_bzero(ptr, count * size);
	return (ptr);
}
