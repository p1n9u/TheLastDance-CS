# Queue

## Definition of Queue

- Object : 선형리스트(linear list)
    - 먼저 들어온 데이터가 먼저 나가는 자료구조
    - 선입선출(FIFO : First-In First-Out)
- Operatation
    - 큐에 데이터를 추가
    - 큐를 생성
    - 큐가 공백상태인지 검사
    - 큐가 포화상태인지 검사
    - 요소를 큐에서 완전히 삭제하면서 가져옴
    - 요소를 큐에서 삭제하지 않고 보기만 하는 연산

## Queue ADT

- Object
    - n개의 element형의 요소들의 선형리스트
- Operation
    - create() ::= 큐를 생성
    - is_empty(q) ::= 큐가 비어있는지를 검사
    - is_full(q) ::= 큐가 가득 찼는가를 검사
    - enqueue(q,e) ::= 큐의 뒤에 요소 e를 추가
    - dequeue(q) ::= 큐의 앞에 있는 있는 요소를 반환한 다음 삭제
    - peek(q) ::= 큐의 앞에 있는 요소를 삭제하지 않고 반환

## Usage of the queue

- 직접적인 응용
    - 시뮬레이션의 대기열(공항에서의 비행기들, 은행에서의 대기열)
        - 큐는 큐잉이론에 따라 시스템의 특성을 시뮬레이션하여 분석하는 데 이용될 수 있음
    - 통신에서의 데이터 패킷들의 모델링에 이용
    - 프린터와 컴퓨터 사이의 버퍼링
        - 서로 다른 속도로 실행되는 두 프로세스 간의 상호 작용을 조화시키는 버퍼 역할을 할 수 있음
        - 대개 데이터를 생산하는 생산자 프로세스가 있고 데이터를 소비하는 소비자 프로세스가 있으며 이 사이에 큐로 구성되는 버퍼가 존재
- 간접적인 응용
    - 스택과 마찬가지로 프로그래머의 도구
    - 많은 알고리즘에서 사용됨

## Queue Implementation

- 배열을 이용하는 방법
    - 선형큐 : 배열을 선형으로 사용하여 큐를 구현
        - 삽입을 계속하기 위해서는 요소들을 이동시켜야 함
        - 문제점이 많아 사용되지 않음
    - 원형큐 : 배열을 원형으로 사용하여 큐를 구현
        - Front와 Rear값이 배열의 끝인[MAX_QUEUE_SIZE-1]에 도달하면 다음에 증가되는 값은 0이 되도록 구현
        - 개념상 원형일뿐, 실제로 원형 모양의 배열은 아님
- 연결리스트를 이용하는 방법
    - 연결된 큐(linked queue) : 연결리스트로 구현된 큐
    - front 포인터는 삭제와 관련되며 rear 포인터는 삽입
    - front는 연결 리스트의 맨 앞에 있는 요소를 가리키며, rear 포인터는 맨 뒤에 있는 요소를 가리킴
    - 큐에 요소가 없는 경우에는 front와 rear는 NULL

## Array Circular Queue

- 원형 큐의 구조
    - 큐의 전단과 후단을 관리하기 위한 2개의 변수 필요
    - front : 첫번째 요소 하나 앞의 인덱스, 삭제와 관련된 변수
    - rear : 마지막 요소의 인덱스, 삽입과 관련된 변수
    - 초기값은 0임(-1 아님)
- 원형 큐의 공백과 포화 상태
    - 공백상태 : front == rear (front변수와 rear 변수 값이 같으면)
    - 포화상태 : front % MAX_QUEUE_SIZE == (rear + 1) % MAX_QUEUE_SIZE
    - 공백상태와 포화상태를 구별하기 위하여 하나의 공간(front)은 항상 비움
- 원형 큐의 삽입과 삭제 알고리즘
    - 나머지(mod) 연산을 사용하여 인덱스를 원형으로 회전시킴
        - front ← (front+1) % MAX_QUEUE_SIZE;
        - rear ← (rear+1) % MAX_QUEUE_SIZE;
- Preliminary
    - 나머지(mod) 연산자 : %
    - front : 첫 번째 요소로부터 시계 방향으로 하나 앞에 위치함.
        - 삭제시 먼저 front를 증가시키고 그 위치에서 데이터를 꺼내와야 함
    - rear : 마지막 요소.
        - 삽입시 무조건 rear를 하나 증가시키고, 증가된 위치에 데이터를 넣어야 함
    - 공백상태 검출 : front == rear
    - 포화상태 검출 : front == (rear + 1) % MAX_QUEUE_SIZE
    - front나 rear에 `+ 1` 연산을 하는 경우, 반드시 `% MAX_QUEUE_SIZE` 연산을 행해야 함.

## Definition of Deque

- Object : 선형리스트(linear list)
    - 덱(deque)은 double-ended queue의 줄임말로 큐의 전단(front)와 후단(rear)에서 모두 삽입과 삭제가 가능한 큐
    - 덱은 스택과 큐의 연산을 모두 가지고 있음
- Operatation
    - 덱의 앞에 데이터를 추가
    - 덱의 뒤에 데이터를 추가
    - 덱을 생성
    - 덱이 공백상태인지 검사
    - 덱이 포화상태인지 검사
    - 요소를 덱의 앞에서 완전히 삭제하면서 가져옴
    - 요소를 덱의 뒤에서 완전히 삭제하면서 가져옴
    - 요소를 덱의 앞에서 삭제하지 않고 보기만 하는 연산
    - 요소를 덱의 뒤에서 삭제하지 않고 보기만 하는 연산

## Deque ADT

- Object
    - n개의 element형의 요소들의 선형리스트
- Operation
    - create() ::= 덱을 생성
    - is_empty(dq) ::= 덱이 비어있는지를 검사
    - is_full(dq) ::= 덱이 가득 찼는가를 검사
    - add_front(dq,e) ::= 덱의 앞에 요소 e를 추가
    - add_rear(dq,e) ::= 덱의 뒤에 요소 e를 추가
    - delete_front(dq) ::= 덱의 앞에 있는 있는 요소를 반환한 다음 삭제
    - delete_rear(dq) ::= 덱의 뒤에 있는 있는 요소를 반환한 다음 삭제
    - get_front(dq) ::= 덱의 앞에 있는 요소를 삭제하지 않고 반환
    - get_rear(dq) ::= 덱의 뒤에 있는 요소를 삭제하지 않고 반환