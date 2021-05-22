#include "../minibash.h"

t_list	*put_to_sort_list(char *content, t_list *start, \
t_list *prev, t_list *corrent)
{
	if (!start)
		start = ft_lstnew(content);
	else if (ft_strncmp(start->content, content, ft_strlen(content + 1)) >= 0)
		ft_lstadd_front(&start, ft_lstnew(content));
	else
	{
		corrent = start;
		while (corrent->next && \
		ft_strncmp(corrent->content, content, ft_strlen(content + 1)) < 0)
		{
			prev = corrent;
			corrent = corrent->next;
		}
		if (corrent->next)
		{
			prev->next = ft_lstnew(content);
			prev = prev->next;
			prev->next = corrent;
		}
		else
			corrent->next = ft_lstnew(content);
	}
	return (start);
}
