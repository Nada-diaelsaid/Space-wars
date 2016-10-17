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
#include <GLFW\glfw3.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "Text_functions.h"


/*

using namespace std;

 struct Vector2f
{float x; float y;};

struct Vector3f
{float x; float y; float z;};
struct OBJFACE
{vector<int> f; vector<int> t; vector<int> n;};


 struct wavefrontobject
 {  vector<string> oname;
    vector<string> mtlname;
	vector<bool> UseTexture;
    vector<bool> UseNormals;
	vector<Vector3f> Vertex;
	vector<Vector3f> Normals;
	vector<Vector2f> Texture;
	vector<OBJFACE>  Face;


	
 };

struct ResTexture 
{
	string name;
	GLuint container;
	
};
struct ResModel 
{
	string name;
	vector<GLuint> container;
	wavefrontobject mod;
	
};

struct Resources
{
public:
	vector<ResTexture> Textures;
    vector<ResModel>   Models;
	bool Resources::CheckTexture(string name);
	void Resources::AddTexture(string name, string filename);
	void Resources::AddModel(string name, string filename);
	GLuint Resources::GetTexture(string name);
	bool Resources::CheckModel(string name);
	void Resources::DrawModel(string name, float x, float y, float z);
//private:


};

int Count(string str,char tofind)
{ int cnt=0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i]==tofind) cnt++;
	}
	return cnt;
}


void Resources::AddTexture(string name, string filename)
{
	ResTexture temp;
	temp.name=name;
	temp.container= SOIL_load_OGL_texture
(
	filename.c_str(),
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
	SOIL_FLAG_MIPMAPS  |SOIL_FLAG_INVERT_Y |SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
);
// check for an error during the load process 
if( 0 == temp.container )
{
    printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
}else
{
    glBindTexture(GL_TEXTURE_2D, temp.container);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

    if( 0 == temp.container )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result());
    }

	
	Resources::Textures.push_back(temp);
	
	
};

GLuint Resources::GetTexture(string name)
{
	for (int i = 0; i < Textures.size() ; i++)
	{
		if (Textures[i].name==name) {return Textures[i].container;break;}


	}



}

bool Resources::CheckTexture(string name)
{
	bool exists=false;
	for (int i = 0; i < Textures.size() ; i++)
	{
		if (Textures[i].name==name) {exists=true;}
	}
	return exists;
}

bool Resources::CheckModel(string name)
{
	if(Resources::Models.size()!=0)
	if(Resources::Models[Resources::Models.size()-1].name==name) 
	{//cout << "exists" << endl;
	return true;} else 
	{//cout << "don't exists" << endl;
	return false;}


	
}

void Resources::DrawModel(string name, float x, float y, float z)
{   if(Resources::Models.size()!=0)
for (int o = 0; o < Resources::Models.size() ; o++)//start o cycle
	if(Resources::Models[o].name==name)
	{
    
    //cout << "drawing " << Resources::Models[Resources::Models.size()-1].mod.oname.size() << " objects"<<endl;
	for (int ob = 0; ob < Resources::Models[Resources::Models.size()-1].mod.oname.size() ; ob++)//start o cycle
	{// cout << "drawing:" << Resources::Models[Resources::Models.size()-1].mod.oname[ob]<< endl;
		glPushMatrix();
		///glTranslatef(x,y,z);
		glCallList(Resources::Models[Resources::Models.size()-1].container[ob]);
		glPopMatrix();
	}

	}

}

void Resources::AddModel(string name, string filename)
{
	bool CORRUPTED=false;//File corruption 
	//cout << "ifstream" << endl;
	ifstream file; file.open(filename);
	if (!file)
	{Log_write("AddModel>File not found!");cout << "AddModel>File not found!"<< endl;}
	else
	{
		//Start reading temp values.
		ResModel a;
		Resources::Models.push_back(a);
		
		string Buffer;
	    float x,y,z,xn,yn,zn,xx,yy,zz,xxx,yyy,zzz;
		int ix,iy,iz,ixn,iyn,izn,ixx,iyy,izz,ixxx,iyyy,izzz;
		Vector2f Temp2;
	    Vector3f Temp3;
		vector<int> NextObject;
		
		Resources::Models[Resources::Models.size()-1].name=name;

		//cout << "reading..." << endl;
		while(!file.eof())
		{//cout << "cycling" << endl;
			getline(file,Buffer);//Read the line
			//cout << Buffer << endl;

if (Buffer[0]!='#') //if it's a comment skip the line
{
if (Buffer[0]=='o' && Buffer[1]==' ')
				{   //cout << "BUFFER:" << Buffer << endl;
					GLuint tempw;
					Resources::Models[Resources::Models.size()-1].container.push_back(tempw);
					Resources::Models[Resources::Models.size()-1].container[Resources::Models[Resources::Models.size()-1].container.size()-1]  = glGenLists(1);
					Resources::Models[Resources::Models.size()-1].mod.UseNormals.push_back(false);
					Resources::Models[Resources::Models.size()-1].mod.UseTexture.push_back(false);	
					Buffer.erase(0,2); Resources::Models[Resources::Models.size()-1].mod.oname.push_back(Buffer);
					NextObject.push_back(Resources::Models.size()-1);
				}
if (Buffer[0]=='u' && Buffer[1]=='s' && Buffer[2]=='e' && Buffer[3]=='m' && Buffer[4]=='t' && Buffer[5]=='l' && Buffer[6]==' ') //if it's a Vertex
				{   Buffer.erase(0,6);
					Resources::Models[Resources::Models.size()-1].mod.mtlname.push_back(Buffer);
			    }
if (Buffer[0]=='v' && Buffer[1]==' ') //if it's a Vertex
				{   NextObject.push_back(Resources::Models.size()-1);
					sscanf(Buffer.c_str(),"v %f %f %f",&x,&y,&z);
					Temp3.x=x;Temp3.y=y;Temp3.z=z;
					Resources::Models[Resources::Models.size()-1].mod.Vertex.push_back(Temp3);
			    }
if (Buffer[0]=='v' && Buffer[1]=='n') //if it's a Vertex Normal
				{   NextObject.push_back(Resources::Models.size()-1);
					Resources::Models[Resources::Models.size()-1].mod.UseNormals[Resources::Models[Resources::Models.size()-1].mod.UseNormals.size()-1]=true;
					sscanf(Buffer.c_str(),"vn %f %f %f",&x,&y,&z);
					Temp3.x=x;Temp3.y=y;Temp3.z=z;
					Resources::Models[Resources::Models.size()-1].mod.Normals.push_back(Temp3);
			    }
if (Buffer[0]=='v' && Buffer[1]=='t') //if it's a texture cordinate
                {   NextObject.push_back(Resources::Models.size()-1);
					Resources::Models[Resources::Models.size()-1].mod.UseTexture[Resources::Models[Resources::Models.size()-1].mod.UseTexture.size()-1]=true;
					sscanf(Buffer.c_str(),"vt %f %f",&x,&y);
					Temp2.x=x;Temp2.y=y;
			        Resources::Models[Resources::Models.size()-1].mod.Texture.push_back(Temp2);
			    }

if (Buffer[0]=='f' && Buffer[1]==' ') //if it's a Face		
	{   NextObject.push_back(Resources::Models.size()-1);
		OBJFACE facedata;
		if(Count(Buffer,' ')==3)
		{   if (sscanf(Buffer.c_str(),"f %i/%i/%i %i/%i/%i %i/%i/%i",&ix,&iy,&iz,&ixn,&iyn,&izn,&ixx,&iyy,&izz)==9)
			{//cout << "bf " << Buffer << endl;
				facedata.f.push_back(ix);facedata.f.push_back(ixn);facedata.f.push_back(ixx);
				facedata.t.push_back(iy);facedata.t.push_back(iyn);facedata.t.push_back(iyy);
				facedata.n.push_back(iz);facedata.n.push_back(izn);facedata.n.push_back(izz);
				Resources::Models[Resources::Models.size()-1].mod.Face.push_back(facedata);	
			}
			if (sscanf(Buffer.c_str(),"f %i//%i %i//%i %i//%i",&ix,&iz,&ixn,&izn,&ixx,&izz)==6)
			{//cout << "bf " << Buffer << endl;
				facedata.f.push_back(ix);facedata.f.push_back(ixn);facedata.f.push_back(ixx);
				facedata.n.push_back(iz);facedata.n.push_back(izn);facedata.n.push_back(izz);
				Resources::Models[Resources::Models.size()-1].mod.Face.push_back(facedata);	
			}
			if (sscanf(Buffer.c_str(),"f %i/%i %i/%i %i/%i",&ix,&iz,&ixn,&izn,&ixx,&izz)==6)
			{//cout << "bf " << Buffer << endl;
				facedata.f.push_back(ix);facedata.f.push_back(ixn);facedata.f.push_back(ixx);
				facedata.t.push_back(iz);facedata.t.push_back(izn);facedata.t.push_back(izz);
				Resources::Models[Resources::Models.size()-1].mod.Face.push_back(facedata);	
			}
		}else
		if(Count(Buffer,' ')==4)
		{   if (sscanf(Buffer.c_str(),"f %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i",&ix,&iy,&iz,&ixn,&iyn,&izn,&ixx,&iyy,&izz,&ixxx,&iyyy,&izzz)==12)
			{//cout << "bf " << Buffer << endl;
				facedata.f.push_back(ix);facedata.f.push_back(ixn);facedata.f.push_back(ixx);facedata.f.push_back(ixxx);
				facedata.t.push_back(iy);facedata.t.push_back(iyn);facedata.t.push_back(iyy);facedata.t.push_back(iyyy);
				facedata.n.push_back(iz);facedata.n.push_back(izn);facedata.n.push_back(izz);facedata.n.push_back(izzz);
				Resources::Models[Resources::Models.size()-1].mod.Face.push_back(facedata);	
			}
			if (sscanf(Buffer.c_str(),"f %i//%i %i//%i %i//%i %i//%i",&ix,&iz,&ixn,&izn,&ixx,&izz,&ixxx,&izzz)==6)
			{//cout << "bf " << Buffer << endl;
				facedata.f.push_back(ix);facedata.f.push_back(ixn);facedata.f.push_back(ixx);facedata.f.push_back(ixxx);
				facedata.n.push_back(iz);facedata.n.push_back(izn);facedata.n.push_back(izz);facedata.n.push_back(izzz);
				Resources::Models[Resources::Models.size()-1].mod.Face.push_back(facedata);	
			}
			if (sscanf(Buffer.c_str(),"f %i/%i %i/%i %i/%i %i/%i",&ix,&iz,&ixn,&izn,&ixx,&izz,&ixxx,&izzz)==9)
			{//cout << "bf " << Buffer << endl;
				facedata.f.push_back(ix);facedata.f.push_back(ixn);facedata.f.push_back(ixx);facedata.f.push_back(ixxx);
				facedata.t.push_back(iz);facedata.t.push_back(izn);facedata.t.push_back(izz);facedata.t.push_back(izzz);
				Resources::Models[Resources::Models.size()-1].mod.Face.push_back(facedata);	
			}
		}else
		{
			int numfaces = Count(Buffer,' ');
			Buffer.erase(0,2);
			cout << "Face numbers:"<< numfaces<< endl;


		}
		
}///face end
}///Comment end
}///while end
file.close();///Close file
Buffer.erase();
}///file end

		
		cout << "elaborating" << endl;


///////////////////////////////////////////////////////////////
//Read Material file!!!!!
	filename.erase(filename.size()-3,filename.size());
	filename.append("mtl");
	ifstream filem; filem.open(filename);
	if (!filem) 
	{
		cout << "Cannot open " <<  filename << "!" << endl;
		CORRUPTED=true;
	}
	
	if (filem) 
	{   string Buffer;
		cout << "Opened:" <<  filename << endl;
		while(!filem.eof())
		{
		getline(filem, Buffer);//Read the line
		//cout << Buffer << endl;

if (Buffer[0]!='#') //if it's a comment skip the line
{
if (Buffer[0]=='n' && Buffer[1]=='e' && Buffer[2]=='w' && Buffer[3]=='m' && Buffer[4]=='t' && Buffer[5]=='l')
{
	Buffer.erase(0,6);

	Resources::Models[Resources::Models.size()-1].mod.mtlname.push_back(Buffer);

}
if (Buffer[0]=='m' && Buffer[1]=='a' && Buffer[2]=='p' && Buffer[3]=='_' && Buffer[4]=='K' && Buffer[5]=='d')
{
	Buffer.erase(0,6);

	FILES.AddTexture(Resources::Models[Resources::Models.size()-1].mod.mtlname[Resources::Models[Resources::Models.size()-1].mod.mtlname.size()-1],Buffer);

}





}
		}



	}
	filem.close();
	///End read material file
    cout << "Compiling model..." << endl;

//for (int ob = 0; ob < Resources::Models[Resources::Models.size()-1].mod.oname.size() ; ob++)//start o cycle
	if(!CORRUPTED)
	{
	for (int model = 0; model < Resources::Models[Resources::Models.size()-1].container.size(); model++)
	{
	glNewList(Resources::Models[Resources::Models.size()-1].container[model],GL_COMPILE);
	
glColor3f(1,1,1);	

glBegin(GL_TRIANGLES);

for (int o = 0; o < Resources::Models[Resources::Models.size()-1].mod.Face.size() ; o++)
   
		for (int l = 0; l < 3; l++)
	{	
		
	if(Resources::Models[Resources::Models.size()-1].mod.Face[o].t.size()==3)
		glTexCoord2f(Resources::Models[Resources::Models.size()-1].mod.Texture[Resources::Models[Resources::Models.size()-1].mod.Face[o].t[l]-1].x,
					 Resources::Models[Resources::Models.size()-1].mod.Texture[Resources::Models[Resources::Models.size()-1].mod.Face[o].t[l]-1].y); 

    if(Resources::Models[Resources::Models.size()-1].mod.Face[o].f.size()==3)
		glVertex3f(Resources::Models[Resources::Models.size()-1].mod.Vertex[Resources::Models[Resources::Models.size()-1].mod.Face[o].f[l]-1].x,
				   Resources::Models[Resources::Models.size()-1].mod.Vertex[Resources::Models[Resources::Models.size()-1].mod.Face[o].f[l]-1].y,
				   Resources::Models[Resources::Models.size()-1].mod.Vertex[Resources::Models[Resources::Models.size()-1].mod.Face[o].f[l]-1].z);


		
    if(Resources::Models[Resources::Models.size()-1].mod.Face[o].n.size()==3)
		glNormal3f(Resources::Models[Resources::Models.size()-1].mod.Normals[Resources::Models[Resources::Models.size()-1].mod.Face[o].n[l]-1].x,
				   Resources::Models[Resources::Models.size()-1].mod.Normals[Resources::Models[Resources::Models.size()-1].mod.Face[o].n[l]-1].y,
				   Resources::Models[Resources::Models.size()-1].mod.Normals[Resources::Models[Resources::Models.size()-1].mod.Face[o].n[l]-1].z);

		
		
	}
glEnd();

glBegin(GL_QUADS);

for (int o = 0; o < Resources::Models[Resources::Models.size()-1].mod.Face.size() ; o++)
   
		for (int l = 0; l < 4; l++)
	{	
		
	if(Resources::Models[Resources::Models.size()-1].mod.Face[o].t.size()==4)
		glTexCoord2f(Resources::Models[Resources::Models.size()-1].mod.Texture[Resources::Models[Resources::Models.size()-1].mod.Face[o].t[l]-1].x,
					 Resources::Models[Resources::Models.size()-1].mod.Texture[Resources::Models[Resources::Models.size()-1].mod.Face[o].t[l]-1].y); 

    if(Resources::Models[Resources::Models.size()-1].mod.Face[o].f.size()==4)
		glVertex3f(Resources::Models[Resources::Models.size()-1].mod.Vertex[Resources::Models[Resources::Models.size()-1].mod.Face[o].f[l]-1].x,
				   Resources::Models[Resources::Models.size()-1].mod.Vertex[Resources::Models[Resources::Models.size()-1].mod.Face[o].f[l]-1].y,
				   Resources::Models[Resources::Models.size()-1].mod.Vertex[Resources::Models[Resources::Models.size()-1].mod.Face[o].f[l]-1].z);


		
    if(Resources::Models[Resources::Models.size()-1].mod.Face[o].n.size()==4)
		glNormal3f(Resources::Models[Resources::Models.size()-1].mod.Normals[Resources::Models[Resources::Models.size()-1].mod.Face[o].n[l]-1].x,
				   Resources::Models[Resources::Models.size()-1].mod.Normals[Resources::Models[Resources::Models.size()-1].mod.Face[o].n[l]-1].y,
				   Resources::Models[Resources::Models.size()-1].mod.Normals[Resources::Models[Resources::Models.size()-1].mod.Face[o].n[l]-1].z);

		
		
	}




glEnd();
		}


glEndList();

	}



	if (!CORRUPTED)//Corrupted
	cout << "List Compiled and ready to display!" << endl;
	else {cout << "AddModel> Model Corrupted!" << endl;Log_write("AddModel> Model Corrupted!");}

}
*/