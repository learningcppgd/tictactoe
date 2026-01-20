#include <iostream>
#include "raylib.h"

//function prototypes 
void drawLines(int width, int height, int size, Color col);
void drawSymbols(int board[3][3], int size, Color col);
void MouseInput(int (& board)[3][3], int size, int& turn);
void CheckforWin(int board[3][3], bool gameover);

int main()
{
	const int screenWidth{ 600 };
	const int screenHeight{ 600 };
	const int cellSize{ screenWidth / 3 };
	const Color color = WHITE;

	int board[3][3]{0};
	int turn{ 1 };
	bool gameover{ false };

	InitWindow(screenWidth, screenHeight, "TicTacToe");

	while (!gameover && !WindowShouldClose())
	{
		//update
		MouseInput(board, cellSize, turn);

		BeginDrawing();
			ClearBackground(BLACK);
			drawLines(screenWidth, screenHeight, cellSize, color);
			drawSymbols(board, cellSize, color);
		EndDrawing();

		CheckforWin(board, gameover);
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

void CheckforWin(int board[3][3], bool gameover)
{
	for (int i{ 0 }; i < 3; i++)
	{
		//cols
		if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i])
		{
			gameover = true;
		}
		//rows
		if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2])
		{
			gameover = true;
		}
	}
	//left diagonal
	if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
	{
		gameover = true;
	}
	//right diagonal
	if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0])
	{
		gameover = true;
	}
}