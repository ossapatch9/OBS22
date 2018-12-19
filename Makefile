#
# OMNeT++/OMNEST Makefile for OBS_22
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out
#

# Name of target to be created (-o option)
TARGET = OBS_22$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -ICoreNode \
    -IEdgeAndCore2 \
    -IEdgeAndHost \
    -IEdgeNode \
    -IMessages \
    -INSFnetUnificado.net \
    -ISourceSink \
    -Iresults

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/CoreNode/CoreControlLogic.o \
    $O/CoreNode/CoreInput.o \
    $O/CoreNode/CoreOutput.o \
    $O/CoreNode/CoreOutputHorizon.o \
    $O/CoreNode/EOConverter.o \
    $O/CoreNode/OEConverter.o \
    $O/CoreNode/OpticalCrossConnect.o \
    $O/CoreNode/Routing.o \
    $O/EdgeNode/Burstifier.o \
    $O/EdgeNode/BurstList.o \
    $O/EdgeNode/Classifier.o \
    $O/EdgeNode/Classifier_Rules.o \
    $O/EdgeNode/EdgeNodeDisassembler.o \
    $O/EdgeNode/Sender.o \
    $O/Messages/Burst.o \
    $O/SourceSink/Sink.o \
    $O/SourceSink/Source.o \
    $O/CoreNode/BCPControlInfo_m.o \
    $O/CoreNode/ControlUnitInfo_m.o \
    $O/CoreNode/CoreRouting_m.o \
    $O/EdgeNode/BurstifierInfo_m.o \
    $O/EdgeNode/BurstSenderInfo_m.o \
    $O/EdgeNode/ScheduleBurst_m.o \
    $O/Messages/Burst_m.o \
    $O/Messages/BurstControlPacket_m.o \
    $O/Messages/Packet_m.o

# Message files
MSGFILES = \
    CoreNode/BCPControlInfo.msg \
    CoreNode/ControlUnitInfo.msg \
    CoreNode/CoreRouting.msg \
    EdgeNode/BurstifierInfo.msg \
    EdgeNode/BurstSenderInfo.msg \
    EdgeNode/ScheduleBurst.msg \
    Messages/Burst.msg \
    Messages/BurstControlPacket.msg \
    Messages/Packet.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f OBS_22 OBS_22.exe libOBS_22.so libOBS_22.a libOBS_22.dll libOBS_22.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f CoreNode/*_m.cc CoreNode/*_m.h
	$(Q)-rm -f EdgeAndCore2/*_m.cc EdgeAndCore2/*_m.h
	$(Q)-rm -f EdgeAndHost/*_m.cc EdgeAndHost/*_m.h
	$(Q)-rm -f EdgeNode/*_m.cc EdgeNode/*_m.h
	$(Q)-rm -f Messages/*_m.cc Messages/*_m.h
	$(Q)-rm -f NSFnetUnificado.net/*_m.cc NSFnetUnificado.net/*_m.h
	$(Q)-rm -f SourceSink/*_m.cc SourceSink/*_m.h
	$(Q)-rm -f results/*_m.cc results/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc CoreNode/*.cc EdgeAndCore2/*.cc EdgeAndHost/*.cc EdgeNode/*.cc Messages/*.cc NSFnetUnificado.net/*.cc SourceSink/*.cc results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/CoreNode/BCPControlInfo_m.o: CoreNode/BCPControlInfo_m.cc \
	CoreNode/BCPControlInfo_m.h
$O/CoreNode/ControlUnitInfo_m.o: CoreNode/ControlUnitInfo_m.cc \
	CoreNode/ControlUnitInfo_m.h
$O/CoreNode/CoreControlLogic.o: CoreNode/CoreControlLogic.cc \
	CoreNode/BCPControlInfo_m.h \
	CoreNode/ControlUnitInfo_m.h \
	CoreNode/CoreControlLogic.h \
	CoreNode/CoreInput.h \
	CoreNode/CoreOutput.h \
	CoreNode/CoreOutputHorizon.h \
	CoreNode/CoreRouting_m.h \
	CoreNode/OpticalCrossConnect.h \
	CoreNode/Routing.h \
	Messages/BurstControlPacket_m.h
$O/CoreNode/CoreInput.o: CoreNode/CoreInput.cc \
	CoreNode/CoreInput.h
$O/CoreNode/CoreOutput.o: CoreNode/CoreOutput.cc \
	CoreNode/CoreOutput.h
$O/CoreNode/CoreOutputHorizon.o: CoreNode/CoreOutputHorizon.cc \
	CoreNode/CoreOutputHorizon.h
$O/CoreNode/CoreRouting_m.o: CoreNode/CoreRouting_m.cc \
	CoreNode/CoreRouting_m.h
$O/CoreNode/EOConverter.o: CoreNode/EOConverter.cc \
	CoreNode/BCPControlInfo_m.h \
	Messages/BurstControlPacket_m.h
$O/CoreNode/OEConverter.o: CoreNode/OEConverter.cc \
	CoreNode/BCPControlInfo_m.h \
	Messages/BurstControlPacket_m.h
$O/CoreNode/OpticalCrossConnect.o: CoreNode/OpticalCrossConnect.cc \
	CoreNode/OpticalCrossConnect.h \
	Messages/Burst.h \
	Messages/Burst_m.h
$O/CoreNode/Routing.o: CoreNode/Routing.cc \
	CoreNode/CoreRouting_m.h \
	CoreNode/Routing.h \
	Messages/BurstControlPacket_m.h
$O/EdgeNode/BurstList.o: EdgeNode/BurstList.cc \
	EdgeNode/BurstList.h \
	EdgeNode/ScheduleBurst_m.h \
	Messages/Burst.h \
	Messages/Burst_m.h
$O/EdgeNode/BurstSenderInfo_m.o: EdgeNode/BurstSenderInfo_m.cc \
	EdgeNode/BurstSenderInfo_m.h
$O/EdgeNode/Burstifier.o: EdgeNode/Burstifier.cc \
	EdgeNode/Burstifier.h \
	EdgeNode/BurstifierInfo_m.h \
	Messages/Burst.h \
	Messages/Burst_m.h \
	Messages/Packet_m.h
$O/EdgeNode/BurstifierInfo_m.o: EdgeNode/BurstifierInfo_m.cc \
	EdgeNode/BurstifierInfo_m.h
$O/EdgeNode/Classifier.o: EdgeNode/Classifier.cc \
	EdgeNode/Classifier.h \
	EdgeNode/Classifier_Rules.h \
	Messages/Packet_m.h
$O/EdgeNode/Classifier_Rules.o: EdgeNode/Classifier_Rules.cc \
	EdgeNode/Classifier_Rules.h \
	Messages/Packet_m.h
$O/EdgeNode/EdgeNodeDisassembler.o: EdgeNode/EdgeNodeDisassembler.cc \
	EdgeNode/EdgeNodeDisassembler.h \
	Messages/Burst.h \
	Messages/Burst_m.h
$O/EdgeNode/ScheduleBurst_m.o: EdgeNode/ScheduleBurst_m.cc \
	EdgeNode/ScheduleBurst_m.h
$O/EdgeNode/Sender.o: EdgeNode/Sender.cc \
	EdgeNode/BurstList.h \
	EdgeNode/BurstSenderInfo_m.h \
	EdgeNode/BurstifierInfo_m.h \
	EdgeNode/ScheduleBurst_m.h \
	EdgeNode/Sender.h \
	Messages/Burst.h \
	Messages/BurstControlPacket_m.h \
	Messages/Burst_m.h
$O/Messages/Burst.o: Messages/Burst.cc \
	Messages/Burst.h \
	Messages/Burst_m.h
$O/Messages/BurstControlPacket_m.o: Messages/BurstControlPacket_m.cc \
	Messages/BurstControlPacket_m.h
$O/Messages/Burst_m.o: Messages/Burst_m.cc \
	Messages/Burst_m.h
$O/Messages/Packet_m.o: Messages/Packet_m.cc \
	Messages/Packet_m.h
$O/SourceSink/Sink.o: SourceSink/Sink.cc \
	Messages/Packet_m.h \
	SourceSink/Sink.h
$O/SourceSink/Source.o: SourceSink/Source.cc \
	CoreNode/CoreRouting_m.h \
	CoreNode/Routing.h \
	Messages/BurstControlPacket_m.h \
	Messages/Packet_m.h \
	SourceSink/Source.h

