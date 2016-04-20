#ifndef	_CL_GPS_H
#define	_CL_GPS_H	1

// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! Geo Handler Module Header
// ! Filename:    ! ClGps.h
// ! Dependent:   ! ClGps
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level Geo functions.
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
// ! 2016-04-06   ! RPi-Coder !  1.1.3   ! Closed  ! WGS84
// ! 2016-04-17   ! RPi-Coder !  1.1.4   ! Closed  !
// !              !           !          !         !                                 
// +--------------+-----------+----------+---------+---------------------------------
//




#define ClGps_NUM_STR_MAX_LEN          12


// World Geodetic System


void ClGps_InitModule (void);

void ClGps_DumpValues (char *_PosStr);

// --------------------------------------------------------------------------------------------
// Input:
// 		[0-11-22.22-n]
// 		[1-22-33.33-n]
// 		[90-00-00.00-n] 
//
// Output:	Degs: [0 .. 90] ['N','S','E','W'] - No leading zeros
// 		Mins: [00 .. 59] - Always two digits
//              Secs: [00.00 .. 59.99] - Always four digits and a decimalpoint
//
// --------------------------------------------------------------------------------------------

void ClGps_GetGeoValues (char *_PosStr, int *_Degs, int *_Mins, float *_Secs, char *_Designator );


// Converts from Geodetic value to Mathematical values: [-180.0000 .. 180.0000 ] 
// 
//

float  ClGps_GetMathValues (int _Degs, int _Mins, float _Secs, char _Designator );

// Phi: 3.141592654 - from HP15C Calculator
//
float  ClGps_MathDeg2Rad (float _MathDegs );

float  ClGps_MathRad2Deg (float _MathRads );


float ClGps_GeoLat2MathLat (float _GeoLat );


#endif // ClGps.h GPS Handling Module



