#Static,shared,dynamic and loadable linux libraries#
##Why library is used
- each and every object file need not be stated when linking, simplifying the multiple use and sharing og software components between applications.
- the library temain seperate from the executable, reducing it's size and thus disk space used.

##Linux library types
- Static libraries(.a):library of object code which is linked with, and becomes part of the application.
- Dynamically linked shared object libraries(.so):
	- 1.Dynamically linked at run time but statically aware.The libraries must be available during compile/link phase.  (.o files are not included into the executable component but are tied to the execution)
	- 2.Dynamically loaded/unloaded and linked during execution using the dynamic linking loader system functions.
- Naming conventions : libraries are typically nams with the prefix "lib". gcc src_file.c -lm -lpthread(/usr/lib/libm.a /usr/lib/libpthread.a)

###Static libraries(.a)
- How to generate a static library(object code archive file)


    compile: cc -Wall -c test1.c test2.c

    create library : ar -cvq libtest.a test1.o test2.o

    list files in static libraries : ar -t libtest.a

    Linking the libtest.a : cc -o exe_name program.c libtest.a


Example:


    //Need to "runlib test.a after creating the library"
	//test1.c
    int add(int a, int b){return a+b;}
    
    //test2.c
    int multiple(int a, int b){return a*b;}
    
    //main.c
    #include <stdio.h>
	int add(int, int);
	int multiple(int, int);
    int main()
    {
    	int left = 2, right = 3;
		printf("add result:%d,multiple result:%d", add(left, right), multiple(left, right));
    }


###Dynamically linked "Shared object" libraries(.so)
- 1.create a shared object

code:

    gcc -Wall -fPIC -c *.c
    gcc -shared -Wl,-soname,libtest.so,1 -o libtest.so.1.0 *.o
    mv libtest.so.1.0 ~/bin/lib/
    ln -s ~/bin/libtest.so.1.0 ~/bin/libtest.so.1
    ln -s ~/bin/libtest.so.1.0 ~/bin/libtest.so 


- 2.use shared object
	gcc -L~/bin/ -ltest -Wall program.c -o program
###library info commands
- ar : list object files in archive binary(ar tf /tmp/libtest.a)
- nm : list symbols, object files(nm /tmp/libtest.a nm -D ~/bin/libtest.so)
- readelf : list symbols in shared libraries(readelf -s /tmp/libtest.so)