#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "game.h"


struct Players
{
	char* name;

	float circleX;
	float circleY;
	float circleD;

	float triangleX1;
	float triangleY1;
	float triangleX2;
	float triangleY2;
	float triangleX3;
	float triangleY3;
	float rotation;


	float width;
	float height;
	float velocityX;
	float velocityY;

	int isActive;

	int direction;

};

struct Players red;
struct Players green;
struct Players blue;

void Game_Init(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	Draw_Players();
	red.isActive = 1;

}


void Game_Update(void)
{


	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
	Set_Player();
	//Player_Controls();
	Agent_Auto_Controls();

	Draw_Players();

	Check_Player_Agent_Collision();
	Check_Agent_Agent_Collision();
	Check_Wall_Collision();
	//Check_Wall_Agent_Collision();
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

	red.circleX = 100;
	red.circleY = 100;
	red.circleD = 70.0f;

	red.triangleX1 = 100.0f;
	red.triangleY1 = 70.0f;
	red.triangleX2 = 125.0f;
	red.triangleY2 = 120.0f;
	red.triangleX3 = 75.0f;
	red.triangleY3 = 120.0f;

	//red.rotation = 0.0f;


   //Red circle
	CP_Graphics_DrawCircle(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD);

	// set the fill color to white
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Graphics_DrawTriangleAdvanced(red.triangleX1 + red.velocityX, red.triangleY1 + red.velocityY, red.triangleX2 + red.velocityX, red.triangleY2 + red.velocityY, red.triangleX3 + red.velocityX, red.triangleY3 + red.velocityY, 1 * red.rotation);


	green.circleX = 400;
	green.circleY = 100;
	green.circleD = 70.0f;

	green.triangleX1 = 400.0f;
	green.triangleY1 = 70.0f;
	green.triangleX2 = 425.0f;
	green.triangleY2 = 120.0f;
	green.triangleX3 = 375.0f;
	green.triangleY3 = 120.0f;

	// Green circle
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	//draw a circle at (100, 100)
	CP_Graphics_DrawCircle(green.circleX + green.velocityX, green.circleY + green.velocityY, green.circleD);


	// set the fill color to white
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Graphics_DrawTriangleAdvanced(green.triangleX1 + green.velocityX, green.triangleY1 + green.velocityY, green.triangleX2 + green.velocityX, green.triangleY2 + green.velocityY, green.triangleX3 + green.velocityX, green.triangleY3 + green.velocityY, 1 * green.rotation);



	blue.circleX = 100;
	blue.circleY = 400;
	blue.circleD = 70.0f;

	blue.triangleX1 = 100.0f;
	blue.triangleY1 = 370.0f;
	blue.triangleX2 = 125.0f;
	blue.triangleY2 = 420.0f;
	blue.triangleX3 = 75.0f;
	blue.triangleY3 = 420.0f;


	// Blue circle
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	//draw a circle at (100, 100)
	CP_Graphics_DrawCircle(blue.circleX + blue.velocityX, blue.circleY + blue.velocityY, blue.circleD);

	// set the fill color to white
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Graphics_DrawTriangleAdvanced(blue.triangleX1 + blue.velocityX, blue.triangleY1 + blue.velocityY, blue.triangleX2 + blue.velocityX, blue.triangleY2 + blue.velocityY, blue.triangleX3 + blue.velocityX, blue.triangleY3 + blue.velocityY, 1 * blue.rotation);


}


void Set_Player(void)
{
	if (IsCircleClicked(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
	{
		red.isActive = 1;
		green.isActive = 0;
		blue.isActive = 0;

	}

	if (IsCircleClicked(green.circleX + green.velocityX, green.circleY + green.velocityY, green.circleD, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
	{
		red.isActive = 0;
		green.isActive = 1;
		blue.isActive = 0;
	}

	if (IsCircleClicked(blue.circleX + blue.velocityX, blue.circleY + blue.velocityY, blue.circleD, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
	{
		red.isActive = 0;
		green.isActive = 0;
		blue.isActive = 1;

	}


}

void Check_Agent_Agent_Collision()
{
	//red and green agent collision
	if (AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, green.circleX + green.velocityX, green.circleY + green.velocityY, green.width * 1.5))
	{

		//check left and right collision for agents
		if ((red.isActive == 0 && red.direction == 4) && (green.isActive == 0 && green.direction == 6))
		{
			red.direction = 6;
			green.direction = 4;

		}

		else if ((red.isActive == 0 && red.direction == 6) && (green.isActive == 0 && green.direction == 4))
		{
			red.direction = 4;
			green.direction = 6;


		}

		//Check up and down for agent
		//check left and right collision for agents
		if ((red.isActive == 0 && red.direction == 8) && (green.isActive == 0 && green.direction == 2))
		{
			red.direction = 2;
			green.direction = 8;

		}

		else if ((red.isActive == 0 && red.direction == 2) && (green.isActive == 0 && green.direction == 8))
		{
			red.direction = 8;
			green.direction = 2;


		}

	}
	//red and blue agent collision
	if (AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, blue.circleX + blue.velocityX, blue.circleY + blue.velocityY, blue.width * 1.5))
	{

		//check left and right collision for agents
		if ((red.isActive == 0 && red.direction == 4) && (blue.isActive == 0 && blue.direction == 6))
		{
			red.direction = 6;
			blue.direction = 4;

		}

		else if ((red.isActive == 0 && red.direction == 6) && (blue.isActive == 0 && blue.direction == 4))
		{
			red.direction = 4;
			blue.direction = 6;


		}

		//Check up and down for agent
		//check left and right collision for agents
		if ((red.isActive == 0 && red.direction == 8) && (blue.isActive == 0 && blue.direction == 2))
		{
			red.direction = 2;
			blue.direction = 8;

		}

		else if ((red.isActive == 0 && red.direction == 2) && (blue.isActive == 0 && blue.direction == 8))
		{
			red.direction = 8;
			blue.direction = 2;


		}

	}

	//green and blue agent collision
	if (AreCirclesIntersecting(green.circleX + green.velocityX, green.circleY + green.velocityY, green.circleD * 1.5, blue.circleX + blue.velocityX, blue.circleY + blue.velocityY, blue.width * 1.5))
	{

		//check left and right collision for agents
		if ((green.isActive == 0 && green.direction == 4) && (blue.isActive == 0 && blue.direction == 6))
		{
			green.direction = 6;
			blue.direction = 4;

		}

		else if ((green.isActive == 0 && green.direction == 6) && (blue.isActive == 0 && blue.direction == 4))
		{
			green.direction = 4;
			blue.direction = 6;


		}

		//Check up and down for agent
		//check left and right collision for agents
		if ((green.isActive == 0 && green.direction == 8) && (blue.isActive == 0 && blue.direction == 2))
		{
			green.direction = 2;
			blue.direction = 8;

		}

		else if ((green.isActive == 0 && green.direction == 2) && (blue.isActive == 0 && blue.direction == 8))
		{
			green.direction = 8;
			blue.direction = 2;


		}

	}
}

void Check_Player_Agent_Collision()
{

	//Check for circle collision between red and green
	if (AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, green.circleX + green.velocityX, green.circleY + green.velocityY, green.width * 1.5))
	{
		if (red.isActive == 1 && red.direction == 6)
		{
			green.direction = 6;

		}

		if (green.isActive == 1 && green.direction == 6)
		{
			red.direction = 6;

		}

		if (red.isActive == 1 && red.direction == 4)
		{
			green.direction = 4;

		}

		if (green.isActive == 1 && green.direction == 4)
		{
			red.direction = 4;

		}

		//Y direction

		if (red.isActive == 1 && red.direction == 2)
		{
			green.direction = 2;

		}
		if (green.isActive == 1 && green.direction == 2)
		{
			red.direction = 2;

		}

		if (red.isActive == 1 && red.direction == 8)
		{
			green.direction = 8;

		}
		if (green.isActive == 1 && green.direction == 8)
		{
			red.direction = 8;

		}



	}

	//Check for circle collision between red and blue
	if (AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, blue.circleX + blue.velocityX, blue.circleY + blue.velocityY, blue.width * 1.5))
	{
		if (red.isActive == 1 && red.direction == 6)
		{
			blue.direction = 6;

		}
		if (blue.isActive == 1 && blue.direction == 6)
		{
			red.direction = 6;

		}

		if (red.isActive == 1 && red.direction == 4)
		{
			blue.direction = 4;

		}
		if (blue.isActive == 1 && blue.direction == 4)
		{
			red.direction = 4;

		}

		//Y direction

		if (red.isActive == 1 && red.direction == 2)
		{
			blue.direction = 2;

		}
		if (blue.isActive == 1 && blue.direction == 2)
		{
			red.direction = 2;

		}

		if (red.isActive == 1 && red.direction == 8)
		{
			blue.direction = 8;

		}
		if (blue.isActive == 1 && blue.direction == 8)
		{
			red.direction = 8;

		}

	}

	//Check for circle collision between green and blue
	if (AreCirclesIntersecting(green.circleX + green.velocityX, green.circleY + green.velocityY, green.circleD * 1.5, blue.circleX + blue.velocityX, blue.circleY + blue.velocityY, blue.width * 1.5))
	{
		if (green.isActive == 1 && green.direction == 6)
		{
			blue.direction = 6;

		}
		if (blue.isActive == 1 && blue.direction == 6)
		{
			red.direction = 6;

		}

		if (green.isActive == 1 && green.direction == 4)
		{
			blue.direction = 4;

		}
		if (blue.isActive == 1 && blue.direction == 4)
		{
			green.direction = 4;

		}

		//Y direction

		if (green.isActive == 1 && green.direction == 2)
		{
			blue.direction = 2;

		}
		if (blue.isActive == 1 && blue.direction == 2)
		{
			green.direction = 2;

		}

		if (green.isActive == 1 && green.direction == 8)
		{
			blue.direction = 8;

		}
		if (blue.isActive == 1 && blue.direction == 8)
		{
			green.direction = 8;

		}

	}


}

void Check_Wall_Collision()
{

	//Check for red wall collision
	if (red.circleX + red.velocityX > CP_System_GetWindowWidth() && !(AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, green.circleX + green.velocityX, green.circleY + green.velocityY, green.width * 1.5)))
	{
		red.direction = 4;
	}

	if (red.circleX + red.velocityX < 0)
	{
		red.direction = 6;
	}
	if (red.circleY + red.velocityY > CP_System_GetWindowHeight())
	{
		red.direction = 8;
	}
	if (red.circleY + red.velocityY < 0)
	{
		red.direction = 2;
	}

	//Check for green wall collision
	if (green.circleX + green.velocityX > CP_System_GetWindowWidth())
	{
		green.direction = 4;
	}
	if (green.circleX + green.velocityX < 0)
	{
		green.direction = 6;
	}
	if (green.circleY + green.velocityY > CP_System_GetWindowHeight())
	{
		green.direction = 8;
	}
	if (green.circleY + green.velocityY < 0)
	{
		green.direction = 2;
	}

	//Check for blue wall collision
	if (blue.circleX + blue.velocityX > CP_System_GetWindowWidth())
	{
		blue.direction = 4;
	}
	if (blue.circleX + blue.velocityX < 0)
	{
		blue.direction = 6;
	}
	if (blue.circleY + blue.velocityY > CP_System_GetWindowHeight())
	{
		blue.direction = 8;
	}
	if (blue.circleY + blue.velocityY < 0)
	{
		blue.direction = 2;
	}

	////check for wall and circle



	//if (red.circleX + red.velocityX < 0 && (AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, green.circleX + green.velocityX, green.circleY + green.velocityY, green.width * 1.5) || AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, blue.circleX + blue.velocityX, blue.circleY + blue.velocityY, blue.width * 1.5)))
	//{
	//	red.direction = 2;
	//}
	//if (red.circleX + red.velocityX > CP_System_GetWindowHeight() && (AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, green.circleX + green.velocityX, green.circleY + green.velocityY, green.width * 1.5) || AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, blue.circleX + blue.velocityX, blue.circleY + blue.velocityY, blue.width * 1.5)))
	//{
	//	red.direction = 6;
	//}
	//if (red.circleX + red.velocityX < 0 && (AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, green.circleX + green.velocityX, green.circleY + green.velocityY, green.width * 1.5) || AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, blue.circleX + blue.velocityX, blue.circleY + blue.velocityY, blue.width * 1.5)))
	//{
	//	red.direction = 6;
	//}

}
void Check_Wall_Agent_Collision(void)
{
	//if (red.circleX + red.velocityX < 0 && (AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, green.circleX + green.velocityX, green.circleY + green.velocityY, green.width * 1.5)))
	//{
	//	red.direction = 2;
	//}
	//if (red.circleX + red.velocityX > CP_System_GetWindowHeight() && (AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, green.circleX + green.velocityX, green.circleY + green.velocityY, green.width * 1.5) || AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, blue.circleX + blue.velocityX, blue.circleY + blue.velocityY, blue.width * 1.5)))
	//{
	//	red.direction = 6;
	//}
	//if (red.circleX + red.velocityX < 0 && (AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, green.circleX + green.velocityX, green.circleY + green.velocityY, green.width * 1.5) || AreCirclesIntersecting(red.circleX + red.velocityX, red.circleY + red.velocityY, red.circleD * 1.5, blue.circleX + blue.velocityX, blue.circleY + blue.velocityY, blue.width * 1.5)))
	//{
	//	red.direction = 6;
	//}
}


void Player_Controls(void)
{

	if (red.isActive == 1 && green.isActive == 0 && blue.isActive == 0)
	{
		if (CP_Input_KeyDown(KEY_W))
		{
			red.velocityY -= 500 * CP_System_GetDt();
			red.rotation = 0;

			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

		if (CP_Input_KeyDown(KEY_S))
		{
			red.velocityY += 500 * CP_System_GetDt();
			red.rotation = 180;
			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

		if (CP_Input_KeyDown(KEY_D))
		{
			red.velocityX += 500 * CP_System_GetDt();
			red.rotation = 90;
			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

		if (CP_Input_KeyDown(KEY_A))
		{
			red.velocityX -= 500 * CP_System_GetDt();
			red.rotation = 270;
			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

	}
	if (red.isActive == 0 && green.isActive == 1 && blue.isActive == 0)
	{
		if (CP_Input_KeyDown(KEY_W))
		{
			green.velocityY -= 500 * CP_System_GetDt();
			green.rotation = 0;

			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

		if (CP_Input_KeyDown(KEY_S))
		{
			green.velocityY += 500 * CP_System_GetDt();
			green.rotation = 180;
			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

		if (CP_Input_KeyDown(KEY_D))
		{
			green.velocityX += 500 * CP_System_GetDt();
			green.rotation = 90;
			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

		if (CP_Input_KeyDown(KEY_A))
		{
			green.velocityX -= 500 * CP_System_GetDt();
			green.rotation = 270;
			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

	}

	if (red.isActive == 0 && green.isActive == 0 && blue.isActive == 1)
	{
		if (CP_Input_KeyDown(KEY_W))
		{
			blue.velocityY -= 500 * CP_System_GetDt();
			blue.rotation = 0;

			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

		if (CP_Input_KeyDown(KEY_S))
		{
			blue.velocityY += 500 * CP_System_GetDt();
			blue.rotation = 180;
			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

		if (CP_Input_KeyDown(KEY_D))
		{
			blue.velocityX += 500 * CP_System_GetDt();
			blue.rotation = 90;
			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

		if (CP_Input_KeyDown(KEY_A))
		{
			blue.velocityX -= 500 * CP_System_GetDt();
			blue.rotation = 270;
			// Set the background color to green and erase anything that was previously drawn
			CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
		}

	}


}

int return_Direction()
{

	int direction_W = 0;
	int direction_A = 0;
	int direction_S = 0;
	int direction_D = 0;

	if (CP_Input_KeyTriggered(KEY_S))
	{
		int direction_S = 1;
	}
}

void Agent_Auto_Controls(void)
{


	//red.velocityX += 50 * CP_System_GetDt();
	//red.rotation = 90;
	//green.velocityX += 50 * CP_System_GetDt();
	//green.rotation = 90;
	//blue.velocityX += 50 * CP_System_GetDt();
	//blue.rotation = 90;
	//CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));

	//Default move to left at init
	if (red.direction == 0)
	{
		red.direction = 6;
		red.velocityX += 250 * CP_System_GetDt();
		red.rotation = 90;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (green.direction == 0)
	{
		green.direction = 6;
		green.velocityX += 250 * CP_System_GetDt();
		green.rotation = 90;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (blue.direction == 0)
	{
		blue.direction = 6;
		blue.velocityX += 250 * CP_System_GetDt();
		blue.rotation = 90;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (red.isActive == 1 && green.isActive == 0 && blue.isActive == 0)
	{
		if (CP_Input_KeyTriggered(KEY_W))
		{
			red.direction = 8;
		}

		if (CP_Input_KeyTriggered(KEY_S))
		{
			red.direction = 2;
		}

		if (CP_Input_KeyTriggered(KEY_D))
		{
			red.direction = 6;
		}

		if (CP_Input_KeyTriggered(KEY_A))
		{
			red.direction = 4;
		}
		//---//

	}

	if (red.direction == 8)
	{
		red.velocityY -= 250 * CP_System_GetDt();
		red.rotation = 0;

		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (red.direction == 2)
	{
		red.velocityY += 250 * CP_System_GetDt();
		red.rotation = 180;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (red.direction == 6)
	{
		red.velocityX += 250 * CP_System_GetDt();
		red.rotation = 90;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (red.direction == 4)
	{
		red.velocityX -= 250 * CP_System_GetDt();
		red.rotation = 270;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}
	if (red.isActive == 0 && green.isActive == 1 && blue.isActive == 0)
	{
		if (CP_Input_KeyTriggered(KEY_W))
		{
			green.direction = 8;
		}

		if (CP_Input_KeyTriggered(KEY_S))
		{
			green.direction = 2;
		}

		if (CP_Input_KeyTriggered(KEY_D))
		{
			green.direction = 6;
		}

		if (CP_Input_KeyTriggered(KEY_A))
		{
			green.direction = 4;
		}
		//---//

	}

	if (green.direction == 8)
	{
		green.velocityY -= 250 * CP_System_GetDt();
		green.rotation = 0;

		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (green.direction == 2)
	{
		green.velocityY += 250 * CP_System_GetDt();
		green.rotation = 180;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (green.direction == 6)
	{
		green.velocityX += 250 * CP_System_GetDt();
		green.rotation = 90;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (green.direction == 4)
	{
		green.velocityX -= 250 * CP_System_GetDt();
		green.rotation = 270;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (red.isActive == 0 && green.isActive == 0 && blue.isActive == 1)
	{
		if (CP_Input_KeyTriggered(KEY_W))
		{
			blue.direction = 8;
		}

		if (CP_Input_KeyTriggered(KEY_S))
		{
			blue.direction = 2;
		}

		if (CP_Input_KeyTriggered(KEY_D))
		{
			blue.direction = 6;
		}

		if (CP_Input_KeyTriggered(KEY_A))
		{
			blue.direction = 4;
		}

	}

	if (blue.direction == 8)
	{
		blue.velocityY -= 250 * CP_System_GetDt();
		blue.rotation = 0;

		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (blue.direction == 2)
	{
		blue.velocityY += 250 * CP_System_GetDt();
		blue.rotation = 180;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (blue.direction == 6)
	{
		blue.velocityX += 250 * CP_System_GetDt();
		blue.rotation = 90;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

	if (blue.direction == 4)
	{
		blue.velocityX -= 250 * CP_System_GetDt();
		blue.rotation = 270;
		// Set the background color to green and erase anything that was previously drawn
		CP_Graphics_ClearBackground(CP_Color_Create(192, 192, 192, 255));
	}

}