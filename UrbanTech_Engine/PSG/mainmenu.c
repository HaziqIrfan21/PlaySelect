#include "cprocessing.h"
#include "mainmenu.h"


CP_Font myFont;
CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;

struct Options
{
	char name[20];
	float x;
	float y;
};

void Main_Menu_Init(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(105, 105, 105, 255));
	myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
	Draw_Rectangle();

}

void Main_Menu_Update(void)
{

}

void Main_Menu_Exit(void)
{

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

	// set the rectangle drawing mode to CENTER
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_TextAlignment(horizontal, vertical);
	// draw a rectangle at the center of the screen, half the size of the screen
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f,
		CP_System_GetWindowWidth() / 5.5f, CP_System_GetWindowHeight() / 4.5f);

	struct Options play;

	struct Options exit;
	
	strcpy(play.name, "Play");
	play.x = CP_System_GetWindowWidth() / 2.0f;
	play.y = CP_System_GetWindowHeight() / 1.5f;

	strcpy(exit.name, "Elay");
	exit.x = CP_System_GetWindowWidth() / 2.0f;
	exit.y = CP_System_GetWindowHeight() / 1.5f;


	CP_Graphics_DrawRect(play.x, play.y,
	CP_System_GetWindowWidth() / 5.5f, CP_System_GetWindowHeight() / 4.5f);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(70.0f);
	CP_Font_DrawText("Play", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 4.0f);

	CP_Font_DrawText("Exit", CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 1.5f);
	


}
