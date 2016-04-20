#ifndef	_CL_STRH_H
#define	_CL_STRH_H	1

// +--------------+-------------------------------------------------------------
// ! Projectname: ! climaLog2000 - Clima Log 2000
// ! Modulename:  ! String Handler Module Header
// ! Filename:    ! ClStrH.h
// ! Dependent:   ! ClStrH.h
// +--------------+-------------------------------------------------------------
// ! Description: ! A collection of useful low-level string functions.
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
// ! 2016-04-03   ! RPi-Coder !  1.7.1   ! Open    ! p = StrPos (_string, _chr) added
// ! 2016-04-03   ! RPi-Coder !  1.7.2   ! Open    !  
// ! 2016-04-03   ! RPi-Coder !  1.7.3   ! Open    ! p = StripLeadingSpaces (_string) added
// ! 2016-04-04   ! RPi-Coder !  1.7.4   ! Open    ! ClStrH_StripSpaceStr added.
// ! 2016-04-04   ! RPi-Coder !  1.7.5   ! Open    ! ClStrH_DeleteFromStart added.
// !              !           !          !         ! Bugs in Pos 
// ! 2016-04-17   ! RPi-Coder !  1.8.1   ! Open    ! Float2Str PosSign added
// !              !           !          !         !                                 
// +--------------+-----------+----------+---------+---------------------------------
//




#define ClStrH_NUM_STR_MAX_LEN          12


//


void ClStrH_DeleteFromStart (char *_TheString,  int _NumToDelete );


void ClStrH_CopyFrom (char *_TheString, char *_TheResultString, int _FromPos, int _Nums );




void ClStrH_StripSpaceStr (char *_TheString);




// ----------------------------------------------------------------------
//   Name:   int  ClStrH_StrPos  ( char *_TheString, char _TheChar);
// ----------------------------------------------------------------------
// 
//   Input:  TheString 
//           TheChar
//           FromPos
//
//   Output: 0: Char not found in String
//           n: Char found as charcter number n. (1 = first char in string)
//
// ----------------------------------------------------------------------

int  ClStrH_StrPos  ( char *_TheString, char _TheChar, int _FromPos);

void ClStrH_Int2Str (int _TheInt, int _NoOfDigs, char *_TheIntStr);

void ClStrH_Float2Str (float _TheFloat, char *_TheFloatStr, int _NumOfDigs, int _NumOfDecs , int _PosSign);


#endif // ClStrH.h String Handler Module Header



