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
int* arr;
char** strx;
char** stry;
char** freq;
float mulx,muly;
int minx,maxx,miny,maxy;
int flag= 0;

void input();
void tostring(int , char*);
int min(int, int);
int max(int, int);
void histogram();
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
	mulx=(width-xoffset)/(columnx);
	//Printing values on axes
	glColor3f(1.0,0.0,0.0);
	float _length = (width -xoffset- 10.0)/(columnx-1);
	for(int i=0;i<=columnx;i++)
	{
		int _w=glutBitmapLength(GLUT_BITMAP_8_BY_13, strx[i]);
		glRasterPos2f(xoffset+ (i)*mulx-_w/2 , yoffset-20);
		int _l=strlen(strx[i]);
		for(int j=0;j<_l;j++) glutBitmapCharacter(GLUT_BITMAP_8_BY_13,strx[i][j]);
	}
	
	for(int i=0;i<=columny;i++)
	{
		int _w=glutBitmapLength(GLUT_BITMAP_8_BY_13, stry[i]);
		glRasterPos2f(xoffset/2-_w/2 , yoffset + (stoi(stry[i])-miny)*muly-6.5);
		int _l=strlen(stry[i]);
		for(int j=0;j<_l;j++) glutBitmapCharacter(GLUT_BITMAP_8_BY_13,stry[i][j]);
	}
	
	//Plotting Points
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_QUADS);
	for(int i=0;i<=columnx;i++)
	{
		int _y = (stoi(freq[i])-miny)*muly;
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
	
	histogram();
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
	glutCreateWindow("Histogram");
	
	histogram();
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
	printf("Input for Histogram\n");
	printf("No of values\n");
	FILE *fp;
	fp=fopen("./input.txt","r");
	fscanf(fp,"%d",&n);
	arr = malloc(sizeof(int)*n);
	
	for(int i=0;i<n;i++)
	{
		fscanf(fp,"%d",&arr[i]);
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
void histogram()
{
	//To input plot data
	if(input_taken == 0)
	{
		input();
		input_taken = 1;
	}
	
	int cmpfunc (const void * a, const void * b) 
	{
		return ( *(int*)a > *(int*)b );
	}
	
	//To find minimum and maximum value on both-axis
	qsort((void*)arr,n,sizeof(arr[0]),cmpfunc);
	minx=arr[0];
	maxx=arr[n-1];

	int range = maxx - minx+1;
	int col_width = ceil(range/10.0);
	
	//To store x-axis points
	free(strx);free(freq);free(stry);
	strx = malloc(sizeof(char*)* (12));
	freq = malloc(sizeof(char*)* (12));
	for(int i=0; i<=11; i++) strx[i]=malloc(sizeof(char)*10),freq[i]=malloc(sizeof(char)*10);
	int i=0,begin;
	for(begin = minx - minx%(col_width); begin < maxx ; i++, begin+=col_width )
	{
		tostring(begin,&strx[i][0]);
	}
	tostring(begin,&strx[i++][0]);
	columnx =i-1;
	
	//To store y-axis points
	int j=0;
	maxy=0,miny=100000000;
	for(int k=0;k<i-1;k++)
	{
		int f=0;
		int temp=stoi(strx[k+1]);
		while(j<n && arr[j]<=temp) f++,j++;
		maxy=max(maxy,f);
		miny=min(miny,f);
		tostring(f,freq[k]);
	}
	for(int _=0;_<columnx;_++) printf("%s ",freq[_]); printf("\n");
	
	columny =(height-yoffset-10)/50;
	stry = malloc(sizeof(char*)* (columny+1));
	for(int i=0;i<=columny; i++) stry[i]=malloc(sizeof(char)*10);
	
	int period = ceil((maxy - miny+0.0)/(columny));
	for(int begin=miny, i = 0 ; i <= (int)columny ; begin=ceil(miny+period*(i+1)), i++)
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
