#include<stdio.h>
#include<math.h>
#include<string.h>
#ifdef __unix__
#include <sys/ioctl.h>
#include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)
#include<windows.h>
#endif
double perspective;
char buffer[30000];
int columns,rows;
float sq(float x){
        return x*x;}
int real(float input,int length){
        return(input/(1.0/(length-0.5)))+(length/2);}
void set_perspective(float x,float y,float z){
        x=x*perspective/(perspective+z);
        y=y*perspective/(perspective+z);}
void draw_background(char i){
        for(int x=0;x<(rows*columns);x++){
                buffer[x]=i;}}
void draw_pixel(char i,int x,int y){
        buffer[(((rows-(y+1))*columns)+x)]=i;}
void draw_line(char i,float x1,float x2,float y1,float y2){
        int dir=1;
        float xdif=sqrt(sq(x2-x1)),ydif=sqrt(sq(y2-y1));
        if(ydif<=xdif){
                if(x2<x1){
                        dir=-1;}
                for(int x=x1;x>=x2;x+=dir){
                        int y=(((x-x1)/xdif)*ydif)+y1;
                        draw_pixel(i,x,y);}}
        else{
                if(y2<y1){
                        dir=-1;}
                for(int x=y1;x>=y2;x+=dir){
                        int y=(((x-y1)/ydif)*xdif)+x1;
                        draw_pixel(i,y,x);}}}
void draw_triangle(char i,float x1,float x2,float x3,float y1,float y2,float y3){
        draw_line(i,x1,x2,y1,y2),draw_line(i,x2,x3,y2,y3),draw_line(i,x3,x1,y3,y1);
        //int points=sqrt((sq(x3-x2))+(sq(y3-y2)));
        //float interval_x=(x3-x2)/(points),interval_y=(y3-y2)/(points);
        //for(int x=0;x<=points;x++){
        //      draw_line(i,x1,x2+interval_x*x,y1,y2+interval_y*x);}}
        }
void draw_triangle_perspective(char i,int x1,int x2,int x3,int y1,int y2,int y3,int z1,int z2,int z3){
        set_perspective(x1,y1,z1);
        set_perspective(x2,y2,z2);
        set_perspective(x3,y3,z3);
        draw_triangle(i,x1,x2,x3,y1,y2,y3);}
void draw_tetrahedron(char i,int x1,int x2,int x3,int x4,int y1,int y2,int y3,int y4,int z1,int z2,int z3,int z4){
        draw_triangle_perspective(i,x1,x2,x3,y1,y2,y3,z1,z2,z3);
        draw_triangle_perspective(i,x4,x2,x3,y4,y2,y3,z4,z2,z3);
        draw_triangle_perspective(i,x1,x4,x3,y1,y4,y3,z1,z4,z3);
        draw_triangle_perspective(i,x1,x2,x4,y1,y2,y4,z1,z2,z4);}
void draw_rectangle(char i,int x1,int x2,int x3,int x4,int y1,int y2,int y3,int y4){
        draw_triangle(i,x1,x2,x3,y1,y2,y3);
        draw_triangle(i,x1,x4,x3,y1,y4,y3);}
void draw_rectangle_perspective(char i,int x1,int x2,int x3,int x4,int y1,int y2,int y3,int y4,int z1,int z2,int z3,int z4){
        set_perspective(x1,y1,z1);
        set_perspective(x2,y2,z2);
        set_perspective(x3,y3,z3);
        set_perspective(x4,y4,z4);
        draw_rectangle(i,x1,x2,x3,x4,y1,y2,y3,y4);}
void draw_cube(char i,int x1,int x2,int x3,int x4,int x5,int x6,int x7,int x8,int y1,int y2,int y3,int y4,int y5,int y6,int y7,int y8,int z1,int z2,int z3,int z4,int z5,int z6,int z7,int z8){
        draw_rectangle_perspective(i,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,z3,z4);
        draw_rectangle_perspective(i,x1,x2,x6,x5,y1,y2,y6,y5,z1,z2,z6,z5);
        draw_rectangle_perspective(i,x3,x2,x6,x7,y3,y2,y6,y7,z3,z2,z6,z7);
        draw_rectangle_perspective(i,x8,x4,x3,x7,y8,y4,y3,y7,z8,z4,z3,z7);
        draw_rectangle_perspective(i,x1,x5,x8,x4,y1,y5,y8,y4,z1,z5,z8,z4);
        draw_rectangle_perspective(i,x5,x6,x7,x8,y5,y6,y7,y8,z5,z6,z7,z8);}
void draw(){
        draw_background(' ');
        //draw calls here!!!
        draw_triangle('X',real(-0.25,columns),real(0,columns),real(0.25,columns),real(-0.25,rows),real(0.25,rows),real(-0.25,rows));
        //draw_rectangle('X',real(-0.25,columns),real(-0.25,columns),real(0.25,columns),real(0.3,columns),real(-0.25,rows),real(0.25,rows),real(0.25,rows),real(-0.3,rows));
        draw_line('X',real(0,columns),real(0.25,columns),real(0.25,rows),real(-0.25,rows));
        #ifdef __unix__
        printf("\033[%d;%dH", (0), (0));
        #elif defined(_WIN32) || defined(WIN32)
        COORD cd;
        cd.X=0,cd.Y=0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cd);
        #endif
        printf(buffer);}
int main(){
        #ifdef __unix__
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        rows=w.ws_row,columns=w.ws_col;
        #elif defined(_WIN32) || defined(WIN32)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
        columns=csbi.srWindow.Right-csbi.srWindow.Left+1,rows=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
        #endif
        perspective=(columns/2.0)/tan((90/2.0)*3.14159265/180.0);
        while(1){
                #ifdef __unix__
                usleep(100);
                #elif defined(_WIN32) || defined(WIN32)
                Sleep(100);
                #endif
                draw();}}
