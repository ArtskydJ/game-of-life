//GOL_Pieces.c
//Joseph Dykstra
//2013-09-11

//For use with GameOfLife.c
#define gliderGunX	36
#define gliderGunY	9
#define gliderX		5
#define gliderY		3
#define lwssX		5
#define lwssY		4
#define blinkerX	3
#define blinkerY	3

const bool gliderGun[gliderGunY][gliderGunX]={
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const bool glider[gliderY][gliderX]={
	{0,0,0,1,0},
	{0,0,0,0,1},
	{0,0,1,1,1}
	};
	
const bool lightWeightSpaceShip[lwssY][lwssX]={
	{1,0,0,1,0},
	{0,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,1}
};

const bool blinker[blinkerY][blinkerX]={
	{0,1,0},
	{0,1,0},
	{0,1,0}
};

void make(int INchoice)
	{
	initArea(RSET);
	switch (INchoice)
		{
		case 0:
			srand(time(0));			//Seed randomizer
			initArea(RNDM);			//Randomize
		break;
		
		case 1:
			for (int i=0; i<gliderGunY; i++)
				for (int j=0; j<gliderGunX; j++)
					area[j+1][i+1]=gliderGun[i][j];
		break;
		
		case 2:	
			for (int i=0; i<gliderY; i++)
				for (int j=0; j<gliderX; j++)
					area[j+1][i+1]=glider[i][j];
		break;
		
		case 3:
			for (int i=0; i<lwssY; i++)
				for (int j=0; j<lwssX; j++)
					area[j+1][i+1]=lightWeightSpaceShip[i][j];
		break;
		
		case 4:
			for (int i=0; i<blinkerY; i++)
				for (int j=0; j<blinkerX; j++)
					area[j+1][i+1]=blinker[i][j];
		break;
		}
	}