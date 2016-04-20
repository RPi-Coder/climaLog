// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! GPS Handler Module
// ! Filename:    ! ClGps.c
// ! Dependent:   ! ClGps.h
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level GPS functions.
// !              ! Copyright (C) 1995-2016 by RPi-Coder.
// !              !
// +--------------+-------------------------------------------------------------
// ! Disclaimer:  ! This file is part of Clima Log 2000 - climaLog2000:
// !              ! https://github.com/RPi-Coder/climaLog2000
// !              ! 
// !              ! To clone: $ git clone https://github.com/RPi-Coder/climaLog2000.git 
// !              ! or:       $ git pull https://github.com/RPi-Coder/climaLog2000.git (NOT TESTED!)
// !              !
// !              ! climaLog2000 is free software: you can redistribute it and/or modify
// !              ! it under the terms of the GNU Lesser General Public License as
// !              ! published by the Free Software Foundation, either version 2 of the
// !              ! License, or (at your option) any later version.
// !              ! 
// !              ! climaLog2000 is distributed in the hope that it will be useful,
// !              ! but WITHOUT ANY WARRANTY; without even the implied warranty of
// !              ! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// !              ! GNU Lesser General Public License for more details.
// !              ! 
// !              ! You should have received a copy of the GNU Lesser General Public
// !              ! License along with climaLog2000.
// !              ! If not, see <http://www.gnu.org/licenses/>.
// !              !
// +--------------+-----------+----------+---------+---------------------------------
// ! Date:        ! Init:     ! Version: ! Status: ! Description:
// ! (yyyy-mm-dd) !           !          !         ! 
// +--------------+-----------+----------+---------+---------------------------------
// ! 2016-04-05   ! RPi-Coder !  1.1.1   ! Closed  ! Created
// ! 2016-04-06   ! RPi-Coder !  1.1.2   ! Closed  ! 
// ! 2016-04-17   ! RPi-Coder !  1.1.3   ! Closed  ! 
// +--------------+-----------+----------+---------+---------------------------------
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>


#include "ClGps.h"
#include "ClStrH.h"



void ClGps_InitModule (void)
{
  
  
}

void ClGps_DumpValues (char *_PosStr)
{
  
  printf("PosStr: [%s]. \n", _PosStr);
  getchar();
  
  ClStrH_StripSpaceStr (_PosStr);

  printf("PosStr: [%s]. \n", _PosStr);
  getchar();
  
}

void ClGps_GetGeoValues (char *_PosStr, int *_Degs, int *_Mins, float *_Secs, char *_Designator )
{
    char TmpStr [BUFSIZ] = "\0";
    
    strcpy (TmpStr, _PosStr);
    
    
    ClStrH_StripSpaceStr (TmpStr);
    
    int sPos = ClStrH_StrPos  ( TmpStr, '-', 0);

    char DegStr [6] = "\0";
    
    sPos--;
    
    ClStrH_CopyFrom (TmpStr, DegStr, 0, sPos );

    int Degs = atoi (DegStr);
    
    sPos++;
    
    ClStrH_DeleteFromStart (TmpStr,  sPos ); // [22-33.33n        ]

    char MinStr [6] = "\0";
    ClStrH_CopyFrom (TmpStr, MinStr, 0, 2 );
    int Mins = atoi (MinStr);

    char SecStr [6] = "\0";
    ClStrH_CopyFrom (TmpStr, SecStr, 3, 5 );
    
    float Secs = atof (SecStr);

    char Designator = '?';
    
    if ( (TmpStr[8]=='n') || (TmpStr[8]=='N') )
      {
	Designator = 'N';
      }
    
    if ( (TmpStr[8]=='s') || (TmpStr[8]=='S') )
      {
	Designator = 'S';
      }
    
    if ( (TmpStr[8]=='e') || (TmpStr[8]=='E') )
      {
	Designator = 'E';
      }
    
    if ( (TmpStr[8]=='w') || (TmpStr[8]=='W') )
      {
	Designator = 'W';
      }

// int *_Degs, int *_Mins, float *_Secs, char *_Designator )      
      
      *_Degs = Degs;
      *_Mins = Mins;
      *_Secs = Secs;
      *_Designator = Designator;
      
    //printf ("(10.) TmpStr: [%s] - sPos: [%d] - DegStr: [%s] - Degs: [%d] - MinStr: [%s] - Mins: [%d] - SecStr: [%s] - Secs: [%f] Des.: [%c]. \n", TmpStr, sPos, DegStr, Degs, MinStr, Mins, SecStr, Secs, Designator);
    //getchar();

    // return 0; 
  
}

float  ClGps_GetMathValues (int _Degs, int _Mins, float _Secs, char _Designator )
{
  
  float RetVal = _Degs * 3600; // 
  RetVal += _Mins * 60;
  RetVal += _Secs;
  RetVal /= 3600;
  
  if ( (_Designator == 'W') || (_Designator == 'S') )
    {
      RetVal = -RetVal;
    }
  
  return RetVal;
}
// Phi: 3.141592654 - from HP15C Calculator
//
// rad = deg (2pi) / 360 = deg * pi / 180;

float  ClGps_MathDeg2Rad (float _MathDegs )
{
  
  float Phi = 3.141592654;
  
  float RetVal = (_MathDegs*Phi) / 180;
  
  
  
  return RetVal;
}

float  ClGps_MathRad2Deg (float _MathRads )
{
  
  
  float Phi = 3.141592654;
  
  float RetVal = (_MathRads*180) / Phi;
  
  
  
  return RetVal;
  
  
  
  
}

