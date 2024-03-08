/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:26:27 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/08 14:07:57 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*expander_join(t_token *t1, t_token *t2)
{
	char	*str;
	size_t	str_len;
	size_t	str2_len;
	
	str_len = t1->txt_size;
	str2_len = t2->txt_size;
	str = malloc((str_len + str2_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, t1->txt, str_len + 1);
	ft_strlcat(str, t2->txt, str_len + str2_len + 1);
	t1->txt_size = str_len + str2_len + 1;
	free_token(t1);
	free_token(t2);
	t1->is_txt_heap = true;
	return (str);
}
