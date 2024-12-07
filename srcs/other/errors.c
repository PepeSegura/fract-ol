/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:59:08 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/07 20:13:36 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_perror(char *msg)
{
	ft_dprintf(2, "Error:\n");
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_error(char *str, bool flag)
{
	if (flag == true)
		ft_dprintf(2, "Error:\n\t%s\n", str);
	else
		ft_dprintf(2, "Usage:\n\t%s\n", str);
	exit(EXIT_FAILURE);
}
