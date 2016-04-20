// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! String Handler Module
// ! Filename:    ! ClStrH.c
// ! Dependent:   ! ClStrH.h
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level string functions.
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
// ! 1995-03-18   ! RPi-Coder !  1.1     ! Open    ! Created. (8031 Platform)
// ! 2014-08-30   ! RPi-Coder !  1.2     ! Open    ! Implemented
// ! 2014-08-30   ! RPi-Coder !  1.3     ! Open    !
// ! 2014-09-02   ! RPi-Coder !  1.4     ! Open    !
// ! 2014-09-03   ! RPi-Coder !  1.5     ! Open    !
// ! 2014-09-04   ! RPi-Coder !  1.6     ! Open    !
// ! 2016-04-02   ! RPi-Coder !  1.7     ! Open    !
// ! 2016-04-03   ! RPi-Coder !  1.7.1   ! Open    ! p = StrPos (_string, _chr) added
// ! 2016-04-03   ! RPi-Coder !  1.7.2   ! Open    ! 
// ! 2016-04-04   ! RPi-Coder !  1.7.4   ! Open    ! ClStrH_StripSpaceStr added.
// ! 2016-04-04   ! RPi-Coder !  1.7.5   ! Open    ! ClStrH_DeleteFromStart added.
// ! 2016-04-06   ! RPi-Coder !  1.7.6   ! Open    ! minors
// ! 2016-04-17   ! RPi-Coder !  1.8.1   ! Open    ! Float2Str PosSign added

// +--------------+-----------+----------+---------+---------------------------------
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>


#include "ClStrH.h"

//  
//  [01234567890]

void ClStrH_DeleteFromStart (char *_TheString,  int _NumToDelete )
{
  char TempStr [BUFSIZ] = "\0";
  
  
  int 	sPtr = 0;
  int 	sLen = strlen (_TheString);
  char 	sChr = 0;
  
  int 	tPtr = 0;
  
  for (sPtr = _NumToDelete; sPtr < sLen; sPtr++ )
    {
      sChr = _TheString [sPtr];
      
      TempStr [tPtr] = sChr;
      tPtr++;
      TempStr [tPtr] = '\0'; 
      
    }
  
  strcpy (_TheString, TempStr);
  
  
  // return 0;
}




void ClStrH_CopyFrom (char *_TheString, char *_TheResultString, int _FromPos, int _Nums )
{
  char	TempStr [BUFSIZ]	= "\0";
  int 	sPtr 			= 0;
  //int 	sLen 			= 0;
  char 	sChr 			= 0;
  int 	tPtr 			= 0;
  int   MaxPos 			= _FromPos + _Nums;
  
  for (sPtr = _FromPos; sPtr < MaxPos; sPtr++ )
    {
	sChr = _TheString[sPtr];
	TempStr [tPtr] = sChr;
	tPtr++;
	TempStr [tPtr] = '\0';
    }
  strcpy (_TheResultString, TempStr);
  // return 0;
}




// +----------------+---------------------------------------------------------------
// ! Function Name: ! void ClStrH_StripSpaceStr (char *_TheString)
// +----------------+---------------------------------------------------------------
// !
// +---------------------------------------------------------------------------------
// ! 2016-04-04   ! RPi-Coder !  1.7.4   ! Open    ! ClStrH_StripSpaceStr
// +--------------+-----------+----------+---------+---------------------------------
//

void ClStrH_StripSpaceStr (char *_TheString)
{
  char  TempStr[BUFSIZ]	= "\0";
  int	Leading		= 1; // Default always leading
  int 	sLen 		= 0; 
  int 	sPtr 		= 0;
  char 	sChr 		= 0; // *****************
  int   tPtr           	= 0;
  sLen = strlen (_TheString);
  for (sPtr = 0; sPtr < sLen; sPtr++)
    {
      sChr = _TheString [sPtr];
      // printf ("sChr: [%c]. \n", sChr);
      if (Leading == 1)
	    {
	      if (sChr == ' ') // Still leading
		{
		  Leading = 1;
		}
		else
		{ // Stop being leading
		  Leading = 0;
		  TempStr [tPtr] = sChr;
		  tPtr++;
		}
	    }
	    else // NOT Leading
	    {
		Leading = 0;
		TempStr [tPtr] = sChr;
		tPtr++;
	    }

    } // FOR LOOP
    // Transfer parameters
  strcpy  (_TheString,TempStr); 
  // return 0;
}



// -----------------------------------------------------------------------------
// int  ClStrH_StrPos  ( char *_TheString, char _TheChar, int _FromPos)
// -----------------------------------------------------------------------------
//
//           +-- First Character at posistion '0'
//           !
//           v
// FromPos: [0 .. n] 
//
// -----------------------------------------------------------------------------

int  ClStrH_StrPos  ( char *_TheString, char _TheChar, int _FromPos)

{
  int 	RetVal	= 0;
  
  // char TmpStr [BUFSIZ] = "\0";
  
  int 	sLen 	= 0;
  int 	sPtr 	= 0;
  // int 	tPtr 	= 0;
  char	sChr 	= 0;
  
  // int Leading = 1; // Default Leading 
  // 1. Transfer Input Data and strip leading 'spaces'
  
  sLen = strlen (_TheString);
  for (sPtr = _FromPos; sPtr < sLen; sPtr++)
    {
      sChr = _TheString [sPtr];
      if (sChr == _TheChar) // Hit!
	{
	  return sPtr+1; // Bug fixed!!
	}
     // printf ("sChar: [%c]. \n ", sChar);
    }
  
  // sChar = getchar ();
  //  strcpy (TmpStr,_TheString);
  // printf ("TheString: [%s] - sLen: [%d] - TmpStr: [%s]. \n", _TheString, sLen,  TmpStr);
  // sChar = getchar ();
  return RetVal;
}



// ClStrH_NUM_STR_MAX_LEN 12

void ClStrH_Int2Str (int _TheInt, int _NoOfDigs, char *_TheIntStr)
{
  
  char thebuf   [BUFSIZ] = "\0";
  char tmpbuf   [BUFSIZ] = "-\0";
  
  // printf ("thebuf: [%s] - tmpbuf: [%s]\n",thebuf, tmpbuf);
  
  int  thei   = _TheInt;
  
  int IntNeg = 0; // 0: False 	- TheInt is Zero or Positive Number (>=0); 
		  // 1: True 	- TheInt is a negative number (< 0);
  
  if (thei >= 0)
    {
	IntNeg = 0; // Negative Number
	thei = thei;
    }
    else
    {
	IntNeg = 1;
	thei = -thei;
    }
  
  // printf ("thei: [%d]  - IntNeg:  [%d] \n",thei, IntNeg );
  
  switch (_NoOfDigs)
    {
      case 0:  sprintf (thebuf,"%d",thei);
        break;
	
      case 1:  sprintf (thebuf,"%1d",thei);
        break;
	
      case 2:  sprintf (thebuf,"%2d",thei);
        break;
	
      case 3:  sprintf (thebuf,"%3d",thei);
        break;
	
      case 4:  sprintf (thebuf,"%4d",thei);
        break;
	
      case 5:  sprintf (thebuf,"%5d",thei);
        break;
	
      case 6:  sprintf (thebuf,"%6d",thei);
        break;
	
      case 7:  sprintf (thebuf,"%7d",thei);
        break;
	
      case 8:  sprintf (thebuf,"%8d",thei);
        break;
	
      default:  sprintf (thebuf,"%d",thei);
    }
    
  int sPtr = 0, sLen = 0; char sChr = 0;
    
  sLen = strlen (thebuf);
  for (sPtr=0; sPtr<sLen; sPtr++)
    {
      sChr = thebuf[sPtr];
      if (sChr == ' ') { thebuf[sPtr] = '0'; }
    }
    
  // thebuf indeholder den positive værdi
  
  if (IntNeg == 1)
    {
	strcat (tmpbuf, thebuf);
	// printf ("tmpbuf: [%s] \n",tmpbuf);
	strcpy (_TheIntStr,tmpbuf);
    }
  else
    {
      strcpy (_TheIntStr,thebuf);
    }
    
  
}




void ClStrH_Float2Str (float _TheFloat, char *_TheFloatStr, int _NumOfDigs, int _NumOfDecs , int _PosSign)
{
  float  thef   		= _TheFloat;
  char   TmpStr[BUFSIZ] 	= "\0"; 
  char   TheBuf[BUFSIZ] 	= "\0"; 
  
  
  if (thef >= 0) // Positive
    {
      if (_PosSign == 1)
	{
	  strcpy  (TheBuf,"+\0"); 
	}
	else
	{
	  strcpy  (TheBuf,"\0"); 
	}
    }
    else
    {
      strcpy  (TheBuf,"\0"); 
     
    }
  
  
  sprintf (TmpStr,"%2.1f",thef);
  
  
  strcat (TheBuf, TmpStr);
  
  strcpy  (_TheFloatStr,TheBuf); 
}


