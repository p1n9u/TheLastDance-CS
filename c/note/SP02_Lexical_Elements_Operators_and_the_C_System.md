# Lexical Elements, Operators, and the C System

## Characters and Lexical Elements

- 구문
    - 올바른 프로그램을 만들 수 있게 하는 규칙
    - 컴파일러
        - C 프로그램이 구문에 맞는지 검사
        - 오류가 있다면, 오류 메시지 출력
        - 오류가 없다면, 목적 코드 생성
    - 컴파일 과정
        - C 프로그램 → 토큰으로 분리 → 토큰을 목적 코드로 변환
- ANSI C 토큰종류
    - 키워드(keywords)
    - 식별자(identifiers)
    - 상수(constants)
    - 문자열 상수(string constants)
    - 연산자(operators)
    - 구두점(puctuators)
- 프로그램에 사용되는 문자
    - lowercase letters : a b c … z
    - uppercase letters : A B C … Z
    - digits : 0 1 2 … 9
    - other characters : + -* / = ( ) [ ] …
    - white space : blank, new line, …

## Comments

- 주석 : 한계자(delimiter) /* 과 */ 사이의 문자열
- 프로그램의 문서화(documentation)를 위한 도구
- 컴파일러는 주석을 하나의 공백 문자로 대치

## Keywords

- 키워드 : C 언어에서 고유한 의미를 가지는 토큰(문법단위)으로 예약된 단어

```c
auto        do          goto        signed      unsigned
break       double      if          sizeof      void
case        else        int         static      volatile
char        enum        long        struct      while
const       extern      register    switch
continue    float       return      typedef
default     for         short       union
```

## Identifier

- 식별자 : 문자, 숫자, 밑줄문자(_)로 구성된 토큰, 대소문자 구별
- 식별자의 첫번째 문자 : 문자, 밑줄문자(_)
- 식별자의 틀린 예
    - not#me /* special character # not allowed */
    - 101_south /* must not start with a digit */
    - -plus /* do not mistake - for _ */
- 의미가 쉽게 연상되는 식별자(변수)를 사용
- 밑줄문자(_)로 시작되는 식별자는 시스템 이름과 충돌될 수 있으므로 가급적 사용하지 말 것.

## Constants

- C의 상수
    - 수치 상수, 문자 상수, 문자열 상수
- 수치 상수
    - 8진수, 10진수, 16진수, 지수, long 상수, 부호없는 정수
    - 수치 상수 표기법 예
        - 8진수 : 0을 맨 앞에 붙인다 011, 0345
        - 10진수 : 상기 이외의 상수치 6800, 8089
        - 16진수 : 0x 또는0X를 맨 앞에 붙인다 0xab, 0x2BCD
        - 지수 : e 또는 E를 붙인다 5e2(=500), 6E3(=6000)
        - 소수점 : 소수점을 사용한다 1.34, 25.89
- 정수상수
    - 0, 17, 234, 0x17
- 실수 상수
    - 1.0, 3.141592, 23E2
- 문자 상수
    - 한쌍의 작은 따옴표(’ ‘)에 묶인 문자
    - ‘a’, ‘b’, ‘+’, ‘\n’
    - c = ‘A’ /* 변수c 에 ‘A’ 문자에 해당하는 문자코드인 65가 대입 */
    - c = 65;
- 문자열 상수
    - 한쌍의 큰 따옴표(” “)에 묶인 문자열
    - [ASCII 코드](https://en.wikipedia.org/wiki/ASCII)
    - [ASCII 코드 cpp](https://en.cppreference.com/w/cpp/language/ascii)
    - “hello”, “very good”
- 열거상수
    - enum에 의해 선언된 상수
- (주의) -49는 상수 수식임

## Operators and Punctuators

[중요! C/C++ 연산자](https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B)
[Sequence Point](https://en.wikipedia.org/wiki/Sequence_point)
[Undefined Behavior](https://en.wikipedia.org/wiki/Undefined_behavior)

## The C System

- C 시스템
    - C 언어, 전처리기, 컴파일러, 라이브러리, 편집기 등으로 구성
- 전처리기
    - #으로 시작하는 행을 전처리지시자라고 함
        - #include <filename>
        - #include "filename"
        - #define PI 3.141592
- 표준 라이브러리
    - 프로그램에 유용한 함수들로 C 시스템이 제공함
    - printf(), scanf(), 등
    - 사용자가 알아서 해당 헤더파일을 포함시켜야 함
