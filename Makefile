all:
	g++ Main.cpp PA6.cpp Song.cpp SongLibrary.cpp
	./a.out
compile:
	g++ Main.cpp PA6.cpp Song.cpp SongLibrary.cpp
run:
	./a.out
debug:
	g++ -Wall -g Main.cpp PA6.cpp Song.cpp SongLibrary.cpp
	lldb a.out