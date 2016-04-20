
// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! File Handler Module Header
// ! Filename:    ! ClFileH.c
// ! Dependent:   ! ClFileH.h
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level File Handling functions.
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
// ! 2016-04-17   ! RPi-Coder ! 1.1.5    !         !  .log changed to .csv
// ! 2016-04-18   ! RPi-Coder ! 1.1.6    !         !  MakeDataFile added
// ! 2016-04-19   ! RPi-Coder ! 1.2.1    !         ! GPS Added
// !              !           !          !         !                                 
// +--------------+-----------+----------+---------+---------------------------------
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#include "ClFileH.h"  


static char ClFileH_LogFileName[ClFileH_MAX_FILENAME_LEN]; // 16

#define ClFileH_debug              1
#define ClFileH_BUFFER_SIZE     1000



//	0: Date
//	1: Time
//	2: Temp
//	3: Hygro
//	4: Baro
//      5: Geiger
//      6: GPS Latitude
//      7: GPS Longitude
//      8: GPS Height
//      9: GPS Speed
//     10: GPS Course
//     11: Wind Direction
//     12: Wind Speed
//     13: North Pole
//     14: Not defined

int ClFileH_MakeDataFile (int _DataType, char *_Data, int _NullData)

{
  int RetVal = 0; // Default OK
  
  char DataFilename [64]= "\0";
  
  char NullData [24] = "(no data)\0";
  
  switch (_DataType)
    {
      
      case 0: 
	strcpy (DataFilename, "/var/www/html/ClDataDate.dat\0");
	break;

      case 1: 
	strcpy (DataFilename, "/var/www/html/ClDataTime.dat");
	break;
	
      case 2: 
	strcpy (DataFilename, "/var/www/html/ClDataTemp.dat");
	break;

      case 3: 
	strcpy (DataFilename, "/var/www/html/ClDataHygro.dat");
	break;
	
      case 4: 
	strcpy (DataFilename, "/var/www/html/ClDataBaro.dat");
	break;
	
      case 5: 
	strcpy (DataFilename, "/var/www/html/ClDataGeig.dat");
	break;

      case 6: 
	strcpy (DataFilename, "/var/www/html/ClDataWindDir.dat");
	break;
	
      case 7: 
	strcpy (DataFilename, "/var/www/html/ClDataWindSpd.dat");
	break;
	
      case 8: 
	strcpy (DataFilename, "/var/www/html/ClDataWindGust.dat");
	break;
	
      case 9: 
	strcpy (DataFilename, "/var/www/html/ClDataGpsLat.dat");
	break;
	
      case 10: 
	strcpy (DataFilename, "/var/www/html/ClDataGpsLon.dat");
	break;
	
      case 11: 
	strcpy (DataFilename, "/var/www/html/ClDataGpsHeight.dat");
	break;
	
      case 12: 
	strcpy (DataFilename, "/var/www/html/ClDataGpsSpeed.dat");
	break;
		
      case 13: 
	strcpy (DataFilename, "/var/www/html/ClDataGpsCourse.dat");
	break;
	
      case 14: 
	strcpy (DataFilename, "/var/www/html/ClDataNorthPole.dat");
	break;
	
      case 15: 
	strcpy (DataFilename, "/var/www/html/ClDataLogStartDate.dat");
	break;
	
      case 16: 
	strcpy (DataFilename, "/var/www/html/ClDataLogStartTime.dat");
	break;

      case 17: 
	strcpy (DataFilename, "/var/www/html/ClDataComment.dat");
	break;
	
      case 18: 
	strcpy (DataFilename, "/var/www/html/ClDataLogInterval.dat");
	break;
	
	
      default:
	strcpy (DataFilename, "/var/www/html/ClDataNull.dat");
	break;
    }
    
//    printf ("Type: [%d] => Filename: [%s] - Filedata: [%s]. \n ", _DataType, DataFilename, _Data);

    FILE *fp;
    
    
    
    
    fp = fopen(DataFilename,"w");
    
    
    if (_NullData == 1)
      {
	fprintf (fp, NullData);
	
	//printf ("Type: [%d] => Filename: [%s] - Filedata: [%s]. \n ", _DataType, DataFilename, NullData);
	
      }
    else
      {
      fprintf (fp, _Data);
      //printf ("Type: [%d] => Filename: [%s] - Filedata: [%s]. \n ", _DataType, DataFilename, _Data);
      }
      
    
    
    fprintf (fp, "\n");
    fclose(fp);
    
   
    
    return RetVal;
  
}



int ClFileH_Init (char *_FileName)

{
   int RetErr = 0; // InitOK
   
   strcpy (ClFileH_LogFileName,_FileName);

   strcat (ClFileH_LogFileName,".csv");

//  printf ("\nLogFileName: [%s]. Press any key ...  \n", FileH_LogFileName );
  return  RetErr;
}


int ClFileH_FileExist (char *_FileName)
{
  int RetValue = 0; // Default: File Don't Exist
  char FileName[ClFileH_MAX_FILENAME_LEN];
  strcpy (FileName, _FileName);
  FILE *ptr_file;
  char buf [ClFileH_BUFFER_SIZE];
  ptr_file = fopen(FileName,"r");
 if (ptr_file) // File don't exist
    {
    RetValue = 1;
    fclose(ptr_file);
    }
  else
    {
    RetValue = 0;
 //  fclose(ptr_file); // ?????????????????
    }
  return RetValue;
}


//  TDB  Here ???
int ClFileH_FileSize (char *_FileName, int *_FileSize)
{
  char FileName [ ClFileH_MAX_FILENAME_LEN];
  int  FileSize = 0;
  char FileLine [ ClFileH_FILE_LINE_MAX_LEN];
  int  slen = 0;
  strcpy (FileName, _FileName); // Transfer from Interface
  FILE *ptr_file;
  char buf[ClFileH_BUFFER_SIZE];
  ptr_file =fopen(FileName,"r");
  char ch = 0;
  if (!ptr_file) // File don't exist
    {
//    printf ("NON EXISTING FILE *************\n");
  //  getchar();

     return 1; // Global_ERROR_1_FILE_DONT_EXIST;
    }
  while (fgets(buf,ClFileH_BUFFER_SIZE, ptr_file)!=NULL)
     {
     strcpy (FileLine,buf);
     slen = strlen (FileLine);
      FileSize += slen;
     } // End while ()
  fclose(ptr_file);
  *_FileSize = FileSize;
  return 0; //Global_ERROR_0_NO_ERRORS_DETECTED;
}

int ClFileH_FileDelete (char *_FileName)
{
  
  return 0;
  
}


int ClFileH_LogLine2LogFile (char *_LogLine)
{
  int  RetError = 0; //Global_ERROR_0_NO_ERRORS_DETECTED;

  FILE *fp;

  fp = fopen(ClFileH_LogFileName,"a");


  if (!fp) // File don't exist
     {
//     printf ("NON EXISTING FILE *************\n");
  //   getchar();

     return 1; // Global_ERROR_1_FILE_DONT_EXIST;
     }


  fprintf (fp, _LogLine);
  fprintf (fp, "\n");

//  fprintf(fp,ctime(&mytime));

  fclose(fp);

  return RetError;

}

