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
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/_ext/546370707/course.o \
	${OBJECTDIR}/_ext/546370707/display.o \
	${OBJECTDIR}/_ext/546370707/entrant.o \
	${OBJECTDIR}/_ext/546370707/event.o \
	${OBJECTDIR}/_ext/546370707/fileIO.o \
	${OBJECTDIR}/_ext/546370707/main.o \
	${OBJECTDIR}/_ext/546370707/node.o \
	${OBJECTDIR}/_ext/546370707/process.o \
	${OBJECTDIR}/_ext/546370707/track.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/event-manager

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/event-manager: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/event-manager ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/546370707/course.o: ../../CS237-Assignment/Extended-Mission/course.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/546370707
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/546370707/course.o ../../CS237-Assignment/Extended-Mission/course.c

${OBJECTDIR}/_ext/546370707/display.o: ../../CS237-Assignment/Extended-Mission/display.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/546370707
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/546370707/display.o ../../CS237-Assignment/Extended-Mission/display.c

${OBJECTDIR}/_ext/546370707/entrant.o: ../../CS237-Assignment/Extended-Mission/entrant.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/546370707
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/546370707/entrant.o ../../CS237-Assignment/Extended-Mission/entrant.c

${OBJECTDIR}/_ext/546370707/event.o: ../../CS237-Assignment/Extended-Mission/event.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/546370707
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/546370707/event.o ../../CS237-Assignment/Extended-Mission/event.c

${OBJECTDIR}/_ext/546370707/fileIO.o: ../../CS237-Assignment/Extended-Mission/fileIO.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/546370707
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/546370707/fileIO.o ../../CS237-Assignment/Extended-Mission/fileIO.c

${OBJECTDIR}/_ext/546370707/main.o: ../../CS237-Assignment/Extended-Mission/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/546370707
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/546370707/main.o ../../CS237-Assignment/Extended-Mission/main.c

${OBJECTDIR}/_ext/546370707/node.o: ../../CS237-Assignment/Extended-Mission/node.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/546370707
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/546370707/node.o ../../CS237-Assignment/Extended-Mission/node.c

${OBJECTDIR}/_ext/546370707/process.o: ../../CS237-Assignment/Extended-Mission/process.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/546370707
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/546370707/process.o ../../CS237-Assignment/Extended-Mission/process.c

${OBJECTDIR}/_ext/546370707/track.o: ../../CS237-Assignment/Extended-Mission/track.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/546370707
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/546370707/track.o ../../CS237-Assignment/Extended-Mission/track.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/event-manager

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
