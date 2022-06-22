CLARIO_FLAGS := $(shell pkg-config cairo --libs --cflags)
X11_LDFLAGS := -lX11 -lXcomposite -lXfixes
BIN := /usr/local/bin
MANPATH := $(shell manpath | cut -d : -f1)/man1/

yllw: yllw.c
	$(CC) $^ -o $@ $(X11_LDFLAGS) $(CLARIO_FLAGS)

install: yllw
	install yllw $(BIN)
	install -m 644 yllw.1 $(MANPATH)

clean:
	rm yllw
