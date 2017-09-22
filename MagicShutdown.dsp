# Microsoft Developer Studio Project File - Name="MagicShutdown" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MagicShutdown - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MagicShutdown.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MagicShutdown.mak" CFG="MagicShutdown - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MagicShutdown - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MagicShutdown - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MagicShutdown - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 sqlite3.lib winmm.lib htmlhelp.lib wsnlib.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcmtd.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MagicShutdown - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 sqlite3.lib winmm.lib htmlhelp.lib wsnlib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MagicShutdown - Win32 Release"
# Name "MagicShutdown - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "sqlite No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sqlite\base64.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlite\CppSQLite3.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlite\Qstring.cpp
# End Source File
# End Group
# Begin Group "gui No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\gui\ComboBoxSuper.cpp
# End Source File
# Begin Source File

SOURCE=.\gui\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\gui\StaticCounter.cpp
# End Source File
# End Group
# Begin Group "date"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\date\FPSMiniCalendarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\date\FPSMiniCalendarListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\date\FPSRecurringDates.cpp
# End Source File
# Begin Source File

SOURCE=.\date\hightime.cpp
# End Source File
# Begin Source File

SOURCE=.\date\OleDateTimeEx.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ini.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicShutdown.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicShutdown.rc
# End Source File
# Begin Source File

SOURCE=.\MagicShutdownDlg.cpp

!IF  "$(CFG)" == "MagicShutdown - Win32 Release"

!ELSEIF  "$(CFG)" == "MagicShutdown - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\md5.cpp

!IF  "$(CFG)" == "MagicShutdown - Win32 Release"

!ELSEIF  "$(CFG)" == "MagicShutdown - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ProcessDate.cpp
# End Source File
# Begin Source File

SOURCE=.\SetDailyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetMonthlyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetWeeklyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetYearlyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\sha2.cpp

!IF  "$(CFG)" == "MagicShutdown - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "MagicShutdown - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ShowRegister.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\XTabCtrl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "sqlite"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sqlite\base64.h
# End Source File
# Begin Source File

SOURCE=.\sqlite\CppSQLite3.h
# End Source File
# Begin Source File

SOURCE=.\sqlite\Qstring.h
# End Source File
# Begin Source File

SOURCE=.\sqlite\sqlite3.h
# End Source File
# End Group
# Begin Group "gui"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\gui\ComboBoxSuper.h
# End Source File
# Begin Source File

SOURCE=.\gui\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\gui\StaticCounter.h
# End Source File
# End Group
# Begin Group "date No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\date\FPSMiniCalendarCtrl.h
# End Source File
# Begin Source File

SOURCE=.\date\FPSMiniCalendarListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\date\FPSRecurringDates.h
# End Source File
# Begin Source File

SOURCE=.\date\hightime.h
# End Source File
# Begin Source File

SOURCE=.\date\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\date\OleDateTimeEx.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\diskid32lib.h
# End Source File
# Begin Source File

SOURCE=.\htmlhelp.h
# End Source File
# Begin Source File

SOURCE=.\ini.h
# End Source File
# Begin Source File

SOURCE=.\MagicShutdown.h
# End Source File
# Begin Source File

SOURCE=.\MagicShutdownDlg.h
# End Source File
# Begin Source File

SOURCE=.\md5.h
# End Source File
# Begin Source File

SOURCE=.\ProcessDate.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SetDailyDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetMonthlyDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetWeeklyDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetYearlyDlg.h
# End Source File
# Begin Source File

SOURCE=.\sha2.h
# End Source File
# Begin Source File

SOURCE=.\ShowRegister.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\XTabCtrl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\actionlist.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\gradient.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon10.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon11.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon12.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon13.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon14.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon15.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon16.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon22.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon6.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon7.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon8.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon9.ico
# End Source File
# Begin Source File

SOURCE=.\res\images_n.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MagicShutdown.ico
# End Source File
# Begin Source File

SOURCE=.\res\MagicShutdown.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
