# Arrays, Pointers, and Strings

## One dimension Arrays

```c
#define SIZE 100

type var_name[SIZE];

float f[5] = {0.0, 1.0, 2.0, 3.0, 4.0};

/**
 * Initialize the rest to zero 
 * if the initialization list is less than the number of array elements
 */
int a[100] = {10};

/**
 * Array with no specified size:
 * Number of initial values implicit array size.
 * Apply to char arrays as well.
 */
int a[] = {2, 3, 4, 5};
int a[4] = {2, 3, 4, 5};
char s[] = "abc";
char s[] = {'a', 'b', 'c', '0'};
```

- 배열(Arrays)
    - 같은 자료형의 자료를 여러 개 생성
    - type : 기본 자료형 + 사용자 정의 자료형
    - size : 상수식
        - lower bound = 0
        - upper bound = SIZE - 1
        - SIZE = upper bound + 1
    - 선언한 범위는 프로그래머가 책임져야 함
    - 범위를 벗어났을 때의 효과는 시스템마다 다름
        - 대체로 실행시간 오류 발생
- 첨자(Subscripting)
    - `a[expr]`
    - a 가 배열이면, a의 원소를 접근할 때 , a[expr]과 같이 씀
        - expr은 정수수식
        - expr을 a의 첨자 (subscript), 혹은 색인(index)이라 함

## Pointers

- 변수의 메모리 상의 저장주소를 다룰 수 있게 함

```c
int v;
&v /* location, or address, in memory of v */

/** 
 * Declaration Pointer Variables
 * pointer to int
 */
int *p;

/**
 * Some examples of assignment to the pointer p
 */
p = 0;
p = NULL; /* equivalent to p = 0 ; */
p = &i ; /* i 의 주소를 갖는 포인터 변수 */
/*
 * an absolute address in memory
 * the cast is necessary to avoid a compiler error
 */
p = (int *) 1776;

/**
 * Example of how the pointer mechanism works.
 */
int a = 1, b = 2, *p;
p = &a;
/*
 * The direct value of p is a memory location,
 * whereas *p is the indirect value of p-namely,
 * the value at the memory location stored in p.
 *
 * b is assigned the value pointed to by p.
 * is equivalent to
 * b = a;
 * b = 1;
 */
b = *p;
```

- 주소 연산자(Address Operator) : ‘&’
    - v가 변수라면, &v는 이 변수의 값이 저장된 메모리 위치, 또는 주소
- 포인터 변수(Pointer Variables)
    - 주소를 값으로 가짐
    - 선언 방법
        - 변수 이름 앞에 ‘*’를 붙임
        - 이는 선언과 캐스팅에 포인터 변수임을 알릴 때만 쓰이며, 아래에 나올 역참조 연산자와 구별한다.
        - 변수는 *p 전체가  아니라 p임을 유의하자.
    - 포인터의 범위
        - 특수 주소 0과 주소공간에 있는 양의 정수
- 역참조 연산자(Dereferencing Operator) : ‘*’
    - 참조, 간접지정(indirection) 혹은 역참조 연산자라고도 함
    - 주소 연산자의 반대 연산자
    - p가 포인터라면, *p는 p가 주소인 변수의 값을 나타냄
- 지정할 수 없는 구조
    - 상수
        - &3
    - 일반식
        - &(k + 99)
    - register 변수
        - register v;
        - &v

## Call-by-Reference

- C는 기본적으로 Call-by-Value(값에 의한 호출) 사용
- Call-by-Reference(참조에 의한 호출)의 효과를 얻기 위해서는 함수 정의의 매개변수 목록에서 포인터를 사용
- "Call-by-Reference" 의 효과를 얻는 방법
    - 함수 매개변수를 포인터형으로 선언
    - 함수 호출 시 주소를 인자로 전달
    - 함수 구현에서 역참조 포인터 사용

## The Relationship Between Arrays and Pointers

```c
int *p, *q;
int a[4];

p = a;      /* is equivalent to p = &a[0]; */
q = a + 3;  /* is equivalent to q = &a[3]; */
a = q;      /* illegal */
```

- 배열 이름 그 자체는 주소 또는 포인터 값이고, 배열과 포인터에는 둘 다 첨자를 사용할 수 있음
    - a[i] is equivalent to *(a + i)
    - p[i] is equivalent to *(p + i)
- 포인터 변수는 다른 주소들을 값으로 가질 수 있음
- 반면에 배열 이름은 고정된(상수) 주소 또는 포인터임

## Pointer Arithmetic and Element Size

- 포인터 연산은 C의 강력한 특징 중 하나
- 변수 p를 특정형에 대한 포인터라고 하면, 수식 `p + 1`은 그 형의 다음 변수를 나타냄
    - 특정형의 size만큼 메모리 주소를 이동함
- p와 q가 모두 한 배열의 원소들을 포인트하고 있다면, `p - q` 는 p와 q 사이에 있는 배열 원소의 개수를 나타내는 int 값을 생성함

## Arrays as Function Arguments

```c
/*
 * double sum(double a[], int n)
 * is equivalent to
 * double sum(double *a, int n)
 */

double sum(double a[], int n)
{
	int i;
	double sum = 0.0;
	for (i = 0; i < n; i++)
		sum += a[i];
	return sum;
}

int main(void)
{
	double v[100], result;
	...
	result = sum(v, 100);
	...
	return 0;
}
```

- 함수 정의에서 배열로 선언된 형식 매개변수는 실질적으로는 포인터임
- 함수의 인자로 배열이 전달되면 , 배열의 기본 주소가 값에 의한 호출로 전달됨
- 배열 원소 자체는 복사되지 않음
- 표기 상의 편리성 때문에 포인터를 매개변수로 선언할 때 배열의 각 괄호 표기법을 사용할 수 있음

## Dynamic Memory Allocations With calloc() and malloc()

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *a, *b;                             /* to be used as an array */
	int n, m;                               /* the size of the array */
	...                                     /* get n from somewhere, perhaps interactively from the user */
	a = calloc(n, sizeof(int));
	b = (int *)malloc(n * sizeof(int));
	...
	realloc(b, m * sizeof(int));            /* reallocation size */
	...
	free(a);
	free(b);
}
```

- stdlib.h에 정의되어 있음
    - calloc : contiguous allocation
    - malloc : memory allocation
- calloc()과 malloc()을 이용해 배열, 구조체, 공용체를 위한 메모리 공간을 동적으로 생성할 수 있음
- 각 원소의 크기가 el_size 인 n개의 원소를 할당하는 방법
    - calloc(n, el_size);
    - malloc(n * el_size);
- calloc()은 모든 원소를 0으로 초기화하는 반면 malloc()은 하지 않음
- 할당 받은 메모리를 반환하기 위해서 free() 사용

## Strings

- char 형의 1차원 배열
- 문자열은 끝의 기호인 \0, 또는 NULL 문자로 끝남
- NULL 문자 : 모든 비트가 0인 바이트; 십진 값 0
- 문자열의 크기는 \0까지 포함한 크기

```c
char *p = "abc";
/**
 * abc bc is printed
 */
printf("%s %s\n", p, p + 1); 

/**
 * Arrays vs Pointers
 */
char *p = "abcde";
char s[] = "abcde";
```

- 문자열 상수
    - 큰따옴표 안에 기술됨
    - 문자열 예 : “abc”
        - 마지막 원소가 NULL 문자이고 크기가 4인 문자 배열
    - 주의 - “a”와 ‘a’는 다름
        - 배열 “a”는 두 원소를 가짐
        - 첫 번째 원소는 ‘a’, 두 번째 원소는 ‘\0’
    - 컴파일러는 문자열 상수를 배열 이름과 같이 포인터로 취급
        - 변수 p에는 문자 배열 “abc”의 기본 주소가 배정
        - char 형의 포인터를 문자열 형식으로 출력하면, 그 포인터가 포인트하는 문자부터 시작하여 ‘\0’이 나올 때까지 문자들이 연속해서 출력됨
        - “abc”와 같은 문자열 상수는 포인터로 취급되기 때문에 “abc”[1] 또는 *(“abc” + 2)와 같은 수식을 사용할 수 있음

```c
/*
 * Some string test examples
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *p1 = "abcde";
    
    char *p2 = (char *)malloc(sizeof(char) * 6);
    p2 = "abcde";
    
    // char *p3 = (char *)malloc(sizeof(char) * 6);
    // p3 = {'a', 'b', 'c', 'd', 'e', '\0'};
    
    // char *p4 = {'a', 'b', 'c', 'd', 'e', '\0'};

    char s1[] = "abcde";
    
    char s2[] = {'a', 'b', 'c', 'd', 'e', '\0'};

    char *p5 = s1;

    // p1[0] = 'f';
    // p2[0] = 'f';
    s1[0] = 'f';
    s2[0] = 'f';
    p5[0] = 'g';

    printf("p1: %s\n", p1);
    printf("p2: %s\n", p2);
    printf("s1: %s\n", s1);
    printf("s2: %s\n", s2);
    printf("p5: %s\n", p5);

    return 0;
}
```

## String Handling Functions in the Standard Library

```c
#include <string.h>

char *strcat(char *s1, const char *s2);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *s1, const char *s2);
size_t strlen(const char *s);
```

- strcat() : concatenate
    - 두 문자열 s1, s2를 결합하고, 결과는 s1에 저장
- strcmp() : compare
    - s1과 s2를 사전적 순서로 비교하여, s1이 작으면 음수, 크면 양수, 같으면 0을 리턴
- strcpy() : copy
    - s2의 문자를 ‘\0’이 나올 때까지 s1에 복사
- strlen() : length
    - ‘\0’ 을 뺀 문자의 개수를 리턴

## Multidimensional Arrays

- C 언어는 배열의 배열을 포함한 어떠한 형의 배열도 허용함
- 2차원 배열은 두 개의 각괄호로 만듬
- 이 개념은 더 높은 차원의 배열을 만들 때에도 반복적으로 적용됨
- 함수 정의에서 형식 매개변수가 다차원 배열일 때, 첫 번째 크기를 제외한 다른 모든 크기를 명시해야 함
    - 기억장소 사상 함수를 위해

```c
/** 
 * Declaration
 *
 * a[i][j]
 * is equivalent to
 *     *(a[i] + j)
 *     (*(a+i))[j]
 *     *((*(a+i)) + j)
 *     *(&a[0][0] + 5 * i + j)
 */
int a[3][5];
```

- 2차원 배열은 행과 열을 갖는 직사각형의 원소의 집합으로 생각하는 것이 편리함
    - 사실 원소들은 하나씩 연속적으로 저장됨
- 기억장소 사상 함수
    - int a[3][5];
        - 배열 a의 a[i][j]에 대한 기억장소 사상 함수 : *(&a[0][0] + 5 * i + j)

```c
/** 
 * Declaration
 */
int a[7][9][2];
```

- 기억장소 사상 함수
    - int a[7][9][2]
        - 배열 a의 a[i][j][k]에 대한 기억장소 사상 함수 : (&a[0][0][0] + 9 * 2 * i + 2 * j + k )

## Arrays of Pointers

- 배열의 원소의 형은 포인터형을 포함하여 임의의 형이 될 수 있음
- 포인터 배열은 문자열을 다룰 때 많이 사용됨

## Arguments to main()

```c
/**
 * ./my_echo a is for apple
 *
 * Result:
 *     argc = 5
 *     argv[0] = my_echo
 *     argv[1] = a
 *     argv[2] = is
 *     argv[3] = for
 *     argv[4] = apple
 */
int main(int argc, char *argv[])
{
	printf("argc = %d\n", argc);

	int i;
	for (i = 0; i < argc; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
}
```

- main()은 운영체제와의 통신을 위해 argc와 argv라는 인자를 사용함
    - argc : 명령어 라인 인자의 개수를 가짐
    - argv : 명령어 라인을 구성하는 문자열들을 가짐
- 위의 프로그램을 컴파일하여 my_echo로 한 후, 다음 명령으로 실행 : `./my_echo a is for apple`

## Ragged Arrays

```c
#include <stdio.h>

int main(void)
{
	char a[2][15] = {"abc:", "a is for apple"};
	char *p[2] = {"abc:", "a is for apple"};
	printf("c%c%c %s %s\n", a[0][0], a[0][1], a[0][2], a[0], a[1]); /* abc abc : a is for apple */
	printf("c%c%c %s %s\n", p[0][0], p[0][1], p[0][2], p[0], p[1]); /* abc abc : a is for apple */
	return 0;
}
```

- 식별자 a
    - 2차원 배열
    - 30개의 char 형을 위한 공간이 할당
    - 즉, a[0]과 a[1]은 15 개 char의 배열
    - 배열 a[0]은 다음으로 초기화됨 : {’a’, ‘b’, ‘c’, ‘:’, ‘\0’}
    - 5개의 원소만 명시되어 있기 때문에 , 나머지는 0(NULL 문자)으로 초기화됨
    - 이 프로그램에서 배열의 모든 원소가 사용되지는 않지만, 모든 원소를 위한 공간이 할당됨
    - 컴파일러는 a[i][j] 의 접근을 위해 기억장소 사상 함수를 사용
    - 즉, 각 원소를 접근하기 위해서는 한 번의 곱셈과 한 번의 덧셈이 필요함
- 식별자 p
    - char 포인터의 1차원 배열
    - 이 선언으로 두 포인터를 위한 공간이 할당
    - p[0] 원소는 “abc:”를 포인트하도록 초기화되고, 이 문자열은 5개의 char를 위한 공간을 필요로 함
    - p[1] 원소는 "a is …”를 포인트하도록 초기화되고, 이 문자열은 15개의 char를 위한 공간을 필요로 함
    - 즉, p는 a보다 더 적은 공간을 사용
    - p[i][j] 접근을 위해 기억장소 사상 함수 사용하지 않음
    - p를 사용하는 것이 a를 사용하는 것보다 빠름
    - a[0][14]는 유효한 수식이지만, p[0][14]는 그렇지 않음
    - p[0] 과 p[1] 은 상수 문자열을 포인트함 변경할 수 없음
- a와 p의 차이는 배열과 포인터의 차이와 유사

- 래기드 배열
    - 배열의 원소인 포인터가 다양한 크기의 배열을 포인트하는 것
    - 앞의 프로그램에서 p의 행들은 다른 길이를 갖기 때문에, p를 래기드 배열이라고 할 수 있음

## Functions as Arguments

```c
/**
 * double sum_square(double f(double x), int m, int n)
 * is equivalent to
 * double sum_square(double f(double), int m, int n)
 */
double sum_square(double f(double x), int m, int n)
{
	int k;
	double sum = 0.0;
	for (k = m; k <= n; k++)
		/**
		 * sum += f(k) * f(k);
		 * is equivalent to
		 * sum += (*f)(k) * (*f)(k);
		 */
		sum += f(k) * f(k);
	return sum;
}
```

- 함수의 포인터는 인자로서 전달될 수 있고, 배열에서도 사용되며, 함수로부터 리턴될 수도 있음
- 포인터 f를 함수처럼 취급할 수도 있고, 또는 포인터 f를 명시적으로 역참조할 수도 있음
    - (*f)(k)
        - f : 함수에 대한 포인터
        - *f : 함수 그 자체
        - (*f)(k) : 함수 호출

## The Type Qualifier const and volatile

```c
const int n = 3;
int v[n]; /* any C compiler should complain */

const int a = 7;
/*
 * the compiler will complain
 * ++*p expression can modify a
 */
int *p = &a;

/*
 * p is not constant
 * assignment to p : O
 * assignment to *p : X
 */
const int a = 7;
const int *p = &a;

/*
 * p is constant
 * assignment to p : X
 * assignment to *p : O
 */
int a;
int* const p = &a;

/*
 * p is constant
 * assignment to p : X
 * assignment to *p : X
 */
const int a = 7;
const int* const p = &a;
```

- const
    - const 는 선언에서 기억영역 클래스 뒤와 형 앞에 옴
        - 사용 예 : `static const int k = 3;`
    - 이것은 "k는 기억영역 클래스 static인 상수 int 이다”라고 읽음
    - const 변수는 초기화될 수는 있지만, 그 후에 배정되거나, 증가, 감소, 또는 수정될 수 없음
    - 변수가 const로 한정된다 해도, 다른 선언에서 배열의 크기를 명시하는 데는 사용될 수 없음

- volatile
    - volatile 객체는 하드웨어에 의하여 어떤 방법으로 수정될 수 있음
    - `extern const volatile int real_time_clock;`
        - 한정자 volatile은 하드웨어에 의해 영향을 받는 객체임을 나타냄
        - 또한 const도 한정자이므로, 이 객체는 프로그램에서 증가, 감소, 또는 배정될 수 없음
        - 즉, 하드웨어는 변경할 수 있지만, 코드로는 변경할 수 없음