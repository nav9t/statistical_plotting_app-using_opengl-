#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
int width = 400;
int height = 400;
int xoffset = 40;
int yoffset = 25;
int columnx;
int columny;

int n;
int** arr;
char** strx;
char** stry;
float mulx,muly;
int minx,maxx,miny,maxy;
int flag= 0;

void input();
void tostring(int , char*);
int min(int, int);
int max(int, int);
void bar_plot();
void key_input(unsigned char, int, int);
int stoi(char*);
int get_x_coordinate(int);
int get_y_coordinate(int);

void init()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,width+0.0,0.0,height+0.0);
}

void display()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
	glVertex2i(xoffset-5,yoffset-5);
	glVertex2i(xoffset-5,height+yoffset);
	glVertex2i(xoffset-5,yoffset-5);
	glVertex2i(width+xoffset,yoffset-5);
	glEnd();
	
	muly=(height-50)/(maxy-miny+0.0);
	mulx=(width-xoffset)/(n);
	
	//Printing values on axes
	glColor3f(1.0,0.0,0.0);
	float _length = (width -xoffset- 10.0)/(n+2);
	for(int i=0;i<=columnx;i++)
	{
		int _w=glutBitmapLength(GLUT_BITMAP_8_BY_13, strx[i]);
		glRasterPos2f(xoffset+ (i)*mulx-_w/2 + _length/2 , yoffset-20);
		int _l=strlen(&strx[i][0]);
		for(int j=0;j<_l;j++) glutBitmapCharacter(GLUT_BITMAP_8_BY_13,strx[i][j]);
	}
	
	for(int i=0;i<=columny;i++)
	{
		int _w=glutBitmapLength(GLUT_BITMAP_8_BY_13, stry[i]);
		glRasterPos2f(xoffset/2-_w/2 , yoffset + (stoi(stry[i])-miny)*muly-6.5);
		int _l=strlen(&stry[i][0]);
		for(int j=0;j<_l;j++) glutBitmapCharacter(GLUT_BITMAP_8_BY_13,stry[i][j]);
	}
	
	//Plotting Points
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_QUADS);
	for(int i=0;i<n;i++)
	{
		int _y = (arr[i][1]-miny)*muly;
		int _x = (i)*mulx+_length/2; 
		
		glVertex2i(_x + xoffset - _length/2, yoffset);
		glVertex2i(_x + xoffset - _length/2, _y+yoffset);
		glVertex2i(_x + xoffset + _length/2, _y+yoffset);
		glVertex2i(_x + xoffset + _length/2, yoffset);
	}
	glEnd();
	
	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	y=height-y;
	if(x>xoffset && x<width-xoffset && y>yoffset && y<height-yoffset)
	{
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex2f(get_x_coordinate(x),yoffset);
		glVertex2f(get_x_coordinate(x),height-10);
		glPopMatrix();
	}
}

void reshape(int w, int h)
{
	height = h;
	width = w;
	
	bar_plot();
	glViewport(0,0,w,h);
	glLoadIdentity();
	init();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize( width, height);
	glutInitWindowPosition( 200, 250);
	glutCreateWindow("Bar Plot");
	
	bar_plot();
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(key_input);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();
}


int get_x_coordinate(int x)
{
	return (x-minx)*mulx+xoffset;
}

int get_y_coordinate(int y)
{
	return (y-miny)*muly+yoffset;
}

void input()
{
	printf("Input for Scatter plot\n");
	printf("No of x-y pairs\n");
	FILE *fp;
	fp=fopen("./input.txt","r");
	fscanf(fp,"%d",&n);
	arr = malloc(sizeof(int*)*n);
	for(int i=0;i<n;i++)
	{
		arr[i]=malloc(sizeof(int)*2);
	}
	
	for(int i=0;i<n;i++)
	{
		fscanf(fp,"%d %d",&arr[i][0],&arr[i][1]);
	}
	printf("\nPlotting the graph\n");
}

void key_input(unsigned char key, int x, int y)
{
	if(key == 27) exit(0);
}

int min(int x, int y)
{
	return x<y?x:y;
}

int max(int x, int y)
{
	return x>y?x:y;
}


int input_taken = 0;
void bar_plot()
{
	columnx =n-1;
	columny =(height-yoffset-10)/50;

	//To input plot data
	if(input_taken == 0)
	{
		input();
		input_taken = 1;
	}
	
	//To find minimum and maximum value on both-axis
	miny=1000000000*0;
	maxy=0;
	for(int i=0;i<n;i++)
	{
		maxy=max(maxy,arr[i][1]);
	}
	
	//To store x-axis points
	strx = malloc(sizeof(char*)* (columnx+1));
	for(int i=0;i<=columnx; i++) strx[i]=malloc(sizeof(char)*10);
	
	for(int i = 0 ; i <= columnx ; i++)
	{
		tostring(arr[i][0],&strx[i][0]);
	}
	
	//To store y-axis points
	stry = malloc(sizeof(char*)* (columny+1));
	for(int i=0;i<=columny; i++) stry[i]=malloc(sizeof(char)*10);
	
	float period = (maxy - miny+0.0)/(columny);
	for(int begin=miny, i = 0 ; i <= columny ; begin=ceil(miny+period*(i+1)), i++)
	{
		tostring(begin,&stry[i][0]);
	}
}

int stoi(char* str)
{
	int i=0;
	int neg=(str[0]=='-'?-1,i++:1);
	int val=0;
	for(;i<strlen(str);i++)
	{
		val*=10;
		val+=(str[i]-'0');
	}
	return val;
}

void tostring(int val, char* str)
{
	if(val==0) 
	{
		strcpy(str,"0");
		return;
	}
	
	char temp[10];
	int neg=(val<0?1:0);
	if(neg) val*=-1;
	//integer to string (reversed)
	int r,i;
	for(i=0;val;i++)
	{
		r = val%10;
		val/=10;
		temp[i]='0'+r;
	}
	if(neg)	temp[i++]='-';
	//reversing the digits
	for(int j=i-1;j>=0;j--) str[i-j-1]=temp[j];
	str[i]='\0';
}
