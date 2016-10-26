COMPILER  = g++
CFLAGS    = -std=c++11 -pthread -g -MMD -MP -Wall -Winit-self -Wno-missing-field-initializers
LDFLAGS   = -lusb -pthread
LIBS      = /home/jugyou/common/NI_USB-6501/lib/niusb6501.o
INCLUDE   = -I./include 
TARGET    = ./$(shell basename `readlink -f .`)
SRCDIR    = ./source
SOURCES   = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR    = ./obj
OBJECTS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	-mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -f $(OBJECTS) $(TARGET)
