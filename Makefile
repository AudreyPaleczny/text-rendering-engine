CXX = g++ # C++
CC = gcc # C compiler 
CXXFLAGS = -Wall - Wextra -std=c++11 -pedantic -I./include $(shell pkg-config --cflags glfw3) # extra options you want to give to your compiler b4 compiling it
CFLAGS = -I./include # I means include & -I is for header files 
LIBS = $(shell pkg-config --libs glfw3) # libraries