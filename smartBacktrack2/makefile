# Makefile2
.PHONY: all
all: a.out 
cc = g++ -std=c++11 -Wall -g

a.out: main.o classes.o func.o backtrack.o greedyAppend.o circularSifting.o
	$(cc) main.o classes.o func.o backtrack.o greedyAppend.o circularSifting.o

main.o: main.cc class_head.h h_head.h
	$(cc) -c main.cc
classes.o: classes.cc class_head.h h_head.h
	$(cc) -c classes.cc
func.o: func.cc class_head.h h_head.h
	$(cc) -c func.cc
backtrack.o: backtrack.cc class_head.h h_head.h
	$(cc) -c backtrack.cc
greedyAppend.o: greedyAppend.cc class_head.h h_head.h
	$(cc) -c greedyAppend.cc
circularSifting.o: circularSifting.cc class_head.h h_head.h
	$(cc) -c circularSifting.cc

.PHONY:clean
clean:
	rm a.out main.o classes.o func.o backtrack.o greedyAppend.o circularSifting.o

