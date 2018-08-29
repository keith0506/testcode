CC=g++
INCLUDES=-I.
CFLAGS:=$(INCLUDES) $(PFLAG) -Wall -Wno-invalid-offsetof 

SRCS=

outlib=../bin/xx.a
objects=$(SRCS:.cpp=.o)

skiplist :
	@$(CC) skiplist.cpp -o skip

timerring :
	@$(CC) timerQ.cpp timer_item.cpp ring.cpp -o timerQ

all : $(objects)
	@rm -f ${outlib}
	@ar cqs ${outlib} ${objects}

$(objects): %.o: %.cpp
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -f *.o ${outlib}
