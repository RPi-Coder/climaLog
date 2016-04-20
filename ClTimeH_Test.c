
// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! Time Handler Module
// ! Filename:    ! ClTimeH_Test.c
// ! Dependent:   ! ClTimeH.h, ClTimeH.c
// +--------------+-------------------------------------------------------------
// ! Description: ! Tes Program for the time handling functions.
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
// +--------------+-----------+----------+---------+---------------------------------
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#include "ClTimeH.h" // Time Handler Module


int main (void)

{
  char DateStr [ClTimeH_DATE_TIME_STR_LEN];
  char TimeStr [ClTimeH_DATE_TIME_STR_LEN];

  ClTimeH_GetTimeStr (TimeStr);
  ClTimeH_GetDateStr (DateStr);

  printf ("\nDateStr: [%s] and TimeStr: [%s]\n", DateStr,TimeStr);
  printf ("Press [ENTER] to continue ...\n");    getchar();

  ClTimeH_TimerStart (0 , 10); // Log    10 sec
  ClTimeH_TimerStart (1 ,  1); // Clock   1 sec
  ClTimeH_TimerStart (2 ,  2); // Led     2 sec
  ClTimeH_TimerStart (3 ,  3); // Beeper  3 sec

  unsigned char     Quit        =  0;
  //unsigned long int LoopCounter =  0;

  while (!Quit)
  	{
       	if  ( ClTimeH_TimerReady  (0) )
      		{
      		ClTimeH_GetDateStr (DateStr);
       		ClTimeH_GetTimeStr (TimeStr);
       		printf ("Log:      [%s] - [%s]  \n",DateStr,TimeStr);
    		}

 	if  ( ClTimeH_TimerReady  (1) )
            	{
               	ClTimeH_GetDateStr (DateStr);
               	ClTimeH_GetTimeStr (TimeStr);
               	printf ("Clock:    [%s] - [%s]  \n",DateStr,TimeStr);
            	}

 	if  ( ClTimeH_TimerReady  (2) )
            	{
               	ClTimeH_GetDateStr (DateStr);
               	ClTimeH_GetTimeStr (TimeStr);
               	printf ("Led:      [%s] - [%s]  \n",DateStr,TimeStr);
            	}

 	if  ( ClTimeH_TimerReady  (3) )
            	{
               	ClTimeH_GetDateStr (DateStr);
               	ClTimeH_GetTimeStr (TimeStr);
               	printf ("Beep:     [%s] - [%s]  \n",DateStr,TimeStr);
            	}
     }
  return 0; // End Main Test Program !!!
}
