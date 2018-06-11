
float xc=0.0,yc=0.0;
float x,y,rad=100.0;
float pk;
float twopi = 2*3.145;

 void texts1(char *str,GLfloat x,GLfloat y,GLfloat z,GLfloat cx=0.0,GLfloat cy = 1.0,GLfloat cz = 1.0){
        glLoadIdentity();
        glColor3f(cx,cy,cz);
        glRasterPos3f(x , y ,z);
        for(int i=0;i<strlen(str);i++)
            {
                    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, str[i] );
            }



        }



void setPixel(float x, float y)
{
	glColor3f(0.0,1.0,.0);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
    glFlush();
}

void CirclePlotPoints(float xx,float yy)
{
    setPixel(xc+xx, yc+yy);
    setPixel(xc+yy, yc+xx);
    setPixel(xc-xx, yc+yy);
    setPixel(xc-yy, yc+xx);
    setPixel(xc+xx, yc-yy);
    setPixel(xc+yy, yc-xx);
    setPixel(xc-xx, yc-yy);
    setPixel(xc-yy, yc-xx);
}

void MidPointCircle()
{
    glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	x = 0;
	y = rad;
	pk = 1-rad;
	while(x<y)
	{
		x++;
		if(pk<0)
		{
			pk = pk+2*x+1;
		}
		else
		{
			y--;
			pk = pk+2*(x-y)+1;
		}
		CirclePlotPoints(x/200.0,y/200.0);
	}
}

void PieChart(int * data,int * xvalue)
{

    float num=12;;
	float angle,angle_next,prevangle=0.0;
	float datasum = 0;
	float point_x,point_y,point_xn,point_yn;
	MidPointCircle();
	for(int i=11;i>=0;i--)
	{
		datasum+=data[i];

	}
	for(int i=0;i<num;i++)
	{
		angle = twopi*data[i]/datasum+prevangle;
		 angle_next = twopi*data[(i+1)%12]/datasum+prevangle;

		point_x = xc + rad*cos(angle);
		point_y = yc + rad*sin(angle);
		 point_xn = xc + rad*cos(prevangle);
		 point_yn = yc + rad*sin(prevangle);
		if(xvalue[i]!=0){
                char ch[12];
                sprintf(ch,"%d",xvalue[i]);
            texts1(ch,(point_x+point_xn)/400,(point_y+point_yn)/400,0.0);
		}
		glColor3f(0.0,1.0,0.0);
		glBegin (GL_LINES);
			glColor3f(1.0,0.0,0.0);
            glVertex2f(xc,yc);
            glVertex2f(point_x/200.0, point_y/200.0);
        glEnd();
        prevangle = angle;
        glColor3f(0.0,0.0,0.0);
        glRectf(-0.9,0.8,-0.75,0.9);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINES);
         glVertex2f(-0.87,0.85);
        glVertex2f(-0.78,0.85);
        glVertex2f(-0.85,0.875);
        glVertex2f(-0.87,0.85);
        glVertex2f(-0.85,0.825);
        glVertex2f(-0.87,0.85);
        glEnd();
	}
}


