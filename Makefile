BOFNAME := aadprt_s
LIBINCLUDE := -l ole32
COMINCLUDE := -I headers
# COMINCLUDE := -I ../../common
CC_x64 := x86_64-w64-mingw32-gcc
CC_x86 := i686-w64-mingw32-gcc
CC=x86_64-w64-mingw32-clang


all:
	$(CC_x64) -o $(BOFNAME).x64.o $(COMINCLUDE) -Os -c entry.c -DBOF 
	$(CC_x86) -o $(BOFNAME).x86.o $(COMINCLUDE) -Os -c entry.c -DBOF
	mv $(BOFNAME).x* ./bin/	
test:
	$(CC_x64) entry.c -g $(COMINCLUDE) $(LIBINCLUDE)  -o $(BOFNAME).x64.exe
	$(CC_x86) entry.c -g $(COMINCLUDE) $(LIBINCLUDE) -o $(BOFNAME).x86.exe
	mv $(BOFNAME).x* ./bin/	

scanbuild:
	$(CC) entry.c -o $(BOFNAME).scanbuild.exe $(COMINCLUDE) $(LIBINCLUDE)
	mv $(BOFNAME).x* ./bin/	

check:
	cppcheck --enable=all $(COMINCLUDE) --platform=win64 entry.c

clean:
	rm ./bin/*
