#primeratiogen.o: primeratiogen.cpp
#	${CXX} ${CXXFLAGS} $< -o $@

primeratiogen: primeratiogen.o
	c++ ${CXXFLAGS} $< -o $@
clean:
	rm -f *.o primeratiogen
