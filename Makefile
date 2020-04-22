CXX = g++
EXEC = main.exe
CXXFLAGS = -Wall -g -MMD -I/usr/local/lib/wx/include/gtk2-unicode-static-3.0 -I/usr/local/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -D__WXGTK__ -pthread

LDFLAGS = -L/usr/local/lib -pthread /usr/local/lib/libwx_gtk2u_xrc-3.0.a /usr/local/lib/libwx_gtk2u_qa-3.0.a /usr/local/lib/libwx_baseu_net-3.0.a /usr/local/lib/libwx_gtk2u_html-3.0.a /usr/local/lib/libwx_gtk2u_adv-3.0.a /usr/local/lib/libwx_gtk2u_core-3.0.a /usr/local/lib/libwx_baseu_xml-3.0.a /usr/local/lib/libwx_baseu-3.0.a -lgthread-2.0 -pthread -lX11 -lXxf86vm -lSM -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lfontconfig -lfreetype -lpng -ljpeg -lexpat -lwxregexu-3.0 -lwxtiff-3.0 -lz -ldl -lm

SRC=$(wildcard *.cpp)
OBJS=$(SRC:.cpp=.o)
DEPS=$(SRC:.cpp=.d)

$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS) $(LDFLAGS) 

*.o: *.cpp
	$(CXX) -c $(CXXFLAGS) $<

.PHONY: clean run all 

clean: 
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -f $(EXEC) 

run: $(EXEC)
	@echo 
	@echo ~~~ NOW RUNNING THE EXECUTABLE: ~~~
	./$(EXEC)

all:
	make clean
	make run

-include $(DEPS)
