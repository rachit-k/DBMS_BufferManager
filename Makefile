sampleobjects = buffer_manager.o file_manager.o sample_run.o
binaryObjects = buffer_manager.o file_manager.o binary_search.o
bintxtObjects = buffer_manager.o file_manager.o bin_txt.o

sample_run : $(sampleobjects)
	     g++ -std=c++11 -o sample_run $(sampleobjects)

binary_search : $(binaryObjects)
		 g++ -std=c++11 -o binary_search $(binaryObjects)

bin_txt : $(bintxtObjects)
		 g++ -std=c++11 -o bin_txt $(bintxtObjects)

sample_run.o : sample_run.cpp
	g++ -std=c++11 -c sample_run.cpp

binary_search.o : binary_search.cpp
	g++ -std=c++11 -c binary_search.cpp

bin_txt.o : bin_txt.cpp
	g++ -std=c++11 -c bin_txt.cpp

buffer_manager.o : buffer_manager.cpp
	g++ -std=c++11 -c buffer_manager.cpp

file_manager.o : file_manager.cpp
	g++ -std=c++11 -c file_manager.cpp

clean :
	rm -f *.o
	rm -f sample_run binary_search bin_txt