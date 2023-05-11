# An Overview of C

## Programming and Preparation

- 프로그램 작성
    - [namu.wiki:문서 편집기](https://namu.wiki/w/%EB%B6%84%EB%A5%98:%EB%AC%B8%EC%84%9C%20%ED%8E%B8%EC%A7%91%EA%B8%B0)
        - ubuntu : vi(m), nano, emacs
        - sublime, vscode가 널리 쓰임
- 컴파일
    - `$ gcc sourcename.c`
        - 결과 : 목적 파일(a.out)
- 목적 파일명 지정
    - `$ gcc -o exename sourcename.c`
- 실행
    - `$ ./a.out`
    - `$ ./exename`
    - UNIX는 파일 경로명으로 프로그램을 실행함

## Program Output

```c
/*
 * sea.c
 */

#include <stdio.h>

int main(void)
{
	printf("from sea to shining C\n");
	return 0;
}
```

- Dissection of the sea Program
    - /* sea.c */
        - /* */은 주석을 나타내며, 컴파일러는 이것을 무시함
    - #include <stdio.h>
        - #으로 시작하는 행은 전처리기(preprocessor)에서 처리됨
        - 프로그램을 컴파일하면 컴파일 전에 전처리기가 먼저 동작됨
        - printf() 함수 사용을 위해<stdio.h> 헤더 파일 복사
        - 필요하다면 헤더파일을 지정한다
    - int main(void)
        - 식별자 다음에 괄호 ()가 오면 그 식별자는 함수라는 것을 나타냄
        - 프로그램은 함수로 구성됨
        - 프로그램의 수행은 항상 main() 함수로부터 시작함
        - main() 함수 정의
            - void : 인수를 받지 않음
            - int형 return값을 가짐
    - { }
        - 중괄호는 여러 문장들을 그룹화하기 위해 사용됨
        - 즉, 중괄호로 둘러싸인 것은 하나의 단위로 취급됨
    - printf()
        - 화면 출력 기능을 가진 library 함수, stdio.h
        - 연속적으로 printf()가 있을 경우, 뒤에 나오는 printf()의 출력은 바로 앞 printf()의 마지막 출력 위치에서부터 시작하여 출력한다.
    - "from sea to shining C\n"
        - 큰 따옴표로 둘러싸인 일련의 문자들을 문자열 상수라고 함
        - 문자열 상수를 이루는 단어들은 그 본래의 의미를 잃어버림
        - \n은 개행(new line) 문자를 나타냄 → 프로그래머가 직접 지시해야함
        - 프로그램 상에서 일반 문자로 표현할 수 없는 것을 표현하고 싶을 때 역슬래시\와 결합된문자를 사용함
    - printf("from sea to shining C\n");
        - C에서 모든 문장은 세미콜론으로 끝남
    - return 0;
        - 0값을 운영체제에 return
    - C에는 행의 개념이 없음
