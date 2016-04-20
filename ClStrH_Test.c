// 
// +--------------+-------------------------------------------------------------
// ! Projectname: ! Clima Log 2000 - climaLog2000
// +--------------+-------------------------------------------------------------
// ! Modulename:  ! Test Program for the String Handler Module
// +--------------+-------------------------------------------------------------
// ! Filenmame:   ! ClStrH_Test.c
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level string functions.
// !              ! Copyright (C) 1995-2016 by RPi-Coder.
// !              !
// +--------------+-------------------------------------------------------------
// ! Platform:    ! Raspberry PI / Linux
// +--------------+-------------------------------------------------------------
// ! Compiler:    ! gccc
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
// ! 1995-03-18   ! RPi-Coder !  1.1     ! Open    ! Created. (8031 Platform)
// ! 2014-08-30   ! RPi-Coder !  1.2     ! Open    ! Implemented
// ! 2014-08-30   ! RPi-Coder !  1.3     ! Open    !
// ! 2014-09-02   ! RPi-Coder !  1.4     ! Open    !
// ! 2014-09-03   ! RPi-Coder !  1.5     ! Open    !
// ! 2014-09-04   ! RPi-Coder !  1.6     ! Open    !
// ! 2016-04-02   ! RPi-Coder !  1.7     ! Open    !
// ! 2016-04-03   ! RPi-Coder !  1.7.1   ! Open    ! p = StrPos (_string, _chr) added
// ! 2016-04-03   ! RPi-Coder !  1.7.2   ! Open    ! 
// ! 2016-04-04   ! RPi-Coder !  1.7.3   ! Open    ! 
// ! 2016-04-04   ! RPi-Coder !  1.7.4   ! Open    ! Further testing ...
// ! 2016-04-04   ! RPi-Coder !  1.7.5   ! Open    ! ClStrH_DeleteFromStart added.
// +--------------+-----------+----------+---------+---------------------------------
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>


#include "ClStrH.h"    // tring Handler 


// ------------------------------------------------------------------------
// Proto Type Definitions:
// ------------------------------------------------------------------------

void Test_GeoPos 		(void);

void Test_StripLeadingSpaces 	(void);

void Test_CopyFrom 		(void);

// ------------------------------------------------------------------------


int main (void)

{

  Test_Converter ();
  
  // Test_GeoPos (); // Testing ...

  // Test_CopyFrom	(); // OK
  
  
  // Test_StripLeadingSpaces (); // OK
  
  return 0;  
  
}


void Test_Converter (void)
{
  
  printf ("(0.1) Testing: Conerter. \n");
  

int Min = 3;

char MinStr[6];

  
  ClStrH_Int2Str (Min, 0, MinStr);

  printf ("MinStr:  [%s]. \n", MinStr);
  
  
  
  /*
  float Temp = 1010.1234;
  
  
  char TempStr [12] = "\0";
  
  
  ClStrH_Float2Str (Temp, TempStr, 2, 1, 0 );

  
  printf ("(0.2) Temp: [%f] - TempStr: [%s]. \n", Temp, TempStr);
  
  */
  
  printf ("Press any key to continue ...");
  getchar();
  
  
}
  


void Test_GeoPos (void)
{
  
  printf ("(0.1) Testing: Geo Posititioning. v1.7.4. \n");
  
  char TheString [BUFSIZ] = "    11-22-33.33-n44-55-66.66e and the rest.\0";

  printf ("(0.2) TheString: Before:  [%s]. \n", TheString);

  ClStrH_StripSpaceStr (TheString);  
  printf ("(0.3) TheString: After:  [%s]. \n", TheString);
  
  //               1  2     3   4  5      
  // TheString:  [0-22-33.33-n33-44-55.55E and the rest.]
  // TheString: [90-22-33.33-n33-44-55.55E and the rest.]
  // TheString: [11-22-33.33-n33-44-55.55E and the rest.]
  //                 
  
  int sPos = 0;
  char sChr = 0;
  char tChr = 0;
  
  int FromPos = 0;

   char LatDegStr 	[10] = "\0";
   char LatMinStr 	[10] = "\0";
   char LatSecStr 	[10] = "\0";
   char LatHempChr	     = '?'; 	// Northern is default and positive
   
   char LonDegStr 	[10] = "\0";
   char LonMinStr 	[10] = "\0";
   char LonSecStr 	[10] = "\0";
   char LonHempChr	     = '?';    //Eastern is default and positive
  
  // Search for first '-'
  
  // int  ClStrH_StrPos  ( char *_TheString, char _TheChar, int _FromPos);
  
  printf ("(1.0)  >>>>>>>>>>>>>>>>>>>>> Latitudes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
  
  FromPos = 0;
  tChr = '-';
  sPos = ClStrH_StrPos  ( TheString, tChr, FromPos);
  
  printf ("(1.1)  sPos: [%d]. \n", sPos);
  
  
  // Fetch Lat Deg String
  
  ClStrH_CopyFrom (TheString, LatDegStr, 0, (sPos-1) );

  printf ("(1.2) LatDegStr: [%s]. \n", LatDegStr);

  ClStrH_DeleteFromStart (TheString,  sPos);

  printf ("(1.3) TheString: After delete sPos:  [%s]. \n", TheString);

  ClStrH_CopyFrom (TheString, LatMinStr, 0, 2 );
  
  
  printf ("(1.4) LatMinStr: [%s]. \n", LatMinStr);
  
  
  ClStrH_DeleteFromStart (TheString,  3);

  printf ("(1.5) TheString: After delete sPos:  [%s]. \n", TheString);

  
  ClStrH_CopyFrom (TheString, LatSecStr, 0, 5 );
  
  
  printf ("(1.6) LatSecStr: [%s]. \n", LatSecStr);
  
  
  ClStrH_DeleteFromStart (TheString,  6);

  printf ("(1.7) TheString: After delete sPos:  [%s]. \n", TheString);

  sChr = TheString[0];
  
  printf ("(1.8) SChr: [%c]. \n", sChr); // [NnSs]
  
  if ( sChr == 'n' || sChr == 'N')
    {
      LatHempChr     = 'N'; 	// Northern is default and positive
      
    }
    
      
  if ( sChr == 's' || sChr == 'S')      
      
    {
      LatHempChr     = 'S'; 	// Northern is default and positive
    }
  
  
  printf ("(1.9       >>>>>>>>>>>><     LatHempChr: [%c]. \n", LatHempChr); // 
  
  ClStrH_DeleteFromStart (TheString,  1);

  printf ("(1.10) TheString: After delete sPos:  [%s]. \n", TheString);


// Longitudes From Here ***********************************************************
  
  printf ("(2.0)  >>>>>>>>>>>>>>>>>>>>> Longitudes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
  
  
  FromPos = 0;
  tChr = '-';
  
  sPos = ClStrH_StrPos  ( TheString, tChr, FromPos);
  
  printf ("(2.1)  >>>>>>>>>>>>>>>            sPos: [%d]. \n", sPos);
  
  
  // Fetch Lat Deg String
  
  ClStrH_CopyFrom (TheString, LonDegStr, 0, (sPos-1) );

  printf ("(2.2)  >>>>>>>>>>>>>      LonDegStr: [%s]. \n", LonDegStr);

  ClStrH_DeleteFromStart (TheString,  sPos);

  printf ("(3) TheString: After delete sPos:  [%s]. \n", TheString);

  ClStrH_CopyFrom (TheString, LonMinStr, 0, 2 );
  
  
  printf ("(4) LonMinStr: [%s]. \n", LonMinStr);
  
  
  ClStrH_DeleteFromStart (TheString,  3);

  printf ("(5) TheString: After delete sPos:  [%s]. \n", TheString);

  
  ClStrH_CopyFrom (TheString, LonSecStr, 0, 5 );
  
  
  printf ("(6) LonSecStr: [%s]. \n", LonSecStr);
  
  
  ClStrH_DeleteFromStart (TheString,  6);

  printf ("(7 )TheString: After delete sPos: ------------------- [%s]. \n", TheString);

  sChr = TheString[4];
  
  printf ("SChr: [%c]. \n", sChr); // [NnSs]
  
  if ( sChr == 'e' || sChr == 'E')
    {
      LonHempChr     = 'E'; 	// Northern is default and positive
      
    }
    
    else
    {
      LonHempChr     = 'W'; 	// Northern is default and positive
    }
  
  
  printf ("(8) LonHempChr: [%c]. \n", LonHempChr); // 
  
  ClStrH_DeleteFromStart (TheString,  1);

  printf ("(9) TheString: After delete sPos:  [%s]. \n", TheString);

  

  
  
  


  
  
  getchar ();
  return 0;
  
  
}


void Test_StripLeadingSpaces (void)
{
  printf ("Testing: Test_StripLeadingSpaces. v1.7.4. \n");
  char TheString [BUFSIZ] = "    111-22-33.33-n peter.";
  char TheChar = '-';
  int  ThePos = 0;
  int  FromPos = 8;
  printf ("Testing: Test_StripLeadingSpaces v1.7.z. \n");
  printf ("TheString: Before:  [%s]. \n", TheString);
  ClStrH_StripSpaceStr (TheString);  
  printf ("TheString: After:  [%s]. \n", TheString);
  getchar ();
  return 0;
}


void Test_CopyFrom (void)
{
  printf ("Testing: Test_CopyFrom. v1.7.4. \n");
//
  char TheString [BUFSIZ] 	= "0123456789012345678901234567890\0";
  char TheResultString [BUFSIZ] = "\0";
  
  printf ("Strings before:  TheString: [%s] - TheResultString: [%s]. \n", TheString, TheResultString);
  ClStrH_CopyFrom (TheString, TheResultString, 3, 5 );
  printf ("Strings after:  TheString: [%s] - TheResultString: [%s]. \n", TheString, TheResultString);
  getchar ();
  
  return 0;
}



  /*
  
  float TheFloat    = 22.0/7.0;
  char  TheFloatStr [12] = "\0";
  
  
  //TheFloat = (22.0/7.0);
  //char TheFloatStr[12];
  
  // KveStrH_Float2Str (TheFloat, &TheFloatStr, 1 );
// KveStrH_NUM_STR_MAX_LEN 12
  
  int 		NumOfDigs 	=   2;
  int           NumOfDecs       =   1;
  int 		TheInt         	= -14;
  char 		TheIntStr[12]   = "\0";
  
  ClStrH_Int2Str (TheInt, NumOfDigs, TheIntStr); // Works only for positive integers
  
  ClStrH_Float2Str (TheFloat, TheFloatStr, NumOfDigs, NumOfDecs );
  
  printf ("Howdy .\n");
   
  printf ("TheInt: [%d] - NumOfDigs: [%d] => ", TheInt, NumOfDigs);
  printf ("TheIntStr: [%s]\n\n", TheIntStr);
   
  printf ("TheFloat: [%f] - NumOfDigs: [%d] - NumOfDecs: [%d] => ", TheFloat, NumOfDigs, NumOfDecs);
     
  printf ("TheFloatStr: [%s]\n\n", TheFloatStr);
   
   
   
   //printf ("The Float Value: %f\n", TheFloat);
   // printf ("The Float Str Value: %s\n", TheFloatStr);
   
   */
  

  