#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h> 
#include<stdlib.h>
#include<conio.h>

char* draw_background(char,int,int);
int draw_rect_real(char,float,float,float,float,char [],int,int);
int draw_line_real(char,float,float,float,float,char[],int,int);
int draw_tri_real(char,float,float,float,float,float,float,char[],int,int);

int main(){
	bool running = true;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int c = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int r = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	int y;
	while(running){
		draw_frame(c,r);
		if(kbhit()){
			running = false;
		}
		Sleep(100);
	}
	return 0;
}

int draw_frame(int c,int r){
	char* frame_buffer = draw_background(' ',c,r);
	
	draw_pixel_real('#',0,0,frame_buffer,c,r);
	
	draw_rect_real('#',0.1,0.1,0.3,0.3,frame_buffer,c,r);
	
	draw_line_real('#',0.1,0.5,0.6,0.95,frame_buffer,c,r);
	
	draw_tri_real('#',0.25,0.4,0.5,0.75,0.75,0.1,frame_buffer,c,r);
	
	
	
	system("cls");
	printf(frame_buffer);
	
	return 0;
}
int cords_t_pixels(int p, float i){
	return i / (1.0 / (p-0.5));
}
char* draw_background(char i,int c,int r){
	char f[30000] = "";
	int x;
	for(x = 0; x < (r * c); x = x + 1){
		f[x] = i;
	}
	return f;
}
int draw_pixel(char i,int x, int y,char f[30000],int c, int r){
	f[(((r-(y +1))*c)+x)] = i;
	return 0;
}
int draw_pixel_real(char i,int x, int y,char f[30000],int c,int r){
	draw_pixel(i,cords_t_pixels(c, x),cords_t_pixels(r, y),f,c,r);
	return 0;
}
int draw_rect(char i,int x1, int y1,int x2, int y2,char f[30000],int c,int r){
	int x,y;
	for(x = x1; x < x2; x = x + 1){
		for(y = y1; y < y2; y = y + 1){
			draw_pixel(i,x,y,f,c,r);
		}
	}
	return 0;
}
int draw_rect_real(char i,float x1, float y1,float x2, float y2,char f[30000],int c,int r){
	draw_rect(i,cords_t_pixels(c, x1),cords_t_pixels(r, y1),cords_t_pixels(c, x2),cords_t_pixels(r, y2),f,c,r);
	return 0;
}
int draw_line(char i,float x1, float y1,float x2, float y2,char f[30000],int c,int r){
	int x;
	int y;
	bool rev_x;
	bool rev_y;
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
			draw_pixel(i,x,y,f,c,r);
		}
	}
	if((x2-x1)<(y2-y1)){
		for(x= y1;x<y2;x=x+1){
			y = (((y-y1)/(y2-y1))*(x2-x1))+x1+0.5;
			draw_pixel(i,y,x,f,c,r);
		}
	}
	return 0;
}
int draw_line_real(char i,float x1, float y1,float x2, float y2,char f[30000],int c, int r){
	draw_line(i,cords_t_pixels(c, x1),cords_t_pixels(r, y1),cords_t_pixels(c, x2),cords_t_pixels(r, y2),f,c,r);
	return 0;
}
int draw_tri(char i,float x1, float y1,float x2, float y2,float x3, float y3,char f[30000],int c,int r){
	draw_line(i,x1,y1,x2,y2,f,c,r);
	draw_line(i,x2,y2,x3,y3,f,c,r);
	draw_line(i,x3,y3,x1,y1,f,c,r);
	return 0;
}
int draw_tri_real(char i,float x1, float y1,float x2, float y2,float x3, float y3,char f[30000],int c,int r){
	draw_tri(i,cords_t_pixels(c, x1),cords_t_pixels(r, y1),cords_t_pixels(c, x2),cords_t_pixels(r, y2),cords_t_pixels(c, x3),cords_t_pixels(r, y3),f,c,r);
	return 0;
}
int draw_polygon(char i,float cords[20],char f[30000],int c,int r){
	int x;
	for(x=0;x<1;x=x+1){
		
	}
	return 0;
}