/*Copyright (C) <2013>  <HomegamesKiro>
This file is part of Obj Loader by HomegamesKiro©.

    Obj Loader is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Obj Loader is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Obj Loader.  If not, see <http://www.gnu.org/licenses/>.*/
#ifndef __CAMERA__HEADER
#define __CAMERA__HEADER

#include "Main.h"

class Camera
{public:
	
	int ViewSensibility;
	bool  ENABLEVIEW;
	void InitCamera();
	void SetSensibility(int sensibility);
	void SetView(int __pp,int __yy,int __rr);
	void UseMouselook(bool __ms);
	bool GetMouseLook();
    void JumpTo(float nx,float ny,float nz);
	void UpdateView(int width, int height);
	void ViewCamera();

//private:
	float x;float y;float z;
	float pitch,yaw,roll;
};

bool Camera::GetMouseLook()
{
	return Camera::ENABLEVIEW;
}


void Camera::InitCamera()
{
	Camera::ViewSensibility=18;
	Camera::pitch=0;
	Camera::yaw=0;
	Camera::roll=0;
	Camera::x=0;
	Camera::y=0;
	Camera::z=0;
};


void Camera::SetSensibility(int sensibility)
{   
	if (sensibility <40)if (sensibility >=1)
	Camera::ViewSensibility=sensibility;
};

void Camera::JumpTo(float nx,float ny,float nz)
{
	x=nx; y=ny; z=nz;
};


void Camera::SetView(int __pp,int __yy,int __rr)
{	
	pitch =float(__pp) ;yaw=float(__yy); roll=float(__rr);
};


void Camera::UseMouselook(bool __ms)
{ENABLEVIEW=__ms;}


void Camera::UpdateView(int width, int height)
{
 double mouse_x;double mouse_y;
 double deltamouse_x;double deltamouse_y;
 glfwGetCursorPos(window,& mouse_x, & mouse_y);
 if(Camera::ENABLEVIEW)
 {
	 Camera::yaw-=float(width/2-mouse_x)/18;
	 Camera::roll-=float(height/2-mouse_y)/18;
	 glfwSetCursorPos(window,width/2,height/2);
 };

 if(Camera::yaw>= 360) Camera::yaw-=360;
	if(Camera::yaw<=-360) Camera::yaw+=360;

	if (Camera::roll>=89) Camera::roll=89;
    if (Camera::roll<=-89) Camera::roll=-89;

 deltamouse_x=mouse_x;deltamouse_y=mouse_y;
};


void Camera::ViewCamera()
{
glRotatef(0,1,0,0);
glRotatef(Camera::pitch,0,0,1); ////////////CAMERA ANGLE   >|  ^  |<
glRotatef(Camera::roll,1,0,0);  ////////////Horizontal Look
glRotatef(Camera::yaw,0,1,0);   ////////////Vertical Look
glTranslatef(Camera::x,Camera::y*-1,Camera::z);

};



#endif 