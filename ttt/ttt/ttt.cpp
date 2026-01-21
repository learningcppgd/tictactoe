#include <iostream>
#include "raylib.h"

//function prototypes 
void drawLines(int width, int height, int size, Color col);
void drawSymbols(int board[3][3], int size, Color col);
void MouseInput(int (& board)[3][3], int size, int& turn);
int CheckforWin(int board[3][3], int& gamestate, int& who_won);
void drawMenu(const char* t1, const char* t2, int cellSize, int fontSize, Color col);
Rectangle ofText(const char* t, int fontSize, int x, int y);
void CheckCLickBegin(int& gamestate, Rectangle rect);
void drawEnding(int who_won, int x, int y, int fontsize, Color col);



enum STATES
{
	MENU = 0, GAME, END
};

int gameState{ MENU };

enum WON
{
	X_PLAYER = 1, O_PLAYER, DRAW
};

int who_won{ 0 };

int main()
{
	const int screenWidth{ 600 };
	const int screenHeight{ 600 };
	const int cellSize{ screenWidth / 3 };
	const Color color = WHITE;
	const int fontSize{ 50 };

	const char* singlePlayer{ "Singleplayer" };
	const char* twoPlayer{ "2 - player" };
	Vector2 t1_pos = { 100, 200 };
	Vector2 t2_pos = { 100, 300 };


	int board[3][3]{0};
	int turn{ 1 };
	bool game_end{ false };


	InitWindow(screenWidth, screenHeight, "TicTacToe");

	while (!game_end && !WindowShouldClose())
	{

		switch (gameState) {

			case MENU:

				BeginDrawing();
				ClearBackground(BLACK);
				drawMenu(singlePlayer, twoPlayer,cellSize,fontSize,color);
				CheckCLickBegin(gameState, ofText(twoPlayer, fontSize, t2_pos.x, t2_pos.y));
				CheckCLickBegin(gameState, ofText(singlePlayer, fontSize, t1_pos.x, t1_pos.y));
				EndDrawing();
				break;

			case GAME:
				//update
				MouseInput(board, cellSize, turn);

				BeginDrawing();
				ClearBackground(BLACK);
				drawLines(screenWidth, screenHeight, cellSize, color);
				drawSymbols(board, cellSize, color);
				EndDrawing();
				CheckforWin(board, gameState, who_won);
				std::cout << CheckforWin(board, gameState, who_won);
				break;
			case END:
				BeginDrawing();
				ClearBackground(BLACK);
				//who won, would you like to play again?
				drawEnding(who_won, t1_pos.x, t1_pos.y, fontSize, color);
				if (IsKeyPressed(KEY_A)) {
					for (int r{ 0 }; r < 3; r++)
						for (int c{ 0 }; c < 3; c++) board[r][c] = 0;

					who_won = 0;     
					turn = 1;         
					gameState = GAME; 
				}
				if (IsKeyPressed(KEY_N))
				{
					game_end = true;
				}
				EndDrawing();
				break;
		}
	}

	CloseWindow();
	return 0;
}

void drawLines(int width, int height, int size, Color col)
{
	for (int i{ 0 }; i < 3; i++)
	{
		//rows
		DrawLine(0, i * size, width, i * size, col);
		//cols
		DrawLine(i * size, 0, i * size, height, col);
	}
}

void drawSymbols(int board[3][3], int size, Color col)
{
	// r - row, c - column
	for (int r{ 0 }; r < 3; r++)
	{
		for (int c{ 0 }; c < 3; c++)
		{
			if (board[r][c] == 1)
			{
				DrawText("X",c * size + 70, r * size + 50 ,100,col);
			}
			if (board[r][c] == 2)
			{
				DrawText("O", c * size + 70, r * size + 50,100,col);
			}
		}
	}
}

void MouseInput(int(&board)[3][3], int size, int& turn)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Vector2 mouse_pos = GetMousePosition();
		int row = mouse_pos.y / size;
		int col = mouse_pos.x / size;

		if (board[row][col] == 0)
		{
			board[row][col] = turn;
			turn = (turn == 1) ? 2 : 1;
		}
	}
}

int CheckforWin(int board[3][3], int& gamestate, int& who_won)
{	

	for (int i{ 0 }; i < 3; i++)
	{
		//cols
		if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i])
		{
			gamestate = END;
			if (board[0][i] == 1) {
				who_won = X_PLAYER;
				return who_won;
			}
			else {
				who_won = O_PLAYER;
				return who_won;
			}
		}
		//rows
		if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2])
		{
			gamestate = END;
			if (board[i][0] == 1) {
				who_won = X_PLAYER;
				return who_won;
			}
			else {
				who_won = O_PLAYER;
				return who_won;
			}
		}
	}
	//left diagonal
	if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
	{
		gamestate = END;
		if (board[0][0] == 1) {
			who_won = X_PLAYER;
			return who_won;
		}
		else {
			who_won = O_PLAYER;
			return who_won;
		}
	}
	//right diagonal
	if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0])
	{
		gamestate = END;
		if (board[0][2] == 1) {
			who_won = X_PLAYER;
			return who_won;
		}
		else {
			who_won = O_PLAYER;
			return who_won;
		}
	}

	bool full{ true };
	for (int r{ 0 }; r < 3; r++)
	{
		for (int c{ 0 }; c < 3; c++)
		{
			if (board[r][c] == 0) full = false;
		}
	}

	if (full)
	{
		gameState = END;
		who_won = DRAW;
		return who_won;
	}
	return 0;
}

void drawMenu(const char *t1, const char* t2,int cellSize,int fontSize,Color col)
{

	DrawText("Choose playmode: ", 100, 100, 50, col);
	DrawText(t1,100, 200, fontSize, col);
	DrawText(t2, 100, 300, fontSize, col);	
	
}

Rectangle ofText(const char* t, int fontSize, int x, int y)
{
	int textWidth = MeasureText(t, fontSize);
	int textHeight = fontSize;

	Rectangle textRect{ x,y,textWidth, textHeight };
	return textRect;
}

void CheckCLickBegin(int& gamestate, Rectangle rect)
{
	Vector2 mouse_pos = GetMousePosition();

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos,rect))
	{
		gamestate = GAME;
	}
}

void drawEnding(int who_won, int x, int y ,int fontsize, Color col)
{
	if (who_won == X_PLAYER) {
		DrawText("X - player won!", x, y, fontsize, col);
	}
	else if (who_won == O_PLAYER){
		DrawText("O - player won!", x, y, fontsize, col);
	} else {
		DrawText("Draw", x, y, fontsize, col);
	}
	DrawText("Would you like to play again?", 125, 300, 25, col);
	DrawText("Yes", 175, 350, 25, col);
	DrawText("No", 325, 350, 25, col);
	DrawText("Press y or n", 200, 400, 25, col);
}
