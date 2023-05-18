# Structures and Unions

- 구조체와 공용체
    - C 언어의 확장 방법
    - 매크로와 라이브러리
    - 사용자 정의 형 배열 , 구조체 , 공용체

## Structures

- 서로 다른 형의 변수들을 하나로 묶어 주는 방법

```c
/**
 * struct card type definition
 *
 * @struct: keyword
 * @card: tag_name
 *
 * @pips: first member
 * @suit: second member
 */
struct card {
	int pips;
	char suit;
};
/*
 * struct card type variable declaration
 */
struct card c1, c2;

/*
 * struct card type definition with variable declaration
 */
struct card {
	int pips;
	char suit;
} c1, c2;

struct card {
	int pips;
	char suit;
};
/*
 * Using typedef
 */
typedef struct card
card card c1, c2;

/*
 * struct card type definition using typedef
 */
typedef struct card {
	int pips;
	char suit;
} card;
card c1, c2;

/*
 * These two structures look same.
 * But different type!
 * 
 * Structures have no tag_name.
 * Variables of the same type can never be declared again.
 */
struct {
	int pips;
	char suit;
} c1, c2;

struct {
	int pips;
	char suit;
} c3, c4;
```

## Accessing Members of a Structure

```c
struct fruit {
	char *name;
	int calories;
};

struct vegetable {
	char *name;
	int calories;
};

struct fruit a;
struct vegetable b;

/*
 * Example of operator '.'
 */
#define CLASS_SIZE 100

struct student {
	char *last_name;
	int student_id;
	char grade;
};
struct student class[CLASS_SIZE];

int fail(struct student class[]) {
	int i, cnt = 0;
	for (i = 0; i < CLASS_SIZE; i++)
		cnt += class[i].grade == 'F';
	return cnt;
}

/*
 * Example of operator '->'
 */
struct complex {
	double re; /* real part */
	double im; /* imag part */
};

typedef struct complex complex;

void add(complex *a, complex *b, complex *c) {
	a->re = b->re + c->re;
	a->im = b->im + c->im;
}
```

- 한 구조체내에서 멤버 이름은 유일해야 하나, 서로 다른 구조체에서는 같은 멤버 이름을 사용할 수 있음
- 멤버 접근 연산자 : `.`
    - 일반 구조체 멤버 접근
- 멤버 접근 연산자 : `->`
    - 포인터를 통한 구조체 멤버 접근 연산자
    - `pointer_to_structure->member_name`
        - Equivalent expression : `(*pointer_to_structure).member_name`

## Using Structures with Functions

- 구조체는 함수의 인자로써 함수에 전달될 수 있고, 함수로부터 리턴될 수도 있음
- 함수의 인자로서 구조체가 전달될 때 구조체는 값으로 전달됨
- 구조체가 많은 멤버를 가지거나, 큰 배열을 멤버로 가질 경우, 함수의 인자로 구조체를 전달하는 것은 상대적으로 비효율적임
- 따라서 대부분의 응용 프로그램에서는 함수의 인자로 구조체의 주소를 사용함

```c
typedef struct {
	char name[25];
	int employee_id;
	struct dept department;
	struct home_address a_ptr;
	double salary;
	...
} employee_data;

employee_data e;

employee_data update(employee_data e){
	...
	printf("Input the department number: ");
	scanf("%d", &n);
	e.department.dept_no = n;
	...
	return e;
}

e = update(e);
```

- department 멤버는 그 자체가 구조체이고, 컴파일러는 각 멤버의 크기를 미리 알아야 하므로 struct dept에 대한 선언이 먼저 와야 함

## Initialization of Structures

```c
/* 
 * the king of hearts
 */
card c = {13, 'h'}; 

/* 
 * a[2][] is assigned zeroes
 */
complex a[3][3] = {
	{
		{1.0, 0.1}, {2.0, 0.2}, {3.0, 0.3}
	},
	{
		{4.0, 0.4}, {5.0, 0.5}, {6.0, 0.6}
	},
};

struct fruit frt = {"plum", 150};

struct home_address {
	char *street;
	char *city_and_state;
	long zip_code;
} address = {"87 West Street", "Aspen, Colorado", 80526};

struct home_address previous_address = {0};
```

## Unions

- 공용체는 구조체와 비슷한 구문 형식을 가지지만 각 멤버들은 같은 기억장소를 공유함
- 공용체형은 메모리의 같은 위치에 저장될 여러 값의 집합을 정의
- 저장된 값을 올바르게 해석하는 것은 프로그래머의 책임

```c
/**
 * union int_or_float type definition
 *
 * @union: keyword
 * @int_or_float: tag_name
 *
 * @i: first member
 * @f: second member
 */
union int_or_float {
	int i;
	float f;
};

/*
 * union int_or_float type variable declaration
 * This declaration assigns storage for identifiers a, b, and c.
 */
union int_or_float a, b, c;

int main(void) {
	union int_or_float n;
	n.i = 4444;
	printf("i: %10d f: %16.10e\n", n.i , n.f);
	n.f = 4444.0;
	printf("i: %10d f: %16.10e\n", n.i , n.f);
	return 0;
}

/** Result:
 * i:       4444 f: 6.2273703755e-42
 * Decimal(int) : 4444
 * Binary : 0b00000000000000000001000101011100
 * Hexadecimal : 0x0000115c
 * Decimal(float) : 6.22737037546e-42
 * Mantissa is 4444
 * 
 * i: 1166729216 f: 4.4440000000e+03
 * Decimal(float) : 4444.0
 * Binary : 0b01000101100010101110000000000000
 * Hexadecimal : 0x458ae000
 * Decimal(int) : 1166729216
 */
```

- int_or_float 형 변수는 MAX(sizeof(int), sizeof (float)) 만큼의 메모리 할당될 것임
- 컴파일러는 공용체의 멤버 중에서 가장 큰 기억장소를 요구하는 멤버의 요구만큼 기억장소를 할당
- 공용체의 멤버 접근 방법은 구조체의 멤버 접근 방법과 동일

## Bit Fields

- 구조체나 공용체에서 int 형이나 unsigned 형의 멤버에 비트 수(폭)를 지정하는 것
- 폭은 콜론 다음에 음수가 아닌 정수적형 상수 수식으로 지정되고, 최대 값은 기계 워드의 비트 수와 같음
- 일반적으로 비트 필드는 구조체의 연속적인 멤버로 선언되며, 컴파일러는 이 멤버들을 최소의 기계 워드로 패킹함
- unsigned 비트 필드에는 음수가 아닌 정수만이 저장되고, int 비트필드는 시스템에 따라 다름
    - 보통 unsigned 비트 필드를 사용

```c
struct pcard {
	unsigned pips : 4;
	unsigned suit : 2;
};
struct pcard c;

/*
 * In this case, x is stored in two words as follows:
 * first word : Store bit fields a and b
 * second word : Store bit fields c
 */
struct xyz {
	int x : 1, y : 16, z : 16;
} xyz;

struct small_integers {
	unsigned i1 : 7, i2 : 7, i3 : 7,
	: 11, /* align to next word */
	i4 : 7, i5 : 7, i6 : 7;
};

/*
 * To access bits and bytes.
 */

typedef struct {
	unsigned b0 : 8, b1 : 8, b2 : 8, b3 : 8;
} word_bytes;

typedef struct {
	unsigned
	b0 :  1, b1 :  1, b2 :  1, b3 :  1, b4 :  1, b5 :  1, b6 :  1,
	b7 :  1, b8 :  1, b9 :  1, b10 : 1, b11 : 1, b12 : 1, b13 : 1,
	b14 : 1, b15 : 1, b16 : 1, b17 : 1, b18 : 1, b19 : 1, b20 : 1,
	b21 : 1, b22 : 1, b23 : 1, b24 : 1, b25 : 1, b26 : 1, b27 : 1,
	b28 : 1, b29 : 1, b30 : 1, b31 : 1;
} word_bits;

typedef union {
	int i;
	word_bits bit;
	word_bytes byte;
} word;
```

- 카드는 4개의 무늬와 각 무늬당 13개의 숫자로 이루어짐
- 카드를 비트 필드로 표현하면 메모리를 절약할 수 있음
- c는 6 비트에 저장됨
- 대부분의 컴퓨터에서는 비트 필드가 워드 경계에 걸치지 않도록 할당됨
- 비트 필드의 배열은 허용되지 않음
- 비트 필드에 주소 연산자 ‘&’를 적용할 수 없음
    - 즉 , 멤버 접근 연산자 ‘→’를 사용할 수는 있어도 , 포인터가 직접 비트 필드를 포인트할 수는 없음
- 패딩과 정렬을 위해 이름 없는 비트 필드나 폭이 0인 비트 필드를 사용할 수 있음