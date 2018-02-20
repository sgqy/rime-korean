
OBJS += dic_entry.o
OBJS += fs_utils.o
OBJS += kr_utils.o
OBJS += str_utils.o
OBJS += main.o

LIBS += -lboost_regex

TARG = krdic

all: $(TARG) 
$(TARG): $(OBJS)
	g++ -o krdic $(OBJS) $(LIBS)
%.o: %.cpp
	g++ -O2 -std=c++11 -c -o $@ $<
clean:
	rm -rf $(OBJS) $(TARG) 
