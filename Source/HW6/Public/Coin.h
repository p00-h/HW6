// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class HW6_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	UStaticMeshComponent* CoinMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	float Speed;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
