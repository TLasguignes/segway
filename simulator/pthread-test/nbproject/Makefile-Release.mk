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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/db41d586/angles.o \
	${OBJECTDIR}/_ext/db41d586/battery.o \
	${OBJECTDIR}/_ext/db41d586/beta.o \
	${OBJECTDIR}/_ext/db41d586/consigne.o \
	${OBJECTDIR}/_ext/db41d586/lib_monitor.o \
	${OBJECTDIR}/_ext/db41d586/lib_msg_GUI.o \
	${OBJECTDIR}/_ext/db41d586/lib_serial.o \
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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pthread-test

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pthread-test: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pthread-test ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/db41d586/angles.o: ../raspberry/lib/src/angles.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/db41d586
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/db41d586/angles.o ../raspberry/lib/src/angles.cpp

${OBJECTDIR}/_ext/db41d586/battery.o: ../raspberry/lib/src/battery.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/db41d586
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/db41d586/battery.o ../raspberry/lib/src/battery.cpp

${OBJECTDIR}/_ext/db41d586/beta.o: ../raspberry/lib/src/beta.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/db41d586
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/db41d586/beta.o ../raspberry/lib/src/beta.cpp

${OBJECTDIR}/_ext/db41d586/consigne.o: ../raspberry/lib/src/consigne.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/db41d586
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/db41d586/consigne.o ../raspberry/lib/src/consigne.cpp

${OBJECTDIR}/_ext/db41d586/lib_monitor.o: ../raspberry/lib/src/lib_monitor.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/db41d586
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/db41d586/lib_monitor.o ../raspberry/lib/src/lib_monitor.cpp

${OBJECTDIR}/_ext/db41d586/lib_msg_GUI.o: ../raspberry/lib/src/lib_msg_GUI.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/db41d586
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/db41d586/lib_msg_GUI.o ../raspberry/lib/src/lib_msg_GUI.cpp

${OBJECTDIR}/_ext/db41d586/lib_serial.o: ../raspberry/lib/src/lib_serial.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/db41d586
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/db41d586/lib_serial.o ../raspberry/lib/src/lib_serial.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
