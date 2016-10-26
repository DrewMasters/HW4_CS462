all: matrix_multiply matrix_writer matrix_reader

libgemm.o: libgemm.c libgemm.h
	oshcc -O -c libgemm.c

libgemm.a: libgemm.o
	ar rcs libgemm.a libgemm.o

matrix_multiply: matrix_multiply.o libgemm.a
	oshcc -o matrix_multiply matrix_multiply.o -lm -L. -lgemm 

matrix_multiply.o: matrix_multiply.c 
	oshcc -O -c matrix_multiply.c

matrix_writer: matrix_writer.c
	gcc -o matrix_writer matrix_writer.c

matrix_reader: matrix_reader.c
	gcc -o matrix_reader matrix_reader.c

clean:
	$(RM) matrix_writer matrix_multiply matrix_test_multiply matrix_reader *.o *.a
