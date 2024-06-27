# 이득우의 언리얼 C++ 게임 개발의 정석

## Chapter 1

### What have I learned

1. 기초적인 에디터 UI
2. 새 C++ 클래스 생성
3. 마켓플레이스 사용법
4. 새 레벨 생성
5. 프로젝트 세팅 (맵/모드) 

## Chapter 2

### What have I learned

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

### What have I learned
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

## Chapter 4

### What have I learned
1. 게임 모드
- 게임 규칙: 플레이어에게 보이지 않는, 실체가 없는 무형적인 요소<br>
게임플레이 중 다양한 사건사고가 발생할 때 게임 진행에 참고해야 하는 핵심 요소, 심판에 해당
  - 아군이 발사한 총알에 맞을 때 데미지를 받을지 말지 등의 규칙
  - 게임의 틀을 잡아주는 역할도 함: 입장할 때마다 플레이어를 점검하고 액터를 생성해 전달하는 역할도 함
- 폰(Pawn): 플레이어가 조종할 수 있는 액터
- 프로젝트 설정
  - 맵 & 모드: 시작 레벨 설정 가능
  - Selected GameMode
    - Default Pawn Class: 게임에 입장한 플레이어에게 주어질 조종할 수 있는 액터, 폰의 타입을 지정하는 곳
- 게임모드 적용: 세팅 > 월드 세팅 > Game Mode > GameMode Override > 만든 게임모드 선택

2. 플레이어의 입장
플레이어가 입장하면 게임 모드는 플레이어에게 폰을 배정해 줌<br>
거기에 PlayerController라는 특별한 액터도 함께 배정
- 플레이어 컨트롤러(PlayerController): 게임 세계에서 현실 세계의 플레이어를 대변하는 무형의 액터
  - 게임 세계에서 플레이어와 1:1로 소통하면서 폰을 조종하는 역할
  - 플레이어가 입장할 때 배정, 배정된 플레이어 컨트롤러는 변경 불가
- 폰(Pawn): 플레이어 컨트롤러에게 조종당하는 액터
  - 플레이어 컨트롤러가 시키는 대로 움직이는 꼭두각시
  - 게임 세계에서 실제로 보여지고 레벨과 물리적인 충돌을 하면서 기획자가 배치한 액터와 상호작용
  - 플레이어 컨트롤러를 통해 현재 조종중인 폰을 버리고 다른 폰으로 옮겨가 조종할 수 있음
  
- 플레이 버튼을 누른다는 것은 만들고 있는 게임에 제작자 플레이어가 입장하는 것<br>
게임모드에 의해 아래 순서로 관련 액터들이 생성 및 게임플레이 설정이 갖춰짐
  1. 플레이어 컨트롤러 생성
  2. 플레이어 폰 생성
  3. 플레이어 컨트롤러가 플레이어 폰 빙의
  4. 게임 시작

- 로그인(Login): 플레이어가 게임에 입장하는 것
  - 로그인 과정에서 플레이어에게 할당할 플레이어 컨트롤러가 생성됨
- PostLogin 이벤트 : 로그인을 완료하면 호출되는 이벤트 함수<br>
PostLogin 함수 내부에서 플레이어가 조종할 폰을 생성하고 플레이어 컨트롤러가 해당 폰에 빙의하는 작업이 이루어짐
  - 폰/컨트롤러 플레이어가 생성되는 시점은 각 액터의 PostInitializeComponents 함수로 파악할 수 있음
  - 빙의를 진행하는 시점은 플레이어 컨트롤러: Possess, 폰: PossessedBy 함수로 파악할 수 있음
  - virtual void OnPossess(APawn \*aPawn) override: Possess 함수 대신에 사용 가능
- Pawn의 Auto Possess Player 속성: 레벨에 이미 배치되어 있는 폰에 플레이어 컨트롤러가 빙의 가능
- C++로 제작된 폰이 아닌 블루프린트로 제작된 폰을 기본 폰으로 사용하려면 블루프린트 에셋의 클래스 정보를 넘겨주면 동일하게 사용 가능<br>
ex) static ConstructorHelpers::FClassFinder<APawn> BP_PAWN_C(TEXT("/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C"));

## Chapter 5

### What have I learned
1. 폰의 구성 요소
- 폰: 움직이는 액터 + 조종당하는 기능, 자동차도 될 수 있고 비행기도 될 수 있음
- 인간형 폰을 제작할 시 고려할 요소
  - 시각적 요소: 인간형 폰이 되려면 애니메이션 기능이 필요<br>
  스켈레탈 메시: 애니메이션을 재생하도록 리깅(Rigging) 데이터를 추가한 메시 -> 이를 관리하는 컴포넌트는 스켈레탈 메시 컴포넌트
  - 충돌 요소: 스켈레탈 메시는 에니메이션에 따라 변하므로 충돌을 담당할 충돌 컴포넌트를 별도로 사용 -> 인간은 캡슐 컴포넌트를 사용
  - 움직임 요소: 언리얼 엔진은 플레이어의 입력에 따라 폰이 움직이는 폰 무브먼트 컴포넌트라고 부르는 특수 컴포넌트를 제공<br>
  FloatingPawnMovement와 CharacterMovement라는 두 가지 폰 무브먼트 컴포넌트를 제공
  - 네비게이션: 폰은 목적지를 알려주면 스스로 목적지까지 이동하는 길 찾기 기능을 가지고 있음
  - 카메라 출력: 플레이어가 조종하는 폰은 플레이어 입력 해석으로 이동 + 자신이 보는 게임세계를 플레이어 모니터에 전송해줘야 함<br>
  폰에 카메라 컴포넌트를 부착하면 플레이어 컨트롤러가 폰에 빙의할 때 폰에 부착된 카메라 상을 플레이어 화면으로 전송
- 폰 컴포넌트:
  - Capsule: 폰의 움직임을 담당하는 충돌 컴포넌트<br>
  충돌 영역은 캐릭터 메시가 쏙 들어갈 만큼의 크기로 보통 설정<br>
  폰을 대표해 게임 세계에서의 움직임을 담당할 예정이므로 루트 컴포넌트로 설정
  - SkeletalMesh: 캐릭터 에셋을 보여주고 추가로 애니메이션도 담당<br>
  언리얼 엔진에서 액터의 기준 위치는 정중앙 위치 but 캐릭터 에셋은 주로 발바닥에 기준 위치를 잡음 -> Z축으로 절반만큼 내려줘야 함
  - FloatingPawnMovement: 플레이어의 입력에 따라 캐릭터가 움직이도록 설정해주는 컴포넌트<br>
  중력을 고려하지 않은 간단한 움직임을 구현할 수 있음
  - SpringArm: 3인칭 시점으로 카메라 구도를 편하게 설정할 수 있는 부가 컴포넌트
  - Camera: 폰에 카메라 컴포넌트를 부착하면 언리얼 엔진은 카메라가 바라보는 게임 세계의 화면을 플레이어의 화면으로 전송
  
2. 폰의 조작
플레이어의 입력은 언리얼 엔진이 제공하는 가상 입력 설정을 사용하면 다양한 기기와 멀티플랫폼에 대응할 수 있다<br>
프로젝트 세팅 -> 입력 설정에서 지정할 수 있으며, Bindings 섹션에서 Action Mappings/Axis Mappings라는 두 가지 입력 설정 항목을 볼 수 있다<br>
Axis Mapping은 조이스틱 레버를 의미하고 Action Mapping은 조이스틱 버튼을 의미한다.
- Axis Mappings: 조이스틱 레버의 신호를 설정하는 곳, 언리얼 엔진은 레버가 중립 위치에 있으면 0, 끝 위치에 있으면 -1~1을 게임 로직에 전달<br>
MoveRight의 경우 A를 누르면 -1, D를 누르면 1이 발생하고 아무 키도 누르지 않으면 0이 지속적으로 발생
- Action Mappings: 조이스틱 버튼의 신호를 설정하는 곳, Axis Mappings와 달리 언리얼 엔진은 버튼을 눌렀을 때/뗄 때만 신호를 전달
- InputComponent: 입력 설정을 처리하기 위한 언리얼 오브젝트, 신호를 받는 BindAxis와 BindAction 함수를 제공
  - SetupInputComponent(UInputComponent \*PlayerInputComponent): 폰의 멤버 함수와 입력 설정을 Binding하는 함수
    - PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABPawn::UpDown): UpDown을 AABPawn::UpDown에 Bind
- AddMovementInput: -1~1의 입력 값을 폰 무브먼트 컴포넌트에 전달해서 폰을 움직이게 함, 추가로 이동할 방향을 WorldDirection(벡터)에 지정해야 함
  - Scale: 1 전진, -1 후진, 0 중립
  - GetActorForwardVector(): 앞벡터
  - GetActorRightVector(): 오른쪽 벡터
  
\* 폰을 조종하기 위한 입력 로직은 폰 클래스에 구현하는 것이 일반적이다. 다만 언리얼 엔진의 입력 시스템은 중간에 플레이어 컨트롤러를 거쳐서 폰에 전달된다<br>
플레이어 컨트롤러에 특정 입력을 처리하는 코드를 구현하면 해당 입력은 플레이어 컨트롤러에서 필터링되어 폰에 전달되지 않는다.

- FInputModeGameOnly InputMode + SetInputMode(InputMode): 플레이어 컨트롤러에게 UI를 배제하고 게임에게만 입력을 전달하도록 명령을 내림

3. 애니메이션의 설정
스켈레탈메시에 애니메이션을 설정<br>
- 애니메이션 임포트: 콘텐츠 브라우저에서 폴더 생성 -> 폴더 선택 후 임포트 버튼을 눌러 에셋 파일 선택 -><br>
Mesh->Skeleton에서 스켈레톤 선택 -> 임포트<br>
확인: 애니메이션 더블클릭해서 확인

애니메이션은 코드로 하기에 한계가 있음 -> 애니메이션 블루프린트
- 애님 그래프: 애니메이션 블루프린트에서 애니메이션을 설계하는 작업 환경

애니메이션 시스템은 C++ 프로그래밍의 애님 인스턴스(Anim Instance)라는 클래스로 관리<br>
스켈레탈 메시 컴포트는 관리하는 캐릭터의 애니메이션을 애님 인스턴스에 위임<br>

## Chapter 6

### What have I learned

1. 캐릭터 모델
- Character(캐릭터): 인간형 폰을 효과적으로 제작하기 위한 특수한 모델
  - 상속 구조: 만든 캐릭터 클래스 -> ACharacter -> APawn(Capsule, SkeletalMesh Component 포함, CharacterMovement로 움직임 관리)
  - GetCapsuleComponent(), GetMesh(), GetCharacterMovement(): ACharacter의 Capsule, Mesh, Movement private 컴포넌트 포인터 접근용 함수
  
캐릭터는 CharacterMovement 컴포넌트를 사용 (<=> Pawn의 FloatingPawnMovement)
- 장점:
  1. 점프와 같은 중력 반영 움직임 제공
  2. 기어가기, 날아가기, 수영등 다양한 이동모드 + 현재 움직임에 대한 더 많은 정보 제공
  3. 멀티 플레이 네트워크 환경에서 자동으로 동기화
  
2. 컨트롤 회전의 활용
플레이어가 게임에 입장할때 부여받는 두 액터: (1) 플레이어 컨트롤러, (2) 폰
- 플레이어 컨트롤러: 물리적인 요소를 고려하지 않은, 플레이어의 의지에 관련된 데이터를 관리
  - 컨트롤 회전: 플레이어의 의지를 나타냄
    - Turn: 캐릭터의 Z축 회전 입력 설정
	- LookUp: 캐릭터의 Y축 회전 입력 설정
- 폰 게임 세계에서 캐릭터가 처한 물리적인 상황을 관리
  - 속도: 폰의 이동 상태를 알려주는 중요한 데이터

AddControllerPitchInput 넣어도 상하이동에 반응하지 않음<br>
언리얼 엔진의 캐릭터 모델은 기본으로 컨트롤 회전의 Yaw값과 폰의 Yaw값이 연동되어 있음 (속성의 UseControllerRotationYaw)<br>
이 때문에 좌우로 움직이면 Z축으로 회전하지만 마우스 상하이동이 폰에 영향 X

3. 삼인칭 컨트롤 구현 (GTA 방식)
블루프린트로 제작한 흰색 마네킹이 가지고 있는 설정
- 캐릭터의 이동: 현재 보는 시점을 기준으로 상하좌우로 마네킹이 이동 but 카메라는 회전 X
- 캐릭터의 회전: 캐릭터가 이동하는 방향으로 회전
- 카메라 지지대 길이: 450cm
- 카메라 회전: 마우스 상하좌우 이동에 따라 카메라 지지대가 상하좌우로 회전
- 카메라 줌: 카메라 시선 - 캐릭터 사이에 장애물이 감지되면 캐릭터가 보이도록 장애물 앞으로 줌인

- SpringArm 컴포넌트: 언리얼 엔진에서 삼인칭 시점의 카메라 설정을 구현할 때 사용할 수 있는 컴포넌트

FRotator 데이터로부터 원하는 방향 값인 FVector 데이터를 얻어야 함<br>
액터의 회전 (0,0,0) == 액터가 바라보는 방향이 월드 X축방향 (1,0,0) -> 월드의 X축방향: 기본 회전값애 대응하는 방향값<br>
스프링암의 회전값은 컨트롤 회전값과 동일 -> 컨트롤 회전 값이 카메라가 바라보는 방향 -> 컨트롤 회전 값으로부터 회전행렬을 생성한 뒤 방향축을 대입해 움직일 방향을 가져올 수 있음
- 언리얼 엔진에서 시선 방향: X축, 우측 방향 Y축
- OrientRotationToMovement: 캐릭터를 움직이는 방향으로 자동 회전, 회전속도 지정 가능

4. 삼인칭 컨트롤 구현 (디아블로 방식)
디아블로의 조작 방식
- 캐릭터의 이동: 상하좌우키 조합해 이동할 방향 결정
- 캐릭터의 회전: 캐릭터는 입력한 방향으로 회전
- 카메라 지지대 길이: 800cm
- 카메라 회전: 카메라 회전 없이 고정 시선으로 45도
- 카메라 줌: 없음 - 카메라와 캐릭터 사이 장애물이 있을 경우 외곽선으로 처리

UPROPERTY를 사용하지 않는 FVector와 같은 값타입 변수는 항상 초기값을 미리 지정하는 것이 안전 -> 찾기 어려운 버그는 사소한 실수로부터 비롯<br>
축 입력 이벤트가 발생할 때 새로 선언한 DirectionToMove 변수를 업데이트, 이후 발생하는 Tick 로직에서 최종 멤버 변수를 참고해 이동
- 부드럽게 회전: UseControllerDesiredRotation (UserControllerRotationYaw 해제)

5. 컨트롤 설정의 변경
입력에 따라 컨트롤 방식을 변경하도록 기능 추가<br>
ViewChange라는 액션 매핑을 추가 -> 해당 키가 눌릴때마다 SetControlMode에 다른 인자값이 들어가도록
- BindAction: 액션 매핑 입력 설정과 연동하는 함수; 버튼이 눌렸는지(EInputEvent::IE_Pressed), 떼어졌는지(EInputEvent::IE_Released)에 대한 부가 인자 지정 가능
- FMath::InterpTo: 지정한 속도로 목표 지점까지 진행하되 도달하면 그 값에서 멈추는 기능<br>
float FInterpTo, Vector VInterpTo, Rotator RInterpTo 세 함수가 있음

## Chapter 7

### What have I learned

1. 애니메이션 블루프린트
언리얼 엔진은 에니메이션 시스템 제작 도구인 애니메이션 블루프린트를 제공<br>
- 애님 그래프: 시각적 도구를 사용해 애니메이션 시스템을 제작하도록 설계됨<br>
애님 인스턴스의 변수 값에 따라 변화하는 애니메이션을 설계하는 공간. 블루프린트로만 제작 가능
- 애님 인스턴스: 애니메이션 블루프린트의 기반을 이룸<br>
스켈레탈 메시를 소유하는 폰의 정보를 받아 애님 그래프가 참조할 데이터를 제공. 블루프린트와 C++로 제작할 수 있음

블루프린트에서 접근하는 키워드: BlueprintReadOnly, BlueprintWriteOnly

2. 폰과 데이터 연동
실제 게임에서 폰의 속도에 따라 다른 애니메이션을 재생하기 위해서는 프레임마다 폰의 속력과 애님 인스턴스의 CurrentPawnSpeed 값이 같아야 함<br>
폰의 데이터와 애님 인스턴스 데이터를 동일하게 만들려면
- 폰의 Tick 함수에서 애님 인스턴스의 CurrentPawnSpeed에 쓰거나
- 애님 인스턴스의 Tick에서 폰의 속도 정보를 가져온 후 CurrentPawnSpeed에 업데이트하는 방법이 있다 (이 방법이 일반적)

애님 인스턴스 클래스는 틱마다 호출되는 NativeUpdateAnimation 함수를 가상 함수로 제공

3. 스테이트 머신의 제작
상황에 따른 복잡한 애니메이션 시스템을 체계적으로 설계할 수 있도록 애님 그래프는 State Machine이라는 기능을 제공<br>
- State: 기계가 반복 수행하는 동작을 설계한 단위
- Transition: 하나의 스테이트에서 다른 스테이트로 이동하기 위한 조건 (언리얼 엔진에서는 Rule로 사용)

State -> 애님 그래프

4. 점프 기능의 구현
캐릭터 무브먼트 컴포넌트에는 대표적으로 점프 기능이 내장되어 있음<br>
ACharacter 클래스에는 Jump 멤버 함수가 있으며, Jump 입력과 연동하면 기능이 바로 완성
- 점프 높이: 캐릭터 무브먼트 컴포넌트를 GetCharacterMovement()로, 420으로 기본설정된 JumpZVelocity의 기본값을 원하는 값으로 변경

점프 애니메이션 구현 -> 폰의 무브먼트 컴포넌트에서 움직임을 파악하는 함수를 얻어올 수 있음
- IsFalling(): 현재 공중에 떠 있는지 알려준다
- IsSwimming(): 현재 수영 중인지 알려준다
- IsCrouching(): 현재 쭈그려있는지 알려준다
- IsMoveOnGround(): 땅 위에서 이동 중인지 알려준다

FloatingPawnMovement 컴포넌트는 해당 함수에 대해 모두 false값, 오직 캐릭터 무브먼트 컴포넌트만 기능을 제대로 구현

5. 애니메이션 리타겟
인간형 캐릭터의 경후 스켈레톤의 구성이 달라도 애니메이션을 교환할 수 있도록 애니메이션 리타겟 기능을 제공<br>
애니메이션 리타겟 기능이 동작하려면 애니메이션을 교환할 캐릭터들의 스켈레톤을 세팅해줘야 함<br>
스켈레톤 에셋 -> 리타겟 매니저 -> 릭 셋업으로 할 수 있음

리타겟으로 새롭게 애니메이션 에셋을 생성할 수 있음<br>
애님 에셋 리타겟 -> 애님 에셋 복제

6. 점프의 구현
점프는 지형에 따라 체공 시간이 다르므로 도약/체공/착지로 나누고 상황에 맞게 재생 시간을 조절해줘야 함
- 도약: 무릎을 구부렸다 펴는 애니메이션을 한 번만 재생
- 체공: 땅에 닿을 때까지 몸이 둥둥 뜨는 애니메이션을 반복적으로 재생
- 착지: 땅에 발을 딛는 애니메이션을 한 번 재생
- Time Remaining (ratio): 트랜지션 시작 스테이트의 애니메이션 재생의 남은 시간 비율을 얻어오는 노드 (0.1 = 재생 시간이 10% 남음)