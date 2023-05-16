# Functions

## Function Definition

```c
/**
 * type function_name(parameter list) : function head
 * { declarations statements } : function body
 */
type function_name(parameter list) { declarations statements }

int factorial(int n) /* header */
{ /* body starts here */
	int i, product = 1;
	for (i = 2; i <= n; i++)
		product *= i;
	return product;
}

all_add(int a, int b)
{
	...
}
```

- 함수형이 정의되지 않은 경우
    - 기본적으로 int형으로 간주
    - 함수형을 정확하게 명시하는 것이 바람직함
- 지역변수와 전역변수
    
    ```c
    #include <stdio.h>
    
    int a = 33; /* a is external and initialized to 33 */
    
    int main(void)
    {
    	int b = 77;
    	printf("a = %d\n", a); /* b is local to main() */
    	printf("b = %d\n", b); /* a is global to main() */
    	return 0;
    }
    ```
    

## The return Statement

- return 문
    - return_statement ::= `return;` | `return expression;`
    - example
        - return;
        - return ++a;
        - return (a * b);
    - return 문에 도달하면 해당 함수 종료
    - 함수형에 일치하도록 변형되어 리턴
    - return문은 없거나(괄호에서 종료), 여러 개 있을 수도 있음
    - 받은 return값을 사용하지 않아도 됨

## Function Prototypes

```c
/**
 * Inform the compiler of
 * the type of parameter,
 * number of parameter,
 * and type of return value.
 */
type function_name(parameter list);
```

- 함수 원형
    - 매개변수 형 리스트(parameter type list)는 콤마로 분리
    - 식별자는 원형에 영향 없음(생략해도 괜찮음)

## Function Declarations from the Compiler's Viewpoint

```c
/**
 * default declaration
 */
int f(); 

/**
 * traditional C style
 */
int f(x)
double x;
{
	...
}

/**
 * ANSI C style
 */
int f(double x)
{
	...
} 
```

- 만약 함수선언이나 정의 또는 함수원형의 선언 전에 함수 f(x)가 호출되었다면, 컴파일러는 기본적으로 위와 같은 형태로 함수가 선언 되었다고 가정

## An Alternate Style for Function Definition Order

- 하향식 함수 작성
    - 함수의 정의(definition)는 원형(prototype)의 역할도 함께 수행
    - 각 함수들에서 호출할 함수가 있는 경우, 해당 피호출 함수의 정의를 먼저 작성

## Function Invocation and Call-by-Value

- 값에 의한 호출(call by value)
    - 인자는 지역적(local)으로 사용, 호출한 환경에 저장된 변수 값 변경 없음
    - [Call-by-Reference](../note/SP06_Arrays_Pointers_and_Strings.md#call-by-reference) 참조

## Developing a Large Program

```bash
# gcc -o pgm main.c fct.c prn.c
-+- pgm.h (list of fct prototypes)
      |
      +-> main.c
      |
      +-> fct.c
      |
      +-> prn.c
```

- 컴파일러는 세개의 .c 파일을 컴파일 하고 세개의 .o 파일로 구성된 하나의 실행 가능한 pgm파일을 만듦

## Using Assertions

```c
#include <stdio.h>
#include <assert.h>

int f(int a, int b);
int g(int c);

int main(void)
{
	int a, b, c;
	...
	scanf("%d%d", &a, &b);
	...
	c = f(a, b);
	assert(c > 0); /* an assertion */
	...
}
```

- assert() 매크로에 인자로 전달된 관계식이 거짓 값을 갖는 경우 시스템은 메시지를 출력하고 프로그램을 중단시킴

## Scope Rules

```c
{
	int a = 2;                  /* outer block a */
	printf("%d", a);                /* 2 is printed */
	{
		int a = 5;              /* inner block a */
		printf("%d", a);            /* 5 is printed */
	}                           /* back to the outer block */
	printf("%d", ++a);              /* 3 is printed */
}

{
	int a = 1, b = 2, c = 3;
	printf("%3d %3d %3d", a, b, c); /* 1 2 3 */
	{
		int b = 4;
		float c = 5.0f;
		printf("%3d %3d %5.1f", a, b, c); /* 1 4 5.0 */
		a = b;
		{
			int c;
			c = b;
			printf("%3d %3d %3d", a, b, c); /* 4 4 4 */
		}
		printf("%3d %3d %3d", a, b, c); /* 4 4 5.0 */
	}
	printf("%3d %3d %3d", a, b, c); /* 4 2 3 */
}
```

- 유효범위 규칙 : 변수나 상수가 유효하게 정의되는 범위
    - 기본적인 유효범위 규칙은 변수가 선언된 블록 안에서만 그 변수를 이용할 수 있음
    - 외부 블록의 변수는 내부에서 다시 정의하지 않는 한 여전히 유효함
    - 만일 내부 블록에서 해당 식별자가 다시 정의되면, 외부 변수는 내부 블록으로부터 숨겨짐
- 범위 효력이 정해지는 시점에 따라 정적 유효범위 규칙과 동적 유효범위 규칙으로 나뉜다.
    - 동적 유효범위 : 실행 시간에 결정(실행 순서에 의해)
    - 정적 유효범위 : 컴파일 시간에 결정(프로그램의 구조에 의해)
- C에서는 정적 유효범위 규칙을 사용한다.

## Storage Classes

- C언어에서 사용되는 변수는 두가지 속성을 가진다.
    - 하나는 형(type)이고
    - 또 다른 하나는 기억영역 클래스(storage class)이다.
        - auto extern register static
- 기억영역 클래스 auto
    - 함수의 몸체 부분에서 선언된 변수는 디폴트로 auto(자동) 기억영역 클래스이다.
    - 키워드 auto를 사용하여 자동 기억영역 클래스임을 명시적으로 선언 할 수도 있다.
        - auto int a, b, c;
        - auto float f;
    - 지역변수들은 블록을 빠져 나가게 되면 모두 메모리에서 제거되어 사용할 수 없게 된다.
    - 그러므로 변수가 저장하고 있던 값들을 잃게 된다.
- 기억영역 클래스 extern
    
    ```c
    /*
     * file1.c
     */
    
    #include <stdio.h>
    
    int a = 1, b = 2, c = 3; /* external variables */
    int f(void);
    
    int main(void)
    {
    	printf("%3d\n", f());
    	printf("%3d%3d%3d", a, b, c);
    	return 0;
    }
    
    /*
     * file2.c
     */
    int f(void)
    {
    	extern int a;
    	int b, c;
    	a = b = c = 4;
    	return (a + b + c);
    }
    ```
    
    - 블록과 함수 간에 정보를 교환하기 위한 방법 중 외부 변수(extern)를 사용하는 방법이 있다.
    - 변수를 함수 밖에서 선언하면, 프로그램이 종료할 때까지 메모리에 계속 남아있다.
    - 외부 변수들은 전역 변수(global variables)로 취급되어 외부 변수 선언 뒤에 있는 블록이나 함수가 끝나더라도 사라지지 않고 변수로 존재하게 된다.
    - 두번째 파일에서 extern의 사용은 컴파일러에게 이 변수가 현재 파일 내의 어디서나 선언되어 있거나 또는 다른 파일 내에 선언되었음을 알려준다.
    - 외부변수는 프로그램이 실행되는 동안 전체에 걸쳐 존재하기 때문에 함수들에 값을 전달하는 용도로 사용될 수 있다.
    - 함수 안으로 정보를 전달하는 데는 두 가지 방법이 있다.
        - 하나는 외부 변수를 사용하는 것이고,
            - 사용이 용이
            - 부작용이 발생할 가능성이 있음
        - 다른 하나는 매개 변수를 사용하는 방식이다.
            - 코드의 모듈성을 향상시킴
            - 원하지 않는 부작용의 가능성을 줄일 수 있음
- 기억영역 클래스 register
    - 기억영역 클래스 register는 컴파일러에게 변수를 가능하다면 고속 메모리인 레지스터에 저장되도록 지시
    - 한정된 자원으로 인해 할당하지 못하면, 이 기억영역 클래스는 디폴트로 자동 기억영역 클래스가 됨
    - 이러한 변수는 사용되기 바로 전에 선언하는 것이 좋음
- 기억영역 클래스 static
    - 기본용도 : 그 블록으로 다시 들어갈 때 지역 변수로 선언된 변수가 이전의 값을 유지하고 있게 하는 것
    - 외부 선언과 관련된 용도 : Static External Variables 참조

## Static External Variables

- 정적 외부 구조물은 프로그램 모듈화에 있어서 매우 중요한 개념인 비공개를 제공함
- 비공개란 변수나 함수의 가시화 또는 유효범위의 제한을 의미함
- 정적 외부 변수의 유효범위는 자신이 선언되어 있는 부분부터 원시 파일의 나머지 부분임
- 다른 파일에서 선언된 함수가 키워드 기억영역 클래스 extern을 사용하여 그 변수를 사용하고자 해도 사용할 수 없음

## Default Initialization

- C언어에서 외부 변수와 정적 변수는 프로그래머가 초기화하지 않아도 시스템에 의해 0으로 초기화된다.
- 이와 같은 방식으로 초기화 되는 것에는 배열, 문자열, 포인터, 구조체, 공용체가있다.
- 반면에, 자동 변수와 레지스터 변수는 일반적으로 시스템에 의해 초기화되지 않는다.
    - 가비지 값을 가질 수도 있음

## Recursion

- 재귀호출(Recursive) : 함수가 자기 자신을 호출
- 단순한 재귀적 루틴은 일반적인 패턴을 따름
    - 재귀의 일반적인 패턴에서는 기본적인 경우와 일반적인 재귀 경우를 처리하는 코드가 있음
    - 보통 두 경우는 한 변수에 의해 결정됨
- 일반적인 재귀 함수의 제어 흐름
    - 변수를 검사하여 기본적인 경우인지 일반적인 경우인지를 결정
    - 기본적인 경우일 때에는 더 이상 재귀 호출을 하지 않고 필요한 값을 리턴
    - 일반적인 경우일 때에는 그 변수의 값이 결국에 기본적인 경우의 값이 될 수 있게 하여 재귀호출
- 재귀호출의 효율성
    - 많은 알고리즘은 재귀적 방식과 반복적 방식 둘 다로 표현할 수 있음
    - 전형적으로, 재귀가 더 간결하고 같은 계산을 하는 데 더 적은 변수를 필요로 함
    - 반면, 재귀는 각 호출을 위한 인자와 변수를 스택에 쌓아두어 관리하기 때문에 많은 시간과 공간을 요구함
    - 즉, 재귀를 사용할 때에는 비효율성을 고려해야 함
    - 그러나 일반적으로 재귀적 코드는 작성하기 쉽고, 이해하기 쉬우며, 유지 보수하기가 쉬움