CLARIO_FLAGS := $(shell pkg-config cairo --libs --cflags)
X11_LDFLAGS := -lX11 -lXcomposite -lXfixes
BIN := /usr/local/bin

yllw: yllw.c
	$(CC) $^ -o $@ $(X11_LDFLAGS) $(CLARIO_FLAGS)

install: yllw
	install yllw $(BIN)

clean:
	rm yllw
