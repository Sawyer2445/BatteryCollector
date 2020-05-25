// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BCSpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ABCSpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABCSpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns the WhereToSpawn sub object  */
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const
	{
		return WhereToSpawn;
	}

	/** Find a random point within BoxComponent  */
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	/** Toggle active spawn volume */
	UFUNCTION(BlueprintCallable, Category = "Spawinig")
	void SetSpawningActive(bool bShouldSpawn);

protected:
	UPROPERTY(EditAnywhere, Category = "Spawning")
	/** The pickups to spawn */
	TSubclassOf<class ABCPickup> WhatToSpawn;

	FTimerHandle SpawnTimer;

	/** Minimum spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;

	/** Max spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;

private:
	/** Box component to specify where pickup should be spawned  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;

	/** Handle spawning a new pickup */
	void SpawnPickup();

	/** The current spawn delay */
	float SpawnDelay;

};
