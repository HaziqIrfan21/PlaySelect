#pragma once

void Game_Init(void);

void Game_Update(void);

void Game_Exit(void);

void Draw_Players(void);


void Player_Controls(void);

void Set_Player(void);

void Agent_Auto_Controls(void);

void Check_Wall_Collision(void);
void Check_Player_Agent_Collision(void);
void Check_Agent_Agent_Collision(void);
void Check_Wall_Agent_Collision(void);
void Collision_Check(void);

