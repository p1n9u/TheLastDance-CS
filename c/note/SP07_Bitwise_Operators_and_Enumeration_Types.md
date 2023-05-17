# Bitwise Operators and Enumeration Types

## Bitwise Operators and Expressions

- 비트단위 연산자
    - 이진숫자의 문자열로 표현된 정수적 수식에 사용
    - 시스템 종속적
    - 여기서는 8 비트 바이트, 4 바이트 워드, 2의 보수로 표현되는 정수, 그리고 ASCII 문자 코드를 갖는 컴퓨터를 가정함
    - [Operators and Punctuators](../note/SP02_Lexical_Elements_Operators_and_the_C_System.md#operators-and-punctuators) 참조
- signed int의 음수 표현 : n-bit(s)
    - 양수
        - 부호 비트는 0으로 놓고, 남는 숫자로 2진수 표현
    - 음수
        - 부호절대값 방법
            
            $-{(2^{n-1}-1)} \sim {(2^{n-1}-1)}$
            
            - 부호 비트를 제외한 수를 양수값으로 읽고, 마이너스 붙임
            - 인간의 입장에서 직관적이지만, 음수의 덧셈이 양수의 뻴셈과 처리 방법이 달라짐
            - 해결을 위해선 피연산자의 절대값을 서로 비교하는 등 추가 연산 필요
        - 1의 보수 방법
            
            $-{(2^{n-1}-1)} \sim {(2^{n-1}-1)}$
            
            - 양수값의 비트를 반전시켜서 음수를 표현
            - 음수의 덧셈과 양수의 뺄셈이 동일하게 처리됨
            - 0을 나타내는 값이 0000…0과 1111…1의 두 가지
            - 덧셈 연산 시 end around carry가 발생해서 1을 더해줘야 함
        - 2의 보수 방법
            
            $-{2^{n-1}} \sim {(2^{n-1}-1)}$
            
            - 1의 보수에 1을 더하는 방법
            - 1111…1이 1을 의미
            - 음의 부호를 붙일 때 1을 더해주는 연산을 해야함

```c
char c = 'Z';
/**
 * Expr         Representation                          Action
 * c            00000000 00000000 00000000 01011010     unshifted
 * c << 1       00000000 00000000 00000000 10110100     left shifted 1
 * c << 4       00000000 00000000 00000101 10100000     left shifted 4
 * c << 31      00000000 00000000 00000000 00000000     left shifted 31
 */

int a = 1 << 31;
unsigned b = 1 << 31;
/**
 * Expr         Representation                          Action
 * a            10000000 00000000 00000000 00000000     unshifted
 * a >> 3       11110000 00000000 00000000 00000000     right shifted 3
 * b            10000000 00000000 00000000 00000000     unshifted
 * b >> 3       00010000 00000000 00000000 00000000     right shifted 3
 */
```

- 왼쪽과 오른쪽 이동 연산자
    - 이동 연산자의 두 피연산자는 정수적 수식이어야 함
    - 각 피연산자에 정수적 승격이 일어남
    - 전체 수식의 형은 승격된 왼쪽 피연산자의 형이 됨
- 왼쪽 이동 연산자
    - `expr1 << expr2`
        - expr1의 비트 표현을 expr2가 지정하는 수만큼 왼쪽으로 이동
        - 하위 비트로는 0이 들어옴
        - 수식에서 c는 int 형으로 승격됨
        - 따라서 결과는 4바이트에 저장됨
- 오른쪽 이동 연산자
    - `expr1 >> expr2`
        - 왼쪽 이동 연산자와 대칭적이지 않음
        - 부호가 없는 정수적 수식에서는 상위 비트로 0이 들어옴
        - 부호가 있는 형일 때에는 시스템에 따라 상위 비트로 0이 들어오는 것도 있고, 1이 들어 오는 것도 있음

## Masks

- [마스크](https://en.wikipedia.org/wiki/Mask_(computing)) : 다른 변수나 수식으로부터 원하는 비트를 추출하는데 사용되는 상수나 변수

## Packing and Unpacking

```c
/*
 * Packing
 * Pack 4 characters into an int.
 */

#include <limits.h>

/**
 * p will be packed with a, b, c, d
 * ___a
 * __a_ __ab
 * _ab_ _abc
 * abc_ abcd
 */
int pack(char a, char b, char c, char d)
{
	int p = a;

	p = (p << CHAR_BIT) | b;
	p = (p << CHAR_BIT) | c;
	p = (p << CHAR_BIT) | d;

	return p;
}
```

```c
/*
 * Unpacking
 * Unpack a byte from an int.
 */

#include <limits.h>

/**
 * @k: 0, 1, 2, or 3
 * @n: 0, 8, 16 or 24
 * @mask: lower-order byte
 */
char unpack(int p, int k)
{
	int n = k * CHAR_BIT;
	unsigned mask = 255;

	mask <<= n;
	return ((p & mask) >> n);
}
```

## Enumeration Types

- 키워드 enum은 열거형을 선언하는데 사용됨
- 이것은 유한집합을 명명하고, 그 집합의 원소로서 식별자를 선언하는 수단을 제공함

```c
enum day {
	sun,
	mon,
	tue,
	wed,
	thu,
	fri,
	sat
};

enum day d1, d2;
d1 = fri;
if (d1 == d2)
	... /* do something */

/**
 * Declaration examples
 */
enum suit {clubs = 1, diamonds, hearts, spades} a, b, c;
enum fruit {apple = 7, pear, orange = 3, lemon} frt;
enum veg {beet = 17, carrot = 17, corn = 17} vege1, vegw2;
enum {fir, pine} tree;
enum veg {beet, carrot, corn} veg;
```

- 사용자 정의형 enum day 생성
- day : tag name
- 열거자는 식별자 sun, mon, …, sat이고, 이들은 int 형 상수임
- 디폴트로 첫 번째 원소는 0이고, 각 원소는 이전 원소의 값보다 하나 큰 값을 가짐
- 이것은 형 정의임
