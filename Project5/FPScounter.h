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
#ifndef __FPScounter
#define __FPScounter

#include <GLFW\glfw3.h>


    int Frames=0;int FINALvalue;
	double deltaTime = glfwGetTime();

int RETURN_FPS()
{ 
	 Frames++;
    // DeltaTime = glfwGetTime();
	 if((float(glfwGetTime()) - float(deltaTime)) >= 1.0f)
	 {   FINALvalue=Frames;
         Frames = 0; 
		 deltaTime = glfwGetTime();
		 return (FINALvalue);
	 } 
	 else return FINALvalue;
	 
}






















#endif __FPScounter