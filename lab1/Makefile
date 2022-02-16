lab1: hello

hello: file_in.o file_out.hello
	g++ file_in.o file_out.o -o hello
file_in.o: file_in.cpp
	g++ -c file_in.cpp
file_out.o: file_out.cpp
	g++ -c file_out.cpp
clean:
	rm -rf *o hello
