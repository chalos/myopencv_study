FLAGS := $(shell pkg-config --cflags opencv) 
FLAGS += -O3
#FLAGS += -DCOARSE
LIBS := $(shell pkg-config --libs opencv)
FILE := jpegascii

all:
	mkdir -p out
	gcc $(FLAGS) $(LIBS) $(FILE).c -o out/$(FILE).exe

clean:
	rm -rf out