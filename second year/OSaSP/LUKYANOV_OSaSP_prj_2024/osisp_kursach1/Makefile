#makefile
CC=gcc
CFLAGS=-W -Wall -Wno-unused-parameter -Wno-unused-variable -Werror -std=c11 -O3 -pedantic -lncurses -lform  
SHELL:=bash
SUBDIRS=./src/executor/ ./src/gui ./src/utility
COMPILE_LIST=./build/*.o

.PHONY:clean,pack, $(SUBDIRS)


all: ./build/main ./build/parser 

./build/*.o: $(SUBDIRS)

$(SUBDIRS):
	mkdir -p ./build
	$(MAKE) -C $@
./build/main: ./src/main.c ./src/config.h ./build/*.o  Makefile
	$(CC) $(CFLAGS) $(COMPILE_LIST) ./src/main.c  -o ./build/main
./build/parser: ./src/parser/parser.c ./src/parser/parser.h
	$(CC) $(CFLAGS) ./src/parser/parser.c -o ./build/parser
clean:
	 -cd ./build && rm -f *
pack: clean
	-rmdir -p build
	pwd | xargs basename | xargs -I{} tar -czvf ../Лукьянов\ Е.О.\ {}.tar.gz ../{} --transform 's,^,Лукьянов Е.О./,'
