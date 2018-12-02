#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/fonctions.o \
	${OBJECTDIR}/global.o \
	${OBJECTDIR}/lib/src/comgui.o \
	${OBJECTDIR}/lib/src/comstm32.o \
	${OBJECTDIR}/lib/src/control.o \
	${OBJECTDIR}/lib/src/messages.o \
	${OBJECTDIR}/lib/src/parameters.o \
	${OBJECTDIR}/lib/src/trace.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/segway_supervisor

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/segway_supervisor: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/segway_supervisor ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/fonctions.o: fonctions.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fonctions.o fonctions.cpp

${OBJECTDIR}/global.o: global.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/global.o global.cpp

${OBJECTDIR}/lib/src/comgui.o: lib/src/comgui.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/comgui.o lib/src/comgui.cpp

${OBJECTDIR}/lib/src/comstm32.o: lib/src/comstm32.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/comstm32.o lib/src/comstm32.cpp

${OBJECTDIR}/lib/src/control.o: lib/src/control.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/control.o lib/src/control.cpp

${OBJECTDIR}/lib/src/messages.o: lib/src/messages.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/messages.o lib/src/messages.cpp

${OBJECTDIR}/lib/src/parameters.o: lib/src/parameters.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/parameters.o lib/src/parameters.cpp

${OBJECTDIR}/lib/src/trace.o: lib/src/trace.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/trace.o lib/src/trace.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/inc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
