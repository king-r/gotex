## -*- Makefile -*-
##
## User: roli
## Time: 09.02.2015 14:22:24
## Makefile created by Oracle Solaris Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CCC = g++
CXX = g++
BASICOPTS = -g
CCFLAGS = $(BASICOPTS) `pkg-config --cflags --libs gtk+-3.0`
CXXFLAGS = $(BASICOPTS) `pkg-config --cflags --libs gtk+-3.0`
CCADMIN = 


# Define the target directories.
TARGETDIR_gotex=GNU-amd64-Linux


all: $(TARGETDIR_gotex)/gotex

## Target: gotex
OBJS_gotex =  \
	$(TARGETDIR_gotex)/LineStringBuilder.o \
	$(TARGETDIR_gotex)/FileOperator.o \
	$(TARGETDIR_gotex)/BufferModificator.o \
	$(TARGETDIR_gotex)/ProgramConfig.o \
	$(TARGETDIR_gotex)/TextFileReader.o \
	$(TARGETDIR_gotex)/ConstStrings.o \
	$(TARGETDIR_gotex)/main.o \
	$(TARGETDIR_gotex)/GtkManager.o \
	$(TARGETDIR_gotex)/static_functions_ui.o \
	$(TARGETDIR_gotex)/GlobalHelperFunctions.o
USERLIBS_gotex = $(SYSLIBS_gotex) 
DEPLIBS_gotex =  
LDLIBS_gotex = $(USERLIBS_gotex)


# Link or archive
$(TARGETDIR_gotex)/gotex: $(TARGETDIR_gotex) $(OBJS_gotex) $(DEPLIBS_gotex)
	$(LINK.cc) $(CCFLAGS_gotex) $(CPPFLAGS_gotex) -o $@ $(OBJS_gotex) $(LDLIBS_gotex) `pkg-config --cflags --libs gtk+-3.0`


# Compile source files into .o files
$(TARGETDIR_gotex)/ConstStrings.o: $(TARGETDIR_gotex) ConstStrings.cpp
	$(COMPILE.cc) $(CCFLAGS_gotex) $(CPPFLAGS_gotex) -o $@ ConstStrings.cpp

$(TARGETDIR_gotex)/TextFileReader.o: $(TARGETDIR_gotex) TextFileReader.cpp
	$(COMPILE.cc) $(CCFLAGS_gotex) $(CPPFLAGS_gotex) -o $@ TextFileReader.cpp

$(TARGETDIR_gotex)/main.o: $(TARGETDIR_gotex) main.cpp
	$(COMPILE.cc) $(CCFLAGS_gotex) $(CPPFLAGS_gotex) -o $@ main.cpp

$(TARGETDIR_gotex)/GtkManager.o: $(TARGETDIR_gotex) GtkManager.cpp
	$(COMPILE.cc) $(CCFLAGS_gotex) $(CPPFLAGS_gotex) -o $@ GtkManager.cpp `pkg-config --cflags --libs gtk+-3.0`

$(TARGETDIR_gotex)/static_functions_ui.o: $(TARGETDIR_gotex) static_functions_ui.cpp
	$(COMPILE.cc) $(CCFLAGS_gotex) $(CPPFLAGS_gotex) -o $@ static_functions_ui.cpp

$(TARGETDIR_gotex)/LineStringBuilder.o: $(TARGETDIR_gotex) LineStringBuilder.cpp
	$(COMPILE.cc) $(CCFLAGS_gotex) $(CPPFLAGS_gotex) -o $@ LineStringBuilder.cpp

$(TARGETDIR_gotex)/FileOperator.o: $(TARGETDIR_gotex) FileOperator.cpp
	$(COMPILE.cc) $(CCFLAGS_gotex) $(CPPFLAGS_gotex) -o $@ FileOperator.cpp

$(TARGETDIR_gotex)/GlobalHelperFunctions.o: $(TARGETDIR_gotex) GlobalHelperFunctions.cpp
	$(COMPILE.cc) $(CCFLAGS_gotex) $(CPPFLAGS_gotex) -o $@ GlobalHelperFunctions.cpp

$(TARGETDIR_gotex)/ProgramConfig.o: $(TARGETDIR_gotex) ProgramConfig.cpp
	$(COMPILE.cc) $(CCFLAGS_gotex) $(CPPFLAGS_gotex) -o $@ ProgramConfig.cpp

$(TARGETDIR_gotex)/BufferModificator.o: $(TARGETDIR_gotex) BufferModificator.cpp
	$(COMPILE.cc) $(CCFLAGS_gotex) $(CPPFLAGS_gotex) -o $@ BufferModificator.cpp

#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_gotex)/gotex \
		$(TARGETDIR_gotex)/TextFileReader.o \
		$(TARGETDIR_gotex)/ConstStrings.o \
		$(TARGETDIR_gotex)/main.o \
		$(TARGETDIR_gotex)/GtkManager.o \
		$(TARGETDIR_gotex)/static_functions_ui.o \
		$(TARGETDIR_gotex)/LineStringBuilder.o
	$(CCADMIN)
	rm -f -r $(TARGETDIR_gotex)


# Create the target directory (if needed)
$(TARGETDIR_gotex):
	mkdir -p $(TARGETDIR_gotex)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

