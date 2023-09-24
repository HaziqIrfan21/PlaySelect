#include "cprocessing.h"
#include "splashscreen.h"

CP_Image logo;
float timeElapsed;
float currentTime;
float fadeInSpeed;

int splashScreenPercentage = 0;
int currentSplashscreenValue= 0;

void splash_screen_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_ShowCursor(1);
	CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));
	
}
void Draw_Circle(void)
{
	
	//Alex:This draws a red circle at the location of mouse

	// Create the color red
	CP_Color myColor = CP_Color_Create(255, 0, 0, 255);

	//This fills in color sets ALL DRAWN SHAPES to follow this color.
	// Set the shape color to red
	CP_Settings_Fill(myColor);

	// draw a circle at the mouse position
	CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 20.0f);
}

 void Splash_FadeIn(void)
{
	 //Alex: This splash screen takes in the time taken to smoothly fade in the logo.

	timeElapsed += CP_System_GetDt();
	currentTime = CP_System_GetDt();
	//Do take note that the number for fadeInSpeed is referring to how long you want the transition to be. 
	fadeInSpeed = 2 / currentTime;
	splashScreenPercentage = (int)timeElapsed % 3;


	//Getting alpha from 0 to 255 in 2 seconds

	currentSplashscreenValue += 255 / fadeInSpeed;

	//resets the fade after 2 seconds. Personally would be better to use a switch or something when need to add fade out.
	if (splashScreenPercentage == 0)
	{

		currentSplashscreenValue = 0;
	}

}

void splash_screen_update(void)
{
	Splash_FadeIn();

			
	
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(logo, 0.f, 0.f, (float)CP_Image_GetWidth(logo), (float)CP_Image_GetHeight(logo), currentSplashscreenValue);
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
	Draw_Circle();

}

void splash_screen_exit(void)
{
	CP_Image_Free(&logo);
}


