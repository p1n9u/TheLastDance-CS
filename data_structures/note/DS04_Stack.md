# Stack

## Definition of List

- Object : 선형리스트(linear list)
    - 쌓아 놓은 더미
    - 후입선출(LIFO : Last-In First-Out)
- Operatation
    - 스택에 데이터를 추가
    - 스택에서 데이터를 삭제
    - 스택을 생성
    - 스택이 공백상태인지 검사
    - 스택이 포화상태인지 검사
    - 요소를 스택에서 완전히 삭제하면서 가져옴
    - 요소를 스택에서 삭제하지 않고 보기만 하는 연산

## Stack ADT

- Object
    - n개의 element형의 요소들의 선형리스트
- Operation
    - create() ::= 스택을 생성
    - is_empty(s) ::= 스택이 비어있는지를 검사
    - is_full(s) ::= 스택이 가득 찼는가를 검사
    - push(s,e) ::= 스택의 맨 위에 요소 e를 추가
    - pop(s) ::= 스택의 맨 위에 있는 요소를 삭제
    - peek(s) ::= 스택의 맨 위에 있는 요소를 삭제하지 않고 반환

## Usage of the stack

- 자료의 출력 순서가 입력 순서의 역순으로 이뤄져야 할 때
    - 입력 : (A,B,C,D,E) → 출력 : (E,D,C,B,A)
- 되돌리기(undo) 기능
    - 최근 수행한 명령어들 중에서 가장 최근에 수행한 것부터 되돌리기
- 함수 호출에서 복귀주소(PC : Program Counter) 기억
    - 시스템 스택 : 컴퓨터 OS만 사용함, 사용자는 접근 안됨
    - 시스템 스택에는 함수가 호출될 때마다 활성화 레코드(activation record)가 만들어지고, 여기에 복귀주소가 기록됨

## Stack Implementation

- 배열을 이용하는 방법
    - 1차원 배열 `stack[MAX_STACK_SIZE]`
    - top 변수 : 스택에서 가장 최근에 입력되었던 자료를 가리킴
        - 가장 먼저 들어온 요소는 stack[0]에, 가장 최근에 들어온 요소는 stack[top]에 저장
        - 스택이 공백상태이면 top은 -1
- 연결리스트를 이용하는 방법
    - 연결된스택(linked stack): 연결리스트를이용하여구현한스택
    - 장점 : 크기가 제한되지 않음
    - 단점 : 구현이 복잡하고 삽입이나 삭제 시간이 오래 걸림
        - 동적 메모리 할당 및 해제 때문