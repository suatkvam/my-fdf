/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 17:58:27 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_YELLOW 0xFFFF00
# define COLOR_CYAN 0x00FFFF
# define COLOR_MAGENTA 0xFF00FF

# define ANSI_COLOR_RESET "\033[0m"
# define ANSI_COLOR_BOLD "\033[1m"
# define ANSI_COLOR_RED "\033[31m"
# define ANSI_COLOR_GREEN "\033[32m"
# define ANSI_COLOR_YELLOW "\033[33m"
# define ANSI_COLOR_BLUE "\033[34m"
# define ANSI_COLOR_MAGENTA "\033[35m"
# define ANSI_COLOR_CYAN "\033[36m"
# define ANSI_COLOR_WHITE "\033[37m"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

int		color_blend(int start_color, int end_color, double t);

#endif
