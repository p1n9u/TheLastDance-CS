# The Fundamental Data Types

## Declarations, Expressions, And Assignment

- 선언(Declarations)
    - 모든 변수는 사용전에 선언
    - 목적 : 메모리 공간 확보 , 올바른 연산 수행
    - 올바른 연산자의 선택
- 수식(Expressions)
    - 상수, 변수, 연산자, 함수 호출 등의 의미있는 결합
    - 상수, 변수, 함수 호출은 그 자체가 수식임
- 배정(Assignment)
    - 문장 : 수식 뒤에 세미콜론이 오면 , 수식은 문장이 됨
        - i = 7  → 배정 수식
        - i = 7; → 문장
        - 3.777; → 문법은 문제 없으나 용도가 없음
        - a + b; → 문법은 문제 없으나 용도가 없음

## The Fundamental Data Types

- [types](https://en.cppreference.com/w/cpp/language/types)
- Literals
    - [integer](https://en.cppreference.com/w/cpp/language/integer_literal)
    - [character](https://en.cppreference.com/w/cpp/language/character_literal)
    - [floating](https://en.cppreference.com/w/cpp/language/floating_literal)
    - [string](https://en.cppreference.com/w/cpp/language/string_literal)
    - [bool](https://en.cppreference.com/w/cpp/language/bool_literal)

## The Use of typedef

- typedef : 식별자를 특정한 형과 연관
    - typedef char uppercase;
    - typedef int INCHES, FEET;
    - typedef unsigned long size_t ; /* found in stddef.h */
- 변수 , 함수 선언시 사용
    - uppercase u;
    - INCHES length, width;
    - 긴 선언문을 축약해 쓸 수 있음
    - 목적에 따라 형 이름을 사용
    - 사용하는 컴퓨터에 따라 형의 메모리 할당 byte 수가 달라질 경우 , 이식하기 쉽게 만듦

## The sizeof Operator

- sizeof : 객체 저장시 메모리 할당 byte 수 알기 위해 사용
    - sizeof (object)
    - Not Function

## The Use of getchar() and putchar()

- <stdio.h> 에 정의된 매크로
- getchar()
    - 키보드에서 문자 읽는 매크로
- putchar()
    - 화면에 문자 출력하는 매크로

## Mathematical Functions

- C 에는 내장 수학함수가 없음
- 수학 Library 에서 제공 <math.h>
- sqrt() pow() exp () log() sin() cos()
- 절대값 함수
    - abs()
        - int , <stdlib.h>
    - fabs()
        - double, <math.h>

## Conversions and Casts

- 정수적 승격(the integral promotions)
    - signed 혹은 unsigned의 char, short, 또는 열거형을 int나 unsigned int 형이
    사용될 수 있는 수식에서 대신 사용 가능
    - 이 경우, 이들 형들 중 모든 값을 int로 표현할 수 있으면 int로 변환되고, 그렇지 않으면 unsigned int로 변환됨
    - char c = 'A';
        - printf ("%d n", c);
        - c는 승격이 일어나 int 형이 됨 (65 출력)
- 일반적 자동 변환(the usual arithmetic conversions)
    - 수식에서 제일 큰 형으로 변환한다
    - long 과 unsigned의 경우, 모든 값을 long으로 표현할 수 있으면 long으로 변환되고, 그렇지 않으면 unsigned long으로 변환됨
- 명시적 변환(casts)
    - 캐스트 예
        - (double) i
        - (long) ('A' + 1.0)
        - f = (float) (( int ) d + 1)
        - d = (double) i / 3
        - (double) (x = 77)
    - 틀린 예
        - (double) x = 77
        - equivalent to ((double) x) = 77 → error
        - 연산자 우선 순위를 고려