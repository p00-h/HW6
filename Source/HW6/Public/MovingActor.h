// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

UCLASS()
class HW6_API AMovingActor : public AActor
{
	GENERATED_BODY()

	FVector StartLocation;
	int32 MoveDirSign = 1;
	
public:	
	// Sets default values for this actor's properties
	AMovingActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	UStaticMeshComponent* CoinMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MoveSpeed = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float MaxRange = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FVector MoveDirection = FVector(1, 0, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float SpinSpeed = 0.0f;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
