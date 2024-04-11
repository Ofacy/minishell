/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:19:15 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/13 13:07:11 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*ft_clear(t_list *list, void *result, void (*del)(void *))
{
	if (result)
		free(result);
	ft_lstclear(&list, del);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*start;
	void	*result;

	start = 0;
	while (lst)
	{
		result = f(lst->content);
		if (!result)
			return (ft_clear(start, 0, del));
		new = ft_lstnew(result);
		if (!new)
			return (ft_clear(start, result, del));
		ft_lstadd_back(&start, new);
		lst = lst->next;
	}
	return (start);
}
