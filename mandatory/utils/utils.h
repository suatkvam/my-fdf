/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 14:17:04 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef FLT_EPSILON
#  define FLT_EPSILON 1.19209290e-07F
# endif

typedef struct s_angle_calc
{
	float	x1;
	float	x2;
	float	y1;
	float	y2;
	float	angle;
	float	dot;
	float	mag;
	float	cos_theta;
	float	angle_rad;
}			t_angle_calc;

int			ft_atoi_base(const char *str, int str_base);
void		ft_free_split(char **split);

float		get_projection_axes_angle_deg(void);
float		get_isometric_axes_angle_deg(void);

#endif
