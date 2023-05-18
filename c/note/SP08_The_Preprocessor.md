# The Preprocessor

```c
#include ...
#define ...
#if ...
#error ...
...
```

- [전처리기](https://learn.microsoft.com/ko-kr/cpp/preprocessor/preprocessor?view=msvc-170)
    - C 언어는 전처리기를 사용하여 그 능력과 표기법을 확장함
    - #으로 시작하는 행을 전처리 지시자라고 함
    - ANSI C에서 #은 여백 문자 다음에 올 수 있지만, 전통적인 C에서는 첫 번째 열에 #이 와야만 함
    - 전처리 지시자를 위한 구문은 C 언어의 나머지 부분과 독립적임
    - 전처리 지시자가 영향을 미치는 범위는 그 파일에서 전처리 지시자가 있는 위치에서 시작하여 그 파일의 끝까지이거나, 다른 지시자에 의해서 그 지시자의 효력이 없어질 때까지 임
    - 전처리기는 C를 알지 못함
    - 전처리 결과 보기
        - `cc -E file.c`
        - 이 명령을 사용하면, 전처리기가 작업을 수행한 다음에 더 이상의 컴파일이 일어나지 않음

## The Use of #include

```c
#include "filename"
#include <filename>
```

- 지정된 파일을 읽어 들임
- #include 에 명시되는 파일의 내용은 제한이 없음
- 또한 그 파일은 전처리기에 의해 다시 확장되어야 하는 또 다른 전처리 지시자를 포함할 수도 있음
- `#include "filename"`
    - 이 행은 filename 파일의 사본으로 대치됨
    - filename 파일은 먼저 현재 디렉토리에서 검색하고, 거기에 없다면 시스템이 정의한 디렉토리에서 검색함
- `#include <filename>`
    - 이것은 시스템이 정의한 디렉토리에서만 검색함
    - UNIX 시스템에서 stdio.h와 stdlib.h 같은 표준 헤더 파일은 /usr/include에 있음
    - 일반적으로, 표준 헤더 파일이 저장된 장소는 시스템에 따라 다름

## The Use of #define

```c
// https://www.kernel.org/doc/html/v4.10/process/coding-style.html#macros-enums-and-rtl

/*
 * Names of macros defining constants and labels in enums are capitalized.
 * Enums are preferred when defining several related constants.
 */
#define identifier token_string

#define CONSTANT            0x12345
#define SECONDS_PER_DAY     (60 * 60 * 24)
#define PI                  3.14159
#define C                   299792.458
#define EOF                 (-1)
#define MAXINT              2147483647
#define MAIL_ADDRESS        "cybrphntm4@hanyang.ac.kr"
#define EQ ==

#define identifier(id_1, ..., id_n) token_string

#define SQ(x)                   ((x) * (x))
#define min(x, y)               (((x) < (y)) ? (x) : (y))
#define min4(a, b, c, d)        min(min(a, b), min(c, d))
#define SQ(x)                   ((x) * (x))
#define CUBE(x)                 (SQ(x) * (x))
#define F_POW(x)                sqrt(sqrt((CUBE(x)))

/*
 * CAPITALIZED macro names are appreciated but macros resembling functions may be named in lower case.
 * Generally, inline functions are preferable to macros resembling functions.
 * Macros with multiple statements should be enclosed in a do-while block:
 *
 * Things to avoid when using macros:
 * 1. macros that affect control flow
 * 2. macros that depend on having a local variable with a magic name
 */
#define macrofun(a, b, c)   \
do {                        \
	if (a == 5)             \
		do_this(b, c);      \
} while (0)
```

- 정의가 길어질 경우에 현재 행의 끝에 역슬래시’\’를 삽입하면, 다음 행에 연결해서 계속 쓸 수 있음
- `#define identifier token_string`
    - 전처리기는 문자열을 제외한 파일의 모든 identifier를 t_string 으로 대치
    - 프로그램의 명확성과 이식성을 높일 수 있음
        - 기호 상수는 불명확한 상수를 연상 기호 식별자로 바꿈으로써 프로그램의 문서화에 도움을 줌
        - 시스템에 따라 달라지는 상수를 한번에 변경할 수 있으므로 이식성을 높여 줌
        - 상수의 실제 값을 검사하는데 한 곳만 검사하면 되므로 신뢰성도 높여 줌
    - 구문 변경
        - C의 구문을 사용자의 취향에 맞게 변경하는 것이 가능
- `#define identifier(id_1, ..., id_n) token_string`
    - 첫 번째 identifier와 왼쪽 괄호 사이에는 공백이 없어야 함
    - 매개변수 목록에는 식별자가 없거나 또는 여러 개가 올 수 있음
    - 매크로를 정의할 때, 올바른 평가 순서를 유지하기 위해 괄호를 적절히 사용해야  함
    - 매크로를 정의할 때, 매크로 몸체에 매크로나 함수를 사용할 수 있음
- `#undef identifier`
    - 매크로 정의를 무효화함

## The Type Definitions and Macros in stddef.h

```c
typedef int ptrdiff_t;      /* pointer difference type */
typedef short wchar_t ;     /* wide character type */
typedef unsigned size_t ;   /* the sizeof type */
#define NULL ((void *) 0)
```

- stddef.h
    - 이 헤더 파일은 다른 곳에서 공통적으로 사용되는 몇 가지 형 정의과 매크로를 포함하고 있음

## The Macros in stdio.h and ctype.h

- stdio.h
    
    ```c
    #define getchar() getc(stdin)
    #define putchar(c) putc((c), stdout)
    ```
    
    - getc()와 putc() 함수
        - getc() : 파일로부터 한 문자를 읽음
        - putc() : 파일에 한 문자를 출력
    - getchar()와 putchar()는 매크로
- ctype.h
    
    ```c
    /*
     * Macro
     * Nonzero (true) is returned if:
     */
    isalpha(c)      /* c가 문자일 때 */
    isupper(c)      /* c가 대문자일 때 */
    islower(c)      /* c가 소문자일 때 */
    isdigit(c)      /* c가 숫자일 때 */
    isalnum(c)      /* c가 영문자나 숫자일 때 */
    isxdigit(c)     /* c가 16진 숫자일 때 */
    isspace(c)      /* c가 공백 문자일 때 */
    ispunct(c)      /* c가 구두 문자일 때 */
    isprint(c)      /* c가 인쇄가능한 문자일 때 */
    isgraph(c)      /* c가 공백이 아닌 인쇄가능한 문자일 때 */
    iscntrl(c)      /* c가 제어 문자일 때 */
    isascii(c)      /* c가 ASCII 코드일 때 */
    
    /*
     * Call to the function or macro
     * Value returned:
     */
    toupper(c)      /* c가 소문자이면 대응되는 대문자, 아니면 c */
    tolower(c)      /* c가 대문자이면 대응되는 소문자, 아니면 c */
    toascii(c)      /* c와 대응되는 ASCII 코드 값 */
    ```
    

## Conditional Compilation

```c
/*
 * if-part
 * elif-parts(opt)
 * else-part(opt)
 * endif-line
 */
#if constant_integral_expression
...
#elif
...
#else
...
#endif

/*
 * Defined
 */
#ifdef identifier
...
#endif

#if defined()
...
#endif

/*
 * Not defined
 */
#ifndef identifier
...
#endif

#if !defined()
...
#endif

/*
 * For Linker
 */
#ifdef __cplusplus
	extern "C" {
#endif

...

#ifdef __cplusplus
}
#endif
```

- 코드가 컴파일되기 위해서는 #if 다음의 상수 수식이 영이 아닌 값(참)을 가져야 함
- `#ifdef`나 `#if defined`와 `#endif` 사이의 코드가 컴파일되기 위해서는 identifier가 이미 정의되어 있어야 하고, 그 identifier가 취소(#undef identifier)되지 않았어야 함
- `#ifndef`와 `#endif` 사이의 코드가 컴파일되기 위해서는 `#ifndef` 다음의 identifier 가 현재 정의되어 있지 않아야 함
- 이식성이 높은 코드를 만들기 위해 사용할 수 있음
- 디버깅을 위해 사용할 수 있음
- 매크로 이름이 중복 지정되는 것을 피하기 위해 사용할 수 있음

## The Predefined Macros

```c
__func__        /* 바깥쪽 함수의 정규화되지 않은 있는 그대로의 이름, char의 로컬 정적 생성자 배열 only ISO C99, C++11 */
__cplusplus     /* 변환 단위가 C++로 컴파일되는 경우 정수 리터럴 값으로 정의 */
__DATE__        /* 현재 소스 파일의 컴파일 날짜 상수 길이 문자열 리터럴 */
__FILE__        /* 현재 소스 파일의 이름 문자열 리터럴로 확장 */
__LINE__        /* 현재 소스 파일의 정수 줄 번호로 정의 */
__STDC__        /* C로 컴파일되고 컴파일러 옵션이 지정된 경우, __STDC*__ 종류가 많음 */
__TIME__        /* 전처리된 변환 단위를 변환하는 시간 문자열 리터럴 */
```

- 컴파일러는 ISO C99, C11, C17 및 ISO C++17 표준에 지정된 미리 정의된 매크로를 지원
- 이 매크로는 항상 사용할 수 있으며, 프로그래머가 정의를 해제할 수 없음
- 각 매크로 이름은 두개의 밑줄문자로 시작해서 두개의 밑줄문자로 끝남

## The Operators # and ##

- “문자열화” 연산자
    
    ```c
    #include <stdio.h>
    
    #define message_for(a, b)                       \
    do {                                            \
    	printf(#a " and " #b ": We love you!\n");   \
    } while (0)
    
    int main(void)
    {
    	/*
    	 * Carole and Debra: We love you!
    	 */
    	message_for(Carole, Debra);
    	return 0;
    }
    ```
    
- 토큰 결합 연산자
    
    ```c
    #define X(i) x ## i
    
    /*
     * x1 = x2 = x3;
     */
    X(1) = X(2) = X(3);
    ```
    

## The assert() Macro

```c
#include <assert.h>

void f(char *p, int n)
{
	...
	assert(p != NULL);
	assert(n > 0 && n < 7):
	...
}
```

- 수식의 값이 기대하고 있는 값인가를 확인할 때 사용
- 만일 단정이 실패하면, 시스템은 메시지를 출력하고 프로그램을 중단함
- NDEBUG가 정의되어 있으면, 모든 단정은 무시됨

## The Use of #error and #pragma

```c
#if !defined(__cplusplus)
	#error C++ compiler required.
#endif
```

- 조건들을 강요하기 위해 사용
- 전처리기가 #error 를 만나면, 컴파일 오류가 발생하고, 이 지시자 다음에 쓰인 문자열이 화면에 출력됨

```c
#pragma token_string
_Pragma(string_literal) /* C99 */
```

- `#pragma` : 컴퓨터별 또는 운영 체제별 컴파일러 기능을 지정
    - 정의에 따라 컴퓨터별 또는 운영 체제에 따라 다르며 일반적으로 모든 컴파일러에 대해 다름
    - 조건부 지시문에서 A pragma 를 사용하여 새 전처리기 기능을 제공할 수 있음
    - 또는 구현 정의 정보를 컴파일러에 제공하는 데 사용
    - 토큰 문자열은 특정 컴파일러 명령 및 인수(있는 경우)를 나타내는 일련의 문자
- `_Pragma` : 매크로 정의 내에서 지시문을 코딩 pragma

## Line Numbers

```c
#line integral_constant "filename"

/*
 * Example
 */
#include <stdio.h>

int main()
{
	printf( "This code is on line %d, in file %s\n", __LINE__, __FILE__ );
#line 10
	printf( "This code is on line %d, in file %s\n", __LINE__, __FILE__ );
#line 20 "hello.c"
	printf( "This code is on line %d, in file %s\n", __LINE__, __FILE__ );
	printf( "This code is on line %d, in file %s\n", __LINE__, __FILE__ );
}
```

- 컴파일러로 하여금 원시 프로그램의 행 번호를 다시 매기게하여 그 다음 행의 번호가 integral_constant가 되게 함
- 또한 컴파일러에게 현재 원시 파일의 이름이 filename이라고 믿게 함
- 파일 이름이 명시되지 않으면 , 행 번호만을 다시 매김
- 보통 행 번호는 프로그래머에게 감추어지고, 경고나 구문 오류가 발생될 때에만 나타남

## Corresponding Functions

- 표준 헤더 파일에 있는 매개변수를 갖는 대부분의 매크로는 이와 대응되는 함수를 표준 라이브러리에 가지고 있음
- 매크로 대신 함수를 사용하기 위해서는 다음과 같이 함
    - 방법 1 : 함수 사용 전에 다음과 같은 행을 삽입
        - `#undef isalpha`
    - 방법 2 : 다음과 같이 호출함
        - `(isalpha)(c)`