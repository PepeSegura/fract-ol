/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:59:08 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/06 20:27:39 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_perror(char *msg)
{
	ft_dprintf(2, "Error:\n\t");
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_error(char *str)
{
	ft_dprintf(2, "Error:\n\t%s\n", str);
	exit(EXIT_FAILURE);
}
