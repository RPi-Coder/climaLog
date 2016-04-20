// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! String Handler Module Header
// ! Filename:    ! ClFileH_Test.c
// ! Dependent:   ! ClFileH Module
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level File handling functions.
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
// ! 2014-08-30   ! RPi-Coder ! 1.1.1    !         !                                 
// ! 2014-08-30   ! RPi-Coder ! 1.1.2    !         !                                 
// ! 2014-08-31   ! RPi-Coder ! 1.1.3    !         !                                 
// ! 2016-04-11   ! RPi-Coder ! 1.1.4    !         !                                 
// ! 2016-04-17   ! RPi-Coder ! 1.1.5    !         ! File Delete added
// ! 2016-04-18   ! RPi-Coder ! 1.1.5    !         ! Make Data File added
// +--------------+-----------+----------+---------+---------------------------------
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#include "ClFileH.h"


// ------------------------------------------------------------------------
void Test_MakeDataFile (void);


// ------------------------------------------------------------------------
int main (void)

{
//   Test_MakeDataFile ();
  
  
  
  ClFileH_MakeDataFile ( 0, "2000-11-22", 0); // Date
  
  
   ClFileH_MakeDataFile ( 1, "11:22:33", 0); // Time
  
   ClFileH_MakeDataFile ( 2, "-12.4", 0); // Temperature
  
   ClFileH_MakeDataFile ( 3, "30.3", 0); // Hygro
  ClFileH_MakeDataFile ( 4, "1012.3", 0); // Baro
  ClFileH_MakeDataFile ( 5, "2.4", 0); // Geiger
  
  ClFileH_MakeDataFile (6, "284.4", 0); // Wind Dir
  ClFileH_MakeDataFile (7, "10.3", 0); // Wind Spd
  ClFileH_MakeDataFile (8, "14.5", 0); // Wind Gust
  
  ClFileH_MakeDataFile ( 9, "56-09-58.31-N", 0);// GPS Lat
  ClFileH_MakeDataFile (10, "10-11-28.29-E", 0);// GPS Long
  ClFileH_MakeDataFile (11, "49", 0); 		// GPS Height
  ClFileH_MakeDataFile (12, "0.2", 0); 		// GPS Speed
  ClFileH_MakeDataFile (13, "0.9", 0); 		// GPS Course
  
  ClFileH_MakeDataFile (14, "5.3", 0); // North Pole

  ClFileH_MakeDataFile (15, "2016-01-31", 0); // Log Start Date
  ClFileH_MakeDataFile (16, "00:00:00", 0);// Log Start time

  
  ClFileH_MakeDataFile (17, "Null Data", 0); // Dummy test 1
  ClFileH_MakeDataFile (99, "Null Data", 0); // Dummy test 2
   
   
  getchar();
  /*
  ClFileH_MakeDataFile ( 1, "11:22:33", 0);
  
  ClFileH_MakeDataFile ( 2, "-12.4", 0);
  ClFileH_MakeDataFile ( 3, "30.3", 0);
  ClFileH_MakeDataFile ( 4, "1012.3", 0);
  ClFileH_MakeDataFile ( 5, "2.4", 0);
  
  ClFileH_MakeDataFile ( 6, "56-09-58.31-N", 0);
  ClFileH_MakeDataFile ( 7, "10-11-28.29-E", 0);
  ClFileH_MakeDataFile ( 8, "49", 0);
  ClFileH_MakeDataFile ( 9, "0.2", 0);
  ClFileH_MakeDataFile (10, "270.9", 0);
  
  ClFileH_MakeDataFile (11, "270.0", 0);
  ClFileH_MakeDataFile (12, "12.3", 0);
  
  ClFileH_MakeDataFile (13, "5.3", 0);

  ClFileH_MakeDataFile (14, "2016-01-31", 0);
  ClFileH_MakeDataFile (15, "00:00:00", 0);

  
  ClFileH_MakeDataFile (16, "Null Data", 0);
  ClFileH_MakeDataFile (99, "Null Data", 0);
  
  */
  
  
   return 0; // End Main Test Program !!!
}

