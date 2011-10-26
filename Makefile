#****************************************************************************
#
# Makefile for rtwt.
# Vianney Bouchaud.
#
# This is a GNU make (gmake) makefile
#****************************************************************************

# DEBUG can be set to YES to include debugging info, or NO otherwise
DEBUG          	:= NO

#****************************************************************************

CC     := gcc
CXX    := clang++
LD     := clang++
AR     := ar rc
RANLIB := ranlib

DEBUG_CFLAGS     := -g -DDEBUG -fPIC
RELEASE_CFLAGS	 := -Wall -W -Wextra -Wno-unknown-pragmas -Wno-format -O3

LIBS		 := -L/usr/X11R6/lib -lXtst -lX11

DEBUG_CXXFLAGS   := ${DEBUG_CFLAGS}
RELEASE_CXXFLAGS := ${RELEASE_CFLAGS}

DEBUG_LDFLAGS    := -g
RELEASE_LDFLAGS  :=

ifeq (YES, ${DEBUG})
   CFLAGS       := ${DEBUG_CFLAGS}
   CXXFLAGS     := ${DEBUG_CXXFLAGS}
   LDFLAGS      := ${DEBUG_LDFLAGS}
else
   CFLAGS       := ${RELEASE_CFLAGS}
   CXXFLAGS     := ${RELEASE_CXXFLAGS}
   LDFLAGS      := ${RELEASE_LDFLAGS}
endif

#****************************************************************************
# Include paths
#****************************************************************************

INCS := -I./includes/

#****************************************************************************
# Makefile code common to all platforms
#****************************************************************************

CFLAGS   := ${CFLAGS}   ${DEFS}
CXXFLAGS := ${CXXFLAGS} ${DEFS}

#****************************************************************************
# Source files
#****************************************************************************

SRCS := srcs/main.cpp		\
	srcs/Keylogger.cpp

OBJS := $(addsuffix .o,$(basename ${SRCS}))

#****************************************************************************
# Name
#****************************************************************************

OUTPUT := keylogger-X11

#****************************************************************************
# Targets of the build
#****************************************************************************

all: ${OUTPUT}

#****************************************************************************
# Output
#****************************************************************************

${OUTPUT}: ${OBJS}
	${LD} -o $@ ${LDFLAGS} ${OBJS} ${LIBS} ${EXTRA_LIBS}

#****************************************************************************
# common rules
#****************************************************************************

# Rules for compiling source files to object files
%.o : %.cpp
	${CXX} -c ${CXXFLAGS} ${INCS} $< -o $@

%.o : %.c
	${CC} -c ${CFLAGS} ${INCS} $< -o $@

dist:
	bash makedistlinux

clean:
	-rm -f core ${OBJS} ${OUTPUT}

depend:
#makedepend ${INCS} ${SRCS}

#****************************************************************************
# epitech rules
#****************************************************************************

re: clean all