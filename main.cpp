#ifdef __APPLE__
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "pie_chart.h"
///prototyping

void inputdatapage();
void activeInputDataPage();
void  histoactiveInputDataPage();
void hitograminputdatapage();
void  lineinputdatapage();
void lineactiveInputDataPage();

///global variables
float width=400;
float height=400;
float w_old=500;
float h_old = 400;
float angle = 60;
int activeState = 0;
float subactive=0;
float x1,y11,x2,y2;
int activearray=0;
int current=0;
int currentColor=0;

//#include "histogram.h"
///vertex arrays
int xinput[13]={0};
int  yinput[13]={0};
int xinput0[13]={0};
int  yinput0[13]={0};
int xinput1[13]={0};
int  yinput1[13]={0};
int xinput2[13]={0};
int  yinput2[13]={0};
int xinput3[13]={0};
int  yinput3[13]={0};
int xinput4[13]={0};
int  yinput4[13]={0};
int xinput5[13]={0};
int  yinput5[13]={0};

//arrays
GLfloat vertexHome[] = {-0.5,-0.65,-0.5,-0.15,-0.1,-0.15,-0.1,-0.65,
   0.1,-0.65,0.1,-0.15,0.5,-0.15,0.5,-0.65,
   -0.8,0.15,-0.8,0.65,-0.4,0.65,-0.4,0.15,
   -0.2,0.15,-0.2,0.65,0.2,0.65,0.2,0.15,
   0.4,0.15,0.4,0.65,0.8,0.65,0.8,0.15};

GLfloat inputVertex[] = {-0.6,-0.8,-0.6,0.8,0.6,0.8,0.6,-0.8,
       -0.6,-0.667,0.6,-0.667, -0.6,-0.533,0.6,-0.533 , -0.6,-0.4,0.6,-0.4, -0.6,-0.2667, 0.6,-0.2667,
       -0.6,-0.1333, 0.6,-0.1333, -0.6,0.0, 0.6,0.0, -0.6,0.1333, 0.6,0.1333, -0.6,0.2667, 0.6,0.2667,
       -0.6,0.4, 0.6,0.4, -0.6,0.533, 0.6,0.533, -0.6,0.667, 0.6,0.667,
       0.0,0.8,0.0,-0.8};

GLfloat colors[] = {0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0,//r1
                    0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0,
                    0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0,
                    0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0,
                    0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0,

                    0.3,0.3,0.3, 0.3,0.3,0.3, 0.3,0.3,0.3, 0.3,0.3,0.3,
                    0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0,
                    0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0,
                    0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0,
                    0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0};
///helper functions
       void texts(char *str,GLfloat x,GLfloat y,GLfloat z,GLfloat cx=0.0,GLfloat cy = 1.0,GLfloat cz = 1.0){
        glLoadIdentity();
        glColor3f(cx,cy,cz);
        glRasterPos3f(x , y ,z);
        for(int i=0;i<strlen(str);i++)
            {   if(width/w_old>1.1)
                glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, str[i] );
                else
                    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, str[i] );
            }



        }


        void initOpengl()
        {
            glClearColor(0.6,0.0,0,0.6);
        }



///callback functions

        void reshape(int w,int h)
        {
    //starting coordinates and right and top

            width = w;
            height = h;
            glViewport(0,0,width,height);

    //creating a persepective
            glMatrixMode( GL_PROJECTION );
            glLoadIdentity();
            gluPerspective(angle,(float)width/(float)height,0.0,0.0);
            glMatrixMode(GL_MODELVIEW);

        }

        void display()
        {
            glClear(GL_COLOR_BUFFER_BIT);

     ///clearing everything from buhffer
            glLoadIdentity();
            if(activeState==0){
                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_COLOR_ARRAY);
                glColorPointer(3,GL_FLOAT,3*sizeof(GLfloat),colors+4*3*currentColor);
                glVertexPointer(2,GL_FLOAT,2*sizeof(GLfloat),vertexHome);
                glDrawArrays(GL_QUADS,0,20);
                glDisableClientState(GL_COLOR_ARRAY);

                glDisableClientState(GL_VERTEX_ARRAY);

        ///writing texts

                texts((char*)"Bar Graph",-0.44,-0.45,0.0);
                texts((char*)"Histogram",0.16,-0.45,0.0);
                texts((char*)"Scatter Plot",-0.76,0.35,0.0);
                texts((char*)"line chart",-0.145,0.35,0.0);
                texts((char*)"Pie Chart",0.46,0.35,0.0);

            }
            else if(activeState==1 || activeState==3 || activeState==5){
                if(subactive-(int)subactive==0)
                    inputdatapage();
                else if(subactive-(int)subactive==0.1f || subactive-(int)subactive==0.2f){
                    glLoadIdentity();
                    activeInputDataPage();
                }
            }
            else if(activeState==2){
                if(subactive==0)
                hitograminputdatapage();
                else
                histoactiveInputDataPage();
            }


            else if(activeState==4)
            {
                if(subactive==0)
                lineinputdatapage();
                else if(subactive-(int)subactive==0.1f || subactive-(int)subactive==0.2f)
                {
                    lineactiveInputDataPage();
                }
            }
            else if(activeState==15){
                glClear(GL_COLOR_BUFFER_BIT);
                glLoadIdentity();
                PieChart(yinput,xinput);
            }

    ///swapping the buffer for displaying the data
            glutSwapBuffers();

        }


        void mouse(int button, int state, int mousex, int mousey)
        {
            GLfloat x = -1.0f+2*mousex/width;
            GLfloat y = -(-1.0f+2*mousey/height);



            if(activeState==0){
                if(button == GLUT_LEFT_BUTTON){

                    if(state == GLUT_DOWN){

                        if((x>-0.5 && x<-0.1) && (y>-0.65 && y<-0.15)){

                            activeState=1;

                        }
                        else if((x>0.1 && x<0.5) && (y>-0.65 && y<-0.15)){
                            activeState = 2 ;

                        }
                        else if((x>-0.8 && x<-0.4) && (y>0.15 && y<0.65)){
                            activeState = 3;

                        }
                        else if((x>-0.2 && x<0.2) && (y>0.15 && y<0.65)){
                            activeState = 4;

                        }
                        else if((x>0.4 && x<0.8) && (y>0.15 && y<0.65)){
                            activeState = 5;

                        }


                    }
                }
            }

            else if(activeState==1 || activeState==3 || activeState==5 || activeState==2 || activeState==4){

                if(button == GLUT_LEFT_BUTTON){

                    if(state == GLUT_DOWN){

                        if((x>-0.6 && x<0.6) && (y>-0.8 && y<-0.667)){
                            y11 = -0.78;
                            y2 = -0.697;
                            current=0;
                        }
                        else if((x>-0.6 && x<0.6) && (y>-0.677 && y<-0.533)){
                            y11 = -0.657;
                            y2 = -0.553;
                            current=1;
                        }
                        else if((x>-0.6 && x<0.6) && (y>-0.533 && y<-0.4)){
                            y11 = -0.513;
                            y2 = -0.42;
                            current=2;
                        }
                        else if((x>-0.6 && x<0.6) && (y>-0.4 && y<-0.2667)){
                            y11 = -0.38;
                            y2 = -0.2867;
                            current=3;

                        }
                        else if((x>-0.6 && x<0.6) && (y>-0.2667 && y<-0.1333)){
                            y11 = -0.2467;
                            y2 = -0.1533;
                            current=4;
                        }
                        else if((x>-0.6 && x<0.6) && (y>-0.1333 && y<-0.0)){
                            y11 = -0.1133;
                            y2 = -0.0200;
                            current=5;
                        }
                        else if((x>-0.6 && x<0.6) && (y>0.0 && y<0.1333)){
                            y11 = 0.02;
                            y2 = 0.1133;
                            current=6;
                        }
                        else if((x>-0.6 && x<0.6) && (y>0.1333 && y<0.2667)){
                            y11 = 0.1533;
                            y2 = 0.2467;
                            current=7;
                        }

                        else if((x>-0.6 && x<0.6) && (y>0.2667 && y<0.4)){
                            y11 = 0.2867;
                            y2 = 0.38;
                            current=8;
                        }

                        else if((x>-0.6 && x<0.6) && (y>0.40 && y<0.5333)){
                            y11 = 0.42;
                            y2 = 0.5133;
                            current=9;
                        }
                        else if((x>-0.6 && x<0.6) && (y>0.5333 && y<0.667)){
                            y11 = 0.553;
                            y2 = 0.647;
                            current=10;
                        }
                        else if((x>-0.6 && x<0.6) && (y>0.667 && y<0.8)){
                            y11 = 0.697;
                            y2 = 0.78;
                            current=11;
                        }
                        else{
                            subactive=0;
                            current=-1;
                        }

                        if(y>-0.8 && y<0.8){
                            if(x>-0.6 && x<0.0)
                            {
                                subactive=0.1;
                            }
                            else if(x>0.0 && x<0.6){

                                subactive=0.2;

                            }
                            if(activeState==2)
                                subactive=0.1;
                        }

                        ///setting current active tab for state 4
                        if(x>-0.4 && x<-0.2 && y>0.9 && y<0.98){
                            activearray=1;
                        }
                        else if(x>-0.2 && x<-0.0 && y>0.9 && y<0.98){
                            activearray=2;
                        }
                        else if(x>0.0 && x<0.2 && y>0.9 && y<0.98){
                            activearray=3;
                        }
                        else if(x>0.2 && x<-0.4 && y>0.9 && y<0.98){
                            activearray=4;
                        }
                        else if(x>0.4 && x<0.6 && y>0.9 && y<0.98){
                                activearray=5;
                        }

                        ///backbutton
                        if(x>-0.9 && x<-0.75 && y>0.8 && y<0.9)
                        {
                            activeState=0;
                            for(int i=0;i<12;i++)
                            {
                                xinput[i]={0};
                                yinput[i]={0};
                            }

                        }


                    }
                }

            }

            ///SUBMIT BUTTON
            if(activeState==5){
                 if(button == GLUT_LEFT_BUTTON)
                 {
                     if(state == GLUT_DOWN)
                     {
                         if(x>=-0.2 && x<=0.2 && y>=-0.95 && y<= -0.85 )
                         {
                             activeState=15;

                         }
                     }
                 }

            }
            else if(activeState==1){
                 if(button == GLUT_LEFT_BUTTON)
                 {
                     if(state == GLUT_DOWN)
                     {
                         if(x>=-0.2 && x<=0.2 && y>=-0.95 && y<= -0.85 )
                         {
							 FILE *fp;
                             fp=fopen("./input.txt","w");
                             int k=11;
                             for(;k>=0;k--)
                             {
								 if(xinput[k]==0 && yinput[k]==0)
								 {
									 k++;
									 break;
								 }
							 }
							 fprintf(fp,"%d\n",11-k+1);
							 for(int _i=11;_i>=k;_i--)
							 {
								 fprintf(fp,"%d %d \n",xinput[_i],yinput[_i]);
							 }
							 fclose(fp);
                             //activeState=11;
                             system("bar_plot");
                             glutPostRedisplay();

                         }
                     }
                 }

            }
            else if(activeState==2){
                 if(button == GLUT_LEFT_BUTTON)
                 {
                     if(state == GLUT_DOWN)
                     {
                         if(x>=-0.2 && x<=0.2 && y>=-0.95 && y<= -0.85 )
                         {
                             //activeState=12;
                             FILE *fp;
                             fp=fopen("./input.txt","w");
                             int k=11;
                             for(;k>=0;k--)
                             {
								 if(xinput[k]==0 && yinput[k]==0)
								 {
									 k++;
									 break;
								 }
							 }
							 fprintf(fp,"%d\n",11-k+1);
							 for(int _i=11;_i>=k;_i--)
							 {
								 fprintf(fp,"%d\n",xinput[_i]);
							 }
							 fclose(fp);

                             system("histogram");
                             glutPostRedisplay();

                         }
                     }
                 }
            }
            else if(activeState==3){
                 if(button == GLUT_LEFT_BUTTON)
                 {
                     if(state == GLUT_DOWN)
                     {
                         if(x>=-0.2 && x<=0.2 && y>=-0.95 && y<= -0.85 )
                         {
							 FILE *fp;
                             fp=fopen("./input.txt","w");
                             int k=11;
                             for(;k>=0;k--)
                             {
								 if(xinput[k]==0 && yinput[k]==0)
								 {
									 k++;
									 break;
								 }
							 }
							 fprintf(fp,"%d\n",11-k+1);
							 for(int _i=11;_i>=k;_i--)
							 {
								 fprintf(fp,"%d %d \n",xinput[_i],yinput[_i]);
							 }
							 fclose(fp);
                             //activeState=13;
                             system("scatter_plot");
                             glutPostRedisplay();

                         }
                     }
                 }
            }
            else if(activeState==4){
                 if(button == GLUT_LEFT_BUTTON)
                 {
                     if(state == GLUT_DOWN)
                     {
                         if(x>=-0.2 && x<=0.2 && y>=-0.95 && y<= -0.85 )
                         {
							 FILE *fp;
                             fp=fopen("input.txt","w");

                             int _m=0;
							 if(yinput0[11]!=0 || yinput0[10]!=0)
							 {
								 _m=1;
								 if(yinput1[11]!=0 || yinput1[10]!=0)
								 {
									 _m=2;
									 if(yinput2[11]!=0 || yinput2[10]!=0)
									 {
										 _m=3;
										 if(yinput3[11]!=0 || yinput3[10]!=0)
										 {
											_m=4;
											if(yinput4[11]!=0 || yinput4[10]!=0)
											{
												 _m=5;
												 if(yinput5[11]!=0 || yinput5[10]!=0)
												 {
													 _m=6;
												 }
										    }
										 }
									 }
								 }
							 }
							 fprintf(fp,"%d\n",_m);
                             int k=11;
                             for(;k>=0;k--)
                             {
								 if(xinput0[k]==0)
								 {
									 k++;
									 break;
								 }
							 }
							 fprintf(fp,"%d\n",11-k+1);
							 for(int _i=11;_i>=k;_i--)
							 {
								 fprintf(fp,"%d ",xinput0[_i]);
							 }
							 fprintf(fp,"%s","\n");
							 if(_m>=1)
							 for(int _i=11;_i>=k;_i--)
							 {
								 fprintf(fp,"%d ",yinput0[_i]);
							 }
							 fprintf(fp,"%s","\n");
							 if(_m>=2)
							 for(int _i=11;_i>=k;_i--)
							 {
								 fprintf(fp,"%d ",yinput1[_i]);
							 }
							 fprintf(fp,"%s","\n");
							 if(_m>=3)
							 for(int _i=11;_i>=k;_i--)
							 {
								 fprintf(fp,"%d ",yinput2[_i]);
							 }
							 fprintf(fp,"%s","\n");
							 if(_m>=4)
							 for(int _i=11;_i>=k;_i--)
							 {
								 fprintf(fp,"%d ",yinput3[_i]);
							 }
							 fprintf(fp,"%s","\n");
							 if(_m>=5)
							 for(int _i=11;_i>=k;_i--)
							 {
								 fprintf(fp,"%d ",yinput4[_i]);
							 }
							 fprintf(fp,"%s","\n");
							 if(_m>=6)
							 for(int _i=11;_i>=k;_i--)
							 {
								 fprintf(fp,"%d ",yinput5[_i]);
							 }

							 fclose(fp);

                             //activeState=14;
                             system("line_graph");
                             glutPostRedisplay();

                         }
                     }
                 }
            }

            //back button for end statges
            if(activeState==15){
                if(button==GLUT_LEFT_BUTTON)
                {
                    if(state == GLUT_DOWN)
                    {
                         if(x>-0.9 && x<-0.75 && y>0.8 && y<0.9)
                        {
                            activeState=activeState%10;

                        }
                    }
                }
            }
        }

        void keyboard(unsigned char key, int x, int y)
        {

            if((activeState==1 || activeState==3 || activeState==5 || activeState==2) && subactive!=0){
                int k = (int)key-48;
                if(k>=0 && k<=9 || k==18 || k==50 ){
                    if(subactive==0.1f){
                        if(k==18 || k==50){
                            xinput[current]/=10;

                        }
                        else if(xinput[current]<1000000)
                        {
                            xinput[current]=xinput[current]*10+k;
                        }
                    }
                    else if(subactive==0.2f){
                       if(k==18 || k==50){
                        yinput[current]/=10;
                    }
                    else if(yinput[current]<1000000)
                    {
                        yinput[current]=yinput[current]*10+k;
                    }
                }

            }
            int tab = (int)key;
            if(tab==9){

               if(subactive==0.1f)
               {
                    subactive = 0.2f;
               }

               else if(subactive==0.2f){
                    subactive=0.1f;
               }

            }

        }

            if(activeState==4)
            {
                int k = (int)key-48;

                if(k>=0 && k<=9 || k==18 || k==50)
                {
                    if(activearray==0){
                        if(subactive==0.1f){
                            if(k==18 || k==50){
                                xinput0[current]/=10;

                            }
                            else if(xinput0[current]<1000000)
                            {
                                xinput0[current]=xinput0[current]*10+k;
                            }
                        }
                        else if(subactive==0.2f){
                           if(k==18 || k==50){
                            yinput0[current]/=10;
                            }
                            else if(yinput0[current]<1000000)
                            {
                                yinput0[current]=yinput0[current]*10+k;
                            }
                        }
                    }

                    else if(activearray==1){
                        if(subactive==0.1f){
                            if(k==18 || k==50){
                                xinput1[current]/=10;

                            }
                            else if(xinput1[current]<1000000)
                            {
                                xinput1[current]=xinput1[current]*10+k;
                            }
                        }
                        else if(subactive==0.2f){
                           if(k==18 || k==50){
                            yinput1[current]/=10;
                            }
                            else if(yinput1[current]<1000000)
                            {
                                yinput1[current]=yinput1[current]*10+k;
                            }
                        }
                    }

                    else if(activearray==2){
                        if(subactive==0.1f){
                            if(k==18 || k==50){
                                xinput2[current]/=10;

                            }
                            else if(xinput2[current]<1000000)
                            {
                                xinput2[current]=xinput2[current]*10+k;
                            }
                        }
                        else if(subactive==0.2f){
                           if(k==18 || k==50){
                            yinput2[current]/=10;
                            }
                            else if(yinput2[current]<1000000)
                            {
                                yinput2[current]=yinput2[current]*10+k;
                            }
                        }
                    }

                    else if(activearray==3){
                        if(subactive==0.1f){
                            if(k==18 || k==50){
                                xinput3[current]/=10;

                            }
                            else if(xinput3[current]<1000000)
                            {
                                xinput3[current]=xinput3[current]*10+k;
                            }
                        }
                        else if(subactive==0.2f){
                           if(k==18 || k==50){
                            yinput3[current]/=10;
                            }
                            else if(yinput3[current]<1000000)
                            {
                                yinput3[current]=yinput3[current]*10+k;
                            }
                        }
                    }

                    else if(activearray==4){
                        if(subactive==0.1f){
                            if(k==18 || k==50){
                                xinput4[current]/=10;

                            }
                            else if(xinput4[current]<1000000)
                            {
                                xinput4[current]=xinput4[current]*10+k;
                            }
                        }
                        else if(subactive==0.2f){
                           if(k==18 || k==50){
                            yinput4[current]/=10;
                            }
                            else if(yinput4[current]<1000000)
                            {
                                yinput4[current]=yinput4[current]*10+k;
                            }
                        }
                    }

                    else if(activearray==5){
                        if(subactive==0.1f){
                            if(k==18 || k==50){
                                xinput5[current]/=10;

                            }
                            else if(xinput5[current]<1000000)
                            {
                                xinput5[current]=xinput5[current]*10+k;
                            }
                        }
                        else if(subactive==0.2f){
                           if(k==18 || k==50){
                            yinput5[current]/=10;
                            }
                            else if(yinput5[current]<1000000)
                            {
                                yinput5[current]=yinput5[current]*10+k;
                            }
                        }
                    }
                }

                int tab = (int)key;
                if(tab==9){

                   if(subactive==0.1f)
                   {
                        subactive = 0.2f;
                   }

                   else if(subactive==0.2f){
                        subactive=0.1f;
                   }

                }

            }
    }

        void hover(int mousex, int mousey)
        {
            GLfloat x = -1.0f+2*mousex/width;
            GLfloat y = -(-1.0f+2*mousey/height);

            if(activeState==0)
            {
                if((x>-0.5 && x<-0.1) && (y>-0.65 && y<-0.15)){

                    currentColor=5;

                }
                else if((x>0.1 && x<0.5) && (y>-0.65 && y<-0.15)){
                    currentColor=4;

                }
                else if((x>-0.8 && x<-0.4) && (y>0.15 && y<0.65)){
                    currentColor=3;

                }
                else if((x>-0.2 && x<0.2) && (y>0.15 && y<0.65)){
                    currentColor=2;

                }
                else if((x>0.4 && x<0.8) && (y>0.15 && y<0.65)){
                    currentColor=1;

                }
                else{
                    currentColor=0;
                }

            }

        }


///visual functions
    void inputdatapage()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(1.0,1.0,1.0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2,GL_FLOAT,2*sizeof(GLfloat),inputVertex);
        texts((char *)"x Values",-0.4,0.9,0.0);
        texts((char *)"y Values",0.2,0.9,0.0);
        glDrawArrays(GL_LINE_LOOP,0,4);
        glDrawArrays(GL_LINES,4,26);
        glDisableClientState(GL_VERTEX_ARRAY);
        glColor3f(0.0,0.0,0.0);
        glRectf(-0.9,0.8,-0.75,0.9);
        glRectf(-0.2,-0.95,0.2,-0.85);
        texts((char *)"submit",-0.1,-0.91,0.0);
        glBegin(GL_LINES);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(-0.87,0.85);
        glVertex2f(-0.78,0.85);
        glVertex2f(-0.85,0.875);
        glVertex2f(-0.87,0.85);
        glVertex2f(-0.85,0.825);
        glVertex2f(-0.87,0.85);
        glEnd();

    }


    void lineinputdatapage()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(1.0,1.0,1.0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(2,GL_FLOAT,2*sizeof(GLfloat),inputVertex);
        texts((char *)"x Values",-0.4,0.82,0.0);
        texts((char *)"y Values",0.2,0.82,0.0);
        glDrawArrays(GL_LINE_LOOP,0,4);
        glDisableClientState(GL_COLOR_ARRAY);
        glDrawArrays(GL_LINES,4,26);
        glDisableClientState(GL_VERTEX_ARRAY);
        glColor3f(0.0,0.0,0.0);
        glRectf(-0.9,0.8,-0.75,0.9);
        glRectf(-0.2,-0.95,0.2,-0.85);
        texts((char *)"submit",-0.1,-0.91,0.0);
         glColor3f(0.0,0.0,0.0);
        glRectf(-0.6,0.9,0.6,0.98);
        glBegin(GL_LINES);
        glColor3f(1.0,1.0,1.0);

        glVertex2f(-0.4,0.9);
        glVertex2f(-0.4,0.98);
        glVertex2f(-0.2,0.9);
        glVertex2f(-0.2,0.98);
        glVertex2f(0.0,0.9);
        glVertex2f(0.0,0.98);
        glVertex2f(0.2,0.9);
        glVertex2f(0.2,0.98);
        glVertex2f(0.4,0.9);
        glVertex2f(0.4,0.98);

        glVertex2f(-0.87,0.85);
        glVertex2f(-0.78,0.85);
        glVertex2f(-0.85,0.875);
        glVertex2f(-0.87,0.85);
        glVertex2f(-0.85,0.825);
        glVertex2f(-0.87,0.85);
        glEnd();
        texts((char *)"1",-0.5,0.92,1.0,1.0,1.0);
        texts((char *)"2",-0.3,0.92,1.0,1.0,1.0);
        texts((char *)"3",-0.1,0.92,1.0,1.0,1.0);
        texts((char *)"4",0.1,0.92,1.0,1.0,1.0);
        texts((char *)"5",0.3,0.92,1.0,1.0,1.0);
        texts((char *)"6",0.5,0.92,1.0,1.0,1.0);

    }



    void hitograminputdatapage()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(1.0,1.0,1.0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2,GL_FLOAT,2*sizeof(GLfloat),inputVertex);
        texts((char *)"x Values",-0.16,0.9,0.0);
        glDrawArrays(GL_LINE_LOOP,0,4);
        glDrawArrays(GL_LINES,4,22);
        glDisableClientState(GL_VERTEX_ARRAY);
       glColor3f(0.0,0.0,0.0);
        glRectf(-0.9,0.8,-0.75,0.9);
        glRectf(-0.2,-0.95,0.2,-0.85);
        texts((char *)"submit",-0.1,-0.91,0.0);
         glColor3f(0.0,0.0,0.0);
        glBegin(GL_LINES);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(-0.87,0.85);
        glVertex2f(-0.78,0.85);
        glVertex2f(-0.85,0.875);
        glVertex2f(-0.87,0.85);
        glVertex2f(-0.85,0.825);
        glVertex2f(-0.87,0.85);
        glEnd();


    }

    void lineactiveInputDataPage()
    {

        glLoadIdentity();
        lineinputdatapage();
        if(subactive==0.1f){
            glColor3f(0.0,1.0,1.0);
            glRectf(-0.55,y11,-0.05,y2);
        }

        if(subactive==0.2f){
            glColor3f(0.0,1.0,1.0);
            glRectf(0.05,y11,0.55,y2);
        }

        if(activearray==0)
        {
            for(int j=9,i=0;j<= 53;j+=4,i++)
            {
                char text[9];
                char ytext[9];
                sprintf(text,"%d",xinput0[i]);
                sprintf(ytext,"%d",yinput0[i]);
                texts(text,-0.54,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
                texts(ytext,0.06,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
            }


        }
        else if(activearray==1)
        {
            for(int j=9,i=0;j<= 53;j+=4,i++)
            {
                char text[9];
                char ytext[9];
                sprintf(text,"%d",xinput0[i]);
                sprintf(ytext,"%d",yinput1[i]);
                texts(text,-0.54,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
                texts(ytext,0.06,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
            }


        }
        else if(activearray==2)
        {
            for(int j=9,i=0;j<= 53;j+=4,i++)
            {
                char text[9];
                char ytext[9];
                sprintf(text,"%d",xinput0[i]);
                sprintf(ytext,"%d",yinput2[i]);
                texts(text,-0.54,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
                texts(ytext,0.06,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
            }


        }
        else if(activearray==3)
        {
            for(int j=9,i=0;j<= 53;j+=4,i++)
            {
                char text[9];
                char ytext[9];
                sprintf(text,"%d",xinput0[i]);
                sprintf(ytext,"%d",yinput3[i]);
                texts(text,-0.54,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
                texts(ytext,0.06,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
            }


        }
        else if(activearray==4)
        {
            for(int j=9,i=0;j<= 53;j+=4,i++)
            {
                char text[9];
                char ytext[9];
                sprintf(text,"%d",xinput0[i]);
                sprintf(ytext,"%d",yinput4[i]);
                texts(text,-0.54,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
                texts(ytext,0.06,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
            }


        }
        else if(activearray==5)
        {
            for(int j=9,i=0;j<= 53;j+=4,i++)
            {
                char text[9];
                char ytext[9];
                sprintf(text,"%d",xinput0[i]);
                sprintf(ytext,"%d",yinput5[i]);
                texts(text,-0.54,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
                texts(ytext,0.06,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
            }


        }

    }

    void histoactiveInputDataPage()
    {

        glLoadIdentity();
        hitograminputdatapage();
        glColor3f(0.0,1.0,1.0);
        glRectf(-0.55,y11,0.55,y2);
        for(int j=9,i=0;j<= 53;j+=4,i++)
        {
            char text[9];
            sprintf(text,"%d",xinput[i]);
            texts(text,-0.54,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
        }


    }

    void activeInputDataPage()
    {

        glLoadIdentity();
        inputdatapage();
        if(subactive==0.1f){
            glColor3f(0.0,1.0,1.0);
            glRectf(-0.55,y11,-0.05,y2);
        }

        if(subactive==0.2f){
            glColor3f(0.0,1.0,1.0);
            glRectf(0.05,y11,0.55,y2);
        }


        for(int j=9,i=0;j<= 53;j+=4,i++)
        {
            char text[9];
            char ytext[9];
            sprintf(text,"%d",xinput[i]);
            sprintf(ytext,"%d",yinput[i]);
            texts(text,-0.54,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
            texts(ytext,0.06,inputVertex[j]-0.085,0.0,1.0,0.0,0.0);
        }


    }

    int main(int argc,char **argv)
    {
    //starting the glut
        FILE *fr = fopen("input.txt","w");
        fclose(fr);
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowSize(width,height);
        glutCreateWindow("plotter");
        initOpengl();
    //callback function
        glutDisplayFunc(display);
        glutIdleFunc(display);
        glutReshapeFunc(reshape);
        glutMouseFunc(mouse);
        glutKeyboardFunc(keyboard);
        glutPassiveMotionFunc(hover);

    ///main loop
        glutMainLoop();

        return 0;

    }
