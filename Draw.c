#include<stdio.h>
#include<math.h>
#include<windows.h>
int c,r;
char f[30000];
int real_x(float i){return (i / (1.0 / (c-0.5)))+(c/2);}
int real_y(float i){return (i / (1.0 / (r-0.5)))+(r/2);}
void draw_background(char i){
	for(int x = 0; x < (r * c); x++){f[x] = i;}
}
void draw_pixel(char i,int x, int y){
	f[(((r-(y +1))*c)+x)] = i;
}
void draw_rect(char i,int x1, int y1,int x2, int y2){
	for(int x = x1; x < x2; x++){for(int y = y1; y < y2; y++){draw_pixel(i,x,y);}}
}
void draw_line(char i,float x1, float y1,float x2, float y2){
	if(y2<y1){
		float tmp= y2;
		y2 = y1;
		y1= tmp;
		tmp= x2;
		x2 = x1;
		x1 = tmp;
	}
	if(x2<x1){
		float tmp= x2;
		x2 = x1;
		x1 = tmp;
		tmp= y2;
		y2 = y1;
		y1 = tmp;
	}
	if((y2-y1)<=(x2-x1)){
		for(int x= x1;x<x2;x++){
			int y = (((x-x1)/(x2-x1))*(y2-y1))+y1+0.5;
			draw_pixel(i,x,y);
		}
	}
	if((x2-x1)<(y2-y1)){
		for(int x= y1;x<y2;x++){
			int y = (((x-y1)/(y2-y1))*(x2-x1))+x1+0.5;
			draw_pixel(i,y,x);
		}
	}
}
void draw_tri(char i,float x1, float y1,float x2, float y2,float x3, float y3){
	draw_line(i,x1,y1,x2,y2);
	draw_line(i,x2,y2,x3,y3);
	draw_line(i,x3,y3,x1,y1);
	float diff_x = x3 - x2;
	float diff_y = y3 - y2;
	int points = sqrt(((x3-x2)*(x3-x2))+((y3-y2)*(y3-y2)));
	float interval_x = diff_x / (points + 1);
	float interval_y = diff_y / (points + 1);
	for(int x = 1; x <= points; x++){draw_line(i,x1,y1,x2+interval_x*x,y2 + interval_y*x);}
}
void draw_frame(){
	draw_background(' ');
	draw_pixel('#',real_x(-0.5),real_y(-0.5));
	draw_pixel('#',real_x(-0.5),real_y(0.5));
	draw_pixel('#',real_x(0.5),real_y(-0.5));
	draw_pixel('#',real_x(0.5),real_y(0.5));
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
		if(kbhit()){return 0;}
		Sleep(100);
	}
}