
// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! Meter Handling Module
// ! Filename:    ! ClMeters.c
// ! Dependent:   ! ClMeters, , , wiringPi etc.
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level Meter functions.
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
// ! 2016-04-12   ! RPi-Coder !  1.1.1   ! Closed  ! Created
// ! 2016-04-13   ! RPi-Coder !  1.1.2   !         !
// ! 2016-04-14   ! RPi-Coder !  1.1.3   !         ! Service Geiger Counter added
// ! 2016-04-16   ! RPi-Coder !  1.1.4   !         ! 
// ! 2016-04-17   ! RPi-Coder !  1.1.5   !         ! FileH Added
// ! 2016-04-18   ! RPi-Coder !  1.1.6   !         ! 
// ! 2016-04-19   ! RPi-Coder !  1.2.1   !         ! Hygro Meter added
// +--------------+-----------+----------+---------+---------------------------------
//

#include <wiringPi.h>
#include <mcp3004.h>
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>

#include <math.h>
#include <time.h>


#include "ClMeters.h"
#include "ClFileH.h"
#include "ClTimeH.h"
#include "ClStrH.h"



// SPI Port Definitions---------------------------------------------------------
#define ClMeters_BASE 		200
#define ClMeters_SPI_CHAN 	  0

// IO Port Definitions ---------------------------------------------------------
#define	ClMeters_LED		  0
#define	ClMeters_G_PULSE	  2
#define	ClMeters_G_CLR		  3


// Proto type definitions starts here ------------------------------------------

float ClMeters_convertToVolt 		(unsigned int 	_cnt);
float ClMeters_convertToDegC 		(unsigned int 	_cnt);
float ClMeters_convertVoltToBaro 	(float 		_Vbaro);

  

// Local Variables must be stored here --------------------------------------------

static int  	 	 ClMeters_GeigerCounter = 0; // Set counter to NULL

static unsigned long int ClMeters_LastLogTime   = 0;

static float 		 ClMeters_LastLogTemp 	= 0;

static float 		 ClMeters_LastLogHygro 	= 0;

static float 		 ClMeters_LastLogBaro 	= 0;

static int 		 ClMeters_LastLogGeiger = 0; 



// Last values must be stored here --------------------------------------------

static int 		ClMeters_LastIoLevel [ClMeters_NumOfIoPorts];


void	ClMeters_InitModule 		(int _LogIntervalMins )

{
  if (wiringPiSetup () == -1)
    {
      exit (1);   
    }   
    
    
 char DStr [24];
 char TStr [24];

  ClTimeH_GetTimeStr (TStr);
  ClTimeH_GetDateStr (DStr);
    
  ClFileH_MakeDataFile (15, DStr, 0);
  ClFileH_MakeDataFile (16, TStr, 0);
  
  
 char LogIntVal[6]="\0";
 
   ClStrH_Int2Str (_LogIntervalMins, 0, LogIntVal);

 
 // itoa (_LogIntervalMins,LogIntVal,10 );
 
 ClFileH_MakeDataFile (18, LogIntVal, 0);
  
 ClFileH_MakeDataFile ( 0, "", 1);
 ClFileH_MakeDataFile ( 1, "", 1);
 ClFileH_MakeDataFile ( 2, "", 1);
 ClFileH_MakeDataFile ( 3, "", 1);
 ClFileH_MakeDataFile ( 4, "", 1);
 ClFileH_MakeDataFile ( 5, "", 1);
 ClFileH_MakeDataFile ( 6, "", 1);
 ClFileH_MakeDataFile ( 7, "", 1);
 ClFileH_MakeDataFile ( 8, "", 1);
 ClFileH_MakeDataFile ( 9, "", 1);
 ClFileH_MakeDataFile (10, "", 1);
 ClFileH_MakeDataFile (11, "", 1);
 ClFileH_MakeDataFile (12, "", 1);
 ClFileH_MakeDataFile (13, "", 1);
 ClFileH_MakeDataFile (14, "", 1);
 

 printf ("ClimaLog started at %s-%s [CEST] - Interval: %s.\n ",DStr,TStr, LogIntVal);    
 
 
  // printf ("ClimaLog started: %s - %s [CEST].\n ", DateStr, TimeStr);    
    // getchar();
  
  
    
  pinMode (ClMeters_LED,     OUTPUT) ;
  pinMode (ClMeters_G_PULSE, INPUT) ;
  pinMode (ClMeters_G_CLR,   OUTPUT) ;
  
  mcp3004Setup (ClMeters_BASE, ClMeters_SPI_CHAN); // 3004 and 3008 are the same 4/8 channels
  
  digitalWrite (ClMeters_G_CLR,   LOW) ;
  delay(2);
  digitalWrite (ClMeters_G_CLR,   HIGH) ;
  
  ClMeters_GeigerCounter = 0;
  
  int i = 0;
  for (i = 0; i < ClMeters_NumOfIoPorts; i++)
    {
      ClMeters_LastIoLevel [i] = 0;
    }
    
    
  ClMeters_LastLogTime  = ClTimeH_TimeNow ();
  
  ClMeters_LastLogTemp 	= ClMeters_ReadThermoMeter ();
  ClMeters_LastLogHygro	= ClMeters_ReadHygroMeter ();
  
  
  ClMeters_LastLogBaro 	= ClMeters_ReadBaroMeter ();
  ClMeters_LastLogGeiger = 0; 
  
//  printf ("Last Time: [%d]. \n", ClMeters_LastLogTime);
  
  printf ("Temp: [%2.1f] - Hygro: [%2.1f]  Baro: [%4.1f] - Geiger: [%d]. \n",  ClMeters_LastLogTemp,ClMeters_LastLogHygro ,ClMeters_LastLogBaro, ClMeters_LastLogGeiger);

  
  int LogFileExist = ClFileH_FileExist ("Cl2000.csv");
  
  
  
  ClFileH_Init ("climaLog");
  
  char LogLine [128] = "\0";
  
  if (LogFileExist == 0)
    {
      strcpy (LogLine,"Date,Time,Temp,Hygro,Baro,Geiger");
      
      ClFileH_LogLine2LogFile (LogLine);
      
      strcpy (LogLine,",,,,,");
      
      ClFileH_LogLine2LogFile (LogLine);
    
    }
  
}

// ----------------------------------------------------------------------
// Eight Voltmeters: [0 .. 7]
// ----------------------------------------------------------------------
float 	ClMeters_ReadVoltMeter (void)
{
  unsigned int ReadX = analogRead (ClMeters_BASE + 0); // ADC channel: [0 .. 7]
  
  return ClMeters_convertToVolt (ReadX);
}



 // Two Thermometers: [0 .. 1]
float 	ClMeters_ReadThermoMeter (void)

{
  unsigned int ReadX = analogRead (ClMeters_BASE + 1); //
  return ClMeters_convertToDegC (ReadX);
}

float 		ClMeters_ReadHygroMeter (void)
{
  
  return 40.5;
  
}



float 	ClMeters_ReadBaroMeter (void)
{
   unsigned int ReadX = analogRead (ClMeters_BASE + 2); // ADC channel: [0 .. 7]
   float Vbaro = ClMeters_convertToVolt (ReadX);
   return ClMeters_convertVoltToBaro (Vbaro);
}


void 	ClMeters_WriteIoPort (int _PortNo, int _PortLevel)
{
   ClMeters_LastIoLevel [_PortNo] = _PortLevel;
  switch (_PortNo)
    {
      case 0: 
	      if (_PortLevel == 0)
		    {
		      digitalWrite (ClMeters_LED, LOW) ;
		      
		    }
		    else
		    {
		      digitalWrite (ClMeters_LED, HIGH) ;
		    }
      break;
      
      default:
//	RetVal = 1;
      break;
    }
    
 
}

void   	ClMeters_LedToggle		(int _LedNo)


{
   int NewLevel = 0;
  
   if (ClMeters_LastIoLevel [_LedNo] == 0)
      {
	NewLevel = 1;
      }
   else
      {
       	NewLevel = 0;
      }
    ClMeters_WriteIoPort (_LedNo, NewLevel);
}


int ClMeters_ServiceGeigerMeter (void)
{
  int RetVal = 0; // default no detection

  if (digitalRead (ClMeters_G_PULSE) == HIGH )
    {
      RetVal = 1;
      ClMeters_GeigerCounter++;
      
      //delay(10);
      digitalWrite (ClMeters_G_CLR,   LOW) ;
      delay(1);
      digitalWrite (ClMeters_G_CLR,   HIGH) ;
      
    }
  
}

int ClMeters_ReadGeigerMeter (void)
{
 
  
  return ClMeters_GeigerCounter;
  
  
}


void     	ClMeters_LogMeters (void)
{
  // 1 - Time parameters
  
  unsigned long int	LogTime   	= ClTimeH_TimeNow ();
  unsigned int 	LogInterval  	= LogTime - ClMeters_LastLogTime; // Sec.
  
  float LogIntervalMin = 0.0;
  
  LogIntervalMin = (float)(LogInterval / 60.0);
  
  
  
  
  
  // 2 - Read Meters
  
  float LogTemp 	= ClMeters_ReadThermoMeter ();
  float LogHygro 	= ClMeters_ReadHygroMeter  ();
  float LogBaro 	= ClMeters_ReadBaroMeter   ();
  int	LogGeiger	= ClMeters_ReadGeigerMeter ();
  
  ClMeters_GeigerCounter = 0;
  
   // 3 - Calc Geiger Level as count per minute - Cpm
  
  float 		GeigerCpm 	=  LogGeiger /LogIntervalMin ;
  
  // GeigerCpm = (LogGeiger/ * 60) / LogInterval;

  ClMeters_LastLogGeiger = LogGeiger;
  
  
  printf ("Log: Termo: %2.1f [Celcius] - Hygro: %2.1f [%rel] - Baro: %4.1f [hPa] - Geiger: %2.1f [C/Min]. \n",  LogTemp, LogHygro, LogBaro, GeigerCpm );
  
  ClMeters_LastLogTime = LogTime;
  char DateStr [24];
  char TimeStr [24];
  ClTimeH_GetTimeStr (TimeStr);
  ClTimeH_GetDateStr (DateStr);
  
  // 0: Date data
  ClFileH_MakeDataFile (0, DateStr,0);
  
  // 1: Time data
  ClFileH_MakeDataFile (1, TimeStr,0);

  char LogLine[128] = "\0";
  
  strcpy (LogLine, DateStr);
  strcat (LogLine,",");
  strcat (LogLine,TimeStr);
  strcat (LogLine,",");
  
  char TempStr [24];
  
  // float 		  LogTemp 	= ClMeters_ReadThermoMeter ();
  // void ClStrH_Float2Str (float _TheFloat, char *_TheFloatStr, int _NumOfDigs, int _NumOfDecs );

  ClStrH_Float2Str (LogTemp, TempStr, 0, 0 ,0);
  strcat (LogLine,TempStr);

  // 2: Temp Data
  ClFileH_MakeDataFile (2, TempStr,0);
  
  strcat (LogLine,",");
  
  char HygroStr [24];
  ClStrH_Float2Str (LogHygro, HygroStr, 0, 0 ,0);
  strcat (LogLine,HygroStr);
  
  // 3: Hygro Data
  ClFileH_MakeDataFile (3, HygroStr,0);
  
  strcat (LogLine,",");
  
  
  char BaroStr [24];
  // float 		  LogTemp 	= ClMeters_ReadThermoMeter ();
  // void ClStrH_Float2Str (float _TheFloat, char *_TheFloatStr, int _NumOfDigs, int _NumOfDecs );
  ClStrH_Float2Str (LogBaro, BaroStr, 0, 0 ,0);
  
  // 4: Baro Data
  ClFileH_MakeDataFile (4, BaroStr,0);

  strcat (LogLine,BaroStr);
  strcat (LogLine,",");
  
  char GeigerStr [24];
  ClStrH_Float2Str (GeigerCpm, GeigerStr, 0, 0 ,0);

  // 5: Baro Data
  ClFileH_MakeDataFile (5, GeigerStr,0);
  

/*
 *  char GeigerStr [24];
    itoa (GeigerCounts,GeigerStr,10);
  strcat (LogLine,GeigerStr);
  */
 // ClStrH_Int2Str (GeigerCounts, 0, GeigerStr);
 
  strcat (LogLine,GeigerStr);
  ClFileH_LogLine2LogFile (LogLine);
}

int             ClMeters_ReadGps (int _GpsRegister, char *_GpsData  )
{
  
  switch (_GpsRegister)
    {
      
      case 0: // Latitude
	strcpy (_GpsData, "56-09-58.31-N");
	break;
      
      case 1: // Latitude
	strcpy (_GpsData, "10-11-28.28-E");
	break;
      
      case 2: // Height
	strcpy (_GpsData, "49");
	break;
      
      case 3: // Speed
	strcpy (_GpsData, "0.3");
	break;
      
      case 4: // Course
	strcpy (_GpsData, "123.4");
	break;
      
      default: // Not Defined 
	strcpy (_GpsData, "NULL-DATA");
	break;
      
    }
  
  return 0;
  
}




// Local Function Implementation Starts Here ------------------------------------------------
   
// 10 Bit ONLY
float ClMeters_convertToVolt (unsigned int _cnt)
    {
      float retval = 0.0;
      retval =  _cnt * 5.0;
      retval /= 1023;
      return retval;
    }

// 10 Bit ONLY
// Spec: 10 mV / K
//
float ClMeters_convertToDegC (unsigned int _cnt)
  {
      // Convert Dig to mV
      // 1023 = 5000 mV
      float mv = 0.0;
      mv = 5000 * _cnt;
      mv /= 1023;
      // Convert to Kelvin
      float kel = 0.0;
      kel = mv / 10.4; // Ideal 10 mv/K according to man. spec.
      // convert to Celcius
      float retval = 0.0;
      retval = kel - 273.15;
      return retval;
  }
  

// 
//         1800   
// Pabs =  ---- x  (Vbaro + 0.256)
//         4.55      
  
float ClMeters_convertVoltToBaro (float _Vbaro)
  {
  
    float RetVal = (_Vbaro+0.256);
  
    RetVal *= 1800;
    RetVal /= 4.55;
    return RetVal;
  
  }


