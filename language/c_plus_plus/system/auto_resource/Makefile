CC = g++

CFLAGS = -g -fPIC -Wall -DRELEASE_C -DNDEBUG

LIB=libshingle.a
DEMO=main

INCLUDE= -I. 
LDFLAG= -L. -lshingle\
		-lpthread -lcrypto -lstdc++

all : $(LIB) $(DEMO) 

$(LIB) : dyn_resource.o repost_resource.o resource_ext.o
	ar cr $(LIB) $^
	@echo
	@echo "PWD : "$(PWD_PATH)
	@echo
	
dyn_resource.o : dyn_resource.cpp
	$(CC) $(CFLAGS) -c $^ $(INCLUDE)

repost_resource.o : repost_resource.cpp
	$(CC) $(CFLAGS) -c $^ $(INCLUDE)
	@echo

resource_ext.o : resource_ext.cpp
	$(CC) $(CFLAGS) -c $^ $(INCLUDE)
	@echo

#demo
$(DEMO) : main.o
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDE) $(LDFLAG)
	@echo

main.o : main.cpp
	$(CC) $(CFLAGS) -c $^ $(INCLUDE)
	@echo
	
.PHONY : clean
clean :
	@echo "Removing linked and compiled files......"
	rm -f  *.o *.a $(DEMO) 
