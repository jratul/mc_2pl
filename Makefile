#run : main.o linked_list.o
#	g++ -o run main.o linked_list.o
#main.o : headers/linked_list.h main.cpp
#	g++ -c main.cpp
#linked_list.o : headers/linked_list.h linked_list.cpp
#	g++ -c linked_list.cpp

run : main.o record.o linked_list.o util.o thread.o rwlock.o
	g++ -o run util.o main.o record.o linked_list.o  thread.o rwlock.o -g -lpthread

main.o : headers/record.h headers/thread.h headers/util.h main.cpp
	g++ -c main.cpp

record.o : headers/record.h headers/linked_list.h record.cpp
	g++ -c record.cpp

linked_list.o : headers/linked_list.h linked_list.cpp
	g++ -c linked_list.cpp

util.o : headers/record.h headers/util.h util.cpp
	g++ -c util.cpp

thread.o : headers/thread.h headers/rwlock.h headers/util.h thread.cpp
	g++ -c thread.cpp

rwlock.h : headers/rwlock.h headers/util.h rwlock.cpp
	g++ -c rwlock.cpp

clean :
	-rm *.o run
