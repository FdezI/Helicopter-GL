
EJECUTABLE= helicopter

MODULOS=  $(EJECUTABLE).o estructuras.o practica2.o $

#  CFLAGS= Parametros para el compilador de C/C++       
CFLAGS=  -g -cpp -DXWINDOWS -I/usr/include -I     

#  LDFLAGS= Parametros para el linkador
LDFLAGS=   -L/usr/lib  

#  LIBS= librerias a usar.
LIBS=    -lglut -lGLU  -lX11 -lXext  -lc -lm -lGL

#  CC= orden de UNIX que invoca al compilador de C/C++ de GNU
CC=        g++

# archivo ejecutable a generar
$(EJECUTABLE): $(MODULOS)	
	$(CC)  -o$(EJECUTABLE) $(LDFLAGS) $(MODULOS)  $(LIBS)   

