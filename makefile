CC       = gcc
CFLAGS   = -O3 -Wall
LIBS      = -lXi -lXmu -lglut -lGLEW -lGLU -lm -lGL
OBJDIR   = ./
OBJS     = $(OBJDIR)/initShader.o $(OBJDIR)/mylib.o

lab04: project1.c $(OBJS)
	$(CC) -o project1 project1.c $(OBJS) $(CFLAGS) $(LIBS)

mylib.o: mylib.h mylib.c
	        gcc -c mylib.c

initShader.o: initShader.c initShader.h
							gcc -c initShader.c


$(OBJDIR)/%.o: %.c %.h
	$(CC) -c @< -o $@ $(CFLAGS)
