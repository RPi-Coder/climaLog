
// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! Time Handler Module
// ! Filename:    ! ClTimeH.c
// ! Dependent:   ! ClTimeH.h, ClTimeH.c
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level time handling functions.
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
// ! 1995-03-18   ! RPi-Coder !  1.1.1   ! Open    ! Created. (8031 Platform)
// ! 2014-08-30   ! RPi-Coder !  1.2.1   ! Open    ! Implemented
// ! 2014-08-30   ! RPi-Coder !  1.3.1   ! Open    !
// ! 2014-09-02   ! RPi-Coder !  1.4.1   ! Open    !
// ! 2014-09-03   ! RPi-Coder !  1.5.1   ! Open    !
// ! 2014-09-04   ! RPi-Coder !  1.6.1   ! Open    !
// ! 2016-04-02   ! RPi-Coder !  1.7.1   ! Open    !
// ! 2016-04-12   ! RPi-Coder !  1.8.1   ! Open    !
// +--------------+-----------+----------+---------+---------------------------------
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "ClTimeH.h"

static int               ClTimeH_DEBUG	= 0;

static unsigned long int LogInterval   	= 0;
static unsigned long int ClockInterval 	= 0;
static unsigned long int LedInterval   	= 0;
static unsigned long int BeepInterval  	= 0;

static unsigned long int LastLogTime    = 0;
static unsigned long int LastClockTime  = 0;
static unsigned long int LastLedTime    = 0;
static unsigned long int LastBeepTime 	= 0;



unsigned long int ClTimeH_TimeNow (void)
{
  time_t TimeNow;
  TimeNow = time(NULL);
  return TimeNow;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

void ClTimeH_Int2Str (int _TheInt, int _NoOfDigs, char *_IntStr)
{
  char thebuf   [BUFSIZ];
  int  thei   = _TheInt;
  int sPtr = 0, sLen = 0; char sChr = 0;
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
	
      case 8:  sprintf (thebuf,"%8d",thei); // 81 ??
        break;
	
      default:  sprintf (thebuf,"%d",thei);
    }
  sLen = strlen (thebuf);
  for (sPtr=0; sPtr<sLen; sPtr++)
    {
      sChr = thebuf[sPtr];
      if (sChr == ' ') { thebuf[sPtr] = '0'; }
    }
  strcpy (_IntStr,thebuf);
}



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

void ClTimeH_GetTimeStr (char *_TimeStr)
{
  char TimeStr [ClTimeH_DATE_TIME_STR_LEN];

  strcpy (TimeStr,""); // Initialize Local Variables
   time_t t = time(NULL);
   struct tm tm = *localtime(&t);

   int  mHour   = 0,
        mMinute	= 0,
        mSecond = 0;
   char mHstr    [4];
   char mMstr    [4];
   char mSstr    [4];

  mHour    =  tm.tm_hour;
  mMinute  =  tm.tm_min;
  mSecond  =  tm.tm_sec;

  ClTimeH_Int2Str (mHour, 2, mHstr);
  ClTimeH_Int2Str (mMinute, 2, mMstr);
  ClTimeH_Int2Str (mSecond, 2, mSstr);
//                 01234567890

//                 01234567890
//                 hh mm ss
  strcpy (TimeStr,"  :  :  ");

  TimeStr [ 0] = mHstr [0];
  TimeStr [ 1] = mHstr [1];

  TimeStr [ 3] = mMstr [0];
  TimeStr [ 4] = mMstr [1];

  TimeStr [ 6] = mSstr [0];
  TimeStr [ 7] = mSstr [1];

  if (ClTimeH_DEBUG)
    {
      printf ("\nTimeStr: [%s]. Press any key ...\n",TimeStr);
      getchar();
    }
// ----------------------
  strcpy (_TimeStr,TimeStr); // Transfer 
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ClTimeH_GetDateStr (char *_DateStr)
{
  char DateStr[ClTimeH_DATE_TIME_STR_LEN];
  strcpy (DateStr,""); // Initialize Local Variables
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  int  mYear     = 0,
       mMonth    = 0,
       mDate     = 0;
       
  char mYstr      [6];
  char mMstr      [4];
  char mDstr      [4];
  
  mYear =   tm.tm_year + 1900;
  mMonth =  tm.tm_mon + 1;
  mDate =   tm.tm_mday;
  ClTimeH_Int2Str (mYear, 4, mYstr);
  ClTimeH_Int2Str (mMonth, 2, mMstr);
  ClTimeH_Int2Str (mDate, 2, mDstr);
//                 01234567890
  strcpy (DateStr,"    -  -  ");
  DateStr [ 0] = mYstr [0];
  DateStr [ 1] = mYstr [1];
  DateStr [ 2] = mYstr [2];
  DateStr [ 3] = mYstr [3];
  DateStr [ 5] = mMstr [0];
  DateStr [ 6] = mMstr [1];
  DateStr [ 8] = mDstr [0];
  DateStr [ 9] = mDstr [1];


  if (ClTimeH_DEBUG)
    {
      printf ("\nDateStr: [%s]. Press any key ...\n",DateStr);
      getchar();
    }
// ----------------------
  strcpy (_DateStr,DateStr); // Transfer 
}

// ----------------------------------------------------------
// Hole secs only
// 0: Logger
// 1: Clock
// 3: Led
// 4: Beeper
// ----------------------------------------------------------

void ClTimeH_TimerStart (int _TimerNo, unsigned long int _TimeInterval)
{
   unsigned long int TimeNow;
   TimeNow = ClTimeH_TimeNow ();
   switch (_TimerNo)
     {
       	case 0: // Logger
          	LogInterval  = _TimeInterval;
	  	LastLogTime  = TimeNow;
       	break;

	case 1: // Clock
		ClockInterval = _TimeInterval;
                LastClockTime  = TimeNow;
	break;

        case 2: // LED
                LedInterval = _TimeInterval;
                LastLedTime  = TimeNow;
        break;

        case 3: // Beep
                BeepInterval = _TimeInterval;
                LastBeepTime  = TimeNow;
        break;
     }
}

int ClTimeH_TimerReady (int _TimerNo)
{
  unsigned long int TimeNow, TimeDiff;

  TimeNow = ClTimeH_TimeNow ();

  int RetValue = 0; // Default NO Trigger

  switch (_TimerNo)
  {
    case 0: // Logger
      TimeDiff = TimeNow - LastLogTime;
      if ( TimeDiff >= LogInterval)
	{ // Trigger
	  RetValue = 1;
          LastLogTime = TimeNow;
         }
      break;

    case 1: // Clock
      TimeDiff = TimeNow - LastClockTime;
      if ( TimeDiff >= ClockInterval)
	{ // Trigger
	  RetValue = 1;
          LastClockTime = TimeNow;
        }
      break;

    case 2: // LED
      TimeDiff = TimeNow - LastLedTime;
      if ( TimeDiff >= LedInterval)
	{ // Trigger
	  RetValue = 1;
          LastLedTime = TimeNow;
                                }
      break;
      
    case 3: // Beeper
      TimeDiff = TimeNow - LastBeepTime;
      if ( TimeDiff >= BeepInterval)
	{ // Trigger
	  RetValue = 1;
          LastBeepTime = TimeNow;
	}
      break;
		}
    return RetValue;
}
