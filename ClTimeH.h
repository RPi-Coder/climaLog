#ifndef _CL_TIMEH_H
#define	_CL_TIMEH_H	1

// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! Time Handler Module
// ! Filename:    ! ClTimeH.h
// ! Dependent:   ! ClTimeH.h, 
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



// Constant definitions starts here

#define ClTimeH_DATE_TIME_STR_LEN 12 // Inclusive string termination



// Typedefinitions start >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>




typedef struct TimerRec_info
  {
    unsigned long int LoggingTime;
    unsigned char     LoggingReady;

    unsigned int      LedTime;
    unsigned char     LedReady;

    unsigned int      ClockTime; // 1
    unsigned char     ClockReady;

    unsigned int      BeeperTime;
    unsigned char     BeeperReady;
  } TimerRec_TYPE;



// Typedefinitions stop <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

unsigned long int ClTimeH_TimeNow (void);

// ------------------------------------------
//  Function: GetTimeStr (TimeStr)
//  Output: DateStr: Format: [HH-MM-SS]
//
//
// ------------------------------------------
//
void ClTimeH_GetTimeStr (char *_TimeStr);


// ------------------------------------------
// Function: GetDateStr (DateStr)
// Output: DateStr: Format: [YYYY-MM-DD]
//
//
// ------------------------------------------
void ClTimeH_GetDateStr   ( char  *_DateStr);


void ClTimeH_TimerStart (int _TimerNo, unsigned long int _TimeInterval);

int  ClTimeH_TimerReady (int _TimerNo);


#endif // ClTimeH.h Time and Date Handler Module Header File



