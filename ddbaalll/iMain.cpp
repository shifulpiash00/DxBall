# define _CRT_SECURE_NO_WARNINGS
# include "iGraphics.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <windows.h>
#define resx 1200  //screen width
#define resy 650   //screen height

int r = 10;  //radius of the ball
int life = 5;  //total life
int winner = 0; //finding whether all levels are completed or not
int timer = 0;  //starting the game
int point = 0;
int score;
char s[100];
int credits = 0;
int highscores = 0;
int instruct = 0;
int exitstate = 0;
int x, y;
int menu = 0;
int settings = 0;
int settingsmenu = 0;
int music = 1;   //music and effect music is on by default
int effectmusic = 1;
int bgcolor = -1;
int background = 0;
int p = 0;
int k = -1, z = -1, w = -1;
char l[10];

typedef struct POWER_UPS{
	int brick;   //index of powerups; meaning in which brick powerup exists
	int trigger; //whether the ball hits the brick having powerup or not;here trigger equals 0 means hitting
	int caught; //whether the paddle caught powerup or not
};
typedef struct POWER_UPS_CO{
	int x, y, l;   //co ordinate and length.it will be on when trigger on(means trigger is 0)
};

int ps = 6;        //powerup speed,meaning in which speed powerups will drop out
int shooter_repeat = 0;   // variable for shooter power up,controlling by space
int textin = 0;      //text input
char name[150];    //in which variable text will be input
int State = 0;       //state means the different state to activate new game or credits etc

int offsetx, offsety;  //co ordinate of x & y from where brick drawing will start
int bpx, bpy;          //the co ordinates of the paddle or beam
int bl, bw;        //brick's length & width
int ball_x, ball_y, dx, dy;   //position of the ball & its speed
int bricks[500][2];     //bricks co-ordinates will be stored in this 2D array;[i][0]for x& [i][1] for y
int present[500];      //whether brick exists or not.1 for existing;0 for removing or not existing
int j;        //the number of total bricks
int gapx, gapy;      //the gap between two bricks
int startanimindex = 0;
int animindex = 0;
int menuindex = 0;

int sl, sw;        //length and width of a beam
double shx[3], shy[3];  //left and upper co ordinates of shooter rectangle in the beam
double shx2[3];       //right co ordinates of shooter rectangle in the beam
int layer;        //the total number of brick layers
int brickcount;    //total number of bricks
int level = 1;   //level number
POWER_UPS shooter = { 0, 0, 0 };  //index of the shooter powerup;trigger(0);caught(0)
POWER_UPS bbeam = { 0, 0, 0 };    //index of the big beam powerup;trigger(0);caught(0)
POWER_UPS sbeam = { 0, 0, 0 };    //index of the small beam powerup;trigger(0);caught(0)
POWER_UPS fireball = { 0, 0, 0 }; //index of the fireball powerup;trigger(0);caught(0)
POWER_UPS_CO shc, bbc, sbc, fic; //powerups co ordinates

char brickl1[3][30] = { "bpic9.bmp", "bpic9.bmp", "bpic7.bmp" };
char brickl2[3][30] = { "bpic7.bmp", "bpic4.bmp", "bpic6.bmp" };
char brickl3[3][30] = { "bpic8.bmp", "bpic1.bmp", "bpic8.bmp" };

char startanim[205][30] = { "ANIMATION\\0001.bmp", "ANIMATION\\0002.bmp", "ANIMATION\\0003.bmp", "ANIMATION\\0004.bmp", "ANIMATION\\0005.bmp", "ANIMATION\\0006.bmp",
"ANIMATION\\0007.bmp", "ANIMATION\\0008.bmp", "ANIMATION\\0009.bmp", "ANIMATION\\0010.bmp", "ANIMATION\\0011.bmp", "ANIMATION\\0012.bmp",
"ANIMATION\\0013.bmp", "ANIMATION\\0014.bmp", "ANIMATION\\0015.bmp", "ANIMATION\\0016.bmp", "ANIMATION\\0017.bmp", "ANIMATION\\0018.bmp",
"ANIMATION\\0019.bmp", "ANIMATION\\0020.bmp", "ANIMATION\\0021.bmp", "ANIMATION\\0022.bmp", "ANIMATION\\0023.bmp", "ANIMATION\\0024.bmp",
"ANIMATION\\0025.bmp", "ANIMATION\\0026.bmp", "ANIMATION\\0027.bmp", "ANIMATION\\0028.bmp", "ANIMATION\\0029.bmp", "ANIMATION\\0030.bmp",
"ANIMATION\\0031.bmp", "ANIMATION\\0032.bmp", "ANIMATION\\0033.bmp", "ANIMATION\\0034.bmp", "ANIMATION\\0035.bmp", "ANIMATION\\0036.bmp",
"ANIMATION\\0037.bmp", "ANIMATION\\0038.bmp", "ANIMATION\\0039.bmp", "ANIMATION\\0040.bmp", "ANIMATION\\0041.bmp", "ANIMATION\\0042.bmp",
"ANIMATION\\0043.bmp", "ANIMATION\\0044.bmp", "ANIMATION\\0045.bmp", "ANIMATION\\0046.bmp", "ANIMATION\\0047.bmp", "ANIMATION\\0048.bmp",
"ANIMATION\\0049.bmp", "ANIMATION\\0050.bmp", "ANIMATION\\0051.bmp", "ANIMATION\\0052.bmp", "ANIMATION\\0053.bmp", "ANIMATION\\0054.bmp",
"ANIMATION\\0055.bmp", "ANIMATION\\0056.bmp", "ANIMATION\\0057.bmp", "ANIMATION\\0058.bmp", "ANIMATION\\0059.bmp", "ANIMATION\\0060.bmp",
"ANIMATION\\0061.bmp", "ANIMATION\\0062.bmp", "ANIMATION\\0063.bmp", "ANIMATION\\0064.bmp", "ANIMATION\\0065.bmp", "ANIMATION\\0066.bmp",
"ANIMATION\\0067.bmp", "ANIMATION\\0068.bmp", "ANIMATION\\0069.bmp", "ANIMATION\\0070.bmp", "ANIMATION\\0071.bmp", "ANIMATION\\0072.bmp",
"ANIMATION\\0073.bmp", "ANIMATION\\0074.bmp", "ANIMATION\\0075.bmp", "ANIMATION\\0076.bmp", "ANIMATION\\0077.bmp", "ANIMATION\\0078.bmp",
"ANIMATION\\0079.bmp", "ANIMATION\\0080.bmp", "ANIMATION\\0081.bmp", "ANIMATION\\0082.bmp", "ANIMATION\\0083.bmp", "ANIMATION\\0084.bmp",
"ANIMATION\\0085.bmp", "ANIMATION\\0086.bmp", "ANIMATION\\0087.bmp", "ANIMATION\\0088.bmp", "ANIMATION\\0089.bmp", "ANIMATION\\0090.bmp",
"ANIMATION\\0091.bmp", "ANIMATION\\0092.bmp", "ANIMATION\\0093.bmp", "ANIMATION\\0094.bmp", "ANIMATION\\0095.bmp", "ANIMATION\\0096.bmp",
"ANIMATION\\0097.bmp", "ANIMATION\\0098.bmp", "ANIMATION\\0099.bmp", "ANIMATION\\0100.bmp", "ANIMATION\\0101.bmp", "ANIMATION\\0102.bmp",
"ANIMATION\\0103.bmp", "ANIMATION\\0104.bmp", "ANIMATION\\0105.bmp", "ANIMATION\\0106.bmp", "ANIMATION\\0107.bmp", "ANIMATION\\0108.bmp",
"ANIMATION\\0109.bmp", "ANIMATION\\0110.bmp", "ANIMATION\\0111.bmp", "ANIMATION\\0112.bmp", "ANIMATION\\0113.bmp", "ANIMATION\\0114.bmp",
"ANIMATION\\0115.bmp", "ANIMATION\\0116.bmp", "ANIMATION\\0117.bmp", "ANIMATION\\0118.bmp", "ANIMATION\\0119.bmp", "ANIMATION\\0120.bmp",
"ANIMATION\\0121.bmp", "ANIMATION\\0122.bmp", "ANIMATION\\0123.bmp", "ANIMATION\\0124.bmp", "ANIMATION\\0125.bmp", "ANIMATION\\0126.bmp",
"ANIMATION\\0127.bmp", "ANIMATION\\0128.bmp", "ANIMATION\\0129.bmp", "ANIMATION\\0130.bmp", "ANIMATION\\0131.bmp", "ANIMATION\\0132.bmp",
"ANIMATION\\0133.bmp", "ANIMATION\\0134.bmp", "ANIMATION\\0135.bmp", "ANIMATION\\0136.bmp", "ANIMATION\\0137.bmp", "ANIMATION\\0138.bmp",
"ANIMATION\\0139.bmp", "ANIMATION\\0140.bmp", "ANIMATION\\0141.bmp", "ANIMATION\\0142.bmp", "ANIMATION\\0143.bmp", "ANIMATION\\0144.bmp",
"ANIMATION\\0145.bmp", "ANIMATION\\0146.bmp", "ANIMATION\\0147.bmp", "ANIMATION\\0148.bmp", "ANIMATION\\0149.bmp", "ANIMATION\\0150.bmp",
"ANIMATION\\0151.bmp", "ANIMATION\\0152.bmp", "ANIMATION\\0153.bmp", "ANIMATION\\0154.bmp", "ANIMATION\\0155.bmp", "ANIMATION\\0156.bmp",
"ANIMATION\\0157.bmp", "ANIMATION\\0158.bmp", "ANIMATION\\0159.bmp", "ANIMATION\\0160.bmp", "ANIMATION\\0161.bmp", "ANIMATION\\0162.bmp",
"ANIMATION\\0163.bmp", "ANIMATION\\0164.bmp", "ANIMATION\\0165.bmp", "ANIMATION\\0166.bmp", "ANIMATION\\0167.bmp", "ANIMATION\\0168.bmp",
"ANIMATION\\0169.bmp", "ANIMATION\\0170.bmp", "ANIMATION\\0171.bmp", "ANIMATION\\0172.bmp", "ANIMATION\\0173.bmp", "ANIMATION\\0174.bmp",
"ANIMATION\\0175.bmp", "ANIMATION\\0176.bmp", "ANIMATION\\0177.bmp", "ANIMATION\\0178.bmp", "ANIMATION\\0179.bmp", "ANIMATION\\0180.bmp",
"ANIMATION\\0181.bmp", "ANIMATION\\0182.bmp", "ANIMATION\\0183.bmp", "ANIMATION\\0184.bmp", "ANIMATION\\0185.bmp", "ANIMATION\\0186.bmp",
"ANIMATION\\0187.bmp", "ANIMATION\\0188.bmp", "ANIMATION\\0189.bmp", "ANIMATION\\0190.bmp", "ANIMATION\\0191.bmp", "ANIMATION\\0192.bmp",
"ANIMATION\\0193.bmp", "ANIMATION\\0194.bmp", "ANIMATION\\0195.bmp", "ANIMATION\\0196.bmp", "ANIMATION\\0197.bmp", "ANIMATION\\0198.bmp",
"ANIMATION\\0199.bmp", "ANIMATION\\0200.bmp", "ANIMATION\\0201.bmp", "ANIMATION\\0202.bmp", "ANIMATION\\0203.bmp", "ANIMATION\\0204.bmp",
"ANIMATION\\0205.bmp" };


char anim[70][30] = { "ANIMATION2\\0001.bmp", "ANIMATION2\\0002.bmp", "ANIMATION2\\0003.bmp", "ANIMATION2\\0004.bmp", "ANIMATION2\\0005.bmp", "ANIMATION2\\0006.bmp",
"ANIMATION2\\0007.bmp", "ANIMATION2\\0008.bmp", "ANIMATION2\\0009.bmp", "ANIMATION2\\0010.bmp", "ANIMATION2\\0011.bmp", "ANIMATION2\\0012.bmp",
"ANIMATION2\\0013.bmp", "ANIMATION2\\0014.bmp", "ANIMATION2\\0015.bmp", "ANIMATION2\\0016.bmp", "ANIMATION2\\0017.bmp", "ANIMATION2\\0018.bmp",
"ANIMATION2\\0019.bmp", "ANIMATION2\\0020.bmp", "ANIMATION2\\0021.bmp", "ANIMATION2\\0022.bmp", "ANIMATION2\\0023.bmp", "ANIMATION2\\0024.bmp",
"ANIMATION2\\0025.bmp", "ANIMATION2\\0026.bmp", "ANIMATION2\\0027.bmp", "ANIMATION2\\0028.bmp", "ANIMATION2\\0029.bmp", "ANIMATION2\\0030.bmp",
"ANIMATION2\\0031.bmp", "ANIMATION2\\0032.bmp", "ANIMATION2\\0033.bmp", "ANIMATION2\\0034.bmp", "ANIMATION2\\0035.bmp", "ANIMATION2\\0036.bmp",
"ANIMATION2\\0037.bmp", "ANIMATION2\\0038.bmp", "ANIMATION2\\0039.bmp", "ANIMATION2\\0040.bmp", "ANIMATION2\\0041.bmp", "ANIMATION2\\0042.bmp",
"ANIMATION2\\0043.bmp", "ANIMATION2\\0044.bmp", "ANIMATION2\\0045.bmp", "ANIMATION2\\0046.bmp", "ANIMATION2\\0047.bmp", "ANIMATION2\\0048.bmp",
"ANIMATION2\\0049.bmp", "ANIMATION2\\0050.bmp", "ANIMATION2\\0051.bmp", "ANIMATION2\\0052.bmp", "ANIMATION2\\0053.bmp", "ANIMATION2\\0054.bmp",
"ANIMATION2\\0055.bmp", "ANIMATION2\\0056.bmp", "ANIMATION2\\0057.bmp", "ANIMATION2\\0058.bmp", "ANIMATION2\\0059.bmp", "ANIMATION2\\0060.bmp",
"ANIMATION2\\0061.bmp", "ANIMATION2\\0062.bmp", "ANIMATION2\\0063.bmp", "ANIMATION2\\0064.bmp", "ANIMATION2\\0065.bmp", "ANIMATION2\\0066.bmp",
"ANIMATION2\\0067.bmp", "ANIMATION2\\0068.bmp", "ANIMATION2\\0069.bmp", "ANIMATION2\\0070.bmp" };

char menubrick[8][30] = { "menu\\1.bmp", "menu\\2.bmp", "menu\\3.bmp", "menu\\4.bmp", "menu\\5.bmp",
"menu\\6.bmp", "menu\\7.bmp", "menu\\8.bmp" };

void createl1();     //creating level 1
void createl2();     //creating level 2
void createl3();     //creating level 3
void setpaddle();    //beam or paddle's length,width
void drawbricks();        //brick draw
void set_powerups();    //function containing co ordinates of powerups
void restartball();     //restarting the ball
void updatehighscores(int score, char *name);
void resetpower();
void iBoldText(double LeftX, double LeftY, char ara[]);
void iBoldRectangle(int LeftX, double LeftY, double dx, double dy);
void animationchange();
void menuchange();

void iBoldText(double LeftX, double LeftY, char ara[]){
	iText(LeftX - 1, LeftY, ara, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(LeftX - 1, LeftY - 1, ara, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(LeftX, LeftY - 1, ara, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(LeftX, LeftY, ara, GLUT_BITMAP_TIMES_ROMAN_24);
}

void iBoldRectangle(int LeftX, double LeftY, double dx, double dy){
	iRectangle(LeftX, LeftY, dx, dy);
	iRectangle(LeftX - 1, LeftY - 1, dx + 2, dy + 2);
	iRectangle(LeftX + 1, LeftY + 1, dx - 2, dy - 2);
}

void imusic(int m)
{
	if (m == 1)
	{
		PlaySound("bgmusic2.wav", NULL, SND_ASYNC | SND_LOOP);

	}
	else
	{
		PlaySound("click.wav", NULL, SND_ASYNC);

	}

}

void ieffectmusic(int n)
{
	if (n == 1)
	{
		PlaySound("brick.wav", NULL, SND_ASYNC);
	}
	else
	{
		PlaySound("", NULL, SND_ASYNC);
	}
}

void startanimationchange()
{
	startanimindex++;
	if (startanimindex == 205)
	{
		State = 1;
		return;
	}
}

void animationchange()
{
	animindex++;
	if (animindex == 70)
	{
		State = 4;
	}
}

void menuchange()
{
	menuindex++;
	if (menuindex >= 8)
	{
		menuindex = 0;
	}
}

void powerup(){

	if (!present[shooter.brick] && !shooter.trigger){

		/*if the brick having shooter powerup disappear & trigger is on(means hitting that brick)
		shooter powerup will activate*/

		shc.y -= ps;  //powerup rectangle will be coming to under the screen in ps speed
		shc.l = 100;    //powerup length will be 10 then which was 0 before for not showing that

		if (shc.x >= bpx && shc.x <= bpx + sw && shc.y >= 10 && shc.y <= sl + 10){

			//whether hits the beam

			shooter.caught = 1; //beam caught the powerup
			shooter.trigger = 1; //hitting the brick having powerup
			shc.l = 0;   //vanishing the powerup image by making length 0
			//sw = 100;   /*not activating when the big or small beam powerup is on;
						//so only the beam having 100 length will be available for shooter powerup*/
			//fireball.caught = 0; //deactivating fireball powerup
			//bbeam.caught = 0;   //deactivating big beam powerup
			//sbeam.caught = 0;   //deactivating small beam powerup
		}
		if (shc.y<0) shooter.trigger = 1, shc.l = 0;
		/*after activating current powerup;the powerup will be deactivated*/
	}

	if (!present[bbeam.brick] && !bbeam.trigger){//for big beam powerup likewise shooter powerup

		bbc.y -= ps;
		bbc.l = 10000;
		if (bbc.x >= bpx && bbc.x <= bpx + sw && bbc.y >= 10 && bbc.y <= sl + 10){
			bbeam.caught = 1;
			bbeam.trigger = 1;
			bbc.l = 0;
			sw = 200;
			//shooter.caught = 0;
			sbeam.caught = 0;
			//fireball.caught = 0;
		}
		if (bbc.y<0) bbeam.trigger = 1, bbc.l = 0;
	}

	if (!present[sbeam.brick] && !sbeam.trigger){
		sbc.y -= ps;
		sbc.l = 10;
		if (sbc.x >= bpx && sbc.x <= bpx + sw && sbc.y >= 0 && sbc.y <= sl){
			sbeam.caught = 1;
			sbeam.trigger = 1;
			sbc.l = 0;
			sw = 50;
			//shooter.caught = 0;
			//.caught = 0;
			//fireball.caught = 0;
		}
		if (sbc.y<0) sbeam.trigger = 1, sbc.l = 0;
	}

	if (!present[fireball.brick] && !fireball.trigger){
		fic.y -= ps;
		fic.l = 10;
		if (fic.x >= bpx && fic.x <= bpx + sw && fic.y >= 0 && fic.y <= sl){
			fireball.caught = 1;
			fireball.trigger = 1;
			fic.l = 0;
			sw = 100;
			//shooter.caught = 0;
			//bbeam.caught = 0;
			//sbeam.caught = 0;
		}
		if (fic.y<0) fireball.trigger = 1, fic.l = 0;
	}
}

void Shooter(){  //for shooting when trigger is on(means trigger 0)
	int c = 0;
	if (shooter.caught&&shooter_repeat){ //caught by beam & shooter repeat is on(while entering space)

		for (int i = 0; i<j; ++i){
			if (present[i] == 0) continue; //if brick doesn't exist,will not be affected

			if (shx[1] >= bricks[i][0] && shx[1] <= bricks[i][0] + bw&&shy[1] >= bricks[i][1] && shy[1] <= bricks[i][1] + bl){

				/*whether the brick affected by the shoot;here shy[1] is always changing
				according to the for loop mentioned under*/
				ieffectmusic(effectmusic);
				present[i] = 0;  //removing that particular brick
				--brickcount;
				point += 10;  //brick number decreasing
				sprintf(s, "%d", point);
				c = 1;
				break;  //if any condition of this or the following is true;brick will remove
			}
		}

		for (int i = 0; i<j; ++i){
			if (present[i] == 0) continue;
			if (shx2[1] >= bricks[i][0] && shx2[1] <= bricks[i][0] + bw&&shy[1] >= bricks[i][1] && shy[1] <= bricks[i][1] + bl){
				ieffectmusic(effectmusic);
				present[i] = 0;
				--brickcount;
				point += 10;
				sprintf(s, "%d", point);
				c = 1;
				break;
			}
		}
		if (c) shy[1] = resy + 10;  //when out of resolution;again will show the shooting triangle

		if (shy[1] >= resy){

			//reconstracting the shooting triangle & making it flexible while moving the beam

			shooter_repeat = 0;
			for (int i = 0; i<3; ++i){
				shy[i] = sl + (i % 2) * 10 + 10;
			}
			for (int i = 0; i<3; ++i){
				shx[i] = bpx + i * 5;
				shx2[i] = shx[i] + sw - 10;
			}
			return;
		}
		for (int i = 0; i<3; ++i){ //in the time of shooting,moving the shooting triangle
			shy[i] += 10;
		}
	}
}

void ballChange(){

	if (timer){
		if (ball_x >= bpx&&ball_x <= bpx + sw&&ball_y >= 0 && ball_y <= bpy + 7 + sl&&dy<0){//collision of beam & ball
			dy = -dy;
			

		}
		else {
			for (int i = 0; i<j; ++i){
				if (present[i] == 0) continue;
				if ((ball_x + r >= bricks[i][0] && ball_x + r <= bricks[i][0] + bw&&ball_y + r >= bricks[i][1] && ball_y + r <= bricks[i][1] + bl) ||
					(ball_x + r >= bricks[i][0] && ball_x + r <= bricks[i][0] + bw&&ball_y - r >= bricks[i][1] && ball_y - r <= bricks[i][1] + bl) ||
					(ball_x - r >= bricks[i][0] && ball_x - r <= bricks[i][0] + bw&&ball_y - r >= bricks[i][1] && ball_y - r <= bricks[i][1] + bl) ||
					(ball_x - r >= bricks[i][0] && ball_x - r <= bricks[i][0] + bw&&ball_y + r >= bricks[i][1] && ball_y + r <= bricks[i][1] + bl)){

					ieffectmusic(effectmusic);
					present[i] = 0;  //removing the brick when collited
					if (!fireball.caught) dy = -dy;
					//fireball powerup never allows ball to reflect
					--brickcount;
					point += 10;
					sprintf(s, "%d", point);
					break;
				}
			}
			if (ball_y <= sl)
			{
				

				restartball();
			}
		}
		if (ball_x + 5 > resx || ball_x + 5 < 0)dx = -dx;//not allowed to go out of screen
		if (ball_y + 5 > resy || ball_y + 5 < 0)dy = -dy;//not allowed to go out of screen

		ball_x += dx, ball_y += dy;
		//movement of ball
	}
}

void restartball()
{
	life--;
	dx = 7;
	dy = 10;
	bpx = 260;
	bpy = 15;
	ball_x = bpx + 50;
	ball_y = bpy + 10;
	setpaddle();
	fireball.caught = 0;
	sbeam.caught = 0;
	bbeam.caught = 0;
	shooter.caught = 0;
	timer = 0;
}

void set_powerups(){

	/*setting the co ordinates of the powerups*/

	shc.x = bricks[shooter.brick][0];
	shc.y = bricks[shooter.brick][1];
	shc.l = 0; //at first giving the length 0,as not to show
	bbc.x = bricks[bbeam.brick][0];
	bbc.y = bricks[bbeam.brick][1];
	bbc.l = 0;
	sbc.x = bricks[sbeam.brick][0];
	sbc.y = bricks[sbeam.brick][1];
	sbc.l = 0;
	fic.x = bricks[fireball.brick][0]; 
	fic.y = bricks[fireball.brick][1];
	fic.l = 0;
}

void setpaddle(){ //height and width of the beam
	sw = 100;
	sl = 15;
}


void createl1(){
	k++;

	shooter.brick = 8;
	bbeam.brick = 25;
	sbeam.brick = 65;
	fireball.brick = 56;
	brickcount = 0;
	j = 0;
	bl = 40;
	bw = 70;
	
	offsetx = 40;
	offsety = 40;
	layer = 6;
	int odd = 0;
	int i23 = bl + offsety;  //the gap between screen height and upper portion of brick
	int ly = 0;
	int skip_row1, skip_row2;
	skip_row1 = 2;  //gap at th no row
	skip_row2 = 5;
	int vd = 3; //gap between some cols happen
	gapx = 2;
	gapy = 2;

	for (int i22 = 1; i22 <= layer; ++i22){
		
		++ly; //layer control
		for (int i = 2 * offsetx; i<resx - 3 * offsetx; i += (bw + gapx)){
		
			bricks[j][0] = i;
			bricks[j][1] = resy - i23;
			j++;
			++brickcount;
		}
		if (ly == skip_row1 || ly == skip_row2) i23 += 2 * (bl + gapy);//in these cases no brick will be created in 2 rows
		i23 += bl + gapy;
	}
	for (int i = 0; i<500; ++i) present[i] = 0;
	for (int i = 0; i<j; ++i) present[i] = 1;
	resetpower();
}

void createl2(){
	z++;
	//srand(time(0));
	shooter.brick = 8;
	bbeam.brick = 25;
	sbeam.brick = 65;
	fireball.brick = 56;
	brickcount = 0;
	j = 0;
	bl = 40;
	bw = 70;
	//srand(time(0));
	offsetx = 40;
	offsety = 40;
	layer = 6;
	int odd = 0;
	int i23 = bl + offsety;  //the gap between screen height and upper portion of brick
	int ly = 0;
	int skip_row1, skip_row2;
	skip_row1 = 2;  //gap at th no row
	skip_row2 = 5;
	int vd = 3; //gap between some cols happen
	gapx = 2;
	gapy = 2;

	for (int i22 = 1; i22 <= layer; ++i22){
		odd = 0;
		++ly; //layer control
		for (int i = 2 * offsetx; i<resx - 3 * offsetx; i += (bw + gapx)){
			++odd; //at one layer,brick control
			if (odd>(7 - (vd + 1) / 2) && odd <= (7 + (vd + 1) / 2) && ly>2 && ly<layer - 1){//in these cases,no brick will be created in the columns
				continue;
			}
			bricks[j][0] = i;
			bricks[j][1] = resy - i23;
			j++;
			++brickcount;
		}
		if (ly == skip_row1 || ly == skip_row2) i23 += 2 * (bl + gapy);//in these cases no brick will be created in 2 rows
		i23 += bl + gapy;
	}
	for (int i = 0; i<500; ++i) present[i] = 0;
	for (int i = 0; i<j; ++i) present[i] = 1;


	resetpower();

}

void createl3(){
	w++;
	shooter.brick = 14;
	bbeam.brick = 49;
	sbeam.brick = 30;
	fireball.brick = 1;
	brickcount = 0;
	gapx = 10;
	gapy = 10;
	j = 0;
	bl = 39;
	bw = 79;
	int ly = 0;
	offsetx = 80;
	offsety = 60;
	layer = 5 + rand() % 3;
	int i23 = bl + offsety;
	int skip_row1 = 2 + rand() % 2;
	int skip_row2 = 5 + rand() % 3;
	for (int i22 = 1; i22 <= layer; ++i22)
	{
		++ly;
		for (int i = (layer - i22)*offsetx; i <= resx - (layer + 1 - i22)*offsetx; i += (bw + gapx))
		{
			bricks[j][0] = i;
			bricks[j][1] = resy - i23;
			j++;
			++brickcount;
		}
		if (ly == skip_row1 || ly == skip_row2) i23 += 2 * (bl + gapy);
		i23 += bl + gapy;
	}
	for (int i = 0; i<j; i++){ present[i] = 1; }
	resetpower();

}

void resetpower(){
	sw = 100;
	shooter.trigger = 0;
	shooter.caught = 0;
	shooter_repeat = 0;
	for (int i = 0; i<3; ++i){
		shy[i] = sl + (i % 2) * 10 + 10;
	}
	for (int i = 0; i<3; ++i){
		shx[i] = bpx + i * 5;
		shx2[i] = shx[i] + sw - 10;
	}
	bbeam.trigger = 0;
	bbeam.caught = 0;
	sbeam.trigger = 0;
	sbeam.caught = 0;
	fireball.trigger = 0;
	fireball.caught = 0;
	set_powerups();
}


void drawbricks(){
	for (int i = 0; i<j; ++i){
		if (present[i]){
			if (level % 3 == 1){
				iShowBMP(bricks[i][0], bricks[i][1], brickl1[k]);
				if (k >= 3){ k = 0; }
				iSetColor(255, 0, 0);
				sprintf(l, "%d", level);
				iBoldText(560, 620, "LEVEL");
				iBoldText(640, 620, l);
			}
			else if (level % 3 == 2){
				iShowBMP(bricks[i][0], bricks[i][1], brickl2[z]);
				if (z >= 3){ z = 0; }
				iSetColor(255, 0, 0);
				sprintf(l, "%d", level);
				iBoldText(560, 620, "LEVEL");
				iBoldText(640, 620, l);
			}
			else{
				iShowBMP(bricks[i][0], bricks[i][1], brickl3[w]);
				if (w >= 3){ w = 0; }
				iSetColor(255, 0, 0);
				sprintf(l, "%d", level);
				iBoldText(560, 620, "LEVEL");
				iBoldText(640, 620, l);

			}
		}
	}
}

void updatehighscores(int score, char *name)
{
	FILE *fp;
	fp = fopen("highscores.txt", "r");
	int topscores[3];
	char plr[3][100];
	int i, j;
	for (i = 0; i<3; i++)
	{
		fscanf(fp, "%s %d", plr[i], &topscores[i]);
	}

	for (i = 0; i<3; i++)
	{
		if (score>topscores[i])
		{
			for (j = 2; j>i; j--)
			{
				topscores[j] = topscores[j - 1];
				strcpy(plr[j], plr[j - 1]);
			}
			topscores[i] = score;
			strcpy(plr[i], name);
			break;
		}
	}
	fclose(fp);
	fp = fopen("highscores.txt", "w");
	for (i = 0; i<3; i++)
	{
		fprintf(fp, "%s %d\n", plr[i], topscores[i]);
	}
	fclose(fp);

}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void iDraw()
{
	if (brickcount == 0){
		++level;
		if (level % 3 == 1) {
			createl1();
			bpx = 260;
			bpy = 15;
			ball_x = bpx + 50;
			ball_y = bpy + 20;
			timer = 0;
		}
		else if (level % 3 == 2) {
			createl2();
			bpx = 260;
			bpy = 15;
			ball_x = bpx + 50;
			ball_y = bpy + 20;
			timer = 0;
		}
		else if (level % 3 == 0){
			createl3();
			bpx = 260;
			bpy = 15;
			ball_x = bpx + 50;
			ball_y = bpy + 20;
			timer = 0;
		}
		return;
	}

	iClear();
	if (State == 0)
	{
		iShowBMP(0, 0, startanim[startanimindex]);
		iText(415, 150, "PRESS SPACE TO CONTINUE", GLUT_BITMAP_TIMES_ROMAN_24);
		return;
	}
	if (State == 1){
		iShowBMP(00, 00, "bg 1.bmp");
		iText(415, 150, "PRESS SPACE TO CONTINUE", GLUT_BITMAP_TIMES_ROMAN_24);
		return;
	}


	if (State == 2){
		iClear();
		iShowBMP(0, 0, menubrick[menuindex]);
		

		iSetColor(255, 255, 255);
		iBoldRectangle(520, 405, 170, 50);
		iText(540, 420, "NEW GAME", GLUT_BITMAP_TIMES_ROMAN_24);
		iBoldRectangle(520, 335, 170, 50);
		iText(535, 350, "HIGH SCORE", GLUT_BITMAP_TIMES_ROMAN_24);
		iBoldRectangle(520, 265, 170, 50);
		iText(555, 280, "CREDITS", GLUT_BITMAP_TIMES_ROMAN_24);
		iBoldRectangle(510, 195, 190, 50);
		iText(520, 210, "INSTRUCTIONS", GLUT_BITMAP_TIMES_ROMAN_24);
		iBoldRectangle(520, 125, 170, 50);
		iText(547, 140, "SETTINGS", GLUT_BITMAP_TIMES_ROMAN_24);
		iBoldRectangle(520, 55, 170, 50);
		iText(575, 70, "EXIT", GLUT_BITMAP_TIMES_ROMAN_24);
		if (menu == 1)
		{
			iSetColor(0, 210, 255);
			iBoldRectangle(520, 405, 170, 50);
			iBoldText(540, 420, "NEW GAME");
		}

		if (menu == 2)
		{
			iSetColor(0, 210, 255);
			iBoldRectangle(520, 335, 170, 50);
			iBoldText(535, 350, "HIGH SCORE");

		}
		if (menu == 3)
		{
			iSetColor(0, 210, 255);
			iBoldRectangle(520, 265, 170, 50);
			iBoldText(555, 280, "CREDITS");
		}
		if (menu == 4)
		{
			iSetColor(0, 210, 255);
			iBoldRectangle(510, 195, 190, 50);
			iBoldText(520, 210, "INSTRUCTIONS");

		}
		if (menu == 5)
		{
			iSetColor(0, 210, 255);
			iBoldRectangle(520, 125, 170, 50);
			iBoldText(547, 140, "SETTINGS");

		}
		if (menu == 6)
		{
			iSetColor(255, 0, 0);
			iBoldRectangle(520, 55, 170, 50);
			iBoldText(575, 70, "EXIT");
		}

		return;

		//return means will not execute next part of idraw() function
	}



	if (State == 3){
		iShowBMP(0, 0, "state 3 image.bmp");
		iText(390, 380, name, GLUT_BITMAP_TIMES_ROMAN_24);
		return;
	}

	if (State == 5){
		iShowBMP(0, 0, "AAA.bmp");
		iSetColor(0, 255, 255);
		iBoldText(490, 460, "NAME");
		iBoldText(620, 460, "SCORE");
		highscores = 1;

		//printing highscores
		char player[3][100];
		char scores[3][100];
		int l;
		FILE *f;
		f = fopen("highscores.txt", "r");
		for (l = 0; l<3; l++){
			fscanf(f, "%s %s", player[l], scores[l]);
		}
		fclose(f);
		//printing the names
		iSetColor(255, 255, 0);
		iBoldText(500, 410, player[0]);
		iBoldText(500, 330, player[1]);
		iBoldText(500, 250, player[2]);
		//printing the scores
		iBoldText(640, 410, scores[0]);
		iBoldText(640, 330, scores[1]);
		iBoldText(640, 250, scores[2]);
		return;
	}

	if (State == 6)
	{
		iShowBMP(0, 0, "credits.bmp");
		credits = 1;
		return;
	}

	if (State == 7)
	{
		iShowBMP(0, 0, "instruct.bmp");
		instruct = 1;
		return;
	}
	if (State == 9)
	{
		iShowBMP(0, 0, "settingsspecial.bmp");
		settings = 1;
		iSetColor(0, 255, 255);
		iBoldText(495, 350, "ON");
		iBoldRectangle(480, 345, 65, 25);
		iBoldText(575, 350, "OFF");
		iBoldRectangle(560, 345, 80, 25);
		iBoldText(495, 200, "ON");
		iBoldRectangle(480, 195, 65, 25);
		iBoldText(575, 200, "OFF");
		iBoldRectangle(560, 195, 80, 25);
		iSetColor(0, 0, 0);
		iBoldText(470, 110, "select background");
		if (settingsmenu == 1)
		{
			iSetColor(0, 0, 255);
			iBoldText(495, 350, "ON");
			iBoldRectangle(480, 345, 65, 25);
		}
		else if (settingsmenu == 2)
		{
			iSetColor(255, 0, 0);
			iBoldText(575, 350, "OFF");
			iBoldRectangle(560, 345, 80, 25);
		}
		else if (settingsmenu == 3)
		{
			iSetColor(0, 0, 255);
			iBoldText(495, 200, "ON");
			iBoldRectangle(480, 195, 65, 25);
		}
		else if (settingsmenu == 4)
		{
			iSetColor(255, 0, 0);
			iBoldText(575, 200, "OFF");
			iBoldRectangle(560, 195, 80, 25);
		}
		else if (settingsmenu == 5)
		{
			iSetColor(255, 255, 0);
			iBoldText(470, 110, "select background");
		}
		return;
	}
	if (State == 10)
	{
		iShowBMP(0, 0, "exit.bmp");
		iShowBMP(400, 300, "quit.bmp");
		if (menu == 7)
		{
			iSetColor(255, 0, 0);
			iBoldRectangle(409, 310, 185, 50);

		}
		if (menu == 8)
		{
			iSetColor(0, 255, 0);
			iBoldRectangle(605, 310, 185, 50);
		}
		return;

	}
	if (State == 11)
	{
		iShowBMP(0, 0, "backcolor.bmp");
		iSetColor(0, 0, 0);
		iBoldText(560, 420, "Black");
		iBoldText(535, 350, "chocolate");
		iBoldText(525, 280, "tyrian purple");
		iBoldText(518, 210, "bulgarian rose");
		iBoldText(528, 140, "dark green");
		if (bgcolor == 0)
		{
			iSetColor(0, 255, 0);
			iBoldText(560, 420, "black");
		}
		if (bgcolor == 1)
		{
			iSetColor(0, 255, 0);
			iBoldText(535, 350, "chocolate");
		}
		if (bgcolor == 2)
		{
			iSetColor(0, 255, 0);
			iBoldText(525, 280, "tyrian purple");
		}
		if (bgcolor == 3)
		{
			iSetColor(0, 255, 0);
			iBoldText(518, 210, "bulgarian rose");
		}
		if (bgcolor == 4)
		{
			iSetColor(0, 255, 0);
			iBoldText(528, 140, "dark green");
		}
		return;
	}

	if (State == 12 && p == 1){
		iShowBMP(0, 0, anim[animindex]);
		return;
	}

	if (background == 0)
	{
		iSetColor(0, 0, 0);
	}
	else if (background == 1)
	{
		iSetColor(102, 51, 0);
	}
	else if (background == 2)
	{
		iSetColor(64, 0, 77);
	}
	else if (background == 3)
	{
		iSetColor(51, 0, 0);
	}
	else if (background == 4)
	{
		iSetColor(0, 51, 26);
	}
	iFilledRectangle(0, 0, resx, resy);

	iSetColor(0, 0, 255);
	if (life == 5){ iBoldText(1000, 620, "LIFE X 5"); }
	if (life == 4){ iBoldText(1000, 620, "LIFE X 4"); }
	if (life == 3){ iBoldText(1000, 620, "LIFE X 3"); }
	if (life == 2){ iBoldText(1000, 620, "LIFE X 2"); }
	if (life == 1){ iBoldText(1000, 620, "LIFE X 1"); }

	iText(80, 620, "POINT", GLUT_BITMAP_TIMES_ROMAN_24);
	iBoldText(160, 620, s);

	iSetColor(255, 0, 255);
	iFilledRectangle(bpx, bpy, sw, sl);
	if (bbeam.caught) iShowBMP(bpx, bpy, "Paddle.bmp");
	else if (sbeam.caught) iShowBMP(bpx, bpy, "Paddle3.bmp");
	else iShowBMP(bpx, bpy, "Paddle2.bmp");
	iSetColor(115, 120, 124);
	if (fireball.caught) iSetColor(255, 0, 0);
	iFilledCircle(ball_x, ball_y, r, 50);
	drawbricks();
	//iSetColor(255, 105, 180);
	if (!present[shooter.brick] && !shooter.trigger){ iShowBMP(shc.x, shc.y, "shooting.bmp"); }
	if (!present[bbeam.brick] && !bbeam.trigger){ iShowBMP(bbc.x, bbc.y, "megabeam_powerup.bmp"); }
	if (!present[sbeam.brick] && !sbeam.trigger){ iShowBMP(sbc.x, sbc.y, "minibeam_powerup.bmp"); }
	if (!present[fireball.brick] && !fireball.trigger){ iShowBMP(fic.x, fic.y, "Fire Ball.bmp"); }
	iSetColor(115, 120, 255);
	if (shooter.caught){
		iSetColor(115, 120, 124);
		iFilledPolygon(shx, shy, 3);
		iFilledPolygon(shx2, shy, 3);
	}
	if (life == 0)
	{
		iShowBMP(0, 0, "gameover.bmp");
		iBoldText(470, 500, "YOUR SCORE IS");//showing score
		sprintf(s, "%d", point);
		iBoldText(660, 500, s);

	}

}

void iMouseMove(int mx, int my)
{
	if (mx + sw / 2>resx || mx - sw / 2 <= 0) return; //not allowing the beam to go outside
	bpx = mx - sw / 2;
	if (!shooter_repeat){ //shooter not activating,creating the shooting triangle
		for (int i = 0; i<3; ++i){
			shx[i] = bpx + i * 5;
			shx2[i] = shx[i] + sw - 10;
		}
	}
	if (!timer)
	{
		ball_x = mx; //while restarting keeping the ball with the beam
	}
}


//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	if (State == 2)
	{
		if (mx >= 520 && mx <= 690 && my >= 405 && my <= 465)
		{
			menu = 1;
		}
		else if (mx >= 520 && mx <= 690 && my >= 335 && my <= 385)
		{
			menu = 2;
		}
		else if (mx >= 520 && mx <= 690 && my >= 265 && my <= 315)
		{
			menu = 3;
		}
		else if (mx >= 510 && mx <= 700 && my >= 195 && my <= 245)
		{
			menu = 4;
		}
		else if (mx >= 520 && mx <= 690 && my >= 125 && my <= 175)
		{
			menu = 5;
		}
		else if (mx >= 520 && mx <= 690 && my >= 55 && my <= 105)
		{
			menu = 6;
		}
		else
		{
			menu = 0;
		}
	}

	if (State == 9)
	{
		if (mx >= 480 && mx <= 545 && my >= 345 && my <= 370)
		{
			settingsmenu = 1;
		}
		else if (mx >= 560 && mx <= 640 && my >= 345 && my <= 370)
		{
			settingsmenu = 2;
		}
		else if (mx >= 480 && mx <= 545 && my >= 195 && my <= 220)
		{
			settingsmenu = 3;
		}
		else if (mx >= 560 && mx <= 640 && my >= 195 && my <= 220)
		{
			settingsmenu = 4;
		}
		else if (mx >= 470 && mx <= 645 && my >= 110 && my <= 130)
		{
			settingsmenu = 5;
		}
		else
		{
			settingsmenu = 0;
		}
	}

	if (State == 10)
	{
		if (mx >= 405 && mx <= 595 && my >= 305 && my <= 365)
		{
			menu = 7;
		}
		if (mx >= 605 && mx <= 795 && my >= 305 && my <= 365)
		{
			menu = 8;
		}
	}

	if (State == 11)
	{
		if (mx >= 560 && mx <= 605 && my >= 420 && my <= 440)
		{
			bgcolor = 0;
		}
		else if (mx >= 535 && mx <= 648 && my >= 350 && my <= 365)
		{
			bgcolor = 1;
		}
		else if (mx >= 525 && mx <= 653 && my >= 280 && my <= 300)
		{
			bgcolor = 2;
		}
		else if (mx >= 518 && mx <= 660 && my >= 210 && my <= 230)
		{
			bgcolor = 3;
		}
		else if (mx >= 528 && mx <= 640 && my >= 140 && my <= 160)
		{
			bgcolor = 4;
		}
		else
		{
			bgcolor = -1;
		}
	}
}


void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (State == 2 || State == 9 || State == 10){//click er sound koi kaj kore
			if (music == 0){ PlaySound("click.wav", NULL, SND_ASYNC); }
		}
		if (State == 2 && mx >= 520 && mx <= 690 && my >= 405 && my <= 465) State = 3; //New game
		if (State == 2 && mx >= 520 && mx <= 690 && my >= 335 && my <= 385) State = 5; //High scores
		if (State == 2 && mx >= 520 && mx <= 690 && my >= 265 && my <= 315) State = 6; //credits
		if (State == 2 && mx >= 510 && mx <= 700 && my >= 195 && my <= 245) State = 7; //instructions
		if (State == 2 && mx >= 520 && mx <= 690 && my >= 125 && my <= 175) State = 9; //settings
		if (State == 2 && mx >= 520 && mx <= 690 && my >= 55 && my <= 105) State = 10;//exit

		if (State == 3 && mx >= 345 && mx <= 740 && my >= 348 && my <= 415) textin = 1;//click to enter name

		if (State == 9 && mx >= 480 && mx <= 545 && my >= 345 && my <= 370)
		{
			music = 1;
			imusic(music);
		}
		if (State == 9 && mx >= 560 && mx <= 640 && my >= 345 && my <= 370)
		{
			music = 0;
			imusic(music);
		}
		if (State == 9 && mx >= 480 && mx <= 545 && my >= 195 && my <= 220)
		{
			effectmusic = 1;
		}
		if (State == 9 && mx >= 560 && mx <= 640 && my >= 195 && my <= 220)
		{
			effectmusic = 0;
		}
		if (State == 9 && mx >= 470 && mx <= 645 && my >= 110 && my <= 130)
		{
			State = 11;
		}
		if (State == 10 && mx >= 405 && mx <= 595 && my >= 305 && my <= 365){ exit(0); }
		if (State == 10 && mx >= 605 && mx <= 795 && my >= 305 && my <= 365){ State = 2; }

		if (State == 11)
		{
			if (mx >= 560 && mx <= 605 && my >= 420 && my <= 440)
			{
				background = 0;
			}
			else if (mx >= 535 && mx <= 648 && my >= 350 && my <= 365)
			{
				background = 1;
			}
			else if (mx >= 525 && mx <= 653 && my >= 280 && my <= 300)
			{
				background = 2;
			}
			else if (mx >= 518 && mx <= 660 && my >= 210 && my <= 230)
			{
				background = 3;
			}
			else if (mx >= 528 && mx <= 640 && my >= 140 && my <= 160)
			{
				background = 4;
			}
		}

	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		timer = 1;
	}
}


void iKeyboard(unsigned char key)
{
	static int k = 0;
	if (key == ' '&& shooter.caught){
		shooter_repeat = 1;
		if (effectmusic == 1){ PlaySound("shooter.wav", NULL, SND_ASYNC); }
	}
	else if (key == ' ' && (State == 1 || State == 0)){
		iPauseTimer(4);
		State = 2;
	}
	else if (State == 3 && textin){
		if (key == '\r'){
			p++;
			State = 12;
			iResumeTimer(3);
			iResumeTimer(0); //resuming the pause moment declared at main
			iResumeTimer(1);
			iResumeTimer(2);

		}
		else{
			name[k++] = key;
			name[k] = '\0';

		}
	}

	if (life == 0)
	{
		p = 0;
		animindex = 0;
		iPauseTimer(3);
		int score = point;
		updatehighscores(score, name);
		if (key == '\r')
		{
			exit(0);
		}
		else if (key == 'k')  //returning to main menu
		{
			level = 1;
			life = 3;
			State = 2;
			timer = 0;
			textin = 1;
			createl1();
			resetpower();
			drawbricks();
			set_powerups();
			for (int i = 0; i<3; ++i){
				shx[i] = 0 + i * 5;
				shx2[i] = shx[i] + sw - 10;
			}
			for (int i = 0; i<3; ++i){
				shy[i] = sl + (i % 2) * 10 + 10;
			}
			point = 0;
			sprintf(s, "%d", point);
			imusic(music);
		}
	}

	if (key == 'p')
	{

		iPauseTimer(0);
		iPauseTimer(1);
		iPauseTimer(2);

	}
	if (key == 'r')
	{
		iResumeTimer(0);
		iResumeTimer(1);
		iResumeTimer(2);

	}
	if (State != 3){
		if (key == 'b'){
			State = 2;
			return;
		}
	}

}

void iSpecialKeyboard(unsigned char key)
{
	if (!shooter_repeat){ //shooter not activating,creating the shooting triangle
		for (int i = 0; i<3; ++i){
			shx[i] = bpx + i * 5;
			shx2[i] = shx[i] + sw - 10;
		}
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if (bpx<resx - sw - 5)
		{
			bpx += 15;
			if (!shooter_repeat){
				for (int i = 0; i<3; ++i){
					shx[i] += 15;
					shx2[i] += 15;
				}
			}
			if (!timer)
			{
				ball_x += 15;
			}
		}

	}
	if (key == GLUT_KEY_LEFT)
	{
		if (bpx>5){
			bpx -= 15;
			if (!shooter_repeat){
				for (int i = 0; i<3; ++i){
					shx[i] -= 15;
					shx2[i] -= 15;
				}
			}
			if (!timer)
			{
				//ball_x -= 15;
			}
		}
		if (bpx < 0)
		{
			bpx = 0;
		}

	}

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
}

int main()
{
	iSetTimer(25, ballChange);
	iPauseTimer(0);
	iSetTimer(1, powerup);
	iPauseTimer(1);
	iSetTimer(1, Shooter);
	iPauseTimer(2);
	iSetTimer(200, animationchange);
	iPauseTimer(3);
	iSetTimer(3, startanimationchange);
	iSetTimer(600, menuchange);
	setpaddle();
	bpx = 260;
	bpy = 15;
	ball_x = bpx + 50;
	ball_y = bpy + sl + r;
	dx = 8;
	dy = 11;
	life = 5;
	sprintf(s, "%d", point);  //conversion the point to string
	createl1();
	//set_powerups();



	imusic(music);
	iInitialize(resx, resy, "DX BALL");
	iStart();
	return 0;
}
