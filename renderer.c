#include<stdio.h>
#include<math.h>
#include<windows.h>
double Z0;char f[30000];
int c,r;
int rl(float i,int p){return(i/(1.0/(p-0.5)))+(p/2);};
//int* perspective(float x,float y,float z){
	//int o[3]={x*Z0/(Z0+z),y*Z0/(Z0+z),z};return o;}
void crs(){COORD cd;cd.X=0;cd.Y=0;SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cd);}
void draw_bkg(char i){for(int x=0;x<(r*c);x++){f[x]=i;}}
void draw_pix(char i,int x,int y){f[(((r-(y +1))*c)+x)]=i;}
void draw_lin(char i,float x1,float y1,float x2,float y2){
	if(x2<x1){float tmp=x2;x2=x1;x1=tmp;}
	if(sqrt(((y2-y1)*(y2-y1)))<=sqrt(((x2-x1)*(x2-x1)))){
		for(int x=x1;x<x2;x++){
			int y=(((x-x1)/(x2-x1))*(y2-y1))+y1+0.5;
			draw_pix(i,x,y);}}
	else{
		for(int x=y1;x<y2;x++){
			int y=(((x-y1)/(y2-y1))*(x2-x1))+x1+0.5;
			draw_pix(i,y,x);}}}
void draw_rct(char i,int x1,int y1,int x2,int y2){for(int x=y1;x<y2;x++){draw_lin(i,x1,x,x2,x);}}
void draw_tri(char i,float x1,float y1,float x2,float y2,float x3,float y3){
	draw_lin(i,x1,y1,x2,y2);draw_lin(i,x2,y2,x3,y3);draw_lin(i,x3,y3,x1,y1);
	int points=sqrt(((x3-x2)*(x3-x2))+((y3-y2)*(y3-y2)));
	float diff_x=x3-x2,diff_y=y3-y2,interval_x=diff_x/(points+1),interval_y=diff_y/(points+1);
	for(int x=1;x<=points;x++){draw_lin(i,x1,y1,x2+interval_x*x,y2+interval_y*x);}}
void draw(){
	draw_bkg(' ');
	//insert functions to draw
	draw_rct('#',rl(-0.45,c),rl(0.05,r),rl(-0.05,c),rl(0.45,r));
	draw_tri('#',rl(0.05,c),rl(0.05,r),rl(0.25,c),rl(0.45,r),rl(0.45,c),rl(0.05,r));
	draw_lin('#',rl(-0.45,c),rl(-0.45,r),rl(-0.05,c),rl(-0.05,r));
	crs();printf(f);}
int main(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
	c=csbi.srWindow.Right-csbi.srWindow.Left+1;r=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
	Z0=(c/2.0)/tan((90/2.0)*3.14159265/180.0);
	while(1){
		if(kbhit()){return 0;}
		draw();
		Sleep(100);}}