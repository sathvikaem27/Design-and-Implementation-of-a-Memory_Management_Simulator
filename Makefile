all:
	g++ main.cpp allocator.cpp buddy.cpp cache.cpp vm.cpp -o memsim

clean:
	del memsim.exe
