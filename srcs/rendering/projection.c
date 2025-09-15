#include "fdf.h"
#include "math.h"

// void	projection(t_point_coordinate *point)
// {
// 	int previous_x;
// 	int previous_y;
// 	double angle_x;
// 	double angle_y;
// 	angle_x = 0.523599;
// 	angle_y = 0.523599;

// 	previous_x = point->x;
// 	previous_y = point->y;

// 	point->x = (previous_x - previous_y) * cos(angle_x);
// 	point->y = (previous_x + previous_y) * sin(angle_y) - point->z;
// }

#include "fdf.h"
#include <math.h>

void	projection(t_point_coordinate *point)
{
	int previous_x;
	int previous_y;
	double angle_x;
	double angle_y;

	// Bu açılarla oynamaya devam edebilirsiniz.
	angle_x = 0.523599;
	angle_y = 0.523599; // İsterseniz bunu tekrar 0.3 yapabilirsiniz.

	previous_x = point->x;
	previous_y = point->y;
	point->x = (previous_x - previous_y) * cos(angle_x);
	point->y = (previous_x + previous_y) * sin(angle_y) - point->z;
}