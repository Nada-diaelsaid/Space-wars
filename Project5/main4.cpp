#include <cassert>
#include <cmath>
#include <string>
#include <iostream>
#include <Windows.h>
#include "GetGlut.h"
#include "Sleep.h"
#include "ObjModel.h"
#include "objloader.h"
#include <algorithm>
#define GL_GLEXT_PROTOTYPES 
#include <SDL_opengl.h>
#include <time.h> 
using namespace std;
int gameover=0;int win=0;int timer=100;char const* t1="100";  string t3;
bool bulletFinish = true, bullet2Finish=true;
bool gameDone= false;
int scoreN=0;char const *pchar="0";char const* aChar="0";string s ;
float xt=1.0,yt=0.0 ,  xt_bullet= 0 , yt_bullet = 0, zt_bullet = 0 ;      // For interactive Keyboard

float xt_bullet2= 0 , yt_bullet2 = 0, zt_bullet2 = 0 , temp = 0 ;
int countobj = 0   , countHunter = 0 , j = 0 ,i = 0  , m; 

GLfloat xthunter[20] ; int yt_hunter[20] ; int zt_hunter[20] ; 

int a = 0;
float x = 1.0,y = 1.0,z=1.0; float z_cam = 15  , x_cam= 65;  // For Movement
float angle =0;  				// For Function animation
float Autorun =1600;			// For Movement Autorun
float MEcount = 0.0f ;// earth
bool movingUp = false; // Whether or not we are moving up or down  
float yLocation = 0.0f;
ObjModel obj;
ObjModel HunterObj[20];
ObjModel planet;
void init();
void initDisplay();
void keyboard(unsigned char key, int x, int y);
void specialkeyboard(int key, int x, int y);
void reshape(int w, int h);
void update();
void display();
void hunter() ;
void gunship();
void animation();
void Auto();
void lightWorld();
void bullet() ;
void bullet2() ;
void time();
void textDisplay(GLfloat i, GLfloat j, char const* text);
void background();
void loseORwin();

int main(int argc, char* argv[])
{
	glutInitWindowPosition(0, 0);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Space wars");
	glutFullScreen();
	glEnable(GL_DEPTH_BUFFER);
	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);
	
	initDisplay() ;
	glutSpecialFunc(specialkeyboard);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glClearColor(0, 0 , 0 ,0);
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutIdleFunc(Auto);
	init();
	
	glutMainLoop();

	return 1;
}

void init()
{
  obj.load("gunship.obj");
  for(i=0 ;i < 20 ; i++)///load 20 ship enemy
	{
	HunterObj[i].load("Low_Poly_Spaceship.obj");
	}
  for ( int n = 0 ; n < 20 ; n++ )///adjust z of the enemy ships
	{
	zt_hunter[n] = -60 ; 
	}
  planet.load("AlienPlanet.obj");
}

void initDisplay()
{
//	glClearColor(0.5, 0.5, 0.5, 0.0);
	//glColor3f(0.0, 0.0, 0.0);
	
	glEnable(GL_CULL_FACE);
	glShadeModel (GL_SMOOTH); //set the shader to smooth shader
	glCullFace(GL_BACK); 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
		glEnable(GL_COLOR_MATERIAL);
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport (0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLdouble)w / (GLdouble)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW); 
	glutPostRedisplay();
}

void update()
{
	//update your variables here
	sleep(1.0 / 60.0);
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	gluLookAt(x_cam, 0.0, z_cam,
		0.0, -0.5, -60.0,
		0.0, 1.0, 1.0);
		

	
	if(x_cam==0 && z_cam==-50)///when camera stable down begin timer
	{
		loseORwin();
	}
	lightWorld();
	background();

	
	hunter();

	bullet();
	bullet2();
	
	gunship();
	
	glutSwapBuffers(); //Do it once frame is ended
}
void keyboard(unsigned char key, int x, int y)
{
	if(!gameDone)//stop moving if game is done
	{
	switch(key)
	{
		case ' ':
			if(bullet2Finish==true || bulletFinish==true ){
				if(bulletFinish==true)
				{
					bulletFinish=false;
					PlaySound((LPCSTR)"shot.wav", NULL, SND_FILENAME | SND_ASYNC);

					xt_bullet = xt ;
					zt_bullet = -60 ;
					yt_bullet = yt-17  ;
					//cout <<"countob  " << countobj << endl;
					countobj++;
				}
			else if(bullet2Finish==true)
				{
					bullet2Finish=false;
					PlaySound((LPCSTR)"shot.wav", NULL, SND_FILENAME | SND_ASYNC);

					xt_bullet2 = xt ;
					zt_bullet2 = -60 ;
					yt_bullet2 = yt-17  ;
					//cout <<"countob  " << countobj << endl;
					countobj++;
				}
			else if(countobj >1){
					countobj=0;
					bulletFinish=true;
					bullet2Finish=false;
					//cout << "countob " << countobj<<endl;
				}
			cout <<bulletFinish<<bullet2Finish<<endl;
			}
			
		break;
			
		case 27://ESC
			exit(0); // normal exit
			break;
		default:
			break;
			}
		}
}
void specialkeyboard(int key, int x, int y)// For keyboard interactive
{
	if(gameDone==false){
	switch ( key )
	{
	case GLUT_KEY_RIGHT:
		if( xt == 61){
			glutPostRedisplay();
			break;
		}
		xt += 12.0;
		cout << xt <<endl;
		glutPostRedisplay();
		break;
			
	case GLUT_KEY_LEFT:
		if( xt == -59){
				glutPostRedisplay();
				break;
		}
		xt -= 12.0;	
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		if( yt == 0){
			glutPostRedisplay();
			break;
		}
		yt -= 2.0;
		glutPostRedisplay();
		break;

	case GLUT_KEY_UP:
		if( yt == 60){
			glutPostRedisplay();
			break;
		}	
		yt += 2.0;
		glutPostRedisplay();
		break;
	default:
		break;
		}
	}
}
void animation(void)
{
	if(angle>=0 && angle<10)
		angle = angle+0.5;
	else angle = 0;
		glutPostRedisplay();
}
void Auto(void)
{
	if(z_cam != -50 ){
		z_cam -= 5.0f ;
	}
	if(x_cam != 0 ){
		x_cam -= 5.0f ;
	}
	yt_bullet += 5.0f ;
	//cout <<"yaaay "<<yt_bullet;
   if(yt_bullet == 18 ){
		
		zt_bullet =  0 ;
		bulletFinish=true;
	}
	yt_bullet2 += 5.0f ;
	
	if(yt_bullet2 == 18 ){

		zt_bullet2 =  0 ;
		bullet2Finish=true;

	}
	for(a = 0 ; a < 20 ; a++){
		 if(xt_bullet == xthunter[a] && yt_bullet == yt_hunter[a]&& zt_bullet == zt_hunter[a]){
			scoreN++;
			s = std::to_string(scoreN);
			pchar = s.c_str();					
			cout <<"pchar "<< pchar<<endl;
			PlaySound((LPCSTR)"explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
			zt_hunter[a] = 0;
			bulletFinish = true;
			zt_bullet = 0; 
		}
		if(xt_bullet2 == xthunter[a] && yt_bullet2 == yt_hunter[a]&& zt_bullet2 == zt_hunter[a]){
			scoreN++;
			s = std::to_string(scoreN);
			pchar = s.c_str();
			cout <<"pchar " <<pchar<<endl;
			PlaySound((LPCSTR)"explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
			zt_hunter[a] = 0;
			bullet2Finish = true;
			zt_bullet2 = 0 ; 
		}
	}
	glutPostRedisplay();
}

void bullet(void){
	glPushMatrix();
	glColor3d(0.1,0.1,0.1);
	glColor3d(1,0.5,0);

	glTranslatef(1,yt_bullet,zt_bullet);
	glTranslated(xt_bullet,yt_bullet, zt_bullet);			
	glutSolidSphere(.80,100,100);
	glPopMatrix();
}
void bullet2(void){
	glPushMatrix();
	glColor3d(0.1,0.1,0.1);
	glColor3d(1,.5,0);
	glTranslatef(1,yt_bullet2,zt_bullet2);
	glTranslated(xt_bullet2,yt_bullet2, zt_bullet2);
	glutSolidSphere(.80,100,100);
	glPopMatrix();
}
void hunter(void){
	glPushMatrix();        
	xthunter[0]= -59 ;
	yt_hunter[0] = 8 ;
	glTranslatef( 0 ,yt_hunter[0] ,zt_hunter[0]);
	glTranslated( xthunter[0],yt_hunter[0],zt_hunter[0]);
	glRotatef(-360,0.0,1.0,0.0);// hunter
	glRotatef(-45,1.0,0.0,0.0);//hunter
	glScalef(2.5,2.5,2.5);
	HunterObj[0].draw();		
	glPopMatrix();

	for( j = 1 ; j < 10 ; j++){
		xthunter[j] = xthunter[j-1]+ 12  ;
		yt_hunter[j] =  yt_hunter[j-1] ;
		glPushMatrix();
		glTranslatef( 0 ,yt_hunter[j] ,zt_hunter[j]);
		glTranslated(  xthunter[j] ,yt_hunter[j],zt_hunter[j]);
		glRotatef(-360,0.0,1.0,0.0);// hunter
		glRotatef(-45,1.0,0.0,0.0);//hunter
		glScalef(2.5,2.5,2.5);
		HunterObj[j].draw();		
		glPopMatrix();
	}

	glPushMatrix();                  
	xthunter[10]= -59 ;
	yt_hunter[10] = 3 ;
	glTranslatef( 0 ,yt_hunter[10] ,zt_hunter[10]);
	glTranslated( xthunter[10],yt_hunter[10],zt_hunter[10]);
	glRotatef(-360,0.0,1.0,0.0);// hunter
	glRotatef(-45,1.0,0.0,0.0);//hunter
	glScalef(2.5,2.5,2.5);
	HunterObj[10].draw();
	glPopMatrix(); 
	for( j = 11 ; j < 20 ; j++){
		xthunter[j] = xthunter[j-1]+ 12  ;
		yt_hunter[j] =  yt_hunter[j-1] ;
		glPushMatrix();
		glTranslatef(0 ,yt_hunter[j] ,zt_hunter[j]);
		glTranslated(xthunter[j] ,yt_hunter[j],zt_hunter[j]);
		glRotatef(-360,0.0,1.0,0.0);// hunter
		glRotatef(-45,1.0,0.0,0.0);//hunter
		glScalef(2.5,2.5,2.5);
		HunterObj[j].draw();
		glPopMatrix();
	}
}

void gunship(){
	glPushMatrix();
	glColor3d(1,1,1);
	glTranslatef(0,-30,-60);
	glTranslated(xt , yt, -60);
	glScalef(0.5,0.5,0.5);
	glRotatef(-180,0.0,0.0,1.0);// gunship
	glRotatef(-270,1.0,0.0,0.0); //gunship
	obj.draw();
	glPopMatrix();
}
void textDisplay(GLfloat x, GLfloat y, char const* text)
{
    glPushMatrix();
    glTranslatef(x, y, -60);
    glScalef(1/152.38, 1/152.38, 1/152.38);
    for( char const* p = text; *p; p++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    }
    glPopMatrix();
}
void time(){
	if(timer>0 && scoreN<20){
		timer--;
		t3 = std::to_string(timer);
		t1 = t3.c_str();
	}
	else if(timer>0 && scoreN==20){
		//do nothing
	}
	else if(timer<=0){
		gameDone=true;
		return;
	}
}
void background(){
	glColor3ub(255,0,0);
	textDisplay(-3,3,"SPACE WARS..");
	//starsss
	srand (time(NULL));
	for (int h = 0; h < 200; h++) {
		if (h<=50){
			///Produce stars in 1st quad
			glPushMatrix();
			glColor3d(1,1,1);
			int i= rand()%35;
			int j= rand()%35;
			glTranslatef(i, j,-60);
			glutSolidSphere(.01,40,10);
			glPopMatrix();
		  }
	  ///Produce stars in 3rd quad
		else if(h>50 && h<=100){
			glPushMatrix();
			glColor3d(1,1,1);
			int i= -1*(rand()%35);
			int j = -1*(rand()%35);
			glTranslatef(i,j,-60);
			glutSolidSphere(.01,40,10);
			glPopMatrix();
	  }
	///Produce stars in 2nd quad
	else if(h>100 && h<=150){
			glPushMatrix();
			glColor3d(1,1,1);
			int i= -1*(rand()%35);
			int j = 1*(rand()%35);
			glTranslatef(i,  j,-60);
			glutSolidSphere(.01,40,10);
			glPopMatrix();
	  }
	else if(h>150 && h<=200){
		///Produce stars in 4th quad
			glPushMatrix();
			glColor3d(1,1,1);
			int i= rand()%35;
			int j = -1*(rand()%35);
			glTranslatef(i,  j,-60);
			glutSolidSphere(.01,40,10);
			glPopMatrix();
		}
	}
	
	//score text
	glColor3ub(255,0,0);
    textDisplay(4,4,"Score:");textDisplay(7,4,pchar);textDisplay(8,4,"/20");
	//time
	glColor3ub(255,0,0);
	textDisplay(-9.75,4,"Time left:");	textDisplay(-5.25,4,t1);
	//draw planet
	glPushMatrix();
	glColor3d(1,1,1);
	glTranslatef(0, -5,-200);
	glScalef(20,20,7);
	//glRotated(90,0,1,0);
	planet.draw();

	
	glPopMatrix();
}

void lightWorld(){
	GLfloat qaAmbient[] = { 20,20,20,10 };
	GLfloat qaDiffuseLight[] = { 80,80,80,10 };
	GLfloat qaSpecularLight[] = { 10,10,10,10 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
}

void loseORwin(){
time();
if(gameDone==true){
	glColor3ub(255,0,0);
	textDisplay(-2.75,-0.75,"GAME OVER!!");
	if(gameover==0)///play game over sound one time only (when gameover is zero)
	{
		PlaySound((LPCSTR)"gameover.wav", NULL, SND_FILENAME | SND_ASYNC);
		gameover++;//increment it in order not to play it again
	}
}
else if(gameDone==false && timer>0 && scoreN==20){
	//cout << "here";
	glColor3ub(255,0,0);
	textDisplay(-2.75,-0.75,"YOU WON!!");
	if(win==0){
		PlaySound((LPCSTR)"win.wav", NULL, SND_FILENAME | SND_ASYNC);
		win++;
	}
}
}