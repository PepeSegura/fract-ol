/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:13:50 by psegura-          #+#    #+#             */
/*   Updated: 2023/05/20 12:31:28 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = ft_len_matrix(matrix);
	while (--i >= 0)
		free(matrix[i]);
	free(matrix);
}
