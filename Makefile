CXX = g++
RM = rm
CXXFLAGS = -I. -Wall -Wextra -std=c++14
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

PROJECT = app
PROJECT_HEADERS =
PROJECT_SOURCES = main.cpp
PROJECT_OBJECTS = $(subst .cpp,.o,$(PROJECT_SOURCES))

all: $(PROJECT)

$(PROJECT): $(PROJECT_OBJECTS)
	$(CXX) -o $(PROJECT) $(PROJECT_OBJECTS) $(CXXFLAGS) $(LDFLAGS)

$(PROJECT_OBJECTS): $(PROJECT_SOURCES) $(PROJECT_HEADERS)
	$(CXX) -c $(PROJECT_SOURCES) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(PROJECT_OBJECTS)
	$(RM) $(PROJECT)

.PHONY: clean all
