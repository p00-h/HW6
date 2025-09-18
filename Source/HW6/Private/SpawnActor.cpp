// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

}

FVector ASpawnActor::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();
	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

void ASpawnActor::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass) return;

	GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);
}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,                      // FTimerHandle
		this,                                  // 호출할 객체
		&ASpawnActor::SpawnCoin,               // 호출할 멤버 함수
		4.0f,                                  // 주기 (초 단위)
		true,                                  // 반복 여부
		2.0f                                   // 첫 실행 딜레이 (옵션)
	);
}

void ASpawnActor::SpawnCoin()
{
	// 원하는 코인 클래스를 Blueprint에서 설정해둘 수 있게 UPROPERTY로 노출
	if (CurrentSpawnCount >= MaxSpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	if (CoinClass)
	{
		SpawnItem(CoinClass);
		CurrentSpawnCount++;
	}
}

// Called every frame
void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

