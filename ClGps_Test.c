// 
// +--------------+-------------------------------------------------------------
// ! Projectname: ! Clima Log 2000 - climaLog2000
// +--------------+-------------------------------------------------------------
// ! Modulename:  ! Test Program for the GPS Handler Module
// +--------------+-------------------------------------------------------------
// ! Filenmame:   ! ClGps_Test.c
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level GPS functions.
// !              ! Copyright (C) 1995-2016 by RPi-Coder.
// !              !
// +--------------+-------------------------------------------------------------
// ! Platform:    ! Raspberry Pi / Linux
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
// ! 2016-04-05   ! RPi-Coder !  0.1.1   ! Closed  ! Created
// ! 2016-04-06   ! RPi-Coder !  0.1.2   !         ! 
// ! 2016-04-08   ! RPi-Coder !  0.1.3   !         ! 
// +--------------+-----------+----------+---------+---------------------------------
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>


#include "ClGps.h"    // Geo Handler 
#include "ClStrH.h"    // String Handler 


int main (void)

{
  ClGps_InitModule ();
  char PosStr[BUFSIZ] = "    11-22-33.33n     \0";

  int Degs = 0;
  int Mins = 0;
  float Secs = 33.33;
  char Designator = '?';
  
  float MathValue = 0.0;
  float MathDegRad  = 0.0;
  
  printf("Testing the Geo functions and procedures ... \n");
  
  
  
  while (1)
    {
      
      printf("Enter position (ddd-mm-ss.ss-D): ");
      
      
      gets (PosStr);

      

    //  ClGeoCalc_DumpValues (PosStr);
      
      
      // printf ("(1.) PosStr: [%s]. \n", PosStr);
      

    //  printf ("(2.) PosStr: [%s] => Degs: [%d] - Mins: [%d] - Secs: [%2.2f] - Designator: [%c]. \n", 
    //	                       PosStr, Degs, Mins, Secs, Designator);
      
      ClGps_GetGeoValues (PosStr, &Degs, &Mins, &Secs, &Designator );
      
      MathValue = ClGps_GetMathValues (Degs, Mins, Secs, Designator );
      


      printf ("(3.) PosStr: [%s] => Degs: [%d] - Mins: [%d] - Secs: [%2.2f] - Designator: [%c]. \n", 
				  PosStr, Degs, Mins, Secs, Designator);

      MathDegRad = ClGps_MathDeg2Rad (MathValue );

      
      printf ("(4.) MathValue: [%4.6f] - Rad: [%4.6f]. \n", MathValue, MathDegRad);
      
      getchar();
      
    }
  
  
  
  
  
  
  
  return 0;  
  
}
  