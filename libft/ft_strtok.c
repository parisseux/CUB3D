/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:19:58 by grohr             #+#    #+#             */
/*   Updated: 2025/07/02 14:27:05 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*save;
	char		*start;

	if (str)
		save = str;
	if (!save || *save == '\0')
		return (NULL);
	while (*save && ft_strchr(delim, *save))
		save++;
	if (*save == '\0')
		return (NULL);
	start = save;
	while (*save && !ft_strchr(delim, *save))
		save++;
	if (*save)
	{
		*save = '\0';
		save++;
	}
	return (start);
}
