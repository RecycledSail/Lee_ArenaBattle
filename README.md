# 이득우의 언리얼 C++ 게임 개발의 정석

## Chapter 1

### What I learned

1. 기초적인 에디터 UI
2. 새 C++ 클래스 생성
3. 마켓플레이스 사용법
4. 새 레벨 생성
5. 프로젝트 세팅 (맵/모드) 

## Chapter 2

### What I learned

1. 월드<br>
뷰포트에 보이는 작업 공간은 컴퓨터 안의 가상 세계 -> 월드라고 부름<br>
게임 콘텐츠를 구동하기 위해 필수적인 환경

- 공간 (단위 cm)
  - 월드의 영역에 존재하기 위해 Transform이라는 구조체를 제공
- 시간 (단위 초)
  - 시간의 스케일을 조정 가능
- 물리
  - 물체가 물리적인 영향을 받으려면 콜리전 정보 필요
- 렌더링
  - 빛 + 반응하는 머터리얼로 구성, 물리기반 렌더링 시스템 제공<br><br>

2. 액터<br>
언리얼 엔진에서 콘텐츠를 구성하는 최소 단위의 물체<br>
액터는 게임 월드의 특정 공간에서 자신에게 주어진 역할을 수행하는 물체를 의미

- 이름
  - 작업을 위해 액터에 부여된 명칭, 여러 액터간 중복 가능
- 유형
  - 게임플레이에서 수행할 액터의 역할, (액터의 Class Name)
- 트랜스폼
  - 액터는 항상 월드에 존재해야 함 -> 항상 트랜스폼이 있음
- 프로퍼티
  - 액터에 설정된 속성 값, 디테일 윈도우에서 편집해서 같은 액터가 다른 일을 하게 할 수 있음
- 게임 로직
  - 액터에 특정 상황이 발생할 때 구체적인 행동 명령시 프로그래밍 코드 필요, 언리얼에서는 블루프린트와 C++ 지원<br><br>
 
3. 레벨<br>
플레이어에게 주어지는 스테이지<br>
언리얼 엔진에서는 월드에 배치된 액터들의 집합을 레벨이라고 부름

4. 컴포넌트
- 시각적 기능: 플레이어에게 어떻게 보여질 것인가
- 물리적 기능: 액터의 이동, 액터 간 상호적용을 어떻게 할 것인가
- 움직임: 액터가 어떤 움직임을 가질 것인가

액터를 설계할 때 유연하게 대처하기 위해 각 기능을 규격화함<br>
이러한 기능을 컴포넌트라고 함

- StaticMesh 컴포넌트: 애니메이션 X, 모델링 에셋 -> 시각적/물리적 기능을 제공<br>
주로 배경 물체에 사용
- SkeletalMesh 컴포넌트: 애니메이션 O, 모델링 에셋 -> 시각적/물리적/애니메이션 기능 제공<br>
주로 캐릭터에 사용
- Collision 컴포넌트 : 구/박스/캡슐로 지정한 영역에 물리적인 기능 설정 -> 시각적 기능 X
- Camera 컴포넌트 : 가상 세계에서 보여지는 현 상황을 플레이어의 모니터에 출력하는 기능
- Audio 컴포넌트 : 가상 세계에서 소리를 발생시키는 데 사용하는 기능
- Particle System 컴포넌트 : 파티클 시스템으로 설계된 이펙트를 화면에 보여주는 기능
- Light 컴포넌트 : 전구, 헤드라이트 등과 같이 물체에 광원 효과 부여하는 기능
- Movement 컴포넌트 : 물체에 특정한 움직임을 부여하는 기능

액터는 여러 개의 컴포넌트를 가질 수 있으나 대표하는 하나의 컴포넌트가 필요 -> Root 컴포넌트<br>
StaticMesh 컴포넌트는 게임 제작에서 가장 많이 사용하는 기본 컴포넌트<br><br>

5. 액터의 설계
- UStaticMeshComponent :<br>
액터가 두 개의 StaticMesh 컴포넌트를 가지려면 액터의 멤버 변수로 두 개의 UStaticMeshComponent 클래스의 포인터를 선언해야 함<br>
액터 클래스가 UStaticMeshComponent 클래스 정보를 참조하게 header 파일에 CoreMinimal.h -> EngineMinimal.h 변경<br>
UStaticMeshComponent 포인터로 선언 -> 구현부에서 메모리 동적으로 할당해 대입<br>
언리얼 엔진에서는 언리얼 실행 환경을 통해 더 이상 사용하지 않는 개체에 할당된 메모리를 자동으로 소멸시키는 기능 O<br><br>

- UPROPERTY : 언리얼 실행 환경이 객체 자동관리하려면 UPROPERTY 매크로를 통해 객체 지정
  - 언리얼 오브젝트에만 사용 가능<br><br>
  
- 언리얼 오브젝트의 구성 요소
  - 클래스 선언 매크로<br>
  클래스가 언리얼 오브젝트임을 선언하기 위한 매크로<br>
  선언 윗줄에 UCLASS라는 매크로 선언, 내부에는 GENERATED_BODY 매크로 선언<br>
  - 클래스 이름 접두사<br>
  U 접두사 : 액터가 아닌 클래스 (UStaticMeshComponent)<br>
  A 접두사 : 액터인 클래스 (AActor)<br>
  - generated.h 헤더 파일<br>
  언리얼 헤더 툴에 의해 자동으로 생성되는 부가 파일<br>
  오즈벡트 선언의 마지막 #include 구문에 이 헤더 파일을 반드시 선언
  - 외부 모듈에의 공개 여부<br>
  윈도우의 DLL 시스템은 DLL 내 클래스 정보를 외부에 공개할 지 결정하는 _declspec(dllexport) 존재<br>
  언리얼 엔진에서 키워드를 사용하려면 '모듈명_API' 키워드를 클래스 선언 앞에 추가 (없으면 다른 모듈에서 해당객체 접근 X)<br><br>
  
- CreateDefaultSubobject()<br>
생성자 코드에서 컴포넌트를 생성하는 용도, 안 문자열은 Hash 값 생성에 사용 -> 다른 컴포넌트와 중복되지 않아야 함<br><br>
  
- RootComponent, SetupAttachment()<br>
RootComponent 변수는 액터를 대표하는 루트 컴포넌트, Comp1->SetupAttachment(Comp2)는 Comp1을 Comp2의 자식으로 만드는 것<br><br>

6. 액터와 에디터 연동
- UPROPERTY(VisibleAnywhere)<br>
디테일 윈도우에서 컴포넌트의 속성을 편집하기 위해서 필요한 것<br><br>

7. 액터 기능의 확장
- Comp1->SetRelativeLocation(FVector)<br> 
컴포넌트의 기본 위치 값을 변경<br>
(F 접두사 클래스 : 언리얼 오브젝트가 아닌 일반 C++ 클래스/구조체)

- UPointLightComponent : 조명 기능
- UParticleSystemComponent : 이펙트 기능<br><br>

8. 객체 유형과 값 유형<br>
- 언리얼 오브젝트의 속성 값
  - 객체 유형 : 객체를 관리 (클래스의 포인터)
  - 값 유형 : 값을 관리 (하단)
- 언리얼 엔진이 제공하는 대표적인 값 유형
  - 바이트 : uint8
  - 정수 : int32
  - 실수 : float
  - 문자열 : FString, FName
  - 구조체 : FVector, FRotator, FTransform
  
- VisibleAnywhere의 문제:<br>
객체를 볼 수 있지만, 해당 객체를 다른 것으로 변경 불가 -> 객체에 속한 속성들은 변경 가능<br>
당연히 값 유형도 VisibleAnywhere로 데이터 변경 불가
- EditAnywhere : 속성의 데이터를 변경할 때 사용하는 키워드
- Category=분류명 : 분류명으로 값이 분류됨<br><br>

9. 에셋의 지정
- 에셋 불러들이기:
  1. 고유한 키 값 파악
  2. 에셋을 관리하는 시스템에 키 값으로 질의 (키 = 경로 값)
  3. 에셋의 포인터를 가져옴
- 복사한 레퍼런스 정보 {오브젝트 타입}'{폴더명}/{파일명}.{에셋명}:
  - 오브젝트 타입 : 에셋의 타입을 명시적으로 지정
  - 폴더/파일명 : 물리적인 디스크에 위치한 에셋의 경로 정보, 다른 에셋과 중복 X
  - 에셋명 : 에디터에서 보여지는 에셋의 이름, 중복 O
- ConstructorHelpers::FObjectFinder<ObjType>Vari1(TEXT("Dir"))<br>
Dir 경로에 있는 ObjType 타입인 에셋을 불러와 Vari1 변수로 선언
- Vari1.Object : 에셋에 대한 포인터
- Vari1.Succeeded() : 불러오기 성공 여부
- Comp1->SetStaticMesh(Vari1.Object) : StaticMesh 컴포넌트에 불러온 에셋을 로딩
- Comp1->SetTemplate(Vari1.Object) : 이펙트 에셋 로딩할 때 SetStaticMesh 대신에 사용<br><br>

## Chapter 3

### What I learned
1. 로깅 환경의 설정
- UE_LOG(카테고리, 로깅 수준, 형식 문자열, 인자..)
  - 로그 카테고리 : 모든 로그에 지정된 분류를 위한 카테고리, 기능마다 로그를 구분하는데 사용
  - 로깅 수준 : Log(흰색), Warning(노란색), Error(붉은색) 세 가지로 나뉨
    - 로그 필터 : 출력 로그 윈도우에 있는 기능, 로깅 수준 + 카테고리로 필터
  - 형식 문자열 : 다양한 데이터를 하나의 문자열로 조합해 출력<br>
  문자열 정의 시 TEXT 매크로를 사용하는 것이 좋음<br>
  문자열 정보를 받아오려면 \* 연산자가 필요 (\*GetName())
  
- DEFINE_LOG_CATEGORY_EXTERN(Category1, Log/Warning/Error, All) -> header 파일
- DEFINE_LOG_CATEGORY(Category1) -> c++ 파일, #include 아래<br>
이 이후에 UE_LOG에 정의한 Custom Category 지정 가능
- #define으로 함수 이름과 코드 라인을 함께 출력하도록 매크로 제작 가능

2. 어설션
- check : 조건을 통과하지 못하면 크래시 화면을 띄움
- ensure : 가볍게 경고만 내리는 어설션

3. 액터의 주요 이벤트 함수
액터는 준비, 게임 참여, 퇴장의 과정을 거침<br>
- virtual void PostInitializeComponents() : 액터에 속한 컴포넌트의 세팅이 완료될 때 호출함
- virtual void BeginPlay() : 액터가 게임에 참여할 때 호출됨
- virtual void Tick() : 매 프레임마다 호출
- virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) : 액터가 게임에서 퇴장할 때 호출
액터의 이벤트 함수들은 가상 함수로 선언되어 있음<br>

4. 움직이는 액터의 설계
- 액터의 Tick 함수를 이용해 액터의 움직임을 구현할 수 있음<br>
이전 렌더링 프레임 ~ 현재 렌더링 프레임까지 소요된 시간은 Tick의 인자인 DeltaSeconds로 알 수 있음<br>
렌더링 프레임은 레벨의 복잡도+컴퓨터 성능 불규칙하게 동작 -> DeltaSeconds 값도 불규칙<br>
- 데이터 은닉을 고려한 설계 방식으로 변수를 생성해야 함
  - UPROPERTY 매크로에 AllowPrivateAccess META 키워드 추가하면 에디터에서 편집 + 변수 데이터 은닉 가능 -> 캡슐화 가능해짐
  - UPROPERTY 매크로 구문 안 키워드 값은 C++ 언어 문법이 아닌 언리얼 엔진의 문법 -> 언리얼 헤더 툴이라는 프로그램으로 분석<br>
  generated라는 이름의 추가 코드를 자동으로 생성 -> generated 코드까지 묶어서 소스 코드를 컴파일하면 실행환경이 이를 사용<br>
  언리얼 헤더툴이 생성하는 코드는 Intermediate 폴더에 저장 -> 자동 변경되므로 수정 불가
- 회전에는 FRotator 사용
  - Pitch: Y축 회전
  - Yaw: Z축 회전
  - Roll: X축 회전
- 언리얼 엔진에서 시간을 관리하는 주체는 월드, TimeManager가 있음
  - Tick 함수가 아닌 곳에서 프레임 시간을 가져올 때는 GetWorld()->GetDeltaSeconds() 함수를 쓸 수 있음
  - GetWorld()->GetTimeSeconds(): 게임 시작 후 현재까지 경과된 시간
  - GetWorld()->GetUnpausedTimeSeconds(): 게임을 중지한 시간을 제외한 경과시간
  - GetWorld()->GetRealTimeSeconds(): 현실 세계의 경과 시간
  - GetWorld()->GetAudioTimeSeconds(): 게임을 중지한 시간을 제외한 현실세계의 경과시간

5. 무브먼트 컴포넌트의 활용
- 언리얼 엔진에서는 움직임 요소를 분리해 액터랑 별도로 관리하도록 프레임워크 -> 무브먼트 컴포넌트
  - 무브먼트 컴포넌트는 액터의 움직임을 책임짐<br>
  액터는 무브먼트 컴포넌트가 제공하는 이동 매커니즘에 따라 움직임<br>
  Tick 함수를 구현하지 않아도 동일하게 움직이는 액터 제작 가능
- 언리얼 엔진에서 제공하는 무브먼트 컴포넌트
  - FloatingPawnMovement: 중력의 영향을 받지 않는 액터의 움직임을 제공, 입력에 따라 자유롭게 움직이도록
  - RotatingMovement: 지정한 속도로 액터를 회전
  - InterpMovement: 지정한 위치로 액터를 이동
  - ProjectileMovement: 액터에 중력의 영향을 받아 포물선을 그리는 발사체의 움직임을 제공<br>
  총알/미사일등에 사용
  
6. 프로젝트의 재구성
- 언리얼 엔진에서 액터의 제거 메뉴는 제공하지 않음, 수동제거 필요
  1. .vs, Binaries, Intermediate, ArenaBattle.sln 파일 제거
  2. uproject를 우클릭하고 Generate Visual Studio project files 메뉴를 선택 -> 자동으로 솔루션 생성
  3. 솔루션 컴파일 진행 시 Binaries 폴더 생성, 빌드가 완료되면 해당 폴더에 DLL 파일 생성
    - 언리얼 빌드 툴이라는 프로그램을 가동시키기 때문<br>
    C++ Source 폴더를 분석하면서 솔루션 파일을 게임 프로젝트 폴더에 생성 + 솔루션 파일에서 참조해야 하는 프로젝트 파일은 Intermediate 폴더의 ProjectFiles 폴더에 생성
- 액터 제거하려면 Source 폴더에서 관련 파일을 지우고 (Fountain.h, Fountain.cpp) Generate Visual Studio project files



