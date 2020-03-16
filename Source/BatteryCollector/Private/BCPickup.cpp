// Fill out your copyright notice in the Description page of Project Settings.


#include "BCPickup.h"

// Sets default values
ABCPickup::ABCPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// All pickup can be uesd on start 
	bIsActive = true;

	//Create the static mesh component 
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;

}

// Called when the game starts or when spawned
void ABCPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABCPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABCPickup::IsActive()
{
	return bIsActive;
}

void ABCPickup::SetActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}

void ABCPickup::WasCollected_Implementation()
{
	//log collect pickup 
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("Pickup %s was collected"), *PickupDebugString);
}

