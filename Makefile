#run : main.o linked_list.o
#	g++ -o run main.o linked_list.o
#main.o : headers/linked_list.h main.cpp
#	g++ -c main.cpp
#linked_list.o : headers/linked_list.h linked_list.cpp
#	g++ -c linked_list.cpp

run : main.o
	g++ -o run main.o

main.o : main.cpp
	g++ -c main.cpp

clean :
	-rm *.o run
