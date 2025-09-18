# HW6

박스 볼륨 내부의 임의 위치에 일정 간격으로 코인 액터를 생성(스폰)하는 간단한 UE5 예제입니다. 코인은 틱마다 회전하며, 예제용 이동/회전 액터(AMovingActor)도 포함되어 있습니다.

> **Engine:** Unreal Engine 5.x
> **Language:** C++ (MSVC / Visual Studio)

---

## 📦 개요

프로젝트에는 다음과 같은 핵심 `AActor` 클래스 3종이 들어 있습니다.

* **ACoin** – 로컬 Yaw 축으로 일정 속도로 회전하는 간단한 코인 액터
* **AMovingActor** – 시작 위치를 기준으로 특정 방향으로 이동하다가 최대 거리에서 반전해 왕복 이동(+ 선택적 스핀)
* **ASpawnActor** – `UBoxComponent` 박스 범위 안에서 임의 좌표를 뽑아 정해진 간격으로 코인을 스폰 (예제에서는 최대 10개까지)

---

## 🗂️ 소스 구조

```
Source/
  ├─ Coin.h / Coin.cpp          // 회전 코인 액터
  ├─ MovingActor.h / .cpp       // 왕복 이동 + 선택적 스핀
  └─ SpawnActor.h / .cpp        // 박스 내부 랜덤 스폰 + 타이머
```

---

## ✨ 주요 기능

### ACoin

* 루트 + 스태틱 메쉬 컴포넌트 구성
* `Speed`(deg/sec)에 따라 매 틱 Yaw 회전

### AMovingActor

* BeginPlay에서 `StartLocation` 저장, `MoveDirection` 정규화
* `MoveSpeed`로 이동, 시작점으로부터의 거리가 `MaxRange` 이상이면 방향 반전
* `SpinSpeed`가 0이 아니면 로컬 Yaw 회전 추가

### ASpawnActor

* `UBoxComponent`(SpawningBox)로 스폰 볼륨을 정의
* `GetRandomPointInVolume()`로 박스 내부 임의 좌표 샘플링
* `SpawnItem()`이 `CoinClass`(TSubclassOf<AActor>)를 스폰
* BeginPlay에서 타이머 등록 → **처음 2초 지연 후 4초 간격**으로 `SpawnCoin()` 호출
* **최대 10개** 생성 시 타이머 해제(스폰 중단) — 예제 구현 기준

> 스폰 간격/지연/최대 개수는 코드로 조절 가능하며, 필요 시 UPROPERTY로 에디터에 노출할 수 있습니다.

---

## 🔧 에디터 노출 파라미터

### ACoin

* `Speed` *(float)* – 초당 회전 속도(도/초)

### AMovingActor

* `MoveSpeed` *(float)* – 이동 속도 (uu/sec)
* `MaxRange` *(float)* – 시작점으로부터의 최대 이동 거리
* `MoveDirection` *(FVector)* – 이동 방향(자동 정규화)
* `SpinSpeed` *(float)* – 로컬 Yaw 회전 속도(도/초)

### ASpawnActor

* `SpawningBox` *(UBoxComponent)* – 스폰 볼륨
* `CoinClass` *(TSubclassOf<AActor>)* – 스폰할 액터 클래스(예: `ACoin` 기반 BP)
* `MaxSpawnCount` *(int32)* – 최대 스폰 개수 (예: 10)

---

## ⏱️ 타이머 커스터마이즈

현재 값은 `ASpawnActor::BeginPlay()`에서 설정되어 있습니다.

```cpp
// IntervalSeconds = 4.0f, FirstDelay = 2.0f, bLoop = true
GetWorld()->GetTimerManager().SetTimer(
    SpawnTimerHandle, this, &ASpawnActor::SpawnCoin,
    4.0f, /*bLoop=*/true, 2.0f
);
```

에디터에서 조절하고 싶다면 아래처럼 노출해 사용하세요.

```cpp
// SpawnActor.h
UPROPERTY(EditAnywhere, Category = "Spawning")
float SpawnIntervalSeconds = 4.0f;

UPROPERTY(EditAnywhere, Category = "Spawning")
float FirstDelaySeconds = 2.0f;
```

그리고 `BeginPlay()`에서 하드코딩 값 대신 위 변수를 사용합니다.

