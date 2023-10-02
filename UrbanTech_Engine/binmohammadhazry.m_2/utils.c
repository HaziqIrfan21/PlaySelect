#include <math.h>
#include "cprocessing.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	

	if (CP_Input_MouseClicked() && (click_x > area_center_x - area_width/2) && (click_x < area_center_x +area_width/2) && (click_y > area_center_y -area_height/2) && (click_y < area_center_y + area_height / 2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
	
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	//float distance = Distance(click_x, click_y, circle_center_x, circle_center_y);
	
	if (CP_Input_MouseClicked() && (CP_Math_Distance(circle_center_x, circle_center_y,click_x,click_y) < diameter / 2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

float Distance(float click_x, float click_y, float circle_center_x, float circle_center_y)
{
	float distance = 0.0f;

	distance = sqrt(((click_x - circle_center_x) * (click_x - circle_center_x)) + ((click_y - circle_center_y) * (click_y - circle_center_y)));
	return distance;
}

