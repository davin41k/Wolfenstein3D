/*
Copyright (c) 2004-2007, Lode Vandevenne

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

# include "math.h"
# include "string.h"
# include <stdio.h>
# include <SDL2/SDL.h>

#define mapWidth 24
#define mapHeight 24
#define WIDTH 600
#define HEIGHT 600
#define TRUE 1
#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main(void)
{
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	SDL_Renderer	*ren;
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Rect		box;
	
    

 	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return (1);
	}
	window = SDL_CreateWindow("Wolf3d", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		return (1);
	}
	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
	{
		SDL_Log("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return (1);
	}
	while(1)
	{
		for(int x = 0; x < WIDTH; x++)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			//which box of the map we're in
			int mapX = (int)(posX);
			int mapY = (int)(posY);

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = fabs(1 / rayDirX);
			double deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0)
					hit = 1;
			}
			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (side == 0)
				perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
			int drawStart; 
			drawStart = -lineHeight / 2 + HEIGHT / 2;
			if(drawStart < 0)
				drawStart = 0;
			int drawEnd;
			drawEnd = lineHeight / 2 + HEIGHT / 2;
			if(drawEnd >= HEIGHT)
				drawEnd = HEIGHT - 1;

		//choose wall color
			int color = 0;
			if (worldMap[mapX][mapY] == 1)
				color = 0xFF0000;
			else if (worldMap[mapX][mapY] == 2)
				color = 0x32CD32;
			else if (worldMap[mapX][mapY] == 3)
				color = 0x0000FF;
			else if (worldMap[mapX][mapY] == 4)
				color = 0;
			else
				color = 16776960;
      if (side == 1) color = color / 2;
			SDL_SetRenderDrawColor(ren, color >> 16 , color >> 8, color, 255);

			// switch (worldMap[mapX][mapY])
			// {
			// 	case 1:  color = 16711680;  break; //red
			// 	case 2:  color = 65280;  break; //green
			// 	case 3:  color = 255;   break; //blue
			// 	case 4:  color = 0;  break; //white
			// 	default: color = 16776960; break; //yellow
			// }

		//give x and y sides different brightness
		///if (side == 1) color = color / 2;

												//draw the pixels of the stripe as a vertical line

			// static int width_wall;
			SDL_SetRenderDrawColor(ren, color >> 16 , color >> 8, color, 255);
			SDL_RenderDrawLine(ren, x, drawStart, x, drawEnd);
			// box.y = drawStart;
			// box.x = x;
			// box.w = 1;
			// box.h =  drawEnd - drawStart; 
			// SDL_RenderDrawRect(ren, &box);
			// SDL_SetRenderDrawColor(ren, 25 , 200 , 100, 255);
			// SDL_RenderFillRect(ren, &box);
			// width_wall += 2;
			//  verLine(x, drawStart, drawEnd, color);
   		 }
    //timing for input and FPS counter
		oldTime = time;
		time = SDL_GetTicks();
		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		//printf(" %f \n", (1.0 / frameTime)); //FPS counter
		//redraw();

		SDL_RenderPresent(ren);														//////////
		SDL_SetRenderDrawColor(ren, 0,  0, 0, 255);
		SDL_RenderClear(ren);

		//speed modifiers
		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
		// readKeys();
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
		if (event.type == SDL_KEYDOWN)
		{
			//move forward if no wall in front of you
			if (event.key.keysym.sym == SDLK_w)
			{
				if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0)
					posX += dirX * moveSpeed;
				if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0)
					posY += dirY * moveSpeed;
			}
			//move backwards if no wall behind you
			if (event.key.keysym.sym == SDLK_s)
			{
				if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == 0)
					posX -= dirX * moveSpeed;
				if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == 0)
					posY -= dirY * moveSpeed;
			}
			//rotate to the right
			if (event.key.keysym.sym == SDLK_e)
			{
				//both camera direction and camera plane must be rotated
				double oldDirX = dirX;
				dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
				dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
				double oldPlaneX = planeX;
				planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
				planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
			}
			//rotate to the left
			if (event.key.keysym.sym == SDLK_q)
			{
				//both camera direction and camera plane must be rotated
				double oldDirX = dirX;
				dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
				dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
				double oldPlaneX = planeX;
				planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
				planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
			}
		}
	}
}