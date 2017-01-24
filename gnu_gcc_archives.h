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
    
How to compile cef on Linux??
(https://bitbucket.org/chromiumembedded/cef/wiki/MasterBuildQuickStart.md#markdown-header-linux-setup)
./install-build-deps.sh will install 722 softwares, time used: 7 m 54s
Press tab to focus on <ok>, press enter
Press tab to <Yes>, press enter

./update.sh(It takes About 14m 20s)

How to find out what functions a static library has?
Windows, dumpbin; Linux, nm.

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
5. sigsegv handler not called child thread(but can be called in main thread)
在主线程里面写 *(int*)=0发现会触发宕机处理函数;而子线程却不会
sigset_t sig_mask;
sigfillset(&sig_mask);
sigdelset(&sig_mask, SIGSEGV);
pthread_sigmask(SIG_SETMASK, &sig_mask, NULL)
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
    
    Preprocess output:
    The output from the C preprocessor looks much like the input, 
    except that all preprocessing directive lines have been replaced with blank lines and all comments with spaces. Long runs of blank lines are discarded.
    
    Source file name and line number information is conveyed by lines of the form:
    # linenum filename flags
    These are called linemarkers. They mean that the following line originated in file filename at line linenum. 
    Filename will never contain any non-printing characters; they are replaced with octal escape sequences.
    
    0 or more flags : 1,2,3,4
    1 表明新文件的开始
    2 在包含另一个文件后,返回到某个文件.
    3 接下来的代码是系统头文件,某些特殊警告应当被禁止.
    4 接下来的代码应该被视为包含在 extern "C" block 中.
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
	
20. The -Wl,xxx option for gcc passes a comma-separated list of tokens as a space-separated list of arguments to the linker.
    gcc -Wl,aaa,bbb,ccc will be 
	ld aaa bbb ccc
	
21. What does _GLIBCXX_VISIBILITY mean?(http://stackoverflow.com/questions/29270208/what-is-glibcxx-visibility)
    attribute visibility hidden gcc
	It's a preprocessor macro. And is defined as:
	
	#if _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY
	#define _GLIBCXX_VISIBILITY(V) __attribute__ ((__visibility__ (#V)))
	#else
	#define _GLIBCXX_VISIBILITY(V) 
	#endif
	So if _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY is true then in your case it will expand to:
	
	__attribute__ (( __visibility__ ("default")))
	else if _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY is false it will do nothing.
	
	The __visibility__ attribute is used for defining the visibility of the symbols in a DSO file. Using "hidden" instead of "default" can be used to hide symbols from things outside the DSO.
	
	For example:
	
	__attribute__ ((__visibility__("default"))) void foo();
	__attribute__ ((__visibility__("hidden"))) void bar();
	The function foo() would be useable from outside the DSO whereas bar() is basically private and can only be used inside the DSO.
	
	You can read a bit more about the __visibility__ attribute here: https://gcc.gnu.org/wiki/Visibility
	
22. g++ dump class layouts and vtables?(http://stackoverflow.com/questions/2123823/dump-class-struct-member-variables-in-g)
    (gcc Debug options, https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html#Debugging-Options)
    g++ -fdump-class-hierarchy -c source_file.cpp
	Use the right tool for the right job. g++ isn't much of a hierarchy viewing tool.
    You can always use a external tool like doxygen, that can dump graphviz diagrams.
    For power-solutions there is gcc-xml, that can dump your whole program into an xml file that you can parse at will.
	
23. hash is not a member of std
    C++ 11：
	#include <functional>
	using std::hash;
	
	C++ 03:
	#include <tr1/functional>
	using std::tr1::hash;
	
24. reuse std::ostringstream oss;
    oss.clear();
	oss.str("");
	
	oss.clear();
	oss.seekp(0);
	//this is for istringstream oss.seekg(0);
	
25. overload pointer operator c++(http://stackoverflow.com/questions/8777845/overloading-member-access-operators-c)
    "It has additional, atypical constraints: It must return an object (or reference to an object) that also has a pointer dereference operator, or it must return a pointer that can be used to select what the pointer dereference operator arrow is pointing at."
	Operator -> is sepecial.
	
26. Build mysql connector C from Unix Source
    tar -zxvf xxx.tar.gz
    cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=~/bin/mysql_connector
	make
	make install
	
27. where is size_t defined in Linux? How to find ??
    /usr/lib/x86_64-redhat-linux/4.1.1/include/stddef.h
    typedef __SIZE_TYPE__ size_t;
    echo '#include <time.h>' | cpp -I/usr/include -D_GNU_SOURCE - > time_expanded.c
    (-D_GNU_SOURCE selects macro __USE_XOPEN, vim /usr/include/time.h, #ifdef __USE_XOPEN strptime #endif)
    
    How to print uLongf?
    1. find where uLongf is defined. typedef unsigned long uLong; typedef uLong uLongf;
    
    extern void *memset(void *__s, int __c, size_t __n) __THROW __nonnull((1));
    grep __THROW /usr/include/*h -nH | grep define
	vim /usr/include/getopt.h
	#define __THROW throw()
	
	nonnull:(https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes)
	The nonnull attribute specifies that some function parameters should be non-null pointers. For instance, the declaration:
    extern void * my_memcpy (void *dest, const void *src, size_t len) __attribute__((nonnull (1, 2)));
	causes the compiler to check that, in calls to my_memcpy, arguments dest and src are non-null. 
	If the compiler determines that a null pointer is passed in an argument slot marked as non-null, and the -Wnonnull option is enabled, a warning is issued.
	If no argument index list is given to the nonnull attribute, all pointer arguments are marked as non-null
	
28. _MM_SET_FLUSH_ZERO_MODE means what ??(https://msdn.microsoft.com/en-us/library/a8b5ts9s(v=vs.90).aspx)
    Writes to bit fifteen of the control register.
	
29. Fix build warning "class 'foo' was previously declared as a struct [-Wmismatched-tags]"
    苦力活,将class struct 不一致的,统一下
	
30. What is the purpose of those command line options? Please help to decipher 解释 the meaning of the following command line:
-Wl,--start-group -lmy_lib -lyour_lib -lhis_lib -Wl,--end-group -ltheir_lib
It is for resolving circular dependences between several libraries (listed between -( and -)).
-( archives -) or --start-group archives --end-group

The archives should be a list of archive files. They may be either explicit file names, or -l options.

The specified archives are searched repeatedly until no new undefined references are created. Normally, an archive is searched only once in the order that it is specified on the command line. If a symbol in that archive is needed to resolve an undefined symbol referred to by an object in an archive that appears later on the command line, the linker would not be able to resolve that reference. By grouping the archives, they all be searched repeatedly until all possible references are resolved.

Using this option has a significant performance cost. It is best to use it only when there are unavoidable circular references between two or more archives.

31. -static-libgcc
On systems that provide libgcc as a shared library, these options force the use of either the shared or static version, respectively. 
If no shared version of libgcc was built when the compiler was configured, these options have no effect.

32. -static-libstdc++
When the g++ program is used to link a C++ program, it normally automatically links against libstdc++. 
If libstdc++ is available as a shared library, and the -static option is not used, then this links against the shared version of libstdc++. That is normally fine. 
However, it is sometimes useful to freeze the version of libstdc++ used by the program without going all the way to a fully static link. 
The -static-libstdc++ option directs the g++ driver to link libstdc++ statically, without necessarily linking other libraries statically. 

33. How to write/read ofstream in Unicode?
std::ofstream fs;
fs.open(filepath, std::ios::out|std::ios::binary);
unsigned char smarker[3];
smarker[0] = 0xEF;
smarker[1] = 0xBB;
smarker[2] = 0xBF;
fs << smarker;
fs.close();

34. print a leading '+' for positive numbers in printf
RTFM(read the fucking manual)
printf("%+d %+d",10,-10); // prints +10 -10

left-pad printf with spaces
printf("|%10s|", "Hello"); 
|     Hello|
right pad printf with spaces
printf("|%-10s|", "Hello"); 
|Hello     |

variable sized padding in printf
if you use * in your format string, it gets a number from the arguments:
printf ("%0*d\n", 3, 5);
Keep in mind you can only pad with spaces or zeros, If you want to pad with something else, you can use something like:
#include <stdio.h>
#include <string.h>
int main (void) {
    char *s = "MyText";
    unsigned int sz = 9;
    char *pad = "########################################";
    printf ("%.*s%s\n", (sz < strlen(s)) ? 0 : sz - strlen(s), pad, s);
}

35. How does __attribute__((constructor)) work??
__attribute__((constructor))
static void initialize_navigationBarImages() {
  navigationBarImages = [[NSMutableDictionary alloc] init];
}

__attribute__((destructor))
static void destroy_navigationBarImages() {
  [navigationBarImages release];
}

Constructor is run when a shared library is loaded, typically during program startup.
The destructor is run when the shared library is unloaded, typically at program exit.

So, the way the constructors and destructors work is that the shared object file contains special sections (.ctors and .dtors on ELF) 
which contain references to the functions marked with the constructor and destructor attributes, respectively. 
When the library is loaded/unloaded the dynamic loader program (ld.so or somesuch) checks whether such sections exist, and if so, calls the functions referenced therein.

Come to think of it, there is probably some similar magic in the normal static linker, 
so that the same code is run on startup/shutdown regardless if the user chooses static or dynamic linking.

The constructor attribute causes the function to be called automatically before execution enters main (). 
Similarly, the destructor attribute causes the function to be called automatically after main () completes or exit () is called. 
Functions with these attributes are useful for initializing data that is used implicitly during the execution of the program.

36. error:specialization of 'std::tr1::hash<const char*>' after instantiation
/usr/include/c++/4.4.4/tr1/function_hash.h:54:12,error: redefinition of 'std::tr1::hash<const char*>', previous definition of 'struct std::tr1::hash<const char*>'
这说明代码里其他包含 unordered_map 的文件已经声明了 std::tr1::hash<const char*> 导致 const char * 已经偏特化过了.
所以1. 死劲分析包含文件,看看哪里调用了 'std::tr1::hash<const char*>'
2. 代码里 grep -w hash *.*  | grep 'const char' 找到声明的那一行,改变下文件的包含顺序,要在声明 std::tr1::hash<const char*> 之前就偏特化,比如定义一个 allSTLInclude.h 里面
#include <tr1/unordered_map> #include<backward/hash_func.h> 在该文件里面重写 std::tr1::hash<const char*>, 其他文件只包含 allSTLInclude.h ,然后再声明 std::tr1::hash<const char*> 即可.

为什么 下面的代码会报错？(/usr/include/c++/4.9.2/tr1/function_hash.h 中对于类型定义的都是 inline size_t operator() 方法)
template<> struct hash<string> : public std::unary_function<string, size_t> {
    size_t operator() (string &s) const {return __gnu_cxx::__stl_hash_string(s.c_str()); }
}
而这样写就不会报错呢？(原因可能是因为 functional_hash.h 里面定义基本类型的hash 都是只定义了 operator() 方法,而非偏特化结构体
指针类型的模板可以定义 struct,自己写的时候先定义 inline operator() ,以后再研究原因)
template<> inline size_t hash<string>::operator() (string s) const 
{
    return __gnu_cxx::__stl_hash_string(s.c_str());
}
但对于 char * 和 const char * 两种写法却都不会报错呢？
template<> struct hash<const char *> : public std::unary_function<const char*, size_t> {
    size_t operator() (const char *s) const {return __gnu_cxx::__stl_hash_string(s); }
}

template<> inline size_t hash<const char *>::operator() (const char * s) const 
{
    return __gnu_cxx::__stl_hash_string(s);
}

一些常用的文件
/usr/include/c++/4.4.4/backward/hash_func.h(被 backward/hashtable.h 包含)  里面定义了 __stl_hash_string 方法,实在 __gnu_cxx 命名空间下
template <class _Key> struct hash{};
偏特化了 char*, const char *(调用 __stl_hash_string 方法),bool,char,unsigned char,short,long,int 等常用类型

c++11 中 定义在 bits/unordered_map, hash 定义在  bits/functional_hash.h 中,都是在 std 命名空间下的,不需要 std::tr1了
但是都需要重载 char*, const char *, std::string

37. What does __builtin_popcount do??(https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins)
Returns the number of 1-bits in x.
Why to use it?
This function tries to use CPU specific instructions, which will always  be orders of magnitude faster than any algorithm you manage to come up  with.
Other bit twiddling hacks:
http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel

38. C struct bit fields
The declaration of a bit-field has the following form inside a structure −

struct {
   type [member_name] : width ;
};

39. operator new inside namespace
namespace X
{
  void* operator new (size_t);
}
error: ‘void* X::operator new(size_t)’ may not be declared within a namespace
3.7.3.1 Allocation functions [basic.stc.dynamic.allocation]

An allocation function shall be a class member function or a global function;
a program is ill-formed if an allocation function is declared in a namespace scope other than global scope or declared static in global scope. [..]

40. What is anonymous inode?
At least in some contexts, an anonymous inode is an inode without an attached directory entry.
int fd = open( "/tmp/file", O_CREAT | O_RDWR, 0666 );
unlink( "/tmp/file" );
// Note that the descriptor fd now points to an inode that has no filesystem entry; you
// can still write to it, fstat() it, etc. but you can't find it in the filesystem.

41. What does  /proc/id/maps mean??

42. How to use clang++'s MemorySanitizer to check unintialized reads?
http://clang.llvm.org/docs/MemorySanitizer.html#has-feature-memory-sanitizer
MemorySanitizer (MSan) is a detector of uninitialized memory reads in C/C++ programs.
cat umr.cc
#include <stdio.h>

int main(int argc, char** argv) {
  int* a = new int[10];
  a[5] = 0;
  if (a[argc])
    printf("xx\n");
  return 0;
}
clang -fsanitize=memory -fsanitize-memory-track-origins -fPIE -pie -fno-omit-frame-pointer -g -O2 umr.cc

43. How to identify platform/compiler from code?
For Mac OS:
#ifdef __APPLE__

#ifdef _WIN32 // note the underscore: without it, it's not msdn official! Windows (x64 and x86)

For MingW on Windows:
#ifdef __MINGW32__

For Linux:
#ifdef __linux__


Build gcc from source code:
tar xzf gcc-4.6.2.tar.gz
cd gcc-4.6.2
./contrib/download_prerequisites
cd ..
mkdir objdir
cd objdir
$PWD/../gcc-4.6.2/configure --prefix=$HOME/gcc-4.6.2 --enable-languages=c,c++,fortran,go
make
make install

44. Where the *.VC.db files are stored?
echo %TEMP%


gcc options
--------------
1. -fno-strict-aliasing (https://gcc.gnu.org/onlinedocs/gcc-4.3.6/gnat_ugn_unw/Switches-for-gcc.html)
Causes the compiler to avoid assumptions regarding non-aliasing of objects of different types. See Optimization and Strict Aliasing for details. 

2. Easy way to find uninitialized member variables
    clang with clang-analyze.
    g++ -Weffc++(There is also a bug that causes it to always give you a warning when using anonymous unions, #pragma GCC diagnostic ignored "-Weffc++")

---
c knowledges
How to print an address of a variable?
The simplest answer, assuming you don't mind the vagaries and variations in format between different platforms, is the standard %p notation.
The C99 standard (ISO/IEC 9899:1999) says in §7.19.6.1:
p The argument shall be a pointer to void. 
The value of the pointer is converted to a sequence of printing characters, in an implementation-defined manner.

---
compile debugging tricks
1. How to show the value of a macro (#define) at compile-time ?
#include <boost/preprocessor/stringize.hpp>
#pragma message("BOOST_VERSION=" BOOST_PP_STRINGIZE(BOOST_VERSION))

#define XSTR(x) STR(x)
#define STR(x) #x

gcc Diagnostic pragmas
https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html#Diagnostic-Pragmas
#pragma GCC diagnostic kind option
Modifies the disposition of a diagnostic. Note that not all diagnostics are modifiable; at the moment only warnings (normally controlled by ‘-W...’) can be controlled, and not all of them. Use -fdiagnostics-show-option to determine which diagnostics are controllable and which option controls them.
kind is ‘error’ to treat this diagnostic as an error, ‘warning’ to treat it like a warning (even if -Werror is in effect), or ‘ignored’ if the diagnostic is to be ignored. option is a double quoted string that matches the command-line option.

          #pragma GCC diagnostic warning "-Wformat"
          #pragma GCC diagnostic error "-Wformat"
          #pragma GCC diagnostic ignored "-Wformat"
Note that these pragmas override any command-line options. GCC keeps track of the location of each pragma, and issues diagnostics according to the state as of that point in the source file. Thus, pragmas occurring after a line do not affect diagnostics caused by that line. 

#pragma GCC diagnostic push
#pragma GCC diagnostic pop
Causes GCC to remember the state of the diagnostics as of each push, and restore to that point at each pop. If a pop has no matching push, the command-line options are restored.
          #pragma GCC diagnostic error "-Wuninitialized"
            foo(a);                       /* error is given for this one */
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wuninitialized"
            foo(b);                       /* no diagnostic for this one */
          #pragma GCC diagnostic pop
            foo(c);                       /* error is given for this one */
          #pragma GCC diagnostic pop
            foo(d);                       /* depends on command-line options */
			
GCC also offers a simple mechanism for printing messages during compilation.
#pragma message string
Prints string as a compiler message on compilation. The message is informational only, and is neither a compilation warning nor an error.
          #pragma message "Compiling " __FILE__ "..."
string may be parenthesized, and is printed with location information. For example,

          #define DO_PRAGMA(x) _Pragma (#x)
          #define TODO(x) DO_PRAGMA(message ("TODO - " #x))
          
          TODO(Remember to fix this)
prints ‘/tmp/file.c:4: note: #pragma message: TODO - Remember to fix this’.

gcc stringification
Sometimes you may want to convert a macro argument into a string constant. 
Parameters are not replaced inside string constants, but you can use the ‘#’ preprocessing operator instead. 
When a macro parameter is used with a leading ‘#’, the preprocessor replaces it with the literal text of the actual argument, converted to a string constant. 
Unlike normal parameter replacement, the argument is not macro-expanded first. This is called stringification.

All leading and trailing whitespace in text being stringified is ignored. Any sequence of whitespace in the middle of the text is converted to a single space in the stringified result. 
Comments are replaced by whitespace long before stringification happens, so they never appear in stringified text.

There is no way to convert a macro argument into a character constant.

If you want to stringify the result of expansion of a macro argument, you have to use two levels of macros.
     #define xstr(s) str(s)
     #define str(s) #s
     #define foo 4
     str (foo)
          ==> "foo"
     xstr (foo)
          ==> xstr (4)
          ==> str (4)
          ==> "4"
	
	

---
#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 5) || \
  defined __STRICT_ANSI__
#  define __attribute__(Spec) /* empty */
# endif
/* The __-protected variants of `format' and `printf' attributes
   are accepted by gcc versions 2.6.4 (effectively 2.7) and later.  */
# if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 7) || \
  defined __STRICT_ANSI__
#  define __format__ format
#  define __printf__ printf
# endif
#endif
   

#define HK_ALIGN_REAL HK_ALIGN_FLOAT
#define HK_ALIGN_FLOAT HK_ALIGN16
#define HK_ALIGN16(DECL) DECL __attribute__((aligned(16)))
#include <argp.h>
// now __attribute__ is ignored, sizeof(AlignTest) = 4
class AlignTest{
  public:
    HK_ALIGN16(float m_number);
};

// put #include <argp.h> here, sizeof(AlignTest) = 16

#include <iostream>
int main()
{
  std::cout << "sizeof is" << sizeof(AlignTest) << std::endl;
  return 0;
}

implicit instantiation of undefined template 'hkCompileError::COMPILE_ASSERTION_FAILURE<false>'
1470
1487
clang++ -g -U__STRICT_ANSI__ test_argp.cpp -o test_argp
__attribute__((aligned(16)))
---

---
1. C++ alignas specific
The alignas specifier may be applied to the declaration of a variable or a non-bitfield class data member, or it can be applied to the declaration or definition of a class/struct/union or enumeration. 
It cannot be applied to a function parameter or to the exception parameter of a catch clause.
The object or the type declared by such a declaration will have its alignment requirement equal to the stricted (largest) non-zero expression of all alignas specifiers used in the declaration, 
unless it would weaken the natural alignment of the type.
alignas(0) is always ignored.
// every object of type sse_t will be aligned to 16-byte boundary
struct alignas(16) sse_t
{
  float sse_data[4];
};
 
// the array "cacheline" will be aligned to 128-byte boundary
alignas(128) char cacheline[128];

2. C structs alignment
At least on most machines, a type is only ever aligned to a boundary as large as the type itself 
[Edit: you can't really demand any "more" alignment than that, because you have to be able to create arrays, and you can't insert padding into an array]. 
On your implementation, short is apparently 2 bytes, and int 4 bytes.

That means your first struct is aligned to a 2-byte boundary. Since all the members are 2 bytes apiece, no padding is inserted between them.
The second contains a 4-byte item, which gets aligned to a 4-byte boundary. 
Since it's preceded by 6 bytes, 2 bytes of padding is inserted between v3 and i, giving 6 bytes of data in the shorts, two bytes of padding, and 4 more bytes of data in the int for a total of 12.
technically the compile aligns to the largest alignment of any item in the struct.

Can the alignment of a structure type be found if the alignments of the structure members are known?

Eg. for:
struct S
{
 a_t a;
 b_t b;
 c_t c[];
};
is the alignment of S = max(alignment_of(a), alignment_of(b), alignment_of(c))?
There are two closely related concepts to here:

The alignment required by the processor to access a particular object
The alignment that the compiler actually uses to place objects in memory
To ensure alignment requirements for structure members, the alignment of a structure must be at least as strict as the alignment of its strictest member. I don't think this is spelled out explicitly in the standard but it can be inferred from the the following facts (which are spelled out individually in the standard):

Structures are allowed to have padding between their members (and at the end)
Arrays are not allowed to have padding between their elements
You can create an array of any structure type
If the alignment of a structure was not at least as strict as each of its members you would not be able to create an array of structures since some structure members some elements would not be properly aligned.

Now the compiler must ensure a minimum alignment for the structure based on the alignment requirements of its members but it can also align objects in a stricter fashion than required, this is often done for performance reasons. For example, many modern processors will allow access to 32-bit integers in any alignment but accesses may be significantly slower if they are not aligned on a 4-byte boundary.

There is no portable way to determine the alignment enforced by the processor for any given type because this is not exposed by the language, although since the compiler obviously knows the alignment requirements of the target processor it could expose this information as an extension.
There is also no portable way (at least in C) to determine how a compiler will actually align an object although many compilers have options to provide some level of control over the alignment.

struct foo {
  uint8_t bar;
  uint8_t baz;
} __attribute__((packed));
__attribute__((aligned(1))) tells the compiler to begin each struct element on the next byte boundary but doesn't tell it how much space it can put at the end. 
  This means that the compiler is allowed to round the struct up to a multiple of the machine word size for better use in arrays and similar.
__attribute__((packed)) tells the compiler to not use any padding at all, even at the end of the struct
What's the difference between "#pragma pack" and "__attribute__((aligned))"??
The #pragma pack(byte-alignment) effect each member of the struct as specified by the byte-alignment input, or on their natural alignment boundary, whichever is less.
The __attribute__((aligned(byte-alignment))) affect the minimum alignment of the variable (or struct field if specified within the struct).

test_align.c
#include <stdio.h>
typedef struct foo{
  int x[2] __attribute__ ((aligned(16)));
} FooType;
int main()
{
  printf("sizeof(foo) is %lu\n", sizeof(FooType));
  return 0;
}
$ gcc -g test_align.c -o test_align
$ ./test_align 
sizeof(foo) is 16

__attribute__ ((aligned))
__attribute__ ((aligned (n)))
__attribute__ ((packed))
Whenever you leave out the alignment factor in an aligned attribute specification, 
the OpenCL compiler automatically sets the alignment for the declared variable or field to the largest alignment which is ever used for any data type on the target device you are compiling for.
The packed attribute specifies that a variable or structure field should have the smallest possible alignment -- one byte for a variable, unless you specify a larger value with the aligned attribute.

How to reduce the size of C structure?
http://www.catb.org/esr/structure-packing/

3. print the sizeof a C++ class at compile time ?
template <int s> struct PrintSize;
PrintSize<sizeof(struct)> aa;
//incomplete type and cannot be defined
template<int N> 
struct print_size_as_warning
{ 
   char operator()() { return N + 256; } //deliberately causing overflow
};

int main() {
        print_size_as_warning<sizeof(int)>()();
        return 0;
}
4. reinterpret_cast
reinterpret_cast < new_type > ( expression )		
Unlike static_cast, but like const_cast, the reinterpret_cast expression does not compile to any CPU instructions. 
It is purely a compiler directive which instructs the compiler to treat the sequence of bits (object representation) of expression as if it had the type new_type.

Use reinterpret_cast to tell if CPU is little endian or big endian ?
int i = 7;
char *p = reinterpret_cast<char*>(&i);
if p[0] == '\x7'
{
  printf("little endian");
}
else
{
  printf("big endian");
}

5. Standard C escape sequences
Escape sequence	Hex value in ASCII	Character represented
\a	07	Alarm (Beep, Bell)
\b	08	Backspace
\f	0C	Formfeed
\n	0A	Newline (Line Feed); see notes below
\r	0D	Carriage Return
\t	09	Horizontal Tab
\v	0B	Vertical Tab
\\	5C	Backslash
\'	27	Single quotation mark
\"	22	Double quotation mark
\?	3F	Question mark
\nnn	any	The character whose numerical value is given by nnn interpreted as an octal number
\xhh	any	The character whose numerical value is given by hh interpreted as a hexadecimal number

6. What is nullptr?
4.10 about pointer conversion says that a prvalue of type std::nullptr_t is a null pointer constant, and that an integral null pointer constant can be converted to std::nullptr_t. The opposite direction is not allowed. 
This allows overloading a function for both pointers and integers, and passing nullptr to select the pointer version. Passing NULL or 0 would confusingly select the int version.
A cast of nullptr_t to an integral type needs a reinterpret_cast, and has the same semantics as a cast of (void*)0 to an integral type (mapping implementation defined). 
A reinterpret_cast cannot convert nullptr_t to any pointer type. Rely on the implicit conversion if possible or use static_cast.
void func(int ); void func(void *);
func(NULL);

7. print traceback in c++
#include <execinfo.h>
#define SIZE 100
void *buffer[SIZE];
char **strings = NULL;
int nptrs = backtrace(buffer, SIZE);
strings = backtrace_symbols(buffer, nptrs);
for (int i = 0; i < nptrs; ++i)
{
 printf("%s", strings[i]);
}

8. when will gcc generate jump table? When will gcc generate compare and branch pairs?
(https://gcc.gnu.org/bugzilla/show_bug.cgi?id=11823)
stmt.c:expand_end_case_type()
/* If range of values is much bigger than number of values,
         make a sequence of conditional branches instead of a dispatch.
         If the switch-index is a constant, do it this way
         because we can optimize it.  */

The heuristic following this comment now does:
               || compare_tree_int (range, 10 * count) > 0//make a sequence of branches instead of dispatch
range is the max case number, count is the number of case.
---

---
C++ Primer 5th edition
Start at page 11,18
Chapter 10, generic algorithm
The generic algorithms, and a more detailed look at iterators, form the subject matter of this chapter.
In general, the algorithms do not work directly on a container. Instead, they operate by traversing a range of elements bounded by two iterators

Trailing return type
A trailing return type follows the parameter list and is preceded by ->. To signal that the return follows the parameter list, we use auto where the return type ordinarily appears:
auto func(int i) -> int(*)[10];

A predicate is an expression that can be called and that returns a value that can be used as a condition.
---
---
cmake options
cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DCMAKE_CXX_FLAGS=-g -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=~/bin .
cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++

How to preprocessing Makefiles? like gcc -E
(http://www.oreilly.com/openbook/make3/book/ch12.pdf)
GNU make with option -n(--just-print), -p(--print-data-base),--warn-undefined-variables, -debug=verbose
Use $(warning ) function to print Makefiles variables, eg : $(warning sub dir is $(SUBDIRS))
---

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
    
13. gdb print register values
    info registers(or i r)
    layout asm
    layout reg
    stepi
    x
    
    gdb install from source code
    sudo apt-get install libreadline
    wget ftp://ftp.gnu.org/gnu/gdb/gdb-7.12.tar.xz
    tar -xf gdb-7.12.tar.xz
    ./configure --prefix=/usr --with-system-readline && make
    (不要选择/usr/bin, gdb 自己会创建 bin 和 lib 目录的,/usr/bin/bin)
    
    gdb ptrace: Operation not permitted
    解决方法:
    sudo su
    echo 0 >  /proc/sys/kernel/yama/ptrace_scope
    
14. use asan to detect adress read/write out of bound
    https://trac.torproject.org/projects/tor/ticket/13499
    https://github.com/google/sanitizers/wiki/SanitizerCommonFlags
    Make asan core dumped(easy to debug,only 32-bit is available, 64-bit NO!!!), ASAN_OPTIONS="disable_core=0:unmap_shadow_on_exit=1:abort_on_error=1:log_path=/home/giant/asan_error_log"
    
    gcc version > 4.9
    gcc -Werror -fsanitize=address -fsanitize=undefined test_assert.c -o test_assert
    cat test_assert.c 
    #include <stdio.h>
    #include <assert.h>
    
    int main()
    {
        int *p = NULL;
        *p = 3;
        //assert(0);
        printf("after assert");
        return 0;
    }

    
    
15. How can a C program produce a core dump of itself without terminating?
    void create_dump(void)
    {
        if(!fork()) {
            // Crash the app in your favorite way here
            abort() || (*((void*)0) = 42);
        }
    }
    
16. How to execute a Linux program in the C program?
    man system
    
17. How to disable abrt?
$ sudo systemctl stop abrt-ccpp

Before:

$ cat /proc/sys/kernel/core_pattern
|/usr/libexec/abrt-hook-ccpp %s %c %p %u %g %t e

i.e. send core dumps to abrt.

After:

$ cat /proc/sys/kernel/core_pattern
core
$ cat /proc/sys/kernel/core_uses_pid
1
systemctl disable abrtd.service
systemctl start abrt-ccpp

18. How to detect memory leaks in C?(not C++,overload new delete, not valgrind)
(asan leak checker,https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer
clang -fsanitize=address -g memory-leak.c
g++ -fsanitize=address main.cpp
ASAN_OPTIONS=detect_leaks=1 ./a.out
)
#define malloc(X) my_malloc( X, __FILE__, __LINE__, __FUNCTION__)

void* my_malloc(size_t size, const char *file, int line, const char *func)
{

    void *p = malloc(size);
    printf ("Allocated = %s, %i, %s, %p[%li]\n", file, line, func, p, size);

    /*Link List functionality goes in here*/

    return p;
}
You maintain a Linked List of addresses being allocated with the file and line number from where there allocated. You update the link list with entries in your malloc.

Similar to above you can write an implementation for free, wherein you check the address entries being asked to be freed against your linked list. If there is no matching entry its a usage error and you can flag it so.

At the end of your program you print or write the contents of your linked list to an logfile. If there are no leaks your linked list should have no entries but if there are some leaks then the logfile gives you exact location of where the memory was allocated.

Note that in using this macro trick, you lose the type checking which functions offer but it's a neat little trick I use a lot of times.

19. clock_gettime(), difference between CLOCK_REALTIME and CLOCK_MONOTONIC
CLOCK_REALTIME represents the machine's best-guess as to the current wall-clock, time-of-day time
CLOCK_REALTIME can jump forwards and backwards as the system time-of-day clock is changed, including by NTP.

CLOCK_MONOTONIC represents the absolute elapsed wall-clock time since some arbitrary, fixed point(boot time) in the past.
 It isn't affected by changes in the system time-of-day clock.
CLOCK_MONOTONIC_RAW  is even better(no NTP adjustments).

How to get boottime?
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <sys/sysinfo.h>

int main(void){
    /* get uptime in seconds */
    struct sysinfo info;
    sysinfo(&info);

    /* calculate boot time in seconds since the Epoch */
    const time_t boottime = time(NULL) - info.uptime;

    /* get monotonic clock time */
    struct timespec monotime;
    clock_gettime(CLOCK_MONOTONIC, &monotime);

    /* calculate current time in seconds since the Epoch */
    time_t curtime = boottime + monotime.tv_sec;

    /* get realtime clock time for comparison */
    struct timespec realtime;
    clock_gettime(CLOCK_REALTIME, &realtime);

    printf("Boot time = %s", ctime(&boottime));
    printf("Current time = %s", ctime(&curtime));
    printf("Real Time = %s", ctime(&realtime.tv_sec));

    return 0;
}

How to erase from vector by value?
Erase-remove idiom. (can not be used for containers that return const_iterator, set.)
// initialises a vector that holds the numbers from 0-9.
std::vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
print(v); 
// removes all elements with the value 5
v.erase( std::remove( v.begin(), v.end(), 5 ), v.end() ); 
print(v);
// removes all odd numbers
v.erase( std::remove_if(v.begin(), v.end(), is_odd), v.end() );
print(v);

20. How does gcc find the following header file?
cat test.c
#include <sys/ptrace.h>
int main(){return 0;}
cpp test.c -v
gcc test.c -v
#include "..." search starts here:
#include <...> search starts here:
 /usr/lib/gcc/x86_64-linux-gnu/5/include
 /usr/local/include
 /usr/lib/gcc/x86_64-linux-gnu/5/include-fixed
 /usr/include/x86_64-linux-gnu
 /usr/include
End of search list.

gcc test.c -M
test.o: test.c /usr/include/stdc-predef.h \
 /usr/include/x86_64-linux-gnu/sys/ptrace.h /usr/include/features.h \
 /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/include/x86_64-linux-gnu/bits/types.h \
 /usr/include/x86_64-linux-gnu/bits/typesizes.h
 
echo '#include <sys/ptrace.h>' | gcc -fsyntax-only -xc -v -H -

21. Which header file defined the macro that specify the machine architecture:
echo | gcc -E -dM -

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
	
11. gdb 定位内存泄露(查看内存布局)
示例代码:
$ cat test.cpp
#include <stdexcept>
class TestClass
{
public:
        virtual ~TestClass(){}
        int i;
        int j;
};
 
void f()
{
        for (int i = 0; i < 2; ++i)
        {
                TestClass* p = new TestClass;
        }
        throw std::bad_alloc();
}
 
int main()
{
        f();
        return 0;
}

$ g++ -g test.cpp -o test
$ gdb test
terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc
Aborted (core dumped)
$ gdb test core
(gdb) run
开始运行程序,会宕掉
(gdb) info proc
process 11024
cmdline = '/home/uname/test'
cwd = '/home/uname'
exe = '/home/uname/test'
(gdb) shell pmap 11024
0000000000400000      4K r-x-- test
0000000000600000      4K r---- test
0000000000601000      4K rw--- test
0000000000602000    200K rw---   [ anon ]
00007ffff716d000     88K r-x-- libgcc_s.so.1
00007ffff7183000   2044K ----- libgcc_s.so.1
00007ffff7382000      4K rw--- libgcc_s.so.1
00007ffff7383000   1056K r-x-- libm-2.23.so
00007ffff748b000   2044K ----- libm-2.23.so
00007ffff768a000      4K r---- libm-2.23.so
00007ffff768b000      4K rw--- libm-2.23.so
00007ffff768c000   1788K r-x-- libc-2.23.so
00007ffff784b000   2048K ----- libc-2.23.so
00007ffff7a4b000     16K r---- libc-2.23.so
00007ffff7a4f000      8K rw--- libc-2.23.so
00007ffff7a51000     16K rw---   [ anon ]
00007ffff7a55000   1480K r-x-- libstdc++.so.6.0.21
00007ffff7bc7000   2048K ----- libstdc++.so.6.0.21
00007ffff7dc7000     40K r---- libstdc++.so.6.0.21
00007ffff7dd1000      8K rw--- libstdc++.so.6.0.21
00007ffff7dd3000     16K rw---   [ anon ]
00007ffff7dd7000    152K r-x-- ld-2.23.so
00007ffff7fe7000     20K rw---   [ anon ]
00007ffff7ff6000      8K rw---   [ anon ]
00007ffff7ff8000      8K r----   [ anon ]
00007ffff7ffa000      8K r-x--   [ anon ]
00007ffff7ffc000      4K r---- ld-2.23.so
00007ffff7ffd000      4K rw--- ld-2.23.so
00007ffff7ffe000      4K rw---   [ anon ]
00007ffffffde000    132K rw---   [ stack ]
ffffffffff600000      4K r-x--   [ anon ]
 total            13268K
(gdb) shell cat /proc/11024/maps 
00400000-00401000 r-xp 00000000 fc:00 2628660                            /home/cxz/test
00600000-00601000 r--p 00000000 fc:00 2628660                            /home/cxz/test
00601000-00602000 rw-p 00001000 fc:00 2628660                            /home/cxz/test
00602000-00634000 rw-p 00000000 00:00 0                                  [heap]
7ffff716d000-7ffff7183000 r-xp 00000000 fc:00 41157143                   /lib/x86_64-linux-gnu/libgcc_s.so.1
7ffff7183000-7ffff7382000 ---p 00016000 fc:00 41157143                   /lib/x86_64-linux-gnu/libgcc_s.so.1
7ffff7382000-7ffff7383000 rw-p 00015000 fc:00 41157143                   /lib/x86_64-linux-gnu/libgcc_s.so.1
7ffff7383000-7ffff748b000 r-xp 00000000 fc:00 41160980                   /lib/x86_64-linux-gnu/libm-2.23.so
7ffff748b000-7ffff768a000 ---p 00108000 fc:00 41160980                   /lib/x86_64-linux-gnu/libm-2.23.so
7ffff768a000-7ffff768b000 r--p 00107000 fc:00 41160980                   /lib/x86_64-linux-gnu/libm-2.23.so
7ffff768b000-7ffff768c000 rw-p 00108000 fc:00 41160980                   /lib/x86_64-linux-gnu/libm-2.23.so
7ffff768c000-7ffff784b000 r-xp 00000000 fc:00 41160988                   /lib/x86_64-linux-gnu/libc-2.23.so
7ffff784b000-7ffff7a4b000 ---p 001bf000 fc:00 41160988                   /lib/x86_64-linux-gnu/libc-2.23.so
7ffff7a4b000-7ffff7a4f000 r--p 001bf000 fc:00 41160988                   /lib/x86_64-linux-gnu/libc-2.23.so
7ffff7a4f000-7ffff7a51000 rw-p 001c3000 fc:00 41160988                   /lib/x86_64-linux-gnu/libc-2.23.so
7ffff7a51000-7ffff7a55000 rw-p 00000000 00:00 0 
7ffff7a55000-7ffff7bc7000 r-xp 00000000 fc:00 55838749                   /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21
7ffff7bc7000-7ffff7dc7000 ---p 00172000 fc:00 55838749                   /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21
7ffff7dc7000-7ffff7dd1000 r--p 00172000 fc:00 55838749                   /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21
7ffff7dd1000-7ffff7dd3000 rw-p 0017c000 fc:00 55838749                   /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21
7ffff7dd3000-7ffff7dd7000 rw-p 00000000 00:00 0 
7ffff7dd7000-7ffff7dfd000 r-xp 00000000 fc:00 41160984                   /lib/x86_64-linux-gnu/ld-2.23.so
7ffff7fe7000-7ffff7fec000 rw-p 00000000 00:00 0 
7ffff7ff6000-7ffff7ff8000 rw-p 00000000 00:00 0 
7ffff7ff8000-7ffff7ffa000 r--p 00000000 00:00 0                          [vvar]
7ffff7ffa000-7ffff7ffc000 r-xp 00000000 00:00 0                          [vdso]
7ffff7ffc000-7ffff7ffd000 r--p 00025000 fc:00 41160984                   /lib/x86_64-linux-gnu/ld-2.23.so
7ffff7ffd000-7ffff7ffe000 rw-p 00026000 fc:00 41160984                   /lib/x86_64-linux-gnu/ld-2.23.so
7ffff7ffe000-7ffff7fff000 rw-p 00000000 00:00 0 
7ffffffde000-7ffffffff000 rw-p 00000000 00:00 0                          [stack]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
(gdb) p 200 * 1024 / 8,64位下指针占8个字节,加上虚表,一个 TestClass 占 16 字节
$1 = 25600
(gdb) set logging file all_memory
(gdb) set height 0
(gdb) set logging on
(gdb) x/25600a 0000000000602000
(gdb) set logging off
(gdb) q
$ cat all_memory |egrep -v '0x0\s*0x0' 
0x602000:	0x0	0x11c11
0x602010:	0x11c00	0x0
0x613c10:	0x0	0x411
0x614020:	0x0	0x21
0x614030:	0x400aa8 <_ZTV3TestClass+16>	0x0
0x614040:	0x0	0x21
0x614050:	0x400aa8 <_ZTV3TestClass+16>	0x0
0x614060:	0x0	0x1ffa1

如何分析 core文件中的内存占用?(或者说new出来的class)
$ objdump -p core
That will give the information from the first three columns of pmap, but in a different format.
The first three columns in pmap correspond to the vaddr, memsz and flags values in the objdump output resepectively.
The fourth column from pmap, the path of the mapped file, appears to be unavailable from the core file.
objdump -p core 

core:     file format elf64-x86-64

Program Header:
    NOTE off    0x0000000000000740 vaddr 0x0000000000000000 paddr 0x0000000000000000 align 2**0
         filesz 0x0000000000000e28 memsz 0x0000000000000000 flags ---
    LOAD off    0x0000000000002000 vaddr 0x0000000000400000 paddr 0x0000000000000000 align 2**12
         filesz 0x0000000000001000 memsz 0x0000000000001000 flags r-x
    LOAD off    0x0000000000003000 vaddr 0x0000000000600000 paddr 0x0000000000000000 align 2**12
         filesz 0x0000000000001000 memsz 0x0000000000001000 flags r--
    LOAD off    0x0000000000004000 vaddr 0x0000000000601000 paddr 0x0000000000000000 align 2**12
         filesz 0x0000000000001000 memsz 0x0000000000001000 flags rw-
    LOAD off    0x0000000000005000 vaddr 0x00000000006b7000 paddr 0x0000000000000000 align 2**12
         filesz 0x0000000000032000 memsz 0x0000000000032000 flags rw-

最靠前的,flags 为 rw- 的即为 heap ,分别分析地址 0x0000000000601000 和地址 0x00000000006b7000
$ gdb test core
(gdb) x/25600a 0x00000000006b7000
打印到文件中即可查到内存中的 class.
gdb 带参数调试:
gdb --args ./testprg arg1 arg2
	
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