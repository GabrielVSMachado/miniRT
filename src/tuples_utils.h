/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:19:30 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/04 22:27:56 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLES_UTILS_H
# define TUPLES_UTILS_H

const float	*tuple(const float x, const float y, const float z,
				const float type);
const float	*point(const float x, const float y, const float z);
const float	*vector(const float x, const float y, const float z);
const float	*add_tuples(const float *t1, const float *t2);
#endif
