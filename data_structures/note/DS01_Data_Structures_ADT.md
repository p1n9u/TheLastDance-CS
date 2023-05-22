# Data Structures, ADT

## 자료구조

- Software
    - Program
        - 자료(data) + 명령(algorithm)
- 분류
    - 단순 구조(primitive, simple)
        - 프로그래밍 언어에서 제공하는 기본적인 데이터 타입
        - 정수, 실수, 문자, 문자열
    - 선형 구조(linear)
        - 자료들 사이의 앞뒤 관계가 일대일(1:1)인 경우
        - 리스트, 스택, 큐, 덱
    - 비선형 구조(non-linear)
        - 자료들 사이의 앞뒤 관계가 계층 구조(Hierarchical Structure) 혹은 망 구조(Network Structure)를 가지는 경우
        - 트리, 그래프
    - 파일 구조(file organization)
- 데이터 타입(data type, 자료형)
    - 데이터의 집합과 연산의 집합

## ADT : Abstract Data Type

- 데이터 타입을 추상적(수학적)으로 정의한 것
    - 추상화 : 시스템의 간략화 된 기술/명세, 시스템의 핵심 구조와 동작에만 집중
    - 좋은 추상화란? : 중요한 정보는 강조되고, 중요하지 않은 세부 사항은 제거
- 데이터나 연산이 무엇(what)인가는 정의됨 : 연산자를 포함
- 데이터나 연산을 어떻게(how) 컴퓨터 상에서 구현할 것인지는 정의되지 않음

- 정의
    - 객체(Object)
        - 추상 데이터 타입에 속하는 객체 정의
    - 연산(Operation)
        - 객체들 사이의 연산을 정의
        - 추상 데이터 타입과 외부를 연결하는 인터페이스의 역할을 함
- 특징
    - 자료구조를 기술(표현)하는 가장 대표적인 방법
    - 정보 은닉(Information Hiding)
        - 중요한 정보만을 나타내고, 중요하지 않은 정보는 숨김
        - 자료구조를 사용할 수 있는 인터페이스(Interface) 정의
            - 혹은 자료구조의 연산(Operation)들의 정의
    - 자료구조의 활용 관점
        - 자료구조를 이용하는 사용자의 관점
            - 자료구조의 내부 구현 소스에 대한 분석 없이 신속하게 자료구조를 이용 가능
        - 자료구조를 공급하는 개발자의 관점
            - 자료구조를 구현하기 전에 설계도를 미리 그려보는 것
- 이해
    - 사용자들은 추상 데이터 타입이 제공하는 연산만을 사용할 수 있다.
    - 사용자들은 추상 데이터 타입을 어떻게 사용하는지를 알아야 한다.
    - 사용자들은 추상 데이터 타입 내부의 데이터를 접근할 수 없다.
    - 사용자들은 어떻게 구현되었는지 몰라도 이용할 수 있다.
    - 만약 다른 사람이 추상 데이터 타입의 구현을 변경하더라도 인터페이스가 변경되지 않으면 사용할 수 있다.

## Requirements

- [C](../../c)
- [알고리즘의 성능 분석](./) -> Link later, Algorithms