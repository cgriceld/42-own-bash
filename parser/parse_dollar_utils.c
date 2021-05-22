/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:51:18 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 13:51:24 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	error_dollar(char **value, t_quo *quo, t_shell *shell)
{
	free(*value);
	error_quotes(&quo, &shell);
}
