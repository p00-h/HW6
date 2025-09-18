// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

class UBoxComponent;

UCLASS()
class HW6_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	FVector GetRandomPointInVolume() const;
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnItem(TSubclassOf<AActor> ItemClass);
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> CoinClass;
	FTimerHandle SpawnTimerHandle;
	void SpawnCoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
