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
#ifndef __Init__
#define __Init__

#include "Scene.h"





static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
if (glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS) 
glfwSetWindowShouldClose(window, GL_TRUE);

};

static void error_callback(int error, const char* description)
{
fputs(description, stderr);
};

void Init(int WW, int WH)
{
	

glfwSetErrorCallback(error_callback);
if (!glfwInit())
{Log_write("!UNABLE TO RUN GLFW!");
	exit(EXIT_FAILURE);}


 window = glfwCreateWindow(WW, WH, WINDOWTITLE.c_str() , NULL, NULL); // Window
//window = glfwCreateWindow(1920, 1080, "Simple example", glfwGetPrimaryMonitor(), NULL); // Fullscreen

glfwSetWindowPos(window,100,100);
glfwSetWindowFocusCallback(window,0);
glfwMakeContextCurrent(window);
glfwSetKeyCallback(window,key_callback);//Keyboard inputs handling



if (!window)
{
glfwTerminate();
exit(EXIT_FAILURE);
}
glfwMakeContextCurrent(window);


}


void Draw()
{
while (!glfwWindowShouldClose(window))
{

glfwPollEvents();
 

DrawScene();


glfwSwapBuffers(window);
}

glfwDestroyWindow(window);
glfwTerminate();
exit(EXIT_SUCCESS);
}
































#endif //__Init__