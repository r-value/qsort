.RECIPEPREFIX = >
CC = gcc

.PHONY: all
all : double_test integer_test

.PHONY: clean
clean :
> rm *.o
> rm *_test

double_test : qsort.o double_test.o xorshift.o
> $(CC) double_test.o qsort.o xorshift.o -o double_test

integer_test : qsort.o integer_test.o xorshift.o
> $(CC) integer_test.o qsort.o xorshift.o -o integer_test

%.c : %.o
> $(CC) -c $< -o $@ -O2
