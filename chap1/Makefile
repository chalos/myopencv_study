
FLAGS := $(shell pkg-config --cflags opencv)
LIBS := $(shell pkg-config --libs opencv)

all:
	mkdir -p out
	gcc $(FLAGS) $(LIBS) ${FILE} -o out/$(FILE).exe

clean:
	rm -rf out