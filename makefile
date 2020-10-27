CC = gcc

TARGET = main
MAIN = $(addsuffix .o, $(TARGET))
OBJ = src/stats/stats.o src/menu/menu.o src/patricia/patricia.o src/tst/tst.o src/word/word.o src/main.o

root = "main"

.PHONY: all clean

all: $(TARGET) clean

ifeq ($(OS), Windows_NT)
clean:
	del $(OBJ)
else
clean:
	rm -rf $(OBJ)
endif

$(OBJ) : %.o : %.c
	$(CC) -c $< -o $@


$(TARGET): % : $(OBJ)
	$(CC) $(OBJ) -o $@
