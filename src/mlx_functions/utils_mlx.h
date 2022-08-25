/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:43:06 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/25 00:22:50 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_MLX_H
# define UTILS_MLX_H

typedef struct s_img
{
	void	*img;
	int		endian;
	int		line_lenght;
	int		bpp;
	char	*addr;
}	t_img;

struct s_data
{
	void	*mlx;
	void	*window;
	t_img	dimg;
};

void	mlx_generate(void *pg);
#endif