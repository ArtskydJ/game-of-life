//////////////////////////////
//    Name: Game Of Life	//
// 	Author: Joseph Dykstra	//
// Written: 2013-01-15		//
//  Ported: 2013-09-11		//
//////////////////////////////

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "including\EasySDL.h"

#define WIDTH   			64		//blocks horizontally
#define HEIGHT  			48		//blocks vertically
#define SIZE				10		//pixels each block
#define NO_COLS				3
#define SCR_WIDTH			(WIDTH*SIZE)
#define SCR_HEIGHT			(HEIGHT*SIZE)
#define SCR_BPP				32
#define BTN_X				SIZE
#define BTN_Y(num,num2)		((num*SCR_HEIGHT)/num2)
#define BTN_WIDTH			(SCR_WIDTH/NO_COLS-SIZE*2)
#define BTN_HEIGHT(num)		(SCR_HEIGHT/(num+1))
#define COL_OFF				0x222222
#define COL_ON				0x9999FF
#define RNDM				0
#define RSET				1
#define MODE_MENU			false 	// true=menu, false=skip
#define DELETE_CELL			2
#define CREATE_CELL			3
#define modeName(n)			((n==0)?"Random":(n==1)?"GlidrGun":(n==2)?"Glider":"Light Weight Space Ship")	//not proper :(
#define speedName(n)		((n==0)?"Extra Fast":(n==1)?"Fast":(n==2)?"Medium":"Slow")						//not proper :(
#define sizeName(n)			((n==0)?"Small":(n==1)?"Medium":"large")										//not proper :(

const int noBtns[NO_COLS]={4,4,3};
char area[WIDTH+2][HEIGHT+2];
void initArea(bool);
#include "Pieces.c"

SDL_Surface *screen=NULL;
SDL_Rect *drawRect;
TTF_Font *font=NULL;



const Uint32 modeColor[3][5]=	//Button colors
	{
	{0x00C800, 0x00C8C8, 0xFF7F00, 0xFF0000, 0xFFFFFF},
	{0x00C800, 0x00C8C8, 0xFF7F00, 0xFF0000, 0xFFFFFF},
	{0x00C800, 0x00C8C8, 0xFF7F00, 0xFF0000, 0xFFFFFF}
	};


int set(void)
	{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 1;
		}
	else
		{
		atexit(SDL_Quit);
		//Graphics
		screen = SDL_SetVideoMode(SCR_WIDTH,SCR_HEIGHT,SCR_BPP,SDL_SWSURFACE);
		if (screen!=NULL) printf("Sucess with screen init\n");
		SDL_Flip(screen);
		
		//Font
		if( TTF_Init() == -1 )
			return -2;
		
		font = TTF_OpenFont( "arial.ttf", 28 );
		if( font == NULL )
			return -3;
		
		return 0;
		}
	}


void reset()
	{
	SDL_WM_SetCaption("Game Of Life | Joseph Dykstra", NULL);
	
	SDL_Event tEvent;
	int tSelection=-1, tX, tY, tClickSelection;
	
	printf("hi2.0\n");
	while (tSelection==-1)
		{
		
		for (int j=0; j<NO_COLS; j++)
			{
			tX=SIZE+((BTN_WIDTH+SIZE)*j);
			for (int i=0; i<noBtns[j]; i++)
				{
				EZ_apply_rect(screen, EZ_new_rect(tX, BTN_Y(i,noBtns[j]), BTN_WIDTH, BTN_HEIGHT(noBtns[j])), modeColor[j][i]);
				EZ_apply_text(screen,modeName(i),font, EZ_new_rect(tX+SIZE,BTN_Y(i,noBtns[j])+(SIZE/2),0,0), EZ_Uint32_to_SDL(0x000000));
				}					//speedName(i), sizeName(i)
			}
		SDL_Flip(screen);
		
		while(SDL_PollEvent(&tEvent))
			{
			if (tEvent.type==SDL_MOUSEBUTTONDOWN)
				{
				if (tEvent.button.x>BTN_X && tEvent.button.x<BTN_WIDTH+BTN_X)
					{
					for (int i=0; i<=noBtns[0]; i++)
						{
						if ( tEvent.button.y > BTN_Y(i,noBtns[0]) && tEvent.button.y < BTN_Y(i,noBtns[0])+BTN_HEIGHT(noBtns[0]) ) //
							tClickSelection=i;
						}
					}
				}
			
			if (tEvent.type==SDL_MOUSEBUTTONUP)
				{
				if (tEvent.button.x>BTN_X && tEvent.button.x<BTN_WIDTH+BTN_X)
					{
					for (int i=0; i<=noBtns[0]; i++)
						{
						if ( tEvent.button.y > BTN_Y(i,noBtns[0]) && tEvent.button.y < BTN_Y(i,noBtns[0])+BTN_HEIGHT(noBtns[0]) ) //
							{
							if (tClickSelection==i)
								tSelection=i;
							}
						}
					}
				}
			
			if (tEvent.type==SDL_QUIT)
				exit(0);
				
			}
		}
	printf("hi4\n");
	
	make(tSelection);
	printf("hi5\n");
	}


void initArea(bool INrsetRndm)
	{
	for (int i=0; i<HEIGHT+2; i++)
		{
		for (int j=0; j<WIDTH+2; j++)
			{
			if		(INrsetRndm==RSET)		//RESET
				area[j][i]=0;
			else if (INrsetRndm==RNDM)		//RANDOM
				area[j][i]=rand()%2;
			}
		}
	}

	
void clearScreen()
	{
	EZ_apply_rect(screen,EZ_new_rect(0,0,SCR_WIDTH,SCR_HEIGHT),COL_OFF);
	}


void draw(int INb)
	{
	for (int i=1; i<HEIGHT+1; i++)
		{
		for (int j=1; j<WIDTH+1; j++)
			{
			if (area[j][i])
				EZ_apply_rect(screen,EZ_new_rect((j-1)*INb,(i-1)*INb,INb,INb),COL_ON);
			else
				EZ_apply_rect(screen,EZ_new_rect((j-1)*INb,(i-1)*INb,INb,INb),COL_OFF);
			}
		}
	SDL_Flip(screen);
	}


void stepForward()
	{
	int neighbors;
	for (int i=0; i<HEIGHT+2; i++)	//Clear L & R Edges
		{
		area[0][i]=0;
		area[WIDTH+1][i]=0;
		}
	for (int j=0; j<WIDTH+2; j++)	//Clear T & B Edges
		{
		area[j][0]=0;
		area[j][HEIGHT+1]=0;
		}
	
	for (int i=1; i<HEIGHT+1; i++)
		{
		for (int j=1; j<WIDTH+1; j++)
			{
			neighbors=0;
			for (int k=-1; k<=1; k++)
				for (int l=-1; l<=1; l++)	//if ((not self) and (alive now&later) or (alive now,dead later))
					if ( (k!=0 || l!=0) && ((area[j+l][i+k]==1) || (area[j+l][i+k]==2)))	
						neighbors++;
			if (area[j][i]) //LIVE CELL
				{
				if (neighbors<2)  area[j][i]=DELETE_CELL; //Under population
				if (neighbors>3)  area[j][i]=DELETE_CELL; //Over crowding
				}
			else            //DEAD CELL
				{
				if (neighbors==3) area[j][i]=CREATE_CELL;  //Reproduction
				}
			}
		}
	for (int i=0; i<HEIGHT+1; i++)
		{
		for (int j=0; j<WIDTH+1; j++)
			{
			if (area[j][i]>=2) area[j][i]-=2;
			}
		}
	}


int main(int argc, char* argv[])
	{
	set();
	int waitTime=50;
	reset();
	printf("wait time=%d\n",waitTime);
	const int blksz=10;//(choice[2]*2+1);
	clearScreen();
	int gens=0;
	printf("while");
	while(true)
		{
		draw(SIZE);
		SDL_Delay(waitTime);
		stepForward();
		gens++;
		if (EZ_checkForExit())
			exit(0);
		}
	printf("error:%d",SDL_GetError());
	}

	
/*
from
int main()

after
reset();
	
	if (choice[0]==RNDM)				//If chose random
		{
		printf("randomizing\n");
		srand(time(0));						//Seed randomizer
		initArea(RNDM);						//Randomize
		}
	else								//If chose diff preset
		{
		printf("loading preset\n");
		initArea(RSET);						//Reset area
		make(choice[0]);					//Create preset
		}
	waitTime=pow(5,choice[1]);
*/


/*
declared right before
main()

int startupMenu(int INmenu)
	{
	int mychoice;
	if (MODE_MENU)
		{
		/*
		output[0]="GAME OF LIFE";
		if (INmenu==0)
			{
			output[1]="Choose:";
			output[2]="Random";
			output[3]="GlidrGun";
			output[4]="Glider";
			output[5]="LtWtSpSh";
			output[6]="Misc";
			mychoice=menu(5, output, TX);
			}
		else if (INmenu==1)
			{
			output[1]="Speed:";
			output[2]="XtraFast";
			output[3]="Fast";
			output[4]="Medium";
			output[5]="Slow";
			mychoice=menu(4, output, TX);
			}
		else if (INmenu==2)
			{
			output[1]="Size:";
			output[2]="Small";
			output[3]="Medium";
			output[4]="Large";
			mychoice=menu(3, output, TX);
			}
		* /
		}
	else
		{
		if      (INmenu==0) mychoice=1; //0=random, other=create
		else if (INmenu==1) mychoice=4; //1=XtraFast, 2=fast, 3=normal, 4=slow
		else if (INmenu==2) mychoice=2; //Large
		}
	return mychoice;
	}
*/


/*
from
void reset()

after
while (tSelection==-1) {

		tX=SIZE;
		for (int i=0; i<noBtns[0]; i++)
			{
			EZ_apply_rect(screen, EZ_new_rect(tX, BTN_Y(i,noBtns[0]), BTN_WIDTH, BTN_HEIGHT(noBtns[0])), modeColor[0][i]);
			EZ_apply_text(screen,modeName(i),font, EZ_new_rect(tX+SIZE,BTN_Y(i,noBtns[0])+(SIZE/2),0,0), EZ_Uint32_to_SDL(0x000000));
			}
		tX=SIZE+BTN_WIDTH+SIZE;
		for (int i=0; i<noBtns[1]; i++)
			{
			EZ_apply_rect(screen, EZ_new_rect(tX, BTN_Y(i,noBtns[1]), BTN_WIDTH, BTN_HEIGHT(noBtns[1])), modeColor[1][i]);
			EZ_apply_text(screen,speedName(i),font, EZ_new_rect(tX+SIZE,BTN_Y(i,noBtns[1])+(SIZE/2),0,0), EZ_Uint32_to_SDL(0x000000));
			}
		tX=SIZE+BTN_WIDTH+SIZE+BTN_WIDTH+SIZE;
		for (int i=0; i<noBtns[2]; i++)
			{
			EZ_apply_rect(screen, EZ_new_rect(tX, BTN_Y(i,noBtns[2]), BTN_WIDTH, BTN_HEIGHT(noBtns[2])), modeColor[2][i]);
			EZ_apply_text(screen,sizeName(i),font, EZ_new_rect(tX+SIZE,BTN_Y(i,noBtns[2])+(SIZE/2),0,0), EZ_Uint32_to_SDL(0x000000));
			}
*/

