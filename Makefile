#primeratiogen.o: primeratiogen.cpp
#	${CXX} ${CXXFLAGS} $< -o $@
CXXFLAGS = -std=c++11

primeratiogen: primeratiogen.o Bjorklund.o
	${CXX} ${CXXFLAGS} $^ -o $@

Bjorktest: Bjorktest.o Bjorklund.o
	${CXX} ${CXXFLAGS} $^ -o $@

clean:
	rm -f *.o primeratiogen
