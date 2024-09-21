INCLUDEPATH = ../../libs/libzed
STATICLIB = ../../libs/libzed/libzed.a
STD = c++17
CC = g++

BINARY = crypto.exe

DIRS = ciphers/ ext/ libs/ parser/
SRCS = $(wildcard $(addsuffix *.cpp, $(DIRS)))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

$(BINARY): crypto.o $(OBJS) $(STATICLIB)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) -I$(INCLUDEPATH) -std=$(STD) -Wno-psabi -fPIC -o $@ -c $^

clean:
	rm -f *.exe *.o
	cd ciphers && rm -f *.exe *.o
	cd ext && rm -f *.exe *.o
	cd libs && rm -f *.exe *.o
	cd parser && rm -f *.exe *.o
	
	cd tests && make clean

remake: clean make

count:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) ! -path "./ext/*" ! -path "./tests/*" ! -name pugixml.cpp -exec wc -l {} +

libzed:
	cd ../../libs/libzed && make clean && git pull && make -j32 static

tests: $(BINARY)
	$(MAKE) -C tests/
	./tests/bin/run_tests.exe

.PHONY: clean count remake libzed
