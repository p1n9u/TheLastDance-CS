# Recursion, Array, Struct

> 해당 Chapter는 C Review, 설명이 간략화 됨
> 

## Recursion

- 알고리즘이나 함수가 수행 도중에 자기 자신을 다시 호출하여 문제를 해결하는 방법
    - 정의자체가 순환적으로 되어 있는 경우에 적합
- 함수의 순환(재귀)호출(recursive call) 사용
    - 문제 또는 사용되는 자료구조가 재귀적으로 정의되어 있을 때
    - 문제 해결이 용이, 알고리즘 정확성 증명이 용이
    - 시간, 공간 사용이 비효율적임

- 팩토리얼

$n! = \begin{cases} 1 & n = 0 \\ n*(n-1)! & n \ge 1 \end{cases}$

```c
int factorial(int n)
{
	if (n == 0)
		return 1;
	else
		return (n * factorial(n-1));
}
```

- 피보나치수열

$fib(n) = \begin{cases} 0 & n = 0 \\ 1 & n = 1 \\ fib(n-2) + fib(n-1) & otherwise \end{cases}$

```c
int fib(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return (fib(n - 2) + fib(n - 1));
}
```

- 이항계수

$_{n}\mathrm{C}_{k} = \begin{cases} 1 & k = 0 \text{ or } k = n \\ _{n-1}\mathrm{C}_{k} + _{n-1}\mathrm{C}_{k-1} & ohterwise \end{cases}$

```c
int combination(int n, int k)
{
	if (k == 0 || k == n)
		return 1;
	else
		return (combination(n-1, k) + combination(n-1, k-1));
}
```

- [하노이탑](../../c/src/spl05_03_tower_of_hanoi), 이진탐색, …

- 순환 알고리즘의 구조
    - 순환 알고리즘은 다음의 부분을 포함
        - 순환 호출을 하는 부분
        - 순환 호출을 멈추는 부분
    - 만약 순환 호출을 멈추는 부분이 없다면?
        - 시스템 오류가 발생할 때까지 무한정 호출
- 컴퓨터에서의 되풀이
    - 순환(recursion)
        - 순환적인 문제에서는 자연스러운 방법
        - 함수 호출의 오버헤드
    - 반복(iteration)
        - 수행속도가 빠름
        - 순환적인 문제에 대해서는 프로그램 작성이 어려울 수 있음
    - 대부분의 순환은 반복으로 바꾸어 작성할 수 있음

## Array

- 동일한 데이터 타입의 데이터를 여러 개 만드는 경우에 사용
- 반복 코드 등에서 배열을 사용하면 효율적인 프로그래밍이 가능
- 배열 ADT
    - Object : <인덱스,요소>쌍의 집합
    - Operation :
        - create(n) ::= n개의 요소를 가진 배열의 생성
        - retrieve(A, i) ::= 배열 A의 i번째 요소 반환
        - store(A, i, item) ::= 배열 A의 i번째 위치에 item저장
- int A[6];
    - 배열 인덱스는 0부터 시작
    - 배열은 메모리의 연속된 위치에 구현되기 때문에, A[0]의 주소가 base가 됨
        - base : 메모리의 기본 주소
        - A[1]의 주소 : base + sizeof(int)
        - A[2]의 주소 : base + 2 * sizeof(int)

## Struct

- 구조체(structure) : 타입이 다른 데이터들을 하나로 묶는 방법
    - cf. 배열(array) : 타입이 같은 데이터들을 하나로 묶는 방법

```c
struct list {
	int data;
	struct list *next;
} a;

typedef struct ListNode{
	char data[10];
	struct ListNode *link;
} ListNode;
```

- 자기참조 구조체(Self-referential Structures)
    - 자기참조 구조체는 자기 자신의형을 참조하는 포인터멤버를 가짐
    - 이러한 자료구조를 동적자료구조라고 함
    - 배열이나 단순변수는 일반적으로 블록을 진입할 때 메모리할당을 받지만, 동적자료구조는 기억장소관리루틴을 사용하여 명시적으로 메모리할당을 요구함

## Memory Allocation

- 프로그램이 메모리를 할당받는 방법
    - 정적 메모리 할당
        - 메모리의 크기는 프로그램이 시작하기 전에 결정
        - 프로그램의 수행 도중에 그 크기가 변경될 수는 없음
        - 만약 처음에 결정된 크기보다 더 큰 입력이 들어온다면 처리하지 못할 것이고 더 작은 입력이 들어온다면 남은 메모리 공간은 낭비될 것임
    - 동적 메모리 할당
        - 프로그램의 실행 도중에 메모리를 할당 받는 것
        - 필요한 만큼만 할당을 받고 또 필요한 때에 사용하고 반납
        - 메모리를 매우 효율적으로 사용가능