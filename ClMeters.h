#ifndef	_CL_METERS_H
#define	_CL_METERS_H	1

// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! Cl Meters Handler Module Header
// ! Filename:    ! ClMeters.h
// ! Dependent:   ! ClMeters.h
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level Meter functions.
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
// ! 2016-04-13   ! RPi-Coder !  1.1.2   !         ! 
// ! 2016-04-14   ! RPi-Coder !  1.1.3   !         ! Service Geiger Counter added
// ! 2016-04-16   ! RPi-Coder !  1.1.4   !         ! 
// ! 2016-04-18   ! RPi-Coder !  1.1.5   !         ! 
// ! 2016-04-19   ! RPi-Coder !  1.2.1   !         ! Hygro Meter added
// +--------------+-----------+----------+---------+---------------------------------
//

#define ClMeters_NumOfIoPorts 4


void	ClMeters_InitModule 		(int _LogIntervalMins);

float	ClMeters_ReadVoltMeter 		(void);

float	ClMeters_ReadThermoMeter 	(void);

float	ClMeters_ReadHygroMeter 	(void);

float	ClMeters_ReadBaroMeter 		(void);

void 	ClMeters_WriteIoPort 		(int _PortNo, int _PortLevel);

void   	ClMeters_LedToggle		(int _LedNo);
 
int 	ClMeters_ServiceGeigerMeter	(void);

int 	ClMeters_ReadGeigerMeter 	(void);

void    ClMeters_LogMeters 		(void);

int     ClMeters_ReadGps 		(int _GpsRegister, char *_GpsData  );


#endif // ClMeters.h Meters Handler Module Header




