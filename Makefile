INCLUDE = /home/jugyou/common/NI_USB-6501/include
LIBS    = /home/jugyou/common/NI_USB-6501/lib
CFLAGS  = -g

.c.o:
	gcc $(CFLAGS) -c $< -I$(INCLUDE)

BIN =	start\



ALL: $(BIN)


clean:
	rm -f *.o
	rm -f $(BIN)


start:		start.o \
		$(LIBS)/niusb6501.o
	gcc -o $@ $^ -L$(LIBS) -lusb
