output: LinkedList.o
	g++ LinkedList.o -o output
LinkedList.o: LinkedList.c
	g++ -c LinkedList.c
clean:
	rm *.0 output