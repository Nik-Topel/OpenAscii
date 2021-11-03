#include<stdio.h>
#include<math.h>
#include"draw.h"

int c;
int r;
char f[30000];

int cords_t_pixels(int p, float i){return i / (1.0 / (p-0.5));}

void draw_background(char i){
	int x;
	for(x = 0; x < (r * c); x = x + 1){
		f[x] = i;
	}
}
void draw_pixel(char i,int x, int y){
	f[(((r-(y +1))*c)+x)] = i;
}
void draw_pixel_real(char i,int x, int y){
	draw_pixel(i,cords_t_pixels(c, x),cords_t_pixels(r, y));
}
void draw_rect(char i,int x1, int y1,int x2, int y2){
	int x,y;
	for(x = x1; x < x2; x = x + 1){
		for(y = y1; y < y2; y = y + 1){
			draw_pixel(i,x,y);
		}
	}
}
void draw_rect_real(char i,float x1, float y1,float x2, float y2){
	draw_rect(i,cords_t_pixels(c, x1),cords_t_pixels(r, y1),cords_t_pixels(c, x2),cords_t_pixels(r, y2));
}
void draw_line(char i,float x1, float y1,float x2, float y2){
	int x;
	int y;
	if(y2<y1){
		float tmp1= y2;
		y2 = y1;
		y1= tmp1;
		float tmp2= x2;
		x2 = x1;
		x1 = tmp2;
	}
	if(x2<x1){
		float tmp1= x2;
		x2 = x1;
		x1 = tmp1;
		float tmp2= y2;
		y2 = y1;
		y1 = tmp2;
	}
	if((y2-y1)<=(x2-x1)){
		for(x= x1;x<x2;x=x+1){
			y = (((x-x1)/(x2-x1))*(y2-y1))+y1+0.5;
			draw_pixel(i,x,y);
		}
	}
	if((x2-x1)<(y2-y1)){
		for(x= y1;x<y2;x=x+1){
			y = (((y-y1)/(y2-y1))*(x2-x1))+x1+0.5;
			draw_pixel(i,y,x);
		}
	}
}
void draw_line_real(char i,float x1, float y1,float x2, float y2){
	draw_line(i,cords_t_pixels(c, x1),cords_t_pixels(r, y1),cords_t_pixels(c, x2),cords_t_pixels(r, y2));
}
void draw_tri(char i,float x1, float y1,float x2, float y2,float x3, float y3){
	draw_line(i,x1,y1,x2,y2);
	draw_line(i,x2,y2,x3,y3);
	draw_line(i,x3,y3,x1,y1);
	float diff_X = x3 - x2;
    float diff_Y = y3 - y2;
    int pointNum = sqrt(((x3-x2)*(x3-x2))+((y3-y2)*(y3-y2)));
    float interval_X = diff_X / (pointNum + 1);
    float interval_Y = diff_Y / (pointNum + 1);
	int x;
    for(x = 1; x <= pointNum; x=x+1)
    {
		draw_line(i,x1,y1,x2+interval_X*x,y2 + interval_Y*x);
    }
}
void draw_tri_real(char i,float x1, float y1,float x2, float y2,float x3, float y3){
	draw_tri(i,cords_t_pixels(c, x1),cords_t_pixels(r, y1),cords_t_pixels(c, x2),cords_t_pixels(r, y2),cords_t_pixels(c, x3),cords_t_pixels(r, y3));
}
//void draw_polygon(char i,float cords[20]){
	//int x;
	//for(x=0;x<1;x=x+1){
		
	//}
//}
void draw_frame(){
	draw_background(' ');
	
	draw_pixel_real('#',0,0);
	
	//draw_rect_real('#',0.1,0.1,0.3,0.3);
	
	//draw_line_real('#',0.1,0.5,0.6,0.95);
	
	draw_tri_real('#',0,0.5,1,1,0.25,0);
	
	system("cls");
	printf(f);
}

int main(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	c = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	r = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	while(1){
		draw_frame();
		if(kbhit()){
			return 0;
		}
		Sleep(100);
	}
}