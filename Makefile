print-%  : ; @echo $* = $($*)	# Use "make print-VARIABLE" to debug.

# AKA, all ".cpp" files needed.
TARGETS = x86 parsing playground

OUT_DIR = out/
SRC_DIR = src/

OBJS_OUT_OF_DIR = $(addsuffix .o,$(TARGETS))
OBJS = $(addprefix $(OUT_DIR),$(OBJS_OUT_OF_DIR))

CC = g++
DEBUG = -g
CFLAGS = -std=c++14 -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: playground

playground : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(OUT_DIR)playground

# This is a "Static Pattern" Makefile rule. It pattern matches all rules
# in OBJS using the "%" character, using the format:
#
# targets : target pattern : prereq-pattern.
#
# In this case, the "targets" are all the .o files, the "target pattern"
# is "out/.*.o", and the "prereq-pattern" is "src/.*.o"
#
# "$<" means the pattern matched prereq. "$@" is the pattern matched target.
$(OBJS): $(OUT_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm out/*
