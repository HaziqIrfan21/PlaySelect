#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "game.h"


struct Players
{
	char* name;

	float circleX;
	float circleY;

	float triangleX1;
	float triangleY1;
	float triangleX2;
	float triangleY2;
	float triangleX3;
	float triangleY3;
	float rotation;


	float width;
	float height;
	float velocity;
};

struct Players red;

void Game_Init(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	Draw_Players();

}


void Game_Update(void)
{
	//Draw_Players();

	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{

}

void Draw_Players(void)
{
	/*float velocity = 10;

	if (CP_Input_KeyDown(KEY_D))
	{
		velocity = 5 * CP_System_GetDt();
	}*/

	CP_Color myColor = CP_Color_Create(255, 0, 0, 255);
	//This fills in color sets ALL DRAWN SHAPES to follow this color.
	// Set the shape color to red
	CP_Settings_Fill(myColor);

	//draw a circle at (100, 100)
	CP_Graphics_DrawCircle(100, 100, 70.0f);

	// set the fill color to white
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Graphics_DrawTriangleAdvanced(100.0f, 70.0f, 125.0f, 120.0f, 75.0f, 120.0f, 90.0f);


	// set the fill color to green
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	//draw a circle at (100, 100)
	CP_Graphics_DrawCircle(400, 100, 70.0f);


	// set the fill color to white
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Graphics_DrawTriangleAdvanced(400.0f, 70.0f, 425.0f, 120.0f, 375.0f, 120.0f, 90.0f);

	// set the fill color to blue
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	//draw a circle at (100, 100)
	CP_Graphics_DrawCircle(100, 400, 70.0f);


	// set the fill color to white
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Graphics_DrawTriangleAdvanced(100.0f, 370.0f, 125.0f, 420.0f, 75.0f, 420.0f, 90.0f);


}