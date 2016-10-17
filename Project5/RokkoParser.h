#pragma once

#include "glut.h"
#include <cstdlib>
#include <iostream>

#include <cmath>

using namespace std;

class RokkoParser
{

public:
   static void objToTxt(const string aInFilename, 
                        const string aOutFilename, 
                        bool aVerbose = false);
   static vector explode(string aStr, char aDelim);
};