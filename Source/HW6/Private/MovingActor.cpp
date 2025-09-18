// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"

// Sets default values
AMovingActor::AMovingActor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	CoinMesh->SetupAttachment(Root);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	MoveDirection.Normalize();
}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector MoveOffset = MoveDirection * MoveSpeed * DeltaTime * MoveDirSign;
	CurrentLocation += MoveOffset;

	if (FVector::Dist(CurrentLocation, StartLocation) >= MaxRange)
	{
		CurrentLocation = StartLocation + MoveDirection * MaxRange * MoveDirSign;
		MoveDirSign *= -1;
	}
	SetActorLocation(CurrentLocation);

	if (!FMath::IsNearlyZero(SpinSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, SpinSpeed * DeltaTime, 0.0f));
	}
}

