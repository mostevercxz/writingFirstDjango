// for the sake of remembering some gnu common options

//What does the FD_CLOEXEC fcntl() flag do?
if (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1) {
}
It sets the close-on-exec flag for the file descriptor, which causes the file descriptor to be automatically (and atomically) closed when any of the exec-family functions succeed.

It also tests the return value to see if the operation failed, which is rather useless if the file descriptor is valid, since there is no condition under which this operation should fail on a valid file descriptor.

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
	
---
waf notes
1. process flow
./waf
waf_entry_point(current_dir, version, wafdir)

---
---
TCP_NODELAY and small buffer Writes
(https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_MRG/1.2/html/Realtime_Tuning_Guide/sect-Realtime_Tuning_Guide-Application_Tuning_and_Deployment-TCP_NODELAY_and_Small_Buffer_Writes.html)
As discussed briefly in Transmission Control Protocol (TCP), 
by default TCP uses Nagle's algorithm to collect small outgoing packets to send all at once. 
This can have a detrimental effect on latency.
Applications that require lower latency on every packet sent should be run on sockets with TCP_NODELAY enabled. It can be enabled through the setsockopt command with the sockets API:
int one = 1;
setsockopt(descriptor, SOL_TCP, TCP_NODELAY, &one, sizeof(one));

TCP_NODELAY has nothing to do with O_NDELAY;
TCP_NODELAY disables the Nagle algorithm, while O_NDELAY puts the file descriptor into "no delay" mode.

Non-blocking io mode:
int flags = fcntl(fd, F_GETFL, 0);
fcntl(fd, F_SETFL, flags | O_NONBLOCK);
The O_NONBLOCK doesn't provide any notification to the user process that a fd is ready for read(2) or write(2) -- 
instead, it changes the behavior of read(2) and write(2) and similar calls to return immediately if the file descriptor isn't ready for reading or writing. 
O_NONBLOCK is typically used in conjunction with select(2) or poll(2) or similar calls to guarantee that the main loop of a client or server won't block on one specific peer, and thus starve all its peers.

The O_NDELAY flag tells UNIX that this program doesn't care what state the DCD signal line is in - 
whether the other end of the port is up and running. 
If you do not specify this flag, your process will be put to sleep until the DCD signal line is the space voltage.
---

---
Basic thread management
1.thread creation
Any thread can create child thread at any time.
2.thread termination
If the parent thread terminates, all of its child threads terminate as well.
3.thread join
A thread can execute a thread join to wait until the other thread terminates. Thread join is for a parent to join with one of its child threads.
4.thread yield
When a thread executes a thread yield, the executing thread is suspended and the CPU is given to some other runnable thread.
---

------------------------
	dynamic librarys
------------------------	
protobuf/bin/protoc: /usr/lib64/libstdc++.so.6: version GLIBCXX_3.4.20 not found
strings /usr/lib64/libstdc++.so.6| grep -i glibc
	
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
18.	pushl $0xFF
	movw %dx, (%eax)
	movb $0xF, (%bl) ?? Address is a double word, bl is a byte.
	
19. /usr/bin/ld: cannot find : No such file or directory
	g++ -g a.o b.o c.o -Wl, -bdynamic
	comma should not have space between the content after it.(冒号后面不加空格)
	g++ -g a.o b.o c.o -Wl,-bdynamic(OK)
	
	
//gdb debugging tips
------------------------
 gbd installing tips
------------------------
(ftp://ftp.gnu.org/old-gnu/Manuals/gdb/html_chapter/gdb_27.html)
su
tar -zxvf xxx.tar.gz -C /tmp/gdb
cd /tmp/gdb
./configure --with-python=yes --exec-prefix=/usr/local/bin
sudo apt-get install python2.6-dev(rpm -ivn /mnt/iso/Packages/python-develxxx.rpm)要装python,否则error检查不通过的
(Error in sourced command file:
Python scripting is not supported in this copy of GDB, use ./configure --with-python=yes)
make 
make install
rm -rf gdbxxx
rm -rf xxx.tar.gz
执行script的速度受到很大影响

-----------------------
Debugging libc.so.2-12.so
0. Where to download glibc ?
http://ftp.gnu.org/gnu/glibc/
1. What is the difference between libc and glibc ??



------------------------
 gbd debugging tips
------------------------
1. gdb show all characters other than "..."
set print elements 0
set logging file xml2015
set logging on
set logging off

2. How to set breakpoints on all functions in a file??(http://sourceware.org/gdb/download/onlinedocs/gdb/Set-Breaks.html#Set-Breaks)
rbreak fileName:. 提示can't find member of namespace class (Note leading single quote)
原因是gdb version >= 7.3才可以,我的是7.2版本的
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

6.	info registers
info registers rax
i r
7.	help layout
	close layout window:ctrl + x + a
8.	Disable warnings being treated as errors
You need to remove -Werror from CFLAGS, CPPFLAGS etc.; these are usually set in Makefile's or build scripts.
9.	自从装了valgrind之后,编译的时候,会多出很多错误出来.会帮助我查出很多内存溢出的错误,但是也很烦人
比如
daemon(1,1)
这条语句,error:ignoring return value of 'int daemon(int,int)', declared with attribute warn_unused_result
这是为什么呢？
10.	How to use my own glibc built from source code?(glibc debug symbols)
	10.1	build,The Glibc documentation recommends building Glibc outside of the source directory in a dedicated build directory.
	tar -zxvf glibc.tar.gz -C /home/userName/develop/
	mkdir -p /home/userName/develop/glibc-build
	cd /home/userName/develop/glibc-build
	vim ../glibc-2.21/configure, CXXFLAGS="-g -O2" to CXXFLAGS="-g"
	../glibc-2.21/configure --prefix=/home/userName/bin/glibc --enable-kernel=2.6.32 libc_cv_forced_unwind=yes libc_cv_ctors_header=yes libc_cv_c_cleanup=yes
	make(--enable-kernel=2.6.32,This tells Glibc to compile the library with support for 2.6.32 and later Linux kernels)
	make install
	10.2	set path, ld_library_path
	su
	mv /lib64/libc.so.6 /lib64/libc.so.6_bak
	ls /lib64/(ls, error while loading shared libraries: libc.so.6: cannot open shared object file: No such file or directory)
	我慌了,移动错对象了...
	ldconfig
	10.3	build program with my own glibc
	g++ -g main.c -o main -Wl,--rpath=/path/to/newglibc(--rpath linker option will make the runtime loader search for libraries in /path/to/newglibc)
	ldd not a dynamic executable(because of missing ld-linux.so.2)(found http://www.tldp.org/)
	ln -s /home/userName/bin/glibc/lib/ld-2.12.1.so /home/userName/bin/glibc/lib/ld-linux.so.2
	10.4	debugging system functions(ex, bcopy)
	gdb ScenesServer/ScenesServer
	run and immediately CTRL + C
	b bcopy
	OK
	
	locale -a, cannot set lc_ctype to default locale no such file or directory
	cp /usr/lib/locale/locale-archive /home/userName/bin/glibc/lib/locale/
	
	date, local time zone must be set--see zic manual page
	cp /usr/share/zoneinfo/Asia/Shanghai /home/userName/bin/glibc/etc/localtime
	
11. gdb print	
	print binary notion numbers,像十六进制那样,打印二进制的值(p 0b11111111)
	p *array @ len
	print/f <expr>  f代表输出的格式
    x 按十六进制格式显示变量
    d 按十进制格式显示变量
    u 按十六进制格式显示无符号整型
    o 按八进制格式显示变量
    t 按二进制格式显示变量
    a 按十六进制格式显示变量
    c 按字符格式显示变量
    f 按浮点数格式显示变量
	
	expressions表达式 @ :: {}
	file::variable
	function::variable
	
12. gdb 显示汇编
	display/i $pc
	undisplay
	delete display
	disable display
	enable display
	info display

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

------------------------
	gdb scripting 
------------------------
1. used-defined commands
define _command_
_code_
end

document _command_
_help_text
end
2. parameter(no array like $argv)
$argc,$arg0,$arg1,$arg2
3. statements
	3.1 the set statements
	3.2 the if control 
		if _expression_
			_state1
		else
			_state1
		end	
	3.3 the while control
		while _expression_
			_statement
		end
4.	Controlled ouptut
	During the execution of a command file, or use-defined commands, normal gdb output is suppressed.
	The only output that appears is what is explicitly printed by the commands in the definition.
	3 commands to generate output:
	echo _text_(print _text_ including any nonprintable character escaped in a C-style string, echo "abc\tdef\n")
	output _expression_(nothing but the value of the _expression_)
	printf _string_, _expressions_(this prints the values pof the _expressions_ under the control of the format string _string_)
	printf "level=%d",GetLevel()
5.	Invoking the shell
	shell ~/script.sh	
6.	Prompt look
	set prompt \033[01;31mgdb$ \033[0m
7.	Preventing gdb from pausing during long output	
	set width  0
	set height 0
8.	set confirm off	
9.	define hook-stop(the hook-stop is a special function that gdb calls at every breakpoint event.)
	end
10.	not a numeric type	
	set $valpos++
	出现这个，多半是复制代码,变量名打错了,应该是$statepos++
	
-----------------------
	valgrind
-----------------------
Invalid write of size 4
Address 0xabcd is 144 bytes inside a block of size 146 alloc'd

144 + 4 > 146


valgrind --db-attach

Invalid write of size 1
Address 0xabcd is 0 bytes after a block of size 8 alloc'd
0 bytes after is "It's adjacent", "directly after it"





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

//epoll
epoll is a new system call introduced in Linux 2.6. It is designed to replace the deprecated select (and also poll). 
1.Unlike these earlier system calls, which are O(n), epoll is an O(1) algorithm
select uses a linear search through the list of watched file descriptors, which causes its O(n) behaviour, whereas epoll uses callbacks in the kernel file structure.
2.Another fundamental difference of epoll is that it can be used in an edge-triggered, as opposed to level-triggered, fashion.
An epoll instance is created by epoll_create or epoll_create1,which return an epoll instance.
epoll_ctl is used to add/remove descriptors to be watched on the epoll instance.
To wait for events on the watched set, epoll_wait is used,which blocks until events are available.

When descriptors are added to an epoll instance, they can be added in two models : level triggered and edge triggered.
When you use level triggered mode, and data is available for reading, epoll_wait will always return with ready events.
If you don't read the data completely, and call epoll_wait on the epoll instance watching the descriptor again,it will return again with a ready event because data is available.
In edge triggered mode, you will only get a readiness notification once. If you don't read data fully, and call epoll_wait on the epoll instance watching the descriptor again, 
it will block because the readiness event was already delivered.

typedef union epoll_data
{
	void *ptr;
	int fd;
	__uint32_t u32;
	__uint64_t u64;
}epoll_data_t;

struct epoll_event
{
	__uint32_t events;
	epoll_data_t data;
};
//represent binary number in C??
#define B_0001  1
#define B_0010  2
#define B_0011  3
#define B_0100  4
#define B_0101  5
#define B_0110  6
#define B_0111  7
#define B_1000  8
#define B_1001  9
#define B_1010  a
#define B_1011  b
#define B_1100  c
#define B_1101  d
#define B_1110  e
#define B_1111  f

#define _B2H(bits)      B_##bits
#define B2H(bits)       _B2H(bits)
#define _HEX(n)         0x##n##UL
#define HEX(n)          _HEX(n)
#define _CCAT(a,B)/>    a##b
#define CCAT(a,B)/>     _CCAT(a,B)/>

#define BYTE(a,B)/>                     HEX( CCAT(B2H( a),B2H( B)/>) )
#define WORD(a,b,c,d)                   HEX( CCAT(CCAT(B2H( a),B2H( B)/>),CCAT(B2H( c),B2H( d))) )
#define DWORD(a,b,c,d,e,f,g,h)  HEX(  CCAT( CCAT(CCAT(B2H( a),B2H( B)/>),CCAT(B2H( c),B2H( d))),CCAT(CCAT(B2H( e),B2H( f)),CCAT(B2H( g),B2H( h))) )  )

        //using example
        char b = BYTE(0100,0001); //equivalent to b = 65; or b = 'A'; or b = 0x41;
        unsigned int w = WORD(1101,1111,0100,0011); //equivalent to w = 57155; or w = 0xdf43;
        unsigned long int dw = DWORD(1101,1111,0100,0011,1111,1101,0010,1000); //equivalent to dw = 3745774888; or dw = 0xdf43fd28;