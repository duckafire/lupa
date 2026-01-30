# SUMMARY (done in ./build/):
# Compile all content from ./src/core in object files,
# use them to compile a static library, and compile an
# executable file with the compiled static library plus
# the content out of ./src/core.

.PHONY: all test clean


PROJ_NAME := lupa

CC := gcc
AR := ar

AFLAGS := rcs
CFLAGS := -Wall -Wextra -Wno-unused-function -std=c90


BLD_D := ./build
OBJ_D := $(BLD_D)/objects

SRC_D := ./src
SRC_LIB_D := $(SRC_D)/core


OUT_EXE := $(BLD_D)/$(PROJ_NAME)
OUT_LIB := $(BLD_D)/lib$(PROJ_NAME).a

ALL_FILES_C := $(shell find $(SRC_D) -type f -name *.c)

FILES_EXE_C := $(filter-out $(SRC_LIB_D)/%, $(ALL_FILES_C))

FILES_LIB_C := $(filter $(SRC_LIB_D)/%, $(ALL_FILES_C))
FILES_LIB_O := $(FILES_LIB_C:$(SRC_LIB_D)/%.c=$(OBJ_D)/%.o)


all: $(OUT_EXE)
	@echo $(OUT_EXE)

test:
	@echo TODO

clean:
	@rm -rf $(BLD_D)

$(OUT_EXE): $(OUT_LIB)
	@$(CC) $(CFLAGS) $(FILES_EXE_C) -o $@ -static -L$(BLD_D) -l$(PROJ_NAME)

$(OUT_LIB): $(FILES_LIB_O)
	@$(AR) $(AFLAGS) $@ $^

$(OBJ_D)/%.o: $(SRC_LIB_D)/%.c
	@mkdir -p $(dir $(OBJ_D)/$*)
	@$(CC) $(CFLAGS) -c $< -o $@

