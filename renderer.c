#include<stdio.h>
#include<math.h>
#include<string.h>
#ifdef __unix__
#include <sys/ioctl.h>
#include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)
#include<windows.h>
#endif
//double perspective;
char buffer[30000];
int columns,rows;
int real(float i,int p){
        return(i/(1.0/(p-0.5)))+(p/2);}
int* perspective(float x,float y,float z){
        int o[3]={x*Z0/(Z0+z),y*Z0/(Z0+z),z};
        return o;}
float argument_parser(int start_pos,char arg[50]){
        char output[50]=arg;
        strncpy(output,start_pos,start_pos+5);
        return atof(output);
void clear(){
        #ifdef __unix__
        printf("\033[%d;%dH", (0), (0));
        #elif defined(_WIN32) || defined(WIN32)
        COORD cd;
        cd.X=0,cd.Y=0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cd);
        #endif
}
void draw_background(char i){
        for(int x=0;x<(rows*columns);x++){
                buffer[x]=i;}}
void draw_pixel(char i,int x,int y){
        buffer[(((rows-(y +1))*columns)+x)]=i;}
void draw_line(char i,float x1,float y1,float x2,float y2){
        if(x2<x1){
                float tmp=x2;
                x2=x1,x1=tmp;}
        if(sqrt(((y2-y1)*(y2-y1)))<=sqrt((x2-x1)*(x2-x1))){
                for(int x=x1;x<x2;x++){
                        int y=(((x-x1)/(x2-x1))*(y2-y1))+y1+0.5;
                        draw_pixel(i,x,y);}}
        else{
                for(int x=y1;x<y2;x++){
                        int y=(((x-y1)/(y2-y1))*(x2-x1))+x1+0.5;
                        draw_pixel(i,y,x);}}}
void draw_rectangle(char i,int x1,int y1,int x2,int y2){
        for(int x=y1;x<y2;x++){
                draw_line(i,x1,x,x2,x);}}
void draw_triangle(char i,float x1,float y1,float x2,float y2,float x3,float y3){
        draw_line(i,x1,y1,x2,y2),draw_line(i,x2,y2,x3,y3),draw_line(i,x3,y3,x1,y1);
        int points=sqrt(((x3-x2)*(x3-x2))+((y3-y2)*(y3-y2)));
        float interval_x=(x3-x2)/(points+1),interval_y=y3-y2/(points+1);
        for(int x=1;x<=points;x++){
                draw_line(i,x1,y1,x2+interval_x*x,y2+interval_y*x);}}
void draw(char *args[100]){
        if(argv = 1){
                draw_background(args[1]);
                for(x=1;x<(sizeof(args)-2);x++){
                        if(args[x][1]="r"){
                                draw_rectangle(args[x][2],real(argument_parser(3,args[x]),columns),real(argument_parser(8,args[x]),rows),real(argument_parser(13,args[x]),columns),real(argument_parser(18,args[x]),rows));}
                        else if(args[x][1]="t"){
                                draw_triangle(args[x][2],real(argument_parser(3,args[x]),columns),real(argument_parser(8,args[x]),rows),real(argument_parser(13,args[x]),columns),real(argument_parser(18,args[x]),rows),real(argument_parser(23,args[x]),columns),real(argument_parser(28,args[x]),rows));}
                        else if(args[x][1]="l"){
                                draw_line(args[x][2],real(argument_parser(3,args[x]),columns),real(argument_parser(8,args[x]),rows),real(argument_parser(13,args[x]),columns),real(argument_parser(18,args[x]),rows));}
                        else if(args[x][1]="p"){
                                draw_pixel(args[x][2],real(argument_parser(3,args[x]),columns),real(argument_parser(8,args[x]),rows));}}}
        clear(),printf(buffer);}
int main(int argc,char *argv[]){
        #ifdef __unix__
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        rows=w.ws_row,columns=w.ws_col;
        #elif defined(_WIN32) || defined(WIN32) 
        CONSOLE_SCREEN_BUFFER_INFO csbi;                                                                                                                                                                                                                                                                                                                                                     
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
        columns=csbi.srWindow.Right-csbi.srWindow.Left+1,rows=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
        #endif
        perspective=(c/2.0)/tan((90/2.0)*3.14159265/180.0);
        while(1){
                draw(argv);
                #ifdef __unix__
                usleep(100);
                #elif defined(_WIN32) || defined(WIN32)
                Sleep(100);
                #endif
                }}
