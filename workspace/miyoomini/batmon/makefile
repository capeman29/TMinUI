ifeq (,$(CROSS_COMPILE))
$(error missing CROSS_COMPILE for this toolchain)
endif

TARGET = batmon
PRODUCT = $(TARGET).elf

CC = $(CROSS_COMPILE)gcc
CFLAGS   = $(MYARCH)
LDFLAGS	 = -lSDL -lSDL_image -lpthread

all:
	$(CC) $(TARGET).c -o $(PRODUCT) $(CFLAGS) $(LDFLAGS)
clean:
	rm -f $(PRODUCT)