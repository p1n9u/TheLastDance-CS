# Flow of Control

## Logical Operators and Expressions

- 단축 평가 (short-circuit evaluation)
    - 결과가 참인지 거짓인지 판명되면 더 이상 다음 수식을 평가하지 않는다.
    - expr1 && expr2
        - expr1이 0면 어차피 0이므로 expr2 평가하지 않음
    - expr1 || expr2
        - expr1이 1이면 어차피 1이므로 expr2 평가하지 않음

## The Compound Statement

- 복합문
    - 복합문은 중괄호 {} 로 묶여진 선언문과 실행문

```c
{
	a = 1;
	{
		b = 2;
		c = 3;
	}
}
```

## The Expression and Empty Statement

```c
a = b; /* an assignment statement */
a + b + c; /* legal, but no useful work gets done */
; /* an empty statement */
printf("%d\n", a); /* a function call */
```

## The if and the if-else Statements

```c
if (expr)
	statement

if (grade >= 90)
	printf("Congratulations!\n");
printf("your grade is %d.\n", grade);

if (y != 0.0)
	x /= y;

if (c == ' ') {
	++blank_cnt;
	printf("found another blank\n");
}
```

- 만일 expr이 0이 아니면(true) statement가 실행
- 그렇지 않으면 statement는 실행되지 않고 다음 문장으로 넘어감

```c
if (expr)
	statement1
else
	statement2

if (x < y)
	min = x;
else
	min = y;

if (c >= 'a' && c <= 'z') {
	++lc_cnt;
} else {
	++other_cnt;
	printf("%c is not a lowercase letter\n", c);
}
```

- expr이 0이 아니면 statement1이 실행되고 statement2는 실행 되지 않음
- expr이 0이면 statement1은 건너뛰고 statement2가 실행 됨
- else는 가장 가까운 if와 연관됨

## The while Statement

```c
while (expr)
	statement

while (i++ < n)
	factorial *= i;

while ((c = getchar ()) != EOF) {
	if (c >= 'a' && c <= 'z')
		++lowercase_letter_cnt;
	++total_cnt;
}

/*
 * Ignore blank characters in the input stream.
 */ 
while ((c = getchar ()) == ' ')
	; /* empty statement */
```

- expr이 0이 아니면 statement를 실행한 후, 다시 while 루프의 시작 부분으로 돌아 감
- expr이 0이면 다음 문장으로 진행함

## The for Statement

```c
for (expr1; expr2; expr3)
	statement

/*
 * Same as the while statement below.
 */
expr1
while (expr2) {
	statement
	expr3
}

for (i = 1; i <= n; ++i)
	factorial *= i;

for (j = 2; k % j == 0; ++j) {
	printf("%d is a divisor of %d\n", j, k);
	sum += j;
}
```

- 우선 expr1을 실행(초기화) 후 expr2가 0이 아니면, statement를 실행한 후, expr3를 수행함 카운트 증가
- expr2가 0이면, 다음 문장으로 진행

## The Comma Operator

- expr1, expr2
    - expr1이 먼저 평가되고, 그 다음 expr2가 평가됨
    - 전체 수식의 값과 형은 가장 오른쪽 피연산자를 따름
    - 가장 낮은 우선순위 갖는 이항 연산자
    - L → R 결합 법칙
- 프로그램 상의 대부분의 콤마는 콤마 연산자가 아님
    - 함수의 인자 목록에서 수식을 분리하는데 사용된 콤마
    - 초기화 목록에서 사용된 콤마
- for ( i = 0, p = head; p != NULL; ++i, p = p->next)

## The do Statement

```c
do
	statement
while (expr);

do {
	sum += i;
	scanf ("%d", &i);
} while (i > 0);

do {
	printf("Input a positive integer: ");
	scanf("%d", &n);
	if (error = (n <= 0))
		printf("\nERROR: Do it again!\n\n");
} while (error);
```

- 먼저 statement를 실행한 후, expr 이 0이 아니면, do 문의 시작 부분으로 돌아 감
- expr이 0이면 다음 문장으로 진행
- do 문은 while 문의 변형된 형태
- while 문은 루프 상단에서 조건을 검사하는 반면 do 문은 루프 하단에서 조건을 검사

## Use Relational Expressions rather than Equality Expressions

- 등가 수식 보다는 관계 수식으로 조건 평가
    - 부동 소수점 자료의 식에 대한 등가 검사는 컴퓨터에서 수 표현의 정확도 때문에 의도대로 작동되지 않을 수 있음
- [What Every Computer Scientists Should Know About Floating Point Arithmetic](https://modoocode.com/199)
	- [pdf](../material/What_Every_Computer_Scientists_Should_Know_About_Floating_Point_Arithmetic.pdf)

## The goto Statement

- 현대 프로그래밍 방법론에서 **유해한 구조물**로 간주
	- [Goto](https://en.wikipedia.org/wiki/Goto)
- 현재 함수 내의 레이블이 붙은 문장으로 무조건 분기함으로써 다른 제어 흐름 메커니즘(if, for, while, do, switch)들이 제공하는 유용한 구조를 파괴
- When should a goto be used?
    - A simple answer is “**not at all**”
    - 물론, Linux나 Assembly-C Linking에서 쓰이기도 하지만 본인이 구현하는 코드에서 쓰는일은 없도록 하자.

## The break and continue Statements

```c
while (1) {
	scanf("%lf", &x);
	if (x < 0.0)
		break; /* exit loop if x is negative */
	printf("%f\n", sqrt(x));
}
/*
 * break jumps to here
 */

for (i = 0; i < TOTAL; ++i) {
	c = getchar();
	if (c >= '0' && c <= '9')
		continue;
	... /* process other characters */

/* 
 * continue transfers control to here to begin next iteration
 */
}
```

- break와 continue는 정상적인 제어의 흐름을 중단시킴
- break 문은 루프의 내부나 switch 문으로부터 빠져 나옴
- continue 문은 for, while, do 루프의 현재 반복 동작을 멈추고 즉시 다음 반복을 하게함

## The switch Statement

```c
switch (c) {
case 'a':
	++a_cnt;
	break;
case 'b' :
case 'B' :
	++b_cnt;
	break;
default :
	++other_cnt;
}
```

- switch 문은 if-else 문을 일반화한 다중 조건문
- switch 다음에 오는 괄호 안에 사용되는 제어식은 반드시 정수적형
- 제어식의 평가 결과에 따라 제어는 해당되는 case 레이블로 분기

## The Conditional Operator

- expr1 ? expr2 : expr3
    - 조건부 연산자 ?: 는 삼항 연산자
    - 3개의 수식을 피연산자로 가짐\
    - expr1이 0이 아니면 expr2가 이 조건부 수식의 값이 됨
    - expr1이 0이면 expr3가 이 조건부 수식의 값이 됨
    - 조건부 수식의 형은 expr2와 expr3에 무관하게 둘 다 포함할 수 있는 일반적인 변환 규칙 적용