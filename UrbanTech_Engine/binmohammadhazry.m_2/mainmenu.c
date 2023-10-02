#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "game.h"

CP_Font myFont;
CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;

struct Options
{
	char *name;
	float x;
	float y;
	float width;
	float height;
};

void Main_Menu_Init(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(105, 105, 105, 255));
	myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
	Draw_Rectangle();

}

void Main_Menu_Update(void)
{
	/*if (IsAreaClicked)
	{
		CP_Engine_Terminate();
	}*/
	Draw_Rectangle();
	Debug_Tools();
}

void Main_Menu_Exit(void)
{

}
void Debug_Tools(void)
{
	float positionX ;
	positionX = CP_Input_GetMouseX();

	float xPosition[] = { positionX };
	

	CP_Font_DrawText(xPosition , CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 1.5f);
	
}
void Draw_Rectangle(void)
{

	////Alex:This draws a red circle at the location of mouse

	// Create the color red
	CP_Color myColor = CP_Color_Create(255, 128,128, 255);

	//This fills in color sets ALL DRAWN SHAPES to follow this color.
	// Set the shape color to red
	CP_Settings_Fill(myColor);

	//// draw a circle at the mouse position
	//CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 20.0f);
	struct Options play;

	struct Options exit;

	play.name = "Play";
	play.x = CP_System_GetWindowWidth() / 2.0f;
	play.y = CP_System_GetWindowHeight() / 4.0f;
	play.width = CP_System_GetWindowWidth() / 5.5f;
	play.height = CP_System_GetWindowHeight() / 4.5f;

	exit.name = "Exit";
	exit.x = CP_System_GetWindowWidth() / 2.0f;
	exit.y = CP_System_GetWindowHeight() / 1.5f;
	exit.width = CP_System_GetWindowWidth() / 5.5f;
	exit.height = CP_System_GetWindowHeight() / 4.5f;
	// set the rectangle drawing mode to CENTER
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_TextAlignment(horizontal, vertical);
	// draw a rectangle at the center of the screen, half the size of the screen
	CP_Graphics_DrawRect(play.x, play.y,play.width, play.height);

	CP_Graphics_DrawRect(exit.x, exit.y,exit.width, exit.height);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(70.0f);

	CP_Font_DrawText("Play", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f);

	//Play button Function
	if (IsAreaClicked(play.x, play.y, play.width, play.height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
	{
		CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);

	}

	CP_Font_DrawText("Exit", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 1.5f);

	//Exit button function
	if(IsAreaClicked(exit.x, exit.y, exit.width, exit.height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
	{
		CP_Engine_Terminate();
	}


}
