# CwithCPP

---

**Reference**

1. C++ reference
    1. [https://en.cppreference.com/w/](https://en.cppreference.com/w/)
2. C++ header
    1. [https://learn.microsoft.com/ko-kr/cpp/standard-library/cpp-standard-library-header-files?view=msvc-170](https://learn.microsoft.com/ko-kr/cpp/standard-library/cpp-standard-library-header-files?view=msvc-170)
3. Book on C, A: Programming in C 4th Edition
4. Introduction to System Programming [ CSE2018, 23577 ]
5. 윤성우 열혈 C++ 프로그래밍 개정판
6. https://github.com/zsaladin/cppexamples

---

**CPP Library**

<iostream>

<iomanip>

<numeric>

<array>

<string>

<vector>

<algorithms>

---

# 0. Starting from Zero

# 1. An Overview of C

## Programming and Preparation

1. Compiler
    1. g++ -o execname sourcename.cpp

## Dissection of the sea Program

```cpp
/* sea.cpp */

#include <iostream>
int main(void)
{
    std::cout<<"from sea to shining C\n";
    return 0;
}
```

1. #include <iostream> ← #include <stdio.h>
    1. #include <stdio.h> → #include <cstdio>
2. std::cout<< ← printf()
    1. std::cout<<”output1”<<”output2”<<”output3”;
    2. std::cout<<”output1”<<std::endl;
        1. std:endl? : newline
- cout
    - Writes to the standard C ouput stream stdout
    - << 연산자를 오버로딩 해서 어떻게 출력할 지 결정 : operator<<(cout, ‘a’); , cout.operator<<()
    - cout.put(’c’); // 문자 출력
    - cout.write(”str”, size); // 문자열 출력
    - cout.width(10); // 폭을 10으로 지정
    - cout.fill(’#’); // 폭을 지정된 문자로 채움
    - cout.precision(10); // 소수점 정밀도 지정 → 유효숫자의 갯수
    - cout.setf(ios_base::showpos); //setflag +부호를 표시해줌 ↔ unsetf()
        - ios_base::boolalpha : true/fasle를 알파벳으로 표현
        - ios_base::left, ios_base::adjustfield : 좌측정렬, flag가 3개 이상
        - ios_base::hex, ios_base::basefield : dec, oct, hex
            - cout<<hex<<16;
            - hex(cout); cout<<16;
    - cout<<setw(10)<<setfill(’#’)<<setprecision(10)<<showpos<<1.1f
        - output result : +1.00000024
        - #include <iomanip>
- cin
    - Reads from the standard C input stream stdin : scanf() in C
    - Do not use & operator
    - Also can use ios_base like cout
    
    ```cpp
    /* buffer control */
    
    // if error, like data type 
    if (cin.fail()) {
    		cin.clear();
    }
    
    // buffer in char, ignore size of buffer until '\n'
    cin.ignore(size, '\n');
    ```
    

# 2. Lexical Elements, Operators, and the C System

## Characters and Lexical Elements

ANSI C 토큰 종류

1. 키워드(keywords)
    1. List
        
        ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled.png)
        
    2. cpp → Reference Check
2. 식별자(identifiers)
    1. 헝가리안?
3. 상수(constants)
4. 문자열 상수(string constants)
    1. ASCII (3, 4)
5. 연산자(operators)
    1. [https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B](https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B)
    2. [https://en.cppreference.com/w/cpp/language/expressions](https://en.cppreference.com/w/cpp/language/expressions)
    3. Sequence-point and Undefined behavior
        1. 한 식에서 특정 변수 하나가 변경이 될 때, 두 번 이상 변경되는 경우 위험
6. 구두점(puctuators)

# 3. The Fundamental Data Types

## Declarations, Expressions, And Assignment

```cpp
#include <iostream>
int main(void)
{
		int i = 0; // Declarations C style [ int i(0); is c++ style ]
    std::cout<<i; // print
    return 0;
}
```

```cpp
/* namespace */

#include <iostream>

using namespace std;

int main(void)
{
		int i = 0;
    cout<<i<<endl; // std?
    return 0;
}
```

## The Fundamental Data Types

![[https://en.cppreference.com/w/cpp/language/types](https://en.cppreference.com/w/cpp/language/types)](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%201.png)

[https://en.cppreference.com/w/cpp/language/types](https://en.cppreference.com/w/cpp/language/types)

## Conversions and Casts

- 정수적 승격 (the integral promotions)
    - signed 혹은 unsigne의 char, short, 또는 열거형을 int나 unsigned int형이
    사용될 수 있는 수식에서 대신 사용 가능
    - 이 경우, 이들 형들 중 모든 값을 int로 표현할 수 있으면 int로 변환되고,
    그렇지 않으면 unsigned int로 변환됨
    - char c = 'A';
        - printf("%d\n", c); // c는 승격이 일어나 int형이 됨 (65출력)
- 일반적 자동 변환 (the usual arithmetic conversions)
    - 수식에서 제일 큰 형으로 변환한다.
    - long double, double, float
    - unsigned long, long, unsigned, int의 순서
    - long과 unsigned의 경우, 모든 값을 long으로 표현할 수 있으면 long으로 변환되고, 그렇지 않으면 unsigned long으로 변환됨
    - examples
        
        ```cpp
        char c; short s; int i; long l; unsigned u; 
        unsigned long ul; float f; double d; long double ld;
        
        c - s / i (int)
        u * 2.0 - i (double)
        c + 3 (int)
        c + 5.0 (double)
        d + s (double)
        2 * i / l (long)
        u * 7 - i (unsigned)
        f * 7 - i (float)
        7 * s * ul (unsigned long)
        ld + c (long double)
        u - ul (unsigned long)
        u - l (system-dependent)
        ```
        
- 캐스트(casts) - 명시적 변환
    - examples
        
        ```cpp
        /* 캐스트 예 */
        (double) i
        (long) ('A' + 1.0) 
        f = (float) ((int) d + 1) 
        d = (double) i / 3
        (double) (x = 77) 
        
        /* 틀린 예 */
        (double) x = 77 /* equivalent to ((double) x) = 77, error */
        
        /* (float)가 + 보다 우선순위 높음 */
        (float) i + 3 <==> ((float) i) + 3
        ```
        
    

# 4. Flow of Control

## Relational Operators and Expressions

![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%202.png)

1. 3 < j < 5
    1. (3 < 2) < 5 ↔ 0 < 5 (true)
    2. 3 < j && j < 5
2. x < x + y
    1. (x - (x + y)) < 0.0
    2. 정밀도 때문에 x와 x + y의 값이 같아서 0

- 단축 평가(short-circuit evaluation)
    - 결과가 참인지 거짓인지 판명되면 더 이상 다음 수식을 평가하지 않는다.
    - expr1 && expr2
        - expr1이 0면 어차피 0이므로 expr2 평가하지 않음
    - expr1 || expr2
        - expr1이 1이면 어차피 1이므로 expr2 평가하지 않음

## The Comma Operator

- expr1, expr2
    - expr1이 먼저 평가되고, 그 다음 expr2가 평가됨
    - 전체 수식의 값과 형은 가장 오른쪽 피연산자를 따름
    - 가장 낮은 우선순위 갖는 이항 연산자
    - L→R 결합 법칙
- 프로그램 상의 대부분의 콤마는 콤마 연산자가 아님
    - 함수의 인자 목록에서 수식을 분리하는데 사용된 콤마
    - 초기화 목록에서 사용된 콤마
- examples
    
    ```cpp
    for (sum = 0, i = 1; i <= n; ++i)
    		sum += i;
    
    for (sum = 0, i = 1; i <= n; sum += i, ++i) /* correct, but do not use. */
    		;
    
    for (sum = 0, i = 1; i <= n; ++i, sum += i) /* wrong */
    		;
    
    for (i = 0, p = head; p != NULL; ++i, p = p -> next) /* Perfect */
    		statements...
    ```
    

## Range based for

```cpp
#incldue <iostream>
#include <array>

using namespace std;

struct node {
		int i;
		float f;
};

int main(void)
{
		int arr[5] = { 0, 1, 2, 3, 4 };

		for ( int i : arr )
		{
				cout<<i<<endl;
		}

		for ( int i : arr ) // call-by-value -> int& i or using pointer
		{
				cout<<i<<endl;
		}

		node n[] = {
				node{ 0, 0.0 },
				node{ 1, 1.1 }
		};

		for ( node nidx : n ) // call-by-value -> node& idx or using pointer
		{
				nidx.i = -1;
		}

		for ( node nidx : n )
		{
				cout<<nidx.i<<" "<<ndix.f<<endl;
		}

		return 0;
}
```

## The goto Statement

- 현대 프로그래밍 방법론에서 유해한 구조물로 간주!
- 현재 함수 내의 레이블이 붙은 문장으로 무조건 분기함으로써 다른 제어 흐름 메커니즘(if, for, while, do, switch)들이 제공하는 유용한 구조를 파괴
- When should a goto be used? → C-Assembly → Embedded ?
    - A simple answer is "not at all.”

# 5. Functions

## Function Definition

- type function_name ( parameter list ) { declarations statements }
    - head : type function_name ( parameter list )
    - body : { declarations statements }
    - function call
        - function_name( arguments );
- prototype
    - type function_name (parameter list);
    - 컴파일러에게 인자 type, 인자 수, return 값의 형을 알림
    - 매개변수 형 리스트(parameter type list)는 콤마로 분리
    - 식별자는 원형에 영향 없음 (생략해도 괜찮음)

## Function Invocation and Call-by-Value

- 값에 의한 호출(call by value)
- 인자는 지역적(local)으로 사용, 호출한 환경에 저장된 변수 값 변경 없음
- Call-by-Reference
    - Compare
        
        ```cpp
        int n0 = 10;
        /* 어떤 변수를 reference 할 것인가 오직 초기화 때만 결정 */
        int& n1 = n0; // n1 = nullptr; (illegal), 
        int* n2 = &n0;
        n1 = 3; // n0의 값이 변경됨.
        
        int n3 = 10;
        const int& n4 = n3;
        n3 = 3;
        n4 = 5; // const! like read-only (illegal)
        
        vector<int> v0;
        vector<int>& v1 = v0;
        vector<int>* v2 = &v0;
        
        int* n5 = new int(10);
        int& n6 = *n5;
        ```
        
    - Address
        - example
            
            ```cpp
            #include <iostream>
            
            using namespace std;
            
            void swap(int* px, int* py)
            {
            		int tmp = *px;
            		*px = *py;
            		*py = tmp;
            }
            
            int main(void) {
            		int x=0, y=1;
            		swap(&x, &y);
            		cout<<x<<endl;
            		cout<<y<<endl;
                return 0;
            }
            ```
            
    - Reference
        - example
            
            ```cpp
            #include <iostream>
            
            using namespace std;
            
            void swap(int& px, int& py)
            {
            		int tmp = px;
            		px = py;
            		py = tmp;
            }
            
            void print_value(const int& pval) // 변경x -> const
            {
            		cout<<pval<<endl;
            }
            
            void square(const int& l)
            {
            		return l*l;
            }
            
            struct person
            {
            		int w;
            }
            
            int& foo(person& p)
            {
            		return p.w;
            }
            
            int main(void) {
            		int x=0, y=1;
            		swap(x, y);
            		print_value(x);
            		print_value(y);
            
            		sqaure(10); // if const doesn't exist illegal. why? can't refer.
            
            		person p{60};
            		foo(p) = 50;
            
                return 0;
            }
            ```
            

## Defualt Params

- 함수의 원형을 별도로 선언하는 경우, 매개변수의 디폴트 값은 함수의 원형 선언에 위치
- 반드시 오른쪽 매개변수의 디폴트 값부터 채우는 형태로 정의할 것

```cpp
int power(int base, int exp = 2)
{
		...
}
```

## Function Overloading

- 함수호출 시 전달되는 인자를 통해서 호출하고자 하는 함수를 구분

```cpp
int count_digit(int n)
{
		int cnt = 0;
		while(num)
		{
				num /= 10;
				cnt++;
		}
		return cnt;
}

int count_digit(string n)
{
		return count_digit(stoi(n));
}

count_digit(12345);
count_digit("12345");
```

## Developing a Large Program

![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%203.png)

1. makefile
2. gcc -o  pgm main.c fct. prn.c

## Storage Classes

C언어에서 사용되는 변수는 두 가지 속성을 가진다. 

하나는 형(type)이고 또 다른 하나는 기억영역 클래스(storage class)이다.

1. auto
    1. 함수의 몸체 부분에서 선언된 변수는 디폴트로 auto(자동) 기억영역 클래스이다.
    2. 키워드 auto 를 사용하여 자동 기억영역 클래스임을 명시적으로 선언 할 수도 있다.
        1. auto int a, b, c
        2. auto float f;
    3. 지역변수들은 블록을 빠져 나가게 되면 모두 메모리에서 제거되어 사용할 수 없게 된다. 그러므로 변수가 저장하고 있던 값들을 잃게 된다.
2. extern ( global과 extern은 쓰지 말자.. )
    1. 블록과 함수 간에 정보를 교환하기 위한 방법 중 외부 변수(extern)를 사용하는 방법이 있다.
    2. 변수를 함수 밖에서 선언하면, 프로그램이 종료할 때까지 메모리에 계속 남아 있다.
    3. 외부변수(external variable)들은 전역변수(global variables)로 취급되어 외부 변수 선언 뒤에 있는 블록이나 함수가 끝나더라도 사라지지 않고 변수로 존재하게 된다.
    4. 함수 간에 정보를 전달하는 두 가지 방법
        1. 외부 변수
        2. 매개변수 메커니즘
    5. 외부 변수
        1. 사용이 용이
        2. 부작용이 발생할 가능성이 있음
    6. 매개변수 매커니즘
        1. 코드의 모듈성을 향상시킴
        2. 원하지 않는 부작용의 가능성을 줄일 수 있음
            1. 전역 변수의 경우, 함수 내부에서 변경 가능
3. register
    1. 기억영역 클래스 register 는 컴파일러에게 변수를 가능하다면 고속 메모리인 레지스터에 저장되도록 지시
    2. 한정된 자원으로 인해 할당하지 못하면, 이 기억영역 클래스는 디폴트로 자동 기억영역 클래스가 됨
    3. 이러한 변수는 사용되기 바로 전에 선언하는 것이 좋음
4. static
    1. 정적(static) 변수의 용도
        1. 기본용도 : 그 블록으로 다시 들어갈 때 지역 변수로 선언된 변수가 이전 의 값을 유지하고 있게 하는 것
        2. 외부 선언과 관련된 용도 (4-b 참조)
    2. 정적 외부 변수
        1. 정적 외부 구조물은 프로그램 모듈화에 있어서 매우 중요한 개념인 비공개를 제공함
        2. 비공개란 변수나 함수의 가시화 또는 유효범위의 제한을 의미함
        3. 정적 외부 변수의 유효범위는 자신이 선언되어 있는 원시 파일의 나머지 부분임
        4. 다른 파일에서 선언된 함수가 키워드 기억영역 클래스 extern을 사용하여 그 변수를 사용하고자 해도 사용할 수 없음
        5. example
            
            ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%204.png)
            

## The Type Qualifier const and volatile

- const
    - const는 선언에서 기억영역 클래스 뒤와 형 앞에 옴
    - 사용 예
        - static const int k = 3;
            - 이것은 "k는 기억영역 클래스 static인 상수 int이다"라고 읽음
    - const 변수는 초기화될 수는 있지만, 그 후에 배정되거나, 증가, 감소, 또는 수정될 수 없음
    - 변수가 const로 한정된다 해도, 다른 선언에서 배열의 크기를 명시하는 데는 사용될 수 없음
    - const#1
        - const int n = 3;
        - int v[n];
        - /* any C compiler should complain */
    - const#2
        - const int a = 7;
        - int *p = &a;
        - /* the compiler will complain */
            - p는 int를 포인트하는 보통의 포인터이기 때문에, 나중에 ++*p와 같은 수식을 사용하여 a에 저장되어 있는 값을 변경할 수 있음
    - const#3
        - const int a = 7;
        - const int *p = &a;
            - 여기서 p 자체는 상수가 아님
            - p에 다른 주소를 배정할 수 있지만, *p에 값을 배정할 수는 없음
    - const#4
        - int a;
        - int * const p = &a;
            - p는 int에 대한 상수 포인터임
            - 따라서, p에 값을 배정할 수는 없지만, *p에는 가능함
    - const#5
        - const int a = 7;
        - const int *const p = &a;
            - p는 상수 int를 포인트하는 상수 포인터임
            - 이제 p와 *p 모두는 배정될 수 없고, 증가나 감소도 안됨
- volatile
    - volatile 객체는 하드웨어에 의하여 어떤 방법으로 수정될 수 있음
    - extern const volatile int real_time_clock;
        - 한정자 volatile은 하드웨어에 의해 영향을 받는 객체임을 나타냄
        - 또한 const도 한정자이므로, 이 객체는 프로그램에서 증가, 감소, 또는 배정될 수 없음
        - 즉, 하드웨어는 변경할 수 있지만, 코드로는 변경할 수 없음

## Default Initialization

- C언어에서 외부 변수와 정적 변수는 프로그래머가 초기화하지 않아도 시스템에 의해 0으로 초기화된다.
- 이와 같은 방식으로 초기화 되는 것에는 배열, 문자열, 포인터, 구조체, 공용체가 있다.
- 반면에, 자동 변수와 레지스터 변수는 일반적으로 시스템에 의해 초기화되지 않는다.
    - garbage value 가질 수도 있음

## Recursion

- 재귀호출(Recursive) : 함수가 자기 자신을 호출
    - 단순한 재귀적 루틴은 일반적인 패턴을 따름
        - 재귀의 일반적인 패턴에서는 기본적인 경우와 일반적인 재귀 경우를 처리하는 코드가 있음
        - 보통 두 경우는 한 변수에 의해 결정됨
    - 일반적인 재귀 함수의 제어 흐름
        - 변수를 검사하여 기본적인 경우인지 일반적인 경우인지를 결정
        - 기본적인 경우일 때에는 더 이상 재귀 호출을 하지 않고 필요한 값을 리턴
        - 일반적인 경우일 때에는 그 변수의 값이 결국에 기본적인 경우의 값이 될 수 있게 하여 재귀 호출
- 재귀호출의 효율성
    - 많은 알고리즘은 재귀적 방식과 반복적 방식 둘 다로 표현할 수 있음
    - 전형적으로, 재귀가 더 간결하고 같은 계산을 하는 데 더 적은 변수를 필요로 함
    - 반면, 재귀는 각 호출을 위한 인자와 변수를 스택에 쌓아두어 관리하기 때문에 많은 시간과 공간을 요구함
    - 즉, 재귀를 사용할 때에는 비효율성을 고려해야 함
    - 그러나 일반적으로 재귀적 코드는 작성하기 쉽고, 이해하기 쉬우며, 유지 보수하기가 쉬움

**End of Functional C**

---

# 6. Arrays, Pointers, and Strings

## Arrays

```cpp
#include <iostream>

using namespace std;

int main(void)
{
		int n; cin>>n; // const int n = 10;
		int a[n]; // array size must be constant
		int s = size(a); // -> int s = sizeof(a) / sizeof(int);

		int b[n];
		memcopy(b, a, sizeof(a)); // -> copy(a, a+3, b);

		return 0;
}
```

## std::array

```cpp
#include <iostream>
#include <array>

using namespace std;

int main(void)
{
		array<int, 5> a{};
		a.at(3);
		a.size();
		a.front(); a.back();

		array<int, 3> a0{ 0, 1, 2 };
		array<int, 3> a1{ 2, 1, 0 };
		a0.swap(a1);
		a0 = a1;
		a0 == a1; // same size, dictionary order

		return 0;
}
```

## Pointers

- p = 0;
- p = NULL; /* equivalent to p = 0 ; */
- p = &I ; /* i의 주소를 갖는 포인터 변수 */
- p = (int *) 1776; /* an absolute address in memory */

![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%205.png)

![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%206.png)

- 지정할 수 없는 구조
    - 상수
        - &3 /* illegal */
    - 일반식
        - &(k ＋ 99) /* illegal */
    - register 변수
        - register v;
        - &v /* illegal */

## Call-by-Reference

- C는 기본적으로 Call-by-Value(값에 의한 호출) 사용
- Call-by-Reference(참조에 의한 호출)의 효과를 얻기 위해서는 함수 정의의 매개변수 목록에서 포인터를 사용
- "Call-by-Reference"의 효과를 얻는 방법
    1. 함수 매개변수를 포인터형으로 선언
    2. 함수 호출 시 주소를 인자로 전달
    3. 함수 구현에서 역참조 포인터 사용

## The Relationship Between Arrays and Pointers

- 배열 이름 그 자체는 주소 또는 포인터 값이고, 배열과 포인터에는 둘 다 첨자를 사용할 수 있음
    - a와 p는 포인터이고 둘 다 첨자를 붙일 수도 있음
        - a[i] is equivalent to *(a + i)
        - p[i] is equivalent to *(p + i)
    - 포인터 변수는 다른 값을 가질 수 있음. 하지만, 배열 이름은 값이 고정된(상수) 포인터이다.
        - p = a + i;
        - a = q; /* Illegal */
- 포인터 변수는 다른 주소들을 값으로 가질 수 있음
- 반면에 배열 이름은 고정된 주소 또는 포인터임

## Pointer Arithmetic and Element Size

- 포인터 연산은 C의 강력한 특징 중 하나
- 변수 p를 특정형에 대한 포인터라고 하면, 수식 p + 1은 그 형의 다음 변수를 나타냄
- p와 q가 모두 한 배열의 원소들을 포인트하고 있다면, p - q는 p와 q 사이에 있는 배열 원소의 개수를 나타내는 int 값을 생성함
    
    ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%207.png)
    

## Arrays as Function Arguments

- 함수 정의에서 배열로 선언된 형식 매개변수는 실질적으로는 포인터임
- 함수의 인자로 배열이 전달되면, 배열의 기본 주소가 "값에 의한 호출"로 전달됨
- 배열 원소 자체는 복사되지 않음
- 표기 상의 편리성 때문에 포인터를 매개변수로 선언할 때 배열의 각 괄호 표기법을 사용할 수 있음
    
    ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%208.png)
    

## Dynamic Memory Allocations With calloc() and malloc()

- C : stdlib.h에 정의되어 있음
    - calloc: contiguous allocation
    - malloc: memory allocation
- calloc()과 malloc()을 이용해 배열, 구조체, 공용체를 위한 메모리 공간을 동적으로 생성할 수 있음
- calloc()과 malloc()
    - 각 원소의 크기가 el_size인 n개의 원소를 할당하는 방법
        - calloc(n, el_size);
        - malloc(n * el_size);
    - calloc()은 모든 원소를 0으로 초기화하는 반면 malloc()은 하지 않음
    - 할당 받은 메모리를 반환하기 위해서 free() 사용
    - cpp : new&delete examples
        
        ```cpp
        /* pointer */
        int *i = new int(123);
        i = nullptr; // NULL macro in C, null ptr -> nullptr_t type!
        delete i;
        
        /* array */
        int *arr = new int[10];
        delete arr[];
        
        int* arr = new int[a] { 1, 2, 3 };
        delete[] arr; 
        
        /* structure */
        struct person
        {
        		int weight;
        		int height;
        }
        
        person* person = new person { 60, 170 };
        person* person[2] =
        {
        		new person { 50, 160 };
        		new person { 60, 170 };
        };
        
        for (Person* person : person )
        {
        		person->weight = 0;
        }
        
        /* class */
        class C
        {
        		int i;
        };
        
        C *pC = new C();
        delete pC;
        ```
        
        1. malloc은 해당 포인터의 타입을 모르기 때문에 리턴 값의 자료형은 (void *). 때문에 malloc함수를 사용 시 자료형을 앞에 선언. 하지만 new는 type-safe(컴파일러가 확인)로 해당 객체에 맞는 포인터로 반환. 때문에 별도의 자료형 선언을 할 필요가 없음.
        2. new를 이용해 객체를 생성하면 초기 값을 줄 수 있음. new로 객체를 생성하면 생성자가 호출됨. 하지만 malloc은 생성자 호출 기능이 없음.
        3. new를 통해 객체생성시 에러가 발생하면 예외처리를 하지만 malloc은 예외처리 없이 NULL값을 반환
        4. malloc은 realloc으로 할당된 메모리 크기를 재조정이 가능 하지만 new는 할당된 크기에 대한 메모리 재조정이 불가능
        5. delete는 소멸자를 호출 하지만 free는 소멸자를 호출해 줄 기능을 갖고 있지 않음

## Strings

- char 형의 1차원 배열
- 문자열은 끝의 기호인 \0, 또는 널 문자로 끝남
- 널 문자: 모든 비트가 0인 바이트; 십진 값 0
- 문자열의 크기는 \0까지 포함한 크기
- 문자열 상수 (constant!!!)
    - 큰따옴표 안에 기술됨
    - 문자열 예 : "abc”
        - 마지막 원소가 널 문자이고 크기가 4인 문자 배열
    - 주의 - "a"와 'a'는 다름
        - 배열 "a"는 두 원소를 가짐
        - 첫 번째 원소는 'a', 두 번째 원소는 '\0’
    - 컴파일러는 문자열 상수를 배열 이름과 같이 포인터로 취급
        - char *p = "abc";
        - printf("%s %s\n", p, p + 1); /* abc bc is printed */
            - 변수 p에는 문자 배열 "abc"의 기본 주소가 배정
            - char 형의 포인터를 문자열 형식으로 출력하면, 그 포인터가 포인트하는 문자부터 시작하여 \0이 나올 때까지 문자들이 연속해서 출력됨
    - "abc"와 같은 문자열 상수는 포인터로 취급되기 때문에 "abc"[1] 또는 *("abc" + 2)와 같은 수식을 사용할 수 있음
- 배열과 포인터의 차이
    - char *p = "abcde”; → **in CPP : const char* p “abcde”;**
    - char s[]= "abcde";
        - // char s= {'a', 'b', 'c', 'd', 'e', '\0'};
        
        ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%209.png)
        

## String-Handling Functions in the Standard Library

- #include <string.h> → <cstring>
    - char *strcat(char *s1, const char *s2);
        - 두 문자열 s1,s2를 결합하고, 결과는 s1에 저장
    - int strcmp(const char *s1, const char *s2);
        - s1과 s2를 사전적 순서로 비교하여, s1이 작으면 음수, 크면 양수, 같으면 0을 리턴
    - char *strcpy(char *s1, const char *s2);
        - s2의 문자를 \0이 나올 때까지 s1에 복사
    - size_t strlen(const char *s);
        - \0을 뺀 문자의 개수를 리턴

## Strings in CPP

```cpp
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
		string str = "abcd"; // index 접근 가능, 객체끼리 연산/비교 가능.
		str.size(); // str.length();

		string str1 = to_string(123); // int to string <-> stoi(), stof()...

		string str2;
		std::getline(cin, str2);

		return 0;
}
```

## Multidimensional Arrays

- C 언어는 배열의 배열을 포함한 어떠한 형의 배열도 허용함
- 2차원 배열은 두 개의 각괄호로 만듬
- 이 개념은 더 높은 차원의 배열을 만들 때에도 반복적으로 적용됨
- 2차원 배열
    - 2차원 배열은 행과 열을 갖는 직사각형의 원소의 집합으로 생각하는 것이 편리함
        - 사실 원소들은 하나씩 연속적으로 저장됨
    - int a[3][5];
        - (&a[0][0] + 5 * i + j)
- 3차원 배열
    - int a[7][9][2];
        - (&a[0][0][0] + 9 * 2 * i + 2 * j + k)
        - 함수 정의 헤더에서 다음은 다 같음
            - int sum(int a[][9][12])
            - int sum(int a[7][9][12])
            - int sum(int (*a)[9][12])
- 기억장소 사상 함수
    - 배열에서 포인터 값과 배열 첨자 사이의 사상

## Ragged Arrays

![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2010.png)

- 래기드 배열 : 배열의 원소인 포인터가 다양한 크기의 배열을 포인트하는 것
- 앞의 프로그램에서 p의 행들은 다른 길이를 갖기 때문에, p를 래기드 배열이라고 할 수 있음

![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2011.png)

- 출력
    - abc abc: a is for apple
    - abc abc: a is for apple
- 래기드 배열: 식별자 a
    - 2차원 배열
    - 30개의 char 형을 위한 공간이 할당
    - 즉, a[0]과 a[1]은 15개 char의 배열
    - 배열 a[0]은 다음으로 초기화됨: {'a', 'b', 'c', ':', '\0'}
    - 5개의 원소만 명시되어 있기 때문에, 나머지는 0(널 문자)으로 초기화됨
    - 이 프로그램에서 배열의 모든 원소가 사용되지는 않지만, 모든 원소를 위한 공간이 할당됨
    - 컴파일러는 a[i][j]의 접근을 위해 기억장소 사상 함수를 사용
    - 즉, 각 원소를 접근하기 위해서는 한 번의 곱셈과 한 번의 덧셈이 필요함
- 래기드 배열: 식별자 p
    - char 포인터의 1차원 배열
    - 이 선언으로 두 포인터를 위한 공간이 할당
    - p[0] 원소는 "abc :"를 포인트하도록 초기화되고, 이 문자열은 5개의 char를 위한 공간을 필요로 함
    - p[1] 원소는 "a is ..."를 포인트하도록 초기화되고, 이 문자열은 15개의 char를 위한 공간을 필요로 함
    - 즉, p는 a보다 더 적은 공간을 사용
    - p[i][j] 접근을 위해 기억장소 사상 함수 사용하지 않음
    - (p를 사용하는 것이 a를 사용하는 것보다 빠름)
    - a[0][14]는 유효한 수식이지만, p[0][14]는 그렇지 않음
    - p[0]과 p[1]은 상수 문자열을 포인트함 - 변경할 수 없음

## Functions as Arguments

- 함수의 포인터는 인자로서 전달될 수 있고, 배열에서도 사용되며, 함수로부터 리턴될 수도 있음

![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2012.png)

- 앞의 코드에서 식별자 x는 사람을 위한 것으로, 컴파일러는 무시함 즉, 다음과 같이 해도 됨

![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2013.png)

- 포인터 f를 함수처럼 취급할 수도 있고, 또는 포인터 f를 명시적으로 역참조할 수도 있음
    - 즉, 다음 두 문장은 같음
        - sum += f(k) * f(k);
        - sum += (*f)(k) * (*f)(k);
- 인자로서의 함수
    - (*f)(k)
        - f 함수에 대한 포인터
        - *f 함수 그 자체
        - (*f)(k) 함수 호출

```cpp
int sum(int a, int b)
{
		return a+b;
}

/* func ptr 0 */
int (*fp)(int, int) = &sum; // pointer is fp! &없어도됨.
(*fp)(1, 2); // function call

/* func ptr2 */
int (&fp)(int, int) = sum;
(*fp)(1, 2);
(*sum)(1, 2);

/* func ptr 3 */
typedef int (*FuncType)(int, int);
FuncType fp = sum;

/* func ptr 4 */
using FuncType = int(*)(int, int);

/* func ptr 5 */
auto fp = sum; // auto는 c에서와 의미가 다름

/* func ptr 6 */
#include <functional>
function<int(int, int)> fp = sum;
```

## void pointer

```cpp
#include <iostream>

using namespace std;

int main(void)
{
		int n = 10;
		int* p = &n;

		void* vp = p;
		int* p0 = (int*)vp; // malloc()의 원리
		int* p1 = (int*)malloc(sizeof(int)*3); // malloc()은 void*를 return 이후 casting

		return 0;
}
```

## std-vector

```cpp
#include <iostream>
#include <vector>

// array<int, 5> arr{1, 2, 3};

using namespace std;

int main(void)
{
		int size;
		cin >> size;
		vector<int> vec(size); // compile time에 몰라도 됨.

		vector<int> vec2(5, 2); // size 5, initialize all elements 2
		int i;
		for ( i=0; i<vec.size(); i++ )
		{
				cout << vec[i] << endl;
		}

		vec2.resize(10, 5); // size를 10으로 조정, 추가된 공간은 5로 초기화 기존공간 변경X
		for(int num : vec)
		{
				cout << num << endl;
		}
		
		// vector의 경우 내부적으로 동적배열을 이용, 재할당이 일어날 수 있고 
		// 이를 막기위해 reserver() 사용하기도 함. 
		vector<int> vec3; // size 0
		vec3.push_back(10); // 10을 vec3 제일 뒤에 추가
		vec3.data();
		vec3.pop_back(); // back <-> front

		// 비교 연산도 가능 단 앞에서 부터 사전식으로 check
		vector<int> vec4{ 1, 2, 3 };
		vector<int> vec5{ 3, 2, 1 };
		vec4.swap(vec5);
		vec4 = vec5;
		
		return 0;
}
```

## 함수 호출 규약

## inline

- 프로그램 코드 라인 안으로 들어간 함수
- 자주 호출되고 짧은 함수의 경우.
- #define 매크로
    - 복잡한 경우 매크로의 형태로 정의하는데 한계
    - 자료형에 의존적이지 않다는 장점이 있음
- 관행적으로 prototype을 잘 만들지 않는다고 함.

```cpp
inline int square(int n)
{
		return n*n;
}
```

# 7. Bitwise Operators and Enumeration Types

- int/long/pointer
    
    ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2014.png)
    
- unsigned

```cpp
// base10 -> 00000001, 8bit max value = 255
uint8_t num0 = 1;
// base8 -> 00000000 00010000, 16bit max value = 65535
uint16_t num1 = 020;
// base16 -> 00000000 00000000 00000000 11111111, 32bit max value = 4294967295
uint32_t num2 = 0xff;
// base2 -> 00000000 00000000 00000000 00001010
uint32_t num3 = 0b1010;
```

- signed
    - 2의 보수
        - 각 비트 반전
        - 1을 더함
    - 음수의 절대 값을 알고 싶으면 원래 수를 알고 싶으면 다시 비트 반전 후 1을 더하면 됨

```cpp
/* 
 * 10000000
		* 1 is Most Significant Bit(MSB)
		* Sign Bit
		* 1 is negative
		* 0 is positive
*/
```

- Floating Point
    
    ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2015.png)
    
    - float : 부호1 지수8 가수23
    - double : 부호1 지수11 가수52

## Bitwise Operators and Expressions

- 이진숫자의 문자열로 표현된 정수적 수식에 사용
- 시스템 종속적
- 여기서는 8 비트 바이트, 4 바이트 워드, 2의 보수로 표현되는 정수, 그리고 ASCII 문자 코드를 갖는 컴퓨터를 가정함
    
    ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2016.png)
    
- 왼쪽과 오른쪽 이동 연산자
    - 이동 연산자의 두 피연산자는 정수적 수식이어야 함
    - 각 피연산자에 정수적 승격이 일어남
    - 전체 수식의 형은 승격된 왼쪽 피연산자의 형이 됨
    - 왼쪽 이동 연산자
        - expr1 << expr2
        - expr1의 비트 표현을 expr2가 지정하는 수만큼 왼쪽으로 이동
        - 하위 비트로는 0이 들어옴
        - 수식에서 c는 int 형으로 승격됨
        - 따라서 결과는 4 바이트에 저장됨
            
            ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2017.png)
            
    - 오른쪽 이동 연산자
        - expr1 >> expr2
        - 왼쪽 이동 연산자와 대칭적이지 않음
        - 부호가 없는 정수적 수식에서는 상위 비트로 0이 들어옴
        - 부호가 있는 형일 때에는 시스템에 따라 상위 비트로 0이 들어오는 것도 있고, 1이 들어오는 것도 있음
            
            ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2018.png)
            

## Masks & Packing and Unpacking

- 마스크 : 다른 변수나 수식으로부터 원하는 비트를 추출하는데 사용되는 상수나 변수
- 패킹
    - 4개의 문자를 하나의 int형에 패킹하는 함수
        
        ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2019.png)
        
- 언패킹
    - 32비트 int안에 있는 문자를 검색하는 함수
        
        ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2020.png)
        

## Enumeration Types

- 키워드 enum은 열거형을 선언하는데 사용됨
- 이것은 유한집합을 명명하고, 그 집합의 원소로서 식별자를 선언하는 수단을 제공함
- example
    - enum day {sun, mon, tue, wed, thu, fri, sat};
        - 사용자 정의형 enum day 생성
        - day : 태그 이름
        - 열거자는 식별자 sun, mon, ..., sat이고, 이들은 int 형 상수임
        - 디폴트로 첫 번째 원소는 0이고, 각 원소는 이전 원소의 값보다 하나 큰 값을 가짐
        - 이것은 형 정의임
    - enum day d1, d2;
        - enum day 형 변수의 선언
    - d1 = fri;
        - d1, d2 변수의 사용

```cpp
/* Scoped Enumeration C++11 */
enum struct e0 {
		ea = 1,
		eb = 2,
		ec = 4,
		ed = 8
};

enum class e1 : int64_t {
		ea = 1
};

int i = (int)e0::ea + (int64_t)e1::ea; // must be cast! 
```

# 8. The Preprocessor

## 전처리기

- C 언어는 전처리기를 사용하여 그 능력과 표기법을 확장함
- #으로 시작하는 행을 전처리 지시자라고 함
    - #include …
    - #define …
    - #if …
    - #error …
- ANSI C에서 #은 여백 문자 다음에 올 수 있지만, 전통적인 C에서는 첫 번째 열에 #이 와야만 함
- 전처리 지시자를 위한 구문은 C 언어의 나머지 부분과 독립적임
- 전처리 지시자가 영향을 미치는 범위는 그 파일에서 전처리 지시자가 있는 위치에서 시작하여 그 파일의 끝까지이거나, 다른 지시자에 의해서 그 지시자의 효력이 없어질 때까지 임
- 전처리기는 C를 알지 못함

## The Use of #include

- 지정된 파일을 읽어 들임
- #include에 명시되는 파일의 내용은 제한이 없음
- 또한 그 파일은 전처리기에 의해 다시 확장되어야 하는 또 다른 전처리 지시자를 포함할 수도 있음
- #include "filename”
    - 이 행은 filename 파일의 사본으로 대치됨
    - filename 파일은 먼저 현재 디렉토리에서 검색하고, 거기에 없다면 시스템이 정의한 디렉토리에서 검색함
- #include <filename>
    - 이것은 시스템이 정의한 디렉토리에서만 검색함
    - UNIX 시스템에서 stdio.h와 stdlib.h 같은 표준 헤더 파일은 /usr/include에 있음
    - 일반적으로, 표준 헤더 파일이 저장된 장소는 시스템에 따라 다름

## The Use of #define

- 두 가지 형식
    - #define identifier token_string // token_string is optional
        - 전처리기는 문자열을 제외한 파일의 모든 identifier를 t_string으로 대치
    - #define identifier(id_1,..., id_n) token_string // token_string is optional
        - 첫 번째 identifier와 왼쪽 괄호 사이에는 공백이 없어야 함
        - 매개변수 목록에는 식별자가 없거나 또는 여러 개가 올 수 있음
        - example
            - #define SQ(x) ((x) * (x))
            - #define F_POW(x) sqrt(sqrt((CUBE(x)))
            - #define min(x, y) (((x) < (y)) ? (x) : (y))
            - #define min4(a, b, c, d) min(min(a, b), min(c, d))
                - 매크로를 정의할 때 올바른 평가 순서를 유지하기 위해 괄호를 적절히 사용해야 함
        - 매크로를 정의할 때, 매크로 몸체에 매크로나 함수를 사용할 수 있음
    - #undef는 매크로 정의를 무효화함
        - #undef identifier
    - 전처리기 결과 보기
        - cc -E file.c
- 정의가 길어질 경우에 현재 행의 끝에 역슬래시 \를 삽입하면, 다음 행에 연결해서 계속 쓸 수 있음
- 프로그램의 명확성과 이식성을 높일 수 있음
- 특수한 상수들도 기호 상수로 코딩될 수 있음
- 기호 상수는 불명확한 상수를 연상 기호 식별자로 바꿈으로써 프로그램의 문서화에 도움을 줌
- 시스템에 따라 달라지는 상수를 한번에 변경할 수 있으므로 이식성을 높여 줌
- 상수의 실제 값을 검사하는데 한 곳만 검사하면 되므로 신뢰성도 높여 줌

## The Macros in stddef.h, stdio.h and ctype.h

- <stddef.h>
    - 이 헤더 파일은 다른 곳에서 공통적으로 사용되는 몇 가지 형 정의과 매크로를 포함하고 있음
    - examples
        - typedef int ptrdiff_t; /* pointer difference type */
        - typedef short wchar_t; /* wide character type */
        - typedef unsigned size_t; /* the sizeof type */
        - #define NULL ((void *) 0)
- <stdio.h>
    - #define getchar() getc(stdin)
    - #define putchar(c) putc((c), stdou
- <ctype.h>
    - isalpha(c) : Nonzero(true) is returned if c is charactor
    - toupper(c) : value returned

## Conditional Compilation

```cpp
/******************** How to use **********************/
#if constant_integral_expression
...
#endif
/******************************************************/
#if
#elif constant_integral_expression | #else
#endif
/******************************************************/
#ifdef identifier // or #if defined(identifier)
...
#endif
/******************************************************/
#ifndef identifier
...
#endif
/******************** For debugging *******************/
#define DEBUG 1
...
#if DEBUG
debugging code
#endif
/******************************************************/
#define DEBUG
...
#ifdef DEBUG
debugging code
#endif
```

- 코드가 컴파일되기 위해서는 #if 다음의 상수 수식이 영이 아닌 값(참)을 가져야 함
- #ifdef나 #if defined와 #endif 사이의 코드가 컴파일되기 위해서는 identifier가 이미 정의되어 있어야 하고, 그 identifier가 취소(#undef identifier)되지 않았어야 함
- #ifndef와 #endif 사이의 코드가 컴파일되기 위해서는 #ifndef 다음의 identifier가 현재 정의되어 있지 않아야 함

## The Predefined Macros

- ANSI C에는 미리 정의된 다섯 개의 매크로가 있고, 이 매크로는 항상 사용할 수 있으며, 프로그래머가 정의를 해제할 수 없음
- 각 매크로 이름은 두개의 밑줄문자로 시작해서 두개의 밑줄문자로 끝남

![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2021.png)

## The Operators # and ##

- # 연산자
    - "문자열화" 연산자
    - #define message_for(a, b) printf(#a " and " #b ": We love you!\n")
- ## 연산자
    - 토큰 결합 연산자
    - #define X(i) x ## i

## The Use of #error and #pragma

- #error
    - 조건들을 강요하기 위해 사용
    - 전처리기가 #error를 만나면, 컴파일 오류가 발생하고, 이 지시자 다음에 쓰인 문자열이 화면에 출력됨

## Line Numbers

- #line integral_constant "filename”
- 이것은 컴파일러로 하여금 원시 프로그램의 행 번호를 다시 매기게 하여 그 다음 행의 번호가 integral_constant가 되게 함
- 또한 컴파일러에게 현재 원시 파일의 이름이 filename이라고 믿게함
- 파일 이름이 명시되지 않으면, 행 번호만을 다시 매김
- 보통 행 번호는 프로그래머에게 감추어지고, 경고나 구문 오류가 발생될 때에만 나타남

## Corresponding Functions

- 표준 헤더 파일에 있는 매개변수를 갖는 대부분의 매크로는 이와 대응되는 함수를 표준 라이브러리에 가지고 있음
- 매크로 대신 함수를 사용하기 위해서는 다음과 같이 함
    1. 함수 사용 전에 다음과 같은 행을 삽입함
        1. #undef isalpha
    2. 다음과 같이 호출함
        1. (isalpha)(c)

# 9. Structures and Unions

- C 언어의 확장 방법
- 매크로와 라이브러리
- 사용자 정의 형 (배열, 구조체, 공용체)

## Using Structures with Functions

- 구조체는 함수의 인자로써 함수에 전달될 수 있고, 함수로부터 리턴될 수도 있음
- 함수의 인자로서 구조체가 전달될 때 구조체는 값으로 전달됨
- 구조체가 많은 멤버를 가지거나, 큰 배열을 멤버로 가질 경우, 함수의 인자로 구조체를 전달하는 것은 상대적으로 비효율적임
- 따라서 대부분의 응용 프로그램에서는 함수의 인자로 구조체의 주소를 사용함

## Unions

- 공용체는 구조체와 비슷한 구문 형식을 가지지만 각 멤버들은 같은 기억장소를 공유함
- 공용체형은 메모리의 같은 위치에 저장될 여러 값의 집합을 정의
- 저장된 값을 올바르게 해석하는 것은 프로그래머의 책임
- 컴파일러는 공용체의 멤버 중에서 가장 큰 기억장소를 요구하는 멤버의 요구만큼 기억장소를 할당
- 패딩?

## Bit Fields

- 구조체나 공용체에서 int 형이나 unsigned 형의 멤버에 비트 수(폭)를 지정하는 것
- 폭은 콜론 다음에 음수가 아닌 정수적형 상수 수식으로 지정되고, 최대 값은 기계 워드의 비트 수와 같음
- 일반적으로 비트 필드는 구조체의 연속적인 멤버로 선언되며, 컴파일러는 이 멤버들을 최소의 기계 워드로 패킹함
- unsigned 비트 필드에는 음수가 아닌 정수만이 저장되고, int 비트 필드는 시스템에 따라 다름 - 보통 unsigned 비트 필드를 사용
- 비트 필드의 배열은 허용되지 않음
- 비트 필드에 주소 연산자 &를 적용할 수 없음
    - 즉, 멤버 접근 연산자 ->를 사용할 수는 있어도, 포인터가 직접 비트 필드를 포인트할 수는 없음

```cpp
struct pcard {
unsigned pips : 4;
unsigned suit : 2;
};
struct pcard c; // c는 6 비트에 저장됨

/* 대부분의 컴퓨터에서는 비트 필드가 워드 경계에 걸치지 않도록 할당됨 */
struct abc {
int a : 1, b : 16, c : 16;
} x;

/*
		* 이 경우 x는 두 워드에 다음과 같이 저장됨
				* 첫 번째 워드 : 비트 필드 a와 b 저장
				* 두 번째 워드 : c 저장
*/
```

- 패딩과 정렬을 위해 이름 없는 비트 필드나 폭이 0인 비트 필드를 사용할 수 있음
    
    ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2022.png)
    
- 비트와 바이트를 접근하기 위해 다음과 같이 선언할 수 있음
    
    ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2023.png)
    
    ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2024.png)
    

## Self-referential Structures

- 자기참조 구조체는 자기 자신의형을 참조하는 포인터멤버를 가짐
- 이러한 자료구조를 동적자료구조라고 함
- 배열이나 단순변수는 일반적으로 블록을 진입할 때 메모리할당을 받지만, 동적자료구조는 기억장소관리루틴을 사용하여 명시적으로 메모리할당을 요구함

## Polish Notation and Stack Evaluation

- 중위 수식을 후위 수식으로 만드는 방법
    1. 중위 수식을 연산자의 우선순위에 따라 완전한 괄호 표현으로 변환
        1. 1 + 3 * 4 → (1 + (3 * 4))
    2. 각 연산자를 그 연산자를 포함하는 괄호 중 제일 가까운 닫는 괄호 뒤로 보냄
        1. (1 + (3 * 4) ) → (1 (3, 4) * ) +
    3. 괄호 제거
        1. 1, 3, 4, *, +
- 폴리시 수식 계산
    - 수식의 각 항목을 왼쪽에서 오른쪽으로 검사하며 다음과 같은 일을 반복한다.
        1. 현재 검사되는 항목이 숫자이면 다음 항목을 검사한다.
        2. 현재 검사되는 항목이 연산자이면 앞의 두 항목(숫자)을 이 연산자의 피연산자로 하여 계산한 후 새로운 항목으로 삽입한다.
        3. 이러한 일은 하나의 숫자가 남을 때까지 반복하고, 마지막 남은 수가 이 수식의 값이다.
    - 폴리시 수식 계산 예제
        - 13, 4, -, 2, 3, *, +
        - 9, 2, 3, *, +
        - 9, 6, +
        - 15
            
            ![Untitled](CwithCPP%209f30ad733c7847f5a8f43107db8ae5ef/Untitled%2025.png)
            

---