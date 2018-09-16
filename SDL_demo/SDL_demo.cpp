//
#include "stdafx.h"
#include "draw.h"

#include <stdio.h>
#include <SDL.h>
#include <math.h>
#include <conio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

inline int x(float t, float a)
{
	float result = 3 * a*t / (1 + t*t*t);
	return (result < (int)result + 0.5) ? (int)result : (int)result + 1;
}

inline int y(float t, float a)
{
	float result = -3 * a*t*t / (1 + t*t*t);
	return (result < (int)result + 0.5) ? (int)result : (int)result + 1;
}

void draw(SDL_Renderer *Renderer, float a, int dx, int dy) {
	SDL_SetRenderDrawColor(Renderer, 100, 100, 100, 255);
	SDL_RenderDrawLine(Renderer, dx, dy - (int)(2 * a), dx, dy + (int)(3 * a));
	SDL_RenderDrawLine(Renderer, dx - (int)(3 * a), dy, dx + (int)(3 * a), dy);
	SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
	SDL_Rect rect = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
	for (float i = -1 + (1 / (2 * a)), di = 1 / (6 * a); i < 10 * a; i += di)
	{
		int _x = x(i, a);
		int _y = y(i, a);
		SDL_RenderDrawPoint(Renderer, _x + dx, _y + dy);
	}
	for (float i = -10 * a, di = 1 / (2 * a); i < -1; i += di)
	{
		int _x = x(i, a);
		int _y = y(i, a);
		SDL_RenderDrawPoint(Renderer, _x + dx, _y + dy);
	}
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_Rect point_A;
	for (float side = 1.0f; side <= 4.0f; side++)
	{
		point_A.x = (4 / 2)*a + dx - side / 2 - a / 2;
		point_A.y = -(4 / 2)*a + dy - side / 2 + a / 2;
		point_A.h = point_A.w = side;
		SDL_RenderDrawRect(Renderer, &point_A);
	}
	for (float side = 1.0f; side <= 4.0f; side++)
	{
		point_A.x = dx - side / 2;
		point_A.y = dy - side / 2;
		point_A.h = point_A.w = side;
		SDL_RenderDrawRect(Renderer, &point_A);
	}
	for (float side = 1.0f; side <= 4.0f; side++)
	{
		point_A.x = dx - a - side / 2;
		point_A.y = dy - side / 2;
		point_A.h = point_A.w = side;
		SDL_RenderDrawRect(Renderer, &point_A);
	}
	for (float side = 1.0f; side <= 4.0f; side++)
	{
		point_A.x = dx - side / 2;
		point_A.y = dy + a - side / 2;
		point_A.h = point_A.w = side;
		SDL_RenderDrawRect(Renderer, &point_A);
	}
	for (int xx = -SCREEN_WIDTH; xx < SCREEN_WIDTH; xx += 15)
	{
		int yy1;
		yy1 = -xx - a;
		int yy2 = -xx - a + 10;
		SDL_RenderDrawLine(Renderer, dx + xx, dy - yy1, dx + xx - 10, dy - yy2);
	}
}

int _tmain(int argc, char **argv)
{
	SDL_Window      *Window;
	SDL_Renderer    *Renderer;
	SDL_Event        event;
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &Window, &Renderer);
	float a = 100;
	int dx = (int)(SCREEN_WIDTH / 2 - a);
	int dy = (int)(SCREEN_HEIGHT / 2);

	draw(Renderer, a, dx, dy);

	SDL_RenderPresent(Renderer);
	bool done = false;
	while (!done)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_KP_PLUS:
					SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
					SDL_RenderClear(Renderer);
					a += 2;
					draw(Renderer, a, dx, dy);
					SDL_RenderPresent(Renderer);
					break;
				case SDLK_KP_MINUS:
					SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
					SDL_RenderClear(Renderer);
					a -= 2;
					draw(Renderer, a, dx, dy);
					SDL_RenderPresent(Renderer);
					break;
				}
				break;
			}
		}
	}
	return 0;
}
