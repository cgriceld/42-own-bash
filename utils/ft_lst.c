/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst     .c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:25:23 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/10 18:25:46 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

t_list	*ft_lstnew(void *content)
{
	t_list *i;

	i = (t_list *)malloc(sizeof(t_list));
	if (i != NULL)
	{
		(*i).content = content;
		(*i).next = NULL;
	}
	return (i);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del((*lst).content);
	free(lst);
}


void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *temp;

	if (!del || !lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}


void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list *temp;

	temp = NULL;
	temp = *(lst);
	if (!*(lst))
	{
		*(lst) = new;
		return ;
	}
	new->next = temp;
	*(lst) = new;
}
