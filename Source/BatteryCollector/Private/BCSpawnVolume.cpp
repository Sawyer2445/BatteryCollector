// Fill out your copyright notice in the Description page of Project Settings.


#include "BCSpawnVolume.h"
#include "Kismet\KismetMathLibrary.h"
#include "Components\BoxComponent.h"
#include "BCPickup.h"


// Sets default values
ABCSpawnVolume::ABCSpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	//Create the BoxComponent to represent the spawn volume
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	//Set the spawn delay ranges
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 5.0f;

}

// Called when the game starts or when spawned
void ABCSpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	SetSpawningActive(true);
}

// Called every frame
void ABCSpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ABCSpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;
	
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ABCSpawnVolume::SetSpawningActive(bool bShouldSpawn)
{
	if (bShouldSpawn)
	{
		//set the timer on SpawnPickup 
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ABCSpawnVolume::SpawnPickup, SpawnDelay, false);
	}
	else
	{
		//clear the timer on SpawnPickup
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

void ABCSpawnVolume::SpawnPickup()
{
	if (WhatToSpawn != NULL)
	{
		// Check world
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// Get random location to spawn 
			FVector	SpawnLocation = GetRandomPointInVolume();

			//Get a random rotation to the spawn Pickup
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.f;
			SpawnRotation.Pitch = FMath::FRand() * 360.f;
			SpawnRotation.Roll = FMath::FRand() * 360.f;

			ABCPickup* SpawnedActor = World->SpawnActor<ABCPickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams); 
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ABCSpawnVolume::SpawnPickup, SpawnDelay, false);
		}
	}
}