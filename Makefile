
DIR_BLD = bld
DIR_INC = -I $(shell pg_config --includedir)
DIR_LIB = src
DIR_TEST = test

SRC_LIB = $(sort $(shell find $(DIR_LIB)/ -type f -name '*.c'))
SRC_TEST = $(sort $(wildcard $(DIR_TEST)/*.c))

OBJ_LIB = $(patsubst $(DIR_LIB)/%.c, $(DIR_BLD)/%.o, $(SRC_LIB))

BIN_LIB = bld/liblasarus.so
BIN_TEST = $(DIR_BLD)/ag-tests




CC = ccache cc
CFLAGS = -fPIC -g -Wall -Wextra $(DIR_INC)
LDFLAGS = -shared -L $(shell pg_config --libdir) -lpq -lfcgi





$(BIN_LIB): $(OBJ_LIB) | $(DIR_BLD)
	$(LINK.c) $^ -o $@

$(BIN_TEST): $(SRC_TEST) $(BIN_LIB) | $(DIR_BLD)
	$(CC) $(CFLAGS) $^ -o $@

$(DIR_BLD)/%.o: $(DIR_LIB)/%.c | $(DIR_BLD)
	$(COMPILE.c) $^ -o $@

$(DIR_BLD):
	mkdir -p $@




all: $(BIN_LIB)

test: $(BIN_TEST)
	./$(BIN_TEST)

check: $(BIN_TEST)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --log-file=$(BIN_TEST).vglog         \
		$(BIN_TEST)
	tail $(BIN_TEST).vglog

clean:
	rm -rfv $(DIR_BLD) $(DOC_TMP)


.PHONY: all doc clean

