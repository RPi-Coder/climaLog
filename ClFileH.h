#ifndef _CL_FILEH_H
#define _CL_FILEH_H      1


// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! String Handler Module Header
// ! Filename:    ! ClFileH.h
// ! Dependent:   ! ClFileH
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level file handling functions.
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
// ! 2016-04-17   ! RPi-Coder ! 1.1.5    !         ! Delete File added
// ! 2016-04-18   ! RPi-Coder ! 1.1.6    !         ! MakeDataFile added
// ! 2016-04-19   ! RPi-Coder ! 1.2.1    !         ! 
// +--------------+-----------+----------+---------+---------------------------------
//




#define ClFileH_MAX_FILENAME_LEN             16
#define ClFileH_FILE_LINE_MAX_LEN           250


//	0: Date
//	1: Time
//	2: Temp
//	3: Hygro
//	4: Baro
//      5: Geiger
//      6: GPS Latitude
//      7: GPS Longitude
//      8: GPS Height
//      9: Wind Direction
//     10: Wind Speed
//     11: North Pole
//     12: [Not defined]

int ClFileH_MakeDataFile (int _DataType, char *_Data, int _NullData);

// -----------------------------------------------------------------
int ClFileH_Init (char *_FileName);

// -----------------------------------------------------------------
// return: 1: File Exist; 0: File Don't Exist
int ClFileH_FileExist (char *_FileName);


// -----------------------------------------------------------------
int ClFileH_FileSize (char *_FileName, int *_FileSize);


int ClFileH_FileDelete (char *_FileName);


// -----------------------------------------------------------------
// return Error Code: 0 => _DiskFree in bytes on disk
int ClFileH_DiskFree (int *_DiskFree);


int ClFileH_LogLine2LogFile (char *_LogLine);


#endif // Module KveFileH.h Module Header
