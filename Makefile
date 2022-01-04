CC := g++

CFLAGS := -std=c++11 -g

SRCS := line_parser.cpp bet_driver.cpp

OBJS := ${SRCS:.cpp=.o} opnum.o

PROGS := ${SRCS:.cpp=} 

.PHONY: all
all: ${PROGS}

bet_driver: bet_driver.o opnum.o
	${CC} ${CFLAGS} $^ -o $@ -ll

line_parser: line_parser.o opnum.o
	${CC} ${CFLAGS} $^ -o $@ -ll

opnum.cpp: opnum.fl
	flex -o opnum.cpp opnum.fl
	
%.o: %.cpp
	${CC} ${CFLAGS} -c $<

clean:
	rm -f ${PROGS} opnum.cpp ${OBJS} *.bak *~
