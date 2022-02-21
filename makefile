all: $(patsubst %.cpp, %, $(wildcard *.cpp))

%.out: %.cpp makefile
	g++ -std=c++11 -g $<  -o $@ -std=c++0x

clean:
	find . -type f ! -iname "*.cpp" ! -iname "makefile" ! -iname "README" ! -iname "*.h" -delete
