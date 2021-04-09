sampleobjects = buffer_manager.o file_manager.o sample_run.o
binaryObjects = buffer_manager.o file_manager.o binary_search.o

sample_run : $(sampleobjects)
	     g++ -std=c++11 -o sample_run $(sampleobjects)

binary_search : $(binaryObjects)
		 g++ -std=c++11 -o binary_search $(binaryObjects)

sample_run.o : sample_run.cpp
	g++ -std=c++11 -c sample_run.cpp

binary_search.o : binary_search.cpp
	g++ -std=c++11 -c binary_search.cpp

buffer_manager.o : buffer_manager.cpp
	g++ -std=c++11 -c buffer_manager.cpp

file_manager.o : file_manager.cpp
	g++ -std=c++11 -c file_manager.cpp

clean :
	rm -f *.o
	rm -f sample_run
