#include "parser.h"
#include "utils.h"

t_point	parse_token(char *token, int x, int y)
{
	t_point	point;
	char	*comma;

	point.x = x;
	point.y = y;
	point.color = -1; // default no color
	comma = ft_strchr(token, ',');
	if (comma)
	{
		*comma = '\0';
		point.z = ft_atoi(token);
		// parse hex color
		if (ft_strncmp(comma + 1, "0x", 2) == 0 || ft_strncmp(comma + 1, "0X",
				2) == 0)
			point.color = ft_atoi_base(comma + 3, 16);
		*comma = ',';
	}
	else
		point.z = ft_atoi(token);
	return (point);
}
