################################################################################
#
# iChargerMon Makefile
#
################################################################################

# CLI Sources ##################################################################

ICHARGERMON_SRCS = src/main.cpp
ICHARGERMON_SRCS += src/icharger.cpp
ICHARGERMON_SRCS += src/icharger_state.cpp

# Binary Targets ###############################################################

ICHARGERMON_BIN = ichargermon

# Common Compiler Flags ########################################################

CFLAGS  = -std=c++11
CFLAGS += -Isrc/
CFLAGS += -Wall

# CLI Compiler Flags ###########################################################

ICHARGERMON_CFLAGS = $(CFLAGS)

# Common Linker Flags ##########################################################

LDFLAGS =

# CLI Linker Flags #############################################################

CLIENT_LDFLAGS  = $(LDFLAGS)

# Build Targets ################################################################

all: $(ICHARGERMON_BIN)

$(ICHARGERMON_BIN): $(ICHARGERMON_SRCS)
	g++ $(ICHARGERMON_CFLAGS) $(ICHARGERMON_LDFLAGS) $^ -o $@

run_ichargermon: ichargermon
	./$(ICHARGERMON_BIN)

clean:
	rm -f $(ICHARGERMON_BIN)
