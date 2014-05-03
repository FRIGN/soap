# soap - simple xdg-open replacement with fallback

include config.mk

SRC = soap.c
OBJ = ${SRC:.c=.o}

all: options soap

options:
	@echo soap build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

soap: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f soap ${OBJ}

install: all
	@test -f /usr/bin/xdg-open_ || (echo backing up to /usr/bin/xdg-open_; mv /usr/bin/xdg-open /usr/bin/xdg-open_)
	@echo installing new xdg-open
	@cp -f soap /usr/bin/xdg-open
	@chmod 755 /usr/bin/xdg-open

uninstall:
	@echo moving xdg-open_ back into place
	@(test -f /usr/bin/xdg-open_ && mv /usr/bin/xdg-open_ /usr/bin/xdg-open) || echo ERROR: xdg-open_ does not exist
