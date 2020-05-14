#include <iostream>
#include <stdlib.h>
#include<GL/gl.h>
//#include<mmsystem.h>
#include <GL/glut.h>
#include<math.h>
#include<cmath>
#include<cstring>
#define playerSizeY .2
#define playerSizeX .1
#define maxAxisX 2
#define maxAxisY 2
#include<time.h>
#include<windows.h>
#include <sstream>
#include<fstream>
# define PI 3.14
using namespace std;
void player();
void enemy1();
void ally1();
void scoreUp();
void sound();
void updateWheel(int value);
void playerWheelMoving();
void showText( float x, float y, char *st,int number);
void showGameOverText(float x, float y, char *st, char * highscore);
void showGameName(float x, float y, char *st);
void display1();
float playerPositionx=0,playerPositiony=0,enemy1Positionx=-0.3,enemy1Positiony=1.8,ally1Positionx=-0.6,ally1Positiony=1.6,scoreUpPositionx=0.3,scoreUpPositiony=1.6;
int timer=500;
int score=0;
float _angleWheel = 0;
float speedWheel = 1.0f;
char scoreText[] = "SCORE: ";
char lifeText[] = "LIFE: ";
char gameOverText[] = "GAME OVER. ";
char highScoreText[] = "HIGHEST SCORE: ";
char gameName[]= "HEART STONE";
bool gameOver=false;
short life=3;
int sky1=38, sky2= 154, sky3=  214;
int sun1= 252, sun2=211, sun3= 3;
int daynightcounter=2;
bool scenestatus=true;
float bigshipposition=0.0;
float smallshipposition=0.0;
void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    display1();
    player();

    enemy1();
    ally1();
    scoreUp();
    showText(.6,.9,scoreText,score);
    showText(.6,.8,lifeText,life);
    showGameName(-0.95,0.9,gameName);

    if(gameOver==true)
    {
        ifstream highScore2;
        highScore2.open("highScore.txt");
        int x;
        highScore2>>x;
        highScore2.close();
        if(x<score)
        {
            ofstream l;
            l.open("highScore.txt");
            l<<score;
            l.close();
        }
        showGameOverText(.0,.0,gameOverText,highScoreText);
        /*ofstream l;
        l.open("highScore.txt");
        l<<"6";
        l.close();*/
    }

    glFlush();



}

void player()

{

    glPushMatrix();

    glColor3f(0.0,0.0,1.0);

    glTranslatef(playerPositionx, playerPositiony, 0.0);

    glBegin(GL_POLYGON);

    glVertex2f(0.0,-0.8);

    glVertex2f(0.1,-0.8);

    glVertex2f(0.1,-1.0);

    glVertex2f(0.0,-1.0);

    glEnd();

    glPopMatrix();

    //WHEEL
    //FIRST BLADE
    glPushMatrix();

    glTranslatef(playerPositionx, playerPositiony, 0.0);
    glTranslatef(0.05,-0.85,  0.0);
    glScaled(0.1,0.1,1.0);
    glPushMatrix();
    glRotatef(_angleWheel, 0.0, 0.0, 1.0);
    glScaled(0.5,0.5,1.0);
    glTranslatef(0.1, -0.1, 0.0);//Rotate about the the vector (1, 2, 3)
    glColor3f(0.0,1.0,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(0.0,0.0);
    glVertex2f(0.9,0.1);
    glVertex2f(0.0,0.2);
    glEnd();
    glPopMatrix();



//SECOND BLADE
    glPushMatrix(); //Save the current state of transformations
    glRotatef(_angleWheel, 0.0, 0.0, 1.0);
    glScaled(0.5,0.5,1.0);
    glTranslatef(-0.1, -0.1, 0.0);//Rotate about the the vector (1, 2, 3)
    glColor3f(0.0,1.0,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(0.0,0.0);
    glVertex2f(-0.9,0.1);
    glVertex2f(0.0,0.2);
    glEnd();
    glPopMatrix();


//THIRD BLADE
    glPushMatrix();
    glRotatef(_angleWheel, 0.0, 0.0, 1.0);
    glScaled(0.5,0.5,1.0);
    glTranslatef(-0.1, -0.1, 0.0);
    glColor3f(0.0,1.0,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(0.0,0.0);
    glVertex2f(0.1,-0.9);
    glVertex2f(0.2,0.0);
    glEnd();
    glPopMatrix();


//FOURTH BLADE
    glPushMatrix();
    glRotatef(_angleWheel, 0.0, 0.0, 1.0);
    glScaled(0.5,0.5,1.0);
    glTranslatef(-0.1, 0.1, 0.0);
    glColor3f(0.0,1.0,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(0.0,0.0);
    glVertex2f(0.1,0.9);
    glVertex2f(0.2,0.0);
    glEnd();
    glPopMatrix();

    glPopMatrix();

}
void playerWheelMoving()
{
    _angleWheel += speedWheel;
    if (_angleWheel > 360) {
        _angleWheel -= 360;
    }
}



void enemy1()

{

    glPushMatrix();

    glColor3ub(169,169,169);

    glTranslatef(enemy1Positionx, enemy1Positiony, 0.0);

    glBegin(GL_POLYGON);

    glVertex2f(0.002,-0.98);

    glVertex2f(0.045,-0.99);

    glVertex2f(0.053,-0.97);

    glVertex2f(0.05,-0.94);
    glVertex2f(0.04,-0.91);
    glVertex2f(0.0023,-0.93);
    glVertex2f(0.001,-0.96);

    glEnd();

    glPopMatrix();

}

void enemy1Move()
{
     //Enemy Movement
    float collision2=enemy1Positiony-playerPositiony;
    //FOR ENEMY 1
    if(((collision2>0.19 && collision2<0.21) || (collision2>0.09 && collision2<0.11) || (collision2>-0.01 && collision2<0.01)) &&  abs(enemy1Positionx-playerPositionx)<0.09 )

    {
        life--;
        if(life<=0)
        {
            gameOver=true;
        }

    }

    if(enemy1Positiony>-maxAxisY)

    {

        enemy1Positiony-=0.1;

    }

    else

    {

        enemy1Positiony=1.8;

        score++;

        cout<<"SCORE: "<<score<<endl;

        srand(time(0));

        enemy1Positionx=((float)(rand()%10))/10-((float)(rand()%10))/10;
        if(timer>100)
        {
            timer=timer-100;
        }

    }
}

void scoreUp()
{
    glPushMatrix();

    glColor3f(0.0,1.0,1.0);

    glTranslatef(scoreUpPositionx, scoreUpPositiony, 0.0);

    glBegin(GL_POLYGON);
    glVertex2f(0.03,-0.95);
    glVertex2f(0.07,-0.95);
    glVertex2f(0.09,-0.93);
    glVertex2f(0.07,-0.93);
    glVertex2f(0.05,-0.91);
    glVertex2f(0.03,-0.93);
    glVertex2f(0.01,-0.93);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.03,-0.95);
    glVertex2f(0.01,-0.99);
    glVertex2f(0.05,-0.97);
    glVertex2f(0.09,-0.99);
    glVertex2f(0.07,-0.95);
    glEnd();

    glPopMatrix();
}

void scoreUpMove()
{
    float collision2=scoreUpPositiony-playerPositiony;
    //FOR ENEMY 1
    if(((collision2>0.19 && collision2<0.21) || (collision2>0.09 && collision2<0.11) || (collision2>-0.01 && collision2<0.01)) &&  abs(scoreUpPositionx-playerPositionx)<0.09 )

    {

        scoreUpPositiony=-0.6;
        score+=10;


    }
    if(scoreUpPositiony>-maxAxisY+0.4)

    {

        scoreUpPositiony-=0.1;

    }

    else

    {

        scoreUpPositiony=1.8;

        srand(time(0)*7);

        scoreUpPositionx=((float)(rand()%10))/10-((float)(rand()%10))/10;
    }
}

void ally1()

{

    glPushMatrix();
    glTranslatef(ally1Positionx, ally1Positiony, 0.0);
    glTranslatef(0.026, -0.38, 0.0);
    glScaled(0.028,0.028,1.0);
    glPushMatrix();
    glColor3f(0.0,1.0,1.0);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
        {
            glColor3f(1.0,0.0,0.0);
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.85;
            float x = r * cos(A);
            float y = r * sin(A)-19.0;
            glVertex2f(x,y );
        }

	glEnd();
    glPopMatrix();

    glPushMatrix();
	glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
        {
            glColor3f(1.0,0.0,0.0);
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.85;
            float x = r * cos(A)+1.48;
            float y = r * sin(A)-19.0;
            glVertex2f(x,y );
        }

	glEnd();
    glPopMatrix();

    glPushMatrix();
    glScaled(3.35,2.5,1.0);
    glTranslatef(-0.29,-7.7, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(0.0,0.0);
	glVertex2f(1.0,0.0);
	glVertex2f(0.5,-1.0);
	glEnd();
    glPopMatrix();
    glPopMatrix();

}
void ally1Move()
{
     float collision2=ally1Positiony-playerPositiony;
    //FOR ALLY 1
    if(((collision2>0.19 && collision2<0.21) || (collision2>0.09 && collision2<0.11) || (collision2>-0.01 && collision2<0.01)) &&  abs(ally1Positionx-playerPositionx)<0.09 )

    {

         //RANDOM X AXIS
        srand(time(0)*3);

        ally1Positionx=((float)(rand()%10))/10-((float)(rand()%10))/10;
        if(abs(ally1Positionx-enemy1Positionx)<0.09 && abs(ally1Positiony-enemy1Positiony)<0.09)
        {
            ally1Positiony+=0.2;
        }
        ally1Positiony=2;
        score+=10;

    }
    //MOVEMENT
    ally1Positiony-=0.1;
    if(ally1Positiony<-0.1)

    {

        life=0;
        gameOver=true;


    }
}

void update(int value)
{
    if(!gameOver)
    {
        enemy1Move();
        ally1Move();
        scoreUpMove();

        glutPostRedisplay();

        glutTimerFunc(timer, update, 0);
    }
    else
    {

    }
}

void specialKeys(int key, int x, int y) {
    if(!gameOver)
    {
        switch (key) {

      case GLUT_KEY_UP:

          if(playerPositiony<maxAxisY-playerSizeY)

          {

              playerPositiony+=0.1;

          }

          break;

      case GLUT_KEY_DOWN:

          if(playerPositiony>=0.1)

          {

              playerPositiony-=0.1;

          }

          break;

       case GLUT_KEY_LEFT:

           if(playerPositionx>=-maxAxisX/2+playerSizeX-0.1)

           {

               playerPositionx-=0.1;

           }

          break;

      case GLUT_KEY_RIGHT:

          if(playerPositionx<maxAxisX/2-playerSizeX)

           {

               playerPositionx+=0.1;

           }

          break;
    }

}


    glutPostRedisplay();

}
/*void sound()
{

    //PlaySound("Doom-OST-E1M1-At-Doom_s-Gate.wav", NULL, SND_ASYNC|SND_FILENAME);
    PlaySound(Text("Doom.wav"), NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);

}*/

void updateWheel(int value)
{
   if(!gameOver)
   {
        playerWheelMoving();
        glutPostRedisplay();

        glutTimerFunc(1, updateWheel, 0);
   }
}
void showText( float x, float y, char *st,int number)
{
    int l,i;


    l=strlen( st );
    glColor3ub(123,199,243);
    glRasterPos2f( x, y);
    for( i=0; i < l; i++)
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);

    }
    stringstream strs;
    strs << number;
    string temp_str = strs.str();
    char* char_type = (char*) temp_str.c_str();
    l=strlen(char_type);
    for( i=0; i < l; i++)
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, char_type[i]);

    }
}
void showGameOverText( float x, float y, char *st, char *highscore)
{
    int l,i;
    l=strlen( st );
    glColor3ub(70,23,55);
    glRasterPos2f( x, y);
    for( i=0; i < l; i++)
    {
       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);

    }
    l=strlen( highscore );
    glRasterPos2f( (x-.1), (y-.1));
    for( i=0; i < l; i++)
    {
       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, highscore[i]);

    }

    ifstream highScore2;
    highScore2.open("highScore.txt");
    int hScore;
    highScore2>>hScore;
    highScore2.close();

    stringstream strs;
    strs << hScore;
    string temp_str = strs.str();
    char* char_type = (char*) temp_str.c_str();
    l=strlen(char_type);
    for( i=0; i < l; i++)
    {
       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, char_type[i]);

    }
}
void showGameName(float x, float y, char *st)
{
    int l,i;
    l=strlen( st );
    glColor3ub(255,0,0);
    glRasterPos2f( x, y);
    for( i=0; i < l; i++)
    {
       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);

    }
}
//Scene

void display1()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);



    //glLoadIdentity();



///fullsky
glPushMatrix();
    glBegin(GL_POLYGON);
	glColor3ub(sky1,sky2,sky3);

	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(-1.0f, 0.0f);

	glEnd();
glPopMatrix();
int i;
	GLfloat x=0.7f; GLfloat y=0.7f; GLfloat radius =.1f;
	int triangleAmount = 20;
	GLfloat twicePi = 2.f * PI;
	glBegin(GL_TRIANGLE_FAN);
	    glColor3ub(sun1, sun2, sun3);
		glVertex2f(x, y);
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();


	    glBegin(GL_POLYGON);//mati
	glColor3ub(255, 230, 128);

	glVertex2f(-1.0f, -0.6f);
	glVertex2f(1.0f,-0.6f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.f, -1.0f);

	glEnd();

    glBegin(GL_POLYGON);//mati1
	glColor3ub(255, 217, 179);

	glVertex2f(-1.0f, -0.6f);
	glVertex2f(1.0f,-0.6f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.f, -1.0f);

	glEnd();

	//water()

    glBegin(GL_QUADS);
    glColor3ub(0, 153, 153);
    glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, -0.5f);
	glVertex2f(-1.0f, -0.5f);
	glEnd();







/*// bird()

  glBegin(GL_LINES);
  glColor3ub(255,255,255);
  glVertex2f(0.2f,0.8f);
  glVertex2f(0.18f,0.77f);

  glColor3ub(255,255,255);
  glVertex2f(0.18f,0.77f);
  glVertex2f(0.15f,0.79f);

  glColor3ub(255,255,255);
  glVertex2f(0.13f,0.8f);
  glVertex2f(0.11f,0.77f);

  glColor3ub(255,255,255);
  glVertex2f(0.11f,0.77f);
  glVertex2f(0.08f,0.79f);

  glEnd();*/

//tree

    glBegin(GL_QUADS);//coplant
	glColor3ub(77, 40, 0);

	glVertex2f(-0.8f, -0.75f);
	glVertex2f(-0.77f,-0.75f);
	glVertex2f(-0.77f, -0.9f);
	glVertex2f(-0.8f, -0.9f);

	glEnd();

    glBegin(GL_QUADS);//coplant2
	glColor3ub(77, 40, 0);

	glVertex2f(-0.77f, -0.3f);
	glVertex2f(-0.76f,-0.3f);
	glVertex2f(-0.77f, -0.75f);
	glVertex2f(-0.8f, -0.75f);

	glEnd();




  glBegin(GL_TRIANGLES);//copata1
	glColor3ub(0, 77, 0);

        	glVertex2f(-0.77f, -0.3f);
	        glVertex2f(-0.86f,-0.33f);
            glVertex2f(-0.8f, -0.36f);


	glEnd();

		  glBegin(GL_TRIANGLES);//copata1
	glColor3ub(0, 77, 0);

        	glVertex2f(-0.9f, -0.45f);
	        glVertex2f(-0.86f,-0.33f);
            glVertex2f(-0.8f, -0.36f);


	glEnd();

	  glBegin(GL_TRIANGLES);//copata2
	glColor3ub(0, 77, 0);

        	glVertex2f(-0.77f, -0.3f);
	        glVertex2f(-0.65f,-0.33f);
            glVertex2f(-0.68f, -0.4f);


	glEnd();


	  glBegin(GL_TRIANGLES);//copata2
	glColor3ub(0, 77, 0);

	        glVertex2f(-0.65f,-0.33f);
            glVertex2f(-0.68f, -0.4f);
            glVertex2f(-0.6f, -0.45f);


	glEnd();

	  glBegin(GL_QUADS);//copata3
	glColor3ub(0, 77, 0);


	        glVertex2f(-0.56f,-0.27f);
            glVertex2f(-0.67f, -0.2f);
            glVertex2f(-0.57f, -0.25f);
            glVertex2f(-0.77f, -0.3f);


	glEnd();

		  glBegin(GL_QUADS);//copata4
	glColor3ub(0, 77, 0);


	        glVertex2f(-0.90f,-0.28f);
            glVertex2f(-0.97f, -0.25f);
            glVertex2f(-0.87f, -0.2f);
            glVertex2f(-0.77f, -0.3f);


	glEnd();

//small boat
    glPushMatrix();
    glTranslatef(smallshipposition, 0.0, 0.0);
    glBegin(GL_POLYGON); //boatp
	glColor3ub(27, 75, 52);

	glVertex2f(0.6f, -0.0f);
	glVertex2f(0.63f, -0.02f);
	glVertex2f(0.65f, -0.02f);
    glVertex2f(0.68f, -0.0f);
    glEnd();



glBegin(GL_TRIANGLES);//bpal
	glColor3ub(27, 75, 52);

	glVertex2f(0.63f, 0.0f);
	glVertex2f(0.65f, 0.1f);
	glVertex2f(0.65f, 0.0f);

	 glEnd();
	 glPopMatrix();

//big ship
    glPushMatrix();
    glTranslatef(bigshipposition, 0.0, 0.0);
    glBegin(GL_POLYGON);//hb
    glColor3ub(0, 0, 0);
	glVertex2f(-0.3f, -0.1f);
	glVertex2f(-0.3f, -0.03f);
	glVertex2f(0.3f, -0.03f);
    glVertex2f(0.3f, -0.1f);
    glEnd();


     glBegin(GL_POLYGON);//hb
    glColor3ub(178, 190, 181);
	glVertex2f(-0.28f, -0.03f);
	glVertex2f(0.28f, -0.03f);
	glVertex2f(0.28f, 0.05f);
	glVertex2f(-0.28f, 0.05f);
    glEnd();
    glBegin(GL_LINES);//bh
    glColor3ub(0,0,0);
    glVertex2f(0.28f, -0.03f);
	glVertex2f(-0.28f, -0.03f);
    glEnd();

    glBegin(GL_POLYGON);//bh
    glColor3ub(0, 0, 0);
    glVertex2f(-0.25f, 0.05f);
    glVertex2f(0.25f, 0.05f);
	glVertex2f(0.25f, 0.12f);
	glVertex2f(-0.25f, 0.12f);

    glEnd();

glBegin(GL_LINES);//bh
    glColor3ub(0,0,0);
    glVertex2f(-0.25f, 0.05f);
    glVertex2f(0.25f, 0.05f);
    glEnd();

    glBegin(GL_POLYGON);//bh
    glColor3ub(178, 190, 181);
    glVertex2f(-0.23f, 0.12f);
    glVertex2f(-0.12f, 0.12f);
	glVertex2f(-0.12f, 0.17f);
	glVertex2f(-0.23f, 0.17f);

    glEnd();

    glBegin(GL_POLYGON);//bh
    glColor3ub(178, 190, 181);
    glVertex2f(0.23f, 0.12f);
    glVertex2f(0.12f, 0.12f);
	glVertex2f(0.12f, 0.17f);
	glVertex2f(0.23f, 0.17f);

    glEnd();

    glBegin(GL_POLYGON);//bh
    glColor3ub(178, 190, 181);
    glVertex2f(-0.09f, 0.12f);
    glVertex2f(0.09f, 0.12f);
	glVertex2f(0.09f, 0.17f);
	glVertex2f(-0.09f, 0.17f);

    glEnd();

    glBegin(GL_LINES);//bh
    glColor3ub(0,0,0);
    glVertex2f(-0.25f, 0.12f);
    glVertex2f(0.25f, 0.12f);
    glEnd();




    glBegin(GL_POLYGON);//bh
	glColor3ub(178, 190, 181);
	glVertex2f(-0.4f, -0.1f);
	glVertex2f(-0.35f, -0.25f);
	glVertex2f(0.35f, -0.25f);
    glVertex2f(0.4f, -0.1f);
    glEnd();



     glBegin(GL_POLYGON);//bh
	glColor3ub(0, 0, 0);
	glVertex2f(-0.35f, -0.25f);
	glVertex2f(0.35f, -0.25f);
	glVertex2f(0.34f,-0.30f);
	glVertex2f(-0.34f, -0.30f);
    glEnd();

    glPopMatrix();


}

void sceneautomaticupdate(int value)
{
    if(scenestatus==true)
    {
        sky1=38; sky2=154;sky3=214;
        sun1= 252; sun2=211; sun3= 3;
        daynightcounter--;
        if(daynightcounter==0)
        {
            scenestatus=false;
        }
    }
    if(scenestatus==false)
    {
        sky1=49; sky2=98; sky3=131;
        sun1= 255; sun2=255; sun3= 255;
        daynightcounter++;
        if(daynightcounter==2)
        {
            scenestatus=true;
        }
    }
    glutPostRedisplay();

    glutTimerFunc(1000, sceneautomaticupdate, 0);
}
void shipmovingupdate(int value)
{
    bigshipposition+=0.0005;
    if(bigshipposition>=1.5)
    {
        bigshipposition=-1.4;
    }
    smallshipposition-=0.0003;
    if(smallshipposition<=-1.7)
    {
        smallshipposition=+0.8;
    }
    glutPostRedisplay();

    glutTimerFunc(1, shipmovingupdate, 0);
}
int main(int argc, char** argv) {



    //sound();
    glutInit(&argc, argv);

    glutInitWindowSize(700, 700);

    glutCreateWindow("Game");



    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutDisplayFunc(display);



    glutTimerFunc(timer, update, 0);

    glutTimerFunc(1, updateWheel, 0);
    glutTimerFunc(1000,sceneautomaticupdate, 0);
	glutTimerFunc(400, shipmovingupdate, 0);
    glutSpecialFunc(specialKeys);

    //glutKeyboardFunc(keyboard);




    glutMainLoop();

    return 0;

}
