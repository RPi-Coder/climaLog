// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! Main Program from ClimaLog 2000
// ! Filename:    ! Cl2000.c
// ! Dependent:   ! wiringPi and all CL2000 Modules
// +--------------+-------------------------------------------------------------
// ! Description: ! Main Program for ClimaLog 2000
// !              ! Copyright (C) 1995-2016 by RPi-Coder.
// !              !
// +--------------+-------------------------------------------------------------
// ! Disclaimer:  ! This file is part of Clima Log 2000 - climaLog2000:
// !              ! https://github.com/RPi-Coder/climaLog2000
// !              ! 
// !              ! To clone: $ git clone https://github.com/RPi-Coder/climaLog2000.git 
// !              ! or:       $ git pull https://github.com/RPi-Coder/climaLog2000.git
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
// ! 2016-04-12   ! RPi-Coder !  1.1.1   ! Closed  ! Created
// ! 2016-04-11   ! RPi-Coder !  1.1.2   ! Closed  ! Created
// ! 2016-04-14   ! RPi-Coder !  1.1.3   ! Closed  ! Time Handler added
// ! 2016-04-16   ! RPi-Coder !  1.1.4   ! Closed  ! Geiger Counter added
// ! 2016-04-17   ! RPi-Coder !  1.1.5   ! Closed  ! ClFileH Added
// ! 2016-04-18   ! RPi-Coder !  1.1.6   ! Closed  ! 
// +--------------+-----------+----------+---------+---------------------------------
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <math.h>
#include <time.h>
    
#include "ClMeters.h"
#include "ClTimeH.h"

// #include "ClFileH.h"


int Init_Cl2000 (void);
int Run_Cl2000  (void);
int Exit_Cl2000 (void);


int main (int argc, char *argv[])
{

  
  char LogIntervalMins[12] = "10"; // Default 10 min log intervals
  
  int i;
  int hit;
  
  // printf ("argc: [%d]  \n", argc );
  
  for ( i = 0; i < argc; i++ )
    {
      hit = strcmp (argv [i],"-li");
      
      if (hit == 0)
	{
	  strcpy (LogIntervalMins, argv [i+1] );
	}
      
      // printf ("i: %d - argv[]: %s - Hit: [%d] \n", i, argv[i], hit);
    }
  
  
  int LogMins = atoi (LogIntervalMins);
  
  

  // printf ("Loginterval: [%s] - %d.\n", LogIntervalMins, LogMins);
  
  
  
  
  // getchar();
  
  
//  Init_Cl2000 ();
//  Run_Cl2000 ();
//  Exit_Cl2000 ();
  
  ClMeters_InitModule (LogMins);
  
  printf ("\nRunning ClimaLog 2000 v1.1.5.\n");
  
  float 	Volt 		= 0.0;
  float 	Temp 		= 0.0;
  float 	Baro 		= 0.0;
  int  		Geiger	 	= 0;
  int 		GeigerDetect  	= 0; // 0: NO new geiger counts; 1: Yes there is new geiger counts
  
  int LogIntervalSecs = LogMins * 60;
  
  /*
  char DateStr [ClTimeH_DATE_TIME_STR_LEN];
  char TimeStr [ClTimeH_DATE_TIME_STR_LEN];

  ClTimeH_GetTimeStr (TimeStr);
  ClTimeH_GetDateStr (DateStr);

  printf ("\nDateStr: [%s] and TimeStr: [%s]\n", DateStr,TimeStr);
  */
  
  
  
  // printf ("Press [ENTER] to continue ...\n");    getchar();

  ClTimeH_TimerStart (0 ,  LogIntervalSecs); // Log    10 sec
  ClTimeH_TimerStart (1 ,  10); // Clock   1 sec
  ClTimeH_TimerStart (2 ,   1); // Led     2 sec
  ClTimeH_TimerStart (3 ,  10); // Beeper  3 sec

  
  ClMeters_WriteIoPort (0,0); // LED Off
  
  while (1)
    {
      
      GeigerDetect = ClMeters_ServiceGeigerMeter ();
      
	if (GeigerDetect == 1)
	  {
	    Geiger =  ClMeters_ReadGeigerMeter ();

	    printf ("Geiger Counter: %d [Counts].  \n",Geiger);
	    
	    
	  }

      
	if  ( ClTimeH_TimerReady  (0) ) // Logger
      		{
      	//	ClTimeH_GetDateStr (DateStr);
       	//	ClTimeH_GetTimeStr (TimeStr);
	
       	//	printf ("Logging:      [%s] - [%s]  \n",DateStr,TimeStr);
	
		ClMeters_LogMeters ();

    		}

    		
 	if  ( ClTimeH_TimerReady  (2) ) // LED
      		{
		  
		  ClMeters_LedToggle (0);

    		}

 	
  		
      
    }
  
  
  return 0;
  
  
}
    
int Init_Cl2000 (void)
{
  ClMeters_InitModule (10);
  
  printf ("Initializing Cl2000 ... ");
  
  delay(3000);
  
  printf ("[OK]\n");
  
  return 0;
  
}

int Run_Cl2000  (void)
{
  printf ("Running Cl2000 ...\n");
  delay(1000);
  
  return 0;
}

int Exit_Cl2000 (void)
{
  printf ("Exiting Cl2000 ...\n");
  delay(1000);
  
  return 0;
}

    
    
