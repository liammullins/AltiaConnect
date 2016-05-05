#
# This file is Altia's version of a Visual Studio Win32.mak file suitable to
# include in a make file for compiling C application code with VC 6.0 thru
# Visual Studio 2010 and beyond (such as Visual Studio 2012 and 2013 which do
# not include an SDK containing a Win32.mak file).  Place this file in the
# same folder as a make file that is doing an include of Win32.mak.  If a
# make file includes ntwin32.mak, change it to include Win32.mak instead.
#
# Revision:  April 21, 2014
#

!IFNDEF _VSVARS_MAK_
_VSVARS_MAK_ = 1

#
# If APPVER not set, do APPVER 4.0.
#

!IFNDEF APPVER
APPVER = 4.0
!ENDIF

#
# If APPVER 4.0, determine if this is Visual C 6.0
#

!IF "$(APPVER)" == "4.0"
!IF !DEFINED(VS80COMNTOOLS) && !DEFINED(VSCOMNTOOLS)
# This is VC 6.0 because it is not VS 2005 or VS .NET
THIS_IS_VC6 = 1
!ENDIF # NOT VS 2005 AND NOT VS .NET
!ENDIF # APPVER == 4.0

#
# Use APPVER to set NMAKE_WINVER and _WIN32_IE variables
#

!IF "$(APPVER)" =="6.1"
NMAKE_WINVER = 0x0601
!IFNDEF _WIN32_IE
_WIN32_IE = 0x0800
!ENDIF # _WIN32_IE
!ENDIF # APPVER == 6.1

!IF "$(APPVER)" =="6.0"
NMAKE_WINVER = 0x0600
!IFNDEF _WIN32_IE
_WIN32_IE = 0x0700
!ENDIF # _WIN32_IE
!ENDIF # APPVER == 6.0

!IF "$(APPVER)" =="5.0"
NMAKE_WINVER = 0x0500
!IFNDEF _WIN32_IE
_WIN32_IE = 0x0500
!ENDIF # _WIN32_IE
!ENDIF # APPVER == 5.0

!IF "$(APPVER)" =="5.01"
NMAKE_WINVER = 0x0501
!IFNDEF _WIN32_IE
_WIN32_IE = 0x0600
!ENDIF # _WIN32_IE
!ENDIF # APPVER == 5.01

!IF "$(APPVER)" =="5.02"
NMAKE_WINVER = 0x0502
!IFNDEF _WIN32_IE
_WIN32_IE = 0x0600
!ENDIF # _WIN32_IE
!ENDIF # APPVER == 5.02

!IF "$(APPVER)" == "4.0"
NMAKE_WINVER = 0x0400
!IFNDEF _WIN32_IE
_WIN32_IE = 0x0400
!ENDIF # _WIN32_IE
!ENDIF # APPVER == 4.0

#
# If architecture is not set, default cpu is i386 and architecture is x86
#

!IF "$(PROCESSOR_ARCHITECTURE)" == ""
CPU=i386
PROCESSOR_ARCHITECTURE=x86
!endif

!IF !DEFINED(CPU) || "$(CPU)" == ""
CPU = $(PROCESSOR_ARCHITECTURE)
!ENDIF # CPU

#
# If PROCESSOR_ARCHITECTURE is x86 or X86, CPU has to be i386
#

!IF ( "$(CPU)" == "X86" ) || ( "$(CPU)" == "x86" )
CPU = i386
!ENDIF # CPU == X86

!IF "$(CPU)" != "i386"
!IF "$(CPU)" != "IA64"
!IF "$(CPU)" != "AMD64"
!ERROR  CPU variable not specified ( CPU=i386, CPU=IA64, CPU=AMD64)
!ENDIF
!ENDIF
!ENDIF


#
# These compiler tool variables required
#

cc     = cl
link   = link
implib = lib
rc     = Rc

#
# Common compiler flags:
#   -c   - compile without linking
#   -W3  - set warning level to level 3    (-W4 for 64-bit compilations)
#   -Zi  - generate debugging information  (usually -Zi is used with -Od)
#   -Od  - disable all optimizations       (usually -Zi is used with -Od)
#   -Ox  - use maximum optimizations
#   -Zd  - generate only public symbols and line numbers for debugging
#   -GS  - enable security checks
#
# i386 specific compiler flags:
#   -Gz  - stdcall   (only if scall is added to makefile's compiler build rules)
#

#
# cflags is next
#
!IFDEF THIS_IS_VC6
# This is Visual C 6.0 Compiler
ccommon = -c -DCRTAPI1=_cdecl -DCRTAPI2=_cdecl -nologo
warnlevel = 
!ELSE
ccommon = -c -DCRTAPI1=_cdecl -DCRTAPI2=_cdecl -nologo -GS
warnlevel = -W3
!ENDIF

!IF "$(CPU)" == "i386"
cflags = $(ccommon) -D_X86_=1  -DWIN32 -D_WIN32 $(warnlevel)
scall  = -Gz
!ELSEIF "$(CPU)" == "IA64"
cflags = $(ccommon) -D_IA64_=1 -DWIN64 -D_WIN64  -DWIN32 -D_WIN32 -W4
scall  =
!ELSEIF "$(CPU)" == "AMD64"
cflags = $(ccommon) -D_AMD64_=1 -DWIN64 -D_WIN64  -DWIN32 -D_WIN32 -W4
scall  =
!ENDIF

# these flags always apply from WINNT and newer systems
winntmore = -D_WINNT -D_WIN32_WINNT=$(NMAKE_WINVER) -DNTDDI_VERSION=$(NMAKE_WINVER)0000

# finally, define WINVER to match APPVER macro
cflags = $(cflags) $(winntmore) -D_WIN32_IE=$(_WIN32_IE) -DWINVER=$(NMAKE_WINVER)

#
# cdebug is next
#

!IF "$(CPU)" != "IA64"
!IFDEF NODEBUG
cdebug = -Ox -DNDEBUG 
!ELSE IFDEF PROFILE
cdebug = -Gh -Ox -DNDEBUG
!ELSE IFDEF TUNE
cdebug = -Gh -Ox -DNDEBUG
!ELSE
cdebug = -Zi -Od -DDEBUG
!ENDIF

!ELSE

!IFDEF NODEBUG
cdebug = -Ox -DNDEBUG
!ELSE
cdebug = -Zi -Od -DDEBUG
!ENDIF

!ENDIF

#
# cvars variants are next, multi-threaded static CRT libs (cvarsmt and cvars)
# or multi-threaded DLL CRT libs (cvarsdll).  DLL CRT libs cause the compiler
# to place a reference to one of the versions of the MS Visual C Run-Time
# (MSVCRT) library into the .obj file.  The DLL CRT libs are used when
# linking the object with the MSVCRT library.  They do not imply the target
# object is itself a DLL.
#

!IFDEF NODEBUG
cvarsmt    = -D_MT -MT
cvars      = $(cvarsmt)
cvarsdll   = -D_MT -D_DLL -MD
!ELSE
cvarsmt    = -D_MT -MTd
cvars      = $(cvarsmt)
cvarsdll   = -D_MT -D_DLL -MDd
!ENDIF

!IFDEF THIS_IS_VC6
# This is Visual C 6.0 Compiler. No MT flags in cvars.
cvars      =
!ENDIF

#
# for POSIX applications
#

psxvars    = -D_POSIX_

#
# resource compiler
#

rcflags = /r
!ifdef NODEBUG
rcvars = -DWIN32 -D_WIN32 -DWINVER=$(NMAKE_WINVER) $(noansi)
!else
rcvars = -DWIN32 -D_WIN32 -DWINVER=$(NMAKE_WINVER) -DDEBUG -D_DEBUG $(noansi)
!endif

#
# Link flags - must be specified after $(link)
#
# Note: $(DLLENTRY) should be appended to each -entry: flag on the link
#       line.
#
# Note: When creating a DLL that uses C Run-Time functions, it is
#       recommended to include the entry point function of the name DllMain
#       in the DLL's source code.  Also, the MAKEFILE should include the
#       -entry:_DllMainCRTStartup$(DLLENTRY) option for the creation of
#       this DLL.  (The C Run-Time entry point _DllMainCRTStartup in turn
#       calls the DLL defined DllMain entry point.)
#

# declarations common to all linker options
!IFDEF THIS_IS_VC6
# This is Visual C 6.0 Compiler
lflags  = /NODEFAULTLIB /INCREMENTAL:NO /PDB:NONE /RELEASE /NOLOGO
!ELSE
lflags  = $(lflags) /INCREMENTAL:NO /NOLOGO
!ENDIF

# declarations for use on Intel x86 systems
!IF "$(CPU)" == "i386"
DLLENTRY = @12
!ENDIF

# declarations for use on Intel Architecture 64-bit systems
!IF "$(CPU)" == "IA64"
DLLENTRY =
!ENDIF

# declarations for use on AMD64 systems
!IF "$(CPU)" == "AMD64"
DLLENTRY =
!ENDIF


#
# Debug link flags - must be specified after $(link)
#
# These switches allow the inclusion of the necessary symbolic information
# for source level debugging with WinDebug, profiling and/or performance
# tuning.
#
# Note: Debug switches are on by default.
#

!IF "$(CPU)" == "i386"

!IFDEF NODEBUG
ldebug = /RELEASE
!ELSE
ldebug = /DEBUG /DEBUGTYPE:cv
!ENDIF

!ELSE

!IFDEF NODEBUG
ldebug = /RELEASE
!ELSE IFDEF PROFILE
ldebug = /DEBUG:mapped,partial /DEBUGTYPE:coff
!ELSE IFDEF TUNE
ldebug = /DEBUG:mapped,partial /DEBUGTYPE:coff
!ELSE IFDEF THIS_IS_VC6
# This is Visual C 6.0 Compiler
ldebug = -debug:full -debugtype:cv
!ELSE
ldebug = /DEBUG /DEBUGTYPE:cv
!ENDIF

!ENDIF

#
# lflags are next
#

conlflags = $(lflags) -subsystem:console,$(APPVER)
conflags  = $(conlflags)
guilflags = $(lflags) -subsystem:windows,$(APPVER)
guiflags  = $(guilflags)
dlllflags = $(lflags) -entry:_DllMainCRTStartup$(DLLENTRY) -dll

# for POSIX applications
psxlflags = $(lflags) -subsystem:posix -entry:__PosixProcessStartup
psxflags  = $(psxlflags)

#
# libs are last
#

# for POSIX applications
psxlibs    = libcpsx.lib psxdll.lib psxrtl.lib oldnames.lib

# optional profiling and tuning libraries
!IF "$(CPU)" != "IA64"

!IFDEF PROFILE
optlibs =  cap.lib
!ELSE IFDEF TUNE
optlibs = wst.lib
!ELSE
optlibs =
!ENDIF

!ELSE
optlibs =
!ENDIF

!IFDEF THIS_IS_VC6
# This is Visual C 6.0 Compiler
libc = libc.lib oldnames.lib
libcmt = libcmt.lib oldnames.lib
libcdll = msvcrt.lib oldnames.lib
!ELSE
libc =
libcmt =
libcdll =
!ENDIF

# basic subsystem specific libraries, less the C Run-Time
winsocklibs = ws2_32.lib mswsock.lib
baselibs    = kernel32.lib $(optlibs) $(winsocklibs) advapi32.lib
winlibs     = $(baselibs) user32.lib gdi32.lib comdlg32.lib winspool.lib

# for Windows applications that use the C Run-Time libraries
conlibs     = $(libc) $(baselibs)
guilibs     = $(libc) $(winlibs)

#for backwards compatibility
conlibsmt   = $(libcmt) $(baselibs)
conlibsdll  = $(libcdll) $(baselibs)
guilibsmt   = $(libcmt) $(winlibs)
guilibsdll  = $(libcdll) $(winlibs)

#ENDIF _VSVARS_MAK_
!ENDIF
