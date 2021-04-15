sampleobjects = buffer_manager.o file_manager.o sample_run.o
linearObjects = buffer_manager.o file_manager.o linear_search.o
binaryObjects = buffer_manager.o file_manager.o binary_search.o
join1Objects = buffer_manager.o file_manager.o join1.o
bintxtObjects = buffer_manager.o file_manager.o bin_txt.o

sample_run : $(sampleobjects)
	     g++ -std=c++11 -o sample_run $(sampleobjects)

linear_search : $(linearObjects)
		 g++ -std=c++11 -o linear_search $(linearObjects)

binary_search : $(binaryObjects)
		 g++ -std=c++11 -o binary_search $(binaryObjects)

join1 : $(join1Objects)
		 g++ -std=c++11 -o join1 $(join1Objects)
		 
bin_txt : $(bintxtObjects)
		 g++ -std=c++11 -o bin_txt $(bintxtObjects)

sample_run.o : sample_run.cpp
	g++ -std=c++11 -c sample_run.cpp

join1.o : join1.cpp
	g++ -std=c++11 -c join1.cpp

linear_search.o : linear_search.cpp
	g++ -std=c++11 -c linear_search.cpp

bin_txt.o : bin_txt.cpp
	g++ -std=c++11 -c bin_txt.cpp

buffer_manager.o : buffer_manager.cpp
	g++ -std=c++11 -c buffer_manager.cpp

file_manager.o : file_manager.cpp
	g++ -std=c++11 -c file_manager.cpp

clean :
	rm -f *.o
	rm -f sample_run linear_search binary_search bin_txt