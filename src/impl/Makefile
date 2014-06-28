### Variables definitions

PREFIX	= /usr/local
BINDIR	= $(PREFIX)/bin
MANDIR	= $(PREFIX)/man/man1

BUILD	= build
OUT	= out
SRC	= src

NAME	= pl
GXX	= g++
OPTS	= -Wall -pedantic -std=c++11
FILES	:= $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(wildcard $(SRC)/*.cpp))

### Primary targets

# Build the application
build: .folders $(FILES)
	$(GXX) $(OPTS) $(FILES) -o $(OUT)/$(NAME)

# Remove all outputs
clean:
	rm -rf $(BUILD) $(OUT)

# Generate the documentation
doc:
	doxygen

# Install the software
install: $(BUILD)
	sudo install -g 0 -o 0 -m 0755 $(OUT)/$(NAME) $(BINDIR)
	sudo install -g 0 -o 0 -m 0644 $(NAME).1 $(MANDIR) && sudo gzip -f $(MANDIR)/$(NAME).1

# Test the application
test: $(BUILD)
	sh test.sh

# Uninstall the software
uninstall:
	sudo rm -f $(BINDIR)/$(NAME) $(MANDIR)/$(NAME).1.gz

### Auxiliary targets

# Create output directories
.folders:
	mkdir -p $(BUILD) $(OUT)

# Compile a '.cpp' file
$(BUILD)/%.o: $(SRC)/%.cpp
	$(GXX) $(OPTS) -c -MD -MP $< -o $@

.PHONY: build clean doc .folders test install uninstall
