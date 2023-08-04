/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:52:52 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/04 15:55:49 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "library.h"

static char	*ft_substred(const char *s, unsigned int start, size_t end)
{
	char	*res;
	size_t	i;

	res = (char *)malloc(sizeof(char) * ((end - start) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i + start < end)
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t end)
{
	size_t	s_len;
	// size_t	diff_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if ((size_t) start >= s_len || end == 0)
		return (try_strdup(""));
	// diff_len = s_len - start;
	// if (diff_len <= end)
	// 	return (ft_substred(s, start, diff_len));
	return (ft_substred(s, start, end));
}

// #include "stdio.h"
// int main(void)
// {
// 	char str[] = "abcdef";
// 	char s[] = "libft-tokyo-tester";
// 	printf("ft_substr()   %s\n", ft_substr(s, 10, 100));
// 	printf("s   %s\n", s + 10);
// 	printf("ft_substr()   %s\n", ft_substr(s, 10, 5));
// 	printf("ft_substr()   %s\n", ft_substr(s, 15, 5));
// 	printf("ft_substr()   %s\n", ft_substr(str, 5, 0));
// 	printf("ft_substr()   %s\n", ft_substr(str, 5, 10));
// 	printf("ft_substr()   %s\n", ft_substr(str, 6, 10));
// 	printf("ft_substr()   %s\n", ft_substr(str, 0, 10));
// 	printf("ft_substr()   %s\n", ft_substr(str, 2, 10));
// 	printf("ft_substr()   %s\n", ft_substr(str, 0, 100));
// 	return (0);
// }