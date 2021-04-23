sampleobjects = buffer_manager.o file_manager.o sample_run.o
linearObjects = buffer_manager.o file_manager.o linear_search.o
binaryObjects = buffer_manager.o file_manager.o binary_search.o
deletionObjects = buffer_manager.o file_manager.o deletion.o
join1Objects = buffer_manager.o file_manager.o join1.o
join2Objects = buffer_manager.o file_manager.o join2.o
bintxtObjects = buffer_manager.o file_manager.o bin_txt.o

sample_run : $(sampleobjects)
	     g++ -std=c++11 -o sample_run $(sampleobjects)

linearsearch : $(linearObjects)
		 g++ -std=c++11 -o linearsearch $(linearObjects)

binarysearch : $(binaryObjects)
		 g++ -std=c++11 -o binarysearch $(binaryObjects)

deletion : $(deletionObjects)
		 g++ -std=c++11 -o deletion $(deletionObjects)

join1 : $(join1Objects)
		 g++ -std=c++11 -o join1 $(join1Objects)

join2 : $(join2Objects)
		 g++ -std=c++11 -o join2 $(join2Objects)
		 
bin_txt : $(bintxtObjects)
		 g++ -std=c++11 -o bin_txt $(bintxtObjects)

sample_run.o : sample_run.cpp
	g++ -std=c++11 -c sample_run.cpp

join1.o : join1.cpp
	g++ -std=c++11 -c join1.cpp

join2.o : join2.cpp
	g++ -std=c++11 -c join2.cpp

linear_search.o : linear_search.cpp
	g++ -std=c++11 -c linear_search.cpp

binary_search.o : binary_search.cpp
	g++ -std=c++11 -c binary_search.cpp

deletion.o : deletion.cpp
	g++ -std=c++11 -c deletion.cpp

bin_txt.o : bin_txt.cpp
	g++ -std=c++11 -c bin_txt.cpp

buffer_manager.o : buffer_manager.cpp
	g++ -std=c++11 -c buffer_manager.cpp

file_manager.o : file_manager.cpp
	g++ -std=c++11 -c file_manager.cpp

clean :
	rm -f *.o
	rm -f sample_run linearsearch binarysearch deletion join1 join2 bin_txt