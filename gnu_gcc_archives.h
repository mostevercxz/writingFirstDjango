// for the sake of remembering some gnu common options

//gcc compile part
1. remove comments from c++ code(http://stackoverflow.com/questions/2394017/remove-comments-from-c-c-code)
	gcc -fpreprocessed -dD -E test.c
2.	generate assembly language file main.s	
	gcc -O2 -S -c foo.c
3.	generate assembly language file with source code in main.c
	gcc -c -g -Wa,-a,-ad [other GCC options] foo.c > foo.lst
	gcc -c -g -Wa,-a,-ad  foo.c > foo.lst
4.	How to translate assembly to binary??(http://stackoverflow.com/questions/3826692/how-do-i-translate-assembly-to-binary)
	learn CPU instructions
	
------------------------
	gcc compile options	
------------------------
1. _GNU_SOURCE. 
	If you define this macro, everything is included: ISO C89, ISO C99, POSIX.1, POSIX.2, BSD, SVID, X/Open, LFS, and GNU extensions. In the cases where POSIX.1 conflicts with BSD, the POSIX definitions take precedence.
	The _GNU_SOURCE will most likely limits source code usage to GNU/Linux and GNU/Hard systems, unless additional work is done to address the non-portability of such functionality on other platforms.
	Feel free to use such extensions, if my development is locked into GNU/Linux and GNU/Hard. Avoid such usages dot any apllications that may be deployed on other Unix and Unix-like operating systems.

2. _REENTRANT(_THREAD_SAFE)
	If I define one of those macros, reentrant versions of several functions get declared. Some of the functions are specified in POSIX.1c but many others are onlt avialable on a few other systems or are unique to the GNU C Library. The problem is the delay in the standardization of the thread safe C library interface.

3. -Wall
	gcc -Wall enables all compiler's warning messages. This option should always be used, in order to generate better code. They do not prevent the compliation of my programs, unless -Werror is specified.

4. -Werror
	turn all warning into errors!!

5. -Bstatic
	tells the linker to use the static versions for all default libraries like libc etc...

6. -g3(-g level)
	Request debugging info anf also use level to specify how much info.THe default level is 2.
	Level 0 produces no debug info at all.
	Level 1 produces minimal info, enough for making breaktraces in parts of the program. This includes descriptions of functions and external variables, but no information about local variables and no line numbers.
	Level 3 includes extra information, such as all the macro definitions present in the program. Some debuggers support macro expansion when you use -g3.

7. -rdynamic
	Pass the flag -export-dynamic to the ELF linker, on targets that support it. This instructs the linker to add all symbols, not only used ones, to the dynamic symbol table. This option is needed for some uses of dlopen or to allow obtaining backtraces from within a program. 

8. -fPIC
	suitable for dynamic linking and avoiding any limit on the size of the global offset table. When this flag is set, the macros __pic__ and __PIC__ are defined to 2.

9. -c
	Compile or assemble the source files, but do not link.

10. -o ofile
	Place output in file ofile.

11. -Idir
	Add the directory dir to the head of the list of directories to be searched for header files.
	If you use more than one -I option, the directories are scanned in left-to-right order; the standard system directories come after.
	If a standard system include directory, or a directory specified with -isystem, is also specified with -I, the -I option will be ignored. 
	The directory will still be searched but as a system directory at its normal position in the system include chain. 
	This is to ensure that GCC's procedure to fix buggy system headers and the ordering for the include_next directive are not inadvertently changed. 
	If you really need to change the search order for system directories, use the -nostdinc and/or -isystem options.

12. What is the difference between 'xml2-config --cflags' and 'xml2-config --libs'?? what does the latter option mean??

13. keyword "view macro expansion"
	g++ -c test.cpp -I. -I../ `mysql_config --cflags` `xml2-config --cflags` -E -o test.i
	
14. Remove comments from c/c++ code
	gcc -fpreprocessed -dD -E test.c

	eit makefile, make -g3 test.cpp -o test
	macro expand/exp
15.	gcc -O1 -S code_example.c
	gcc -O1 -o program code_example.o main.c
	ATT assembly-code formats VS Intel assembly-code formats
	gcc -O1 -S -masm=intel code_example.c
	
	sizeof C data types in IA32:
	char b
	short w
	int,long int l
	char* l
	float s
	double l
	long double t
	eax
	ecx
	edx
	ebx
	esi
	edi
	esp,stack pointer
	ebp,frame pointer
16.	Operand specifies : the different operand possibilities can be classified into three types.
	1. immediate, is for constant values. a '$' followed by an integer. Form:$Immediate, Value:Immediate
	2. registers, denotes the contents of one of the registers. Form: Ei, Value: R[Ei]
	3. memory reference, Form: Imm(Eb, Ei, s), Value: M[Imm + R[Eb] + R[Ei] * s], s must be 1,2,4,8

17.	Data movement Instructions
	mov s,d(movb, movw, movl,byte,word,double word)
	
	movs s,d(move with sign extension)
	movsbw sign-extended byte to word
	movsbl sign-extended byte to double word
	movswl sign-extended word to double word
	
	movz s,d(move with zero extension)
	movzbw, movzbl, movzwl
	
	pushl S(R[%esp] <-- R[%esp] - 4, M[R[%esp]] <-- S) push double word
	popl D(D <-- M[R[%esp]]; R[%esp] <-- R[%esp] + 4) pop double word
	
//gdb debugging tips

------------------------
 gbd debugging tips
------------------------
1. gdb show all characters other than "..."
set print elements 0

2. How to set breakpoints on all functions in a file??(http://sourceware.org/gdb/download/onlinedocs/gdb/Set-Breaks.html#Set-Breaks)
(stackoverflow上的方法还没试过http://stackoverflow.com/questions/475283/using-gdb-stop-the-program-when-it-is-using-any-function-from-file-x)
rbreak fileName.cpp:.
rbreak fileName.cpp:<regex>
(If I used the commands above, then run "gdb Server", it prompts "core dumped")我一用就core dumped...
So, Use the commands below :
rbreak fileName.cpp:.
info b
then copy all the breakpoints info to a notepad++, then replace 'at fileName.cpp:401' to none, then copy it to gdb.
将info b的输出拷贝到notepad++里面，然后将后面的部分替换掉即可

3. All-stop mode, You might even find your program stopped in another thread after continuing or even single-stepping. 
This happens whenever some other thread runs into a breakpoint, a signal, or an exception before the first thread completes whatever you requested.
You can modify gdb's default behavior by locking the OS scheduler to allow only a single thread to run.
set scheduler-locking on

4. Debuggin gcc compile time(http://stackoverflow.com/questions/6390532/debugging-gcc-compile-times)
g++ some_file.cc -ftime-report will give you a rough estimate of time spent in different compiling phase.(templates, name lookup and parsing).
STeven Watanabe has proposed a template profiler , available in boost sandbox that helps getting the number of potential instantiation of anything in a .cc

5. How to check the compile time of phase??  How to capture all of my compiler's output to a file??
-Q Makes the compiler print out each function name as it is compiled, and print some statistics about each pass when it finishes.
make &> results.txt
make > results.txt 2>&1

-------------------------------
	gdb tricks I should know
-------------------------------
1. break where if condition
2. command 1
>print addr
>print len
>end
3. gdb --args executeable_program --deep-dish --toppings=pepperoni(run program with parameters)
gdb executeable_program
run --deep-dish --toppings=pepperoni
4. Finding source files

gdb's directory command to add the source directory to my source path:
apt-get source coreutils
sudo apt-get install coreutils-dbgsym
gdb /bin/ls
directory ~/src/coreutils-7.4/src/

Sometimes, however, debug symbols end up with absolute paths, such as the kernel's. In that case, I can use set substitute-path to tell gdb how to translate paths
apt-get source linux-image-2.6.32-25-generic
sudo apt-get install linux-image-2.6.32-25-generic-dbgsym
gdb /usr/lib/debug/boot/vmlinux-2.6.32-25-generic
set substitute-path /build/buildd/linux-2.6.32 /home/nelhage/src/linux-2.6.32/

5. Debugging macros, using gcc -ggdb3 test.c -o test
info macro task_is_stopped_or_traced
macro expand task_is_stopped_or_traced(init_task)
Gdb actually knows which contexts macros are and aren't visible, so when you have the program stopped inside some function, you can only access macros visible at that point

6. gdb setting variables
(gdb)set $tempVar=(temp_var+abc) * cde
(gdb)break 660 if $tempVar>10000

7. register variables
$sp for the stack pointer, $pc for the program coounter
Combined with a knowledge of your machine's calling convention, for example, you can use these to inspect function parameters:
(gdb) break write if $rsi == 2
will break on all writes to stderr on amd64, where the $rsi register is used to pass the first parameter.

8. the x command(x/i is invaluable as a quick way to disassemble memory:)
x/FMT address
FMT controls how the memory should be dumped, and consists of (up to) three components:
A numeric COUNT of how many elements to dump
A single-character FORMAT, indicating how to interpret and display each element
A single-character SIZE, indicating the size of each element to display.

x displays COUNT elements of length SIZE each, starting from ADDRESS, formatting them according to the FORMAT.
There are many valid "format" arguments; help x in gdb will give you the full list, 
x/x displays elements in hex, x/d displays them as signed decimals, x/c displays characters, 
x/i disassembles memory as instructions, and x/s interprets memory as C strings.
The SIZE argument can be one of: b, h, w, and g, for one-, two-, four-, and eight-byte blocks, respectively.

9. the @ symbol
p *&a[0]@5	

struct argp_option{
	const char *name;	//the log name for this option, corresponding to the long option '--name'
	int key;			//The integer key provided by the current option to the option parser.
						//If key has a value that is a printable ascii char, is also specifies a short option '-char'
						// , where char is the ascii char with the code key.
	const char *arg;	// If non-zero, this is the name of an argument associated with this option,
						// which must be provided ('--name=value' or '-char value')
	int flags;			//Flags associated with this option
	const char *dic;	// A documentation string for this option
	int group;			// In a long help message, options are sorted alphabetically within each group, 
						// and the groups presented in the order 0, 1, 2, бн, n, -m, бн, -2, -1.
};

arrays of length zero
struct zero_length_struct
{
	int length;
	int data[0];
};
struct zero_length_struct *p = (zero_length_struct *)malloc(sizeof(zero_length_struct) + 4 * 3);
int array[] = {1,2,3};
strncpy(p->data, array, 12);

//2015-03-04
How to get the timezone of the linux system??
1.set the system time zone :
/etc/sysconfig/clock
/etc/profile
2. #include <time.h>
#include <iostream>
int main()
{
	tzset();
	std::cout << "timezone is" << timezone << std::endl;
}