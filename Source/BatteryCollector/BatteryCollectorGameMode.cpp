// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "BCSpawnVolume.h"
#include "GameFramework/PawnMovementComponent.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PrimaryActorTick.bCanEverTick = true;
	//Base DecayRate 
	DecayRate = 0.01f;

	
}

void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{	
		if (MyCharacter->GetCurrentPower() > PowerToWin)
		{
			SetCurrentState(EBatteryPlayState::EWon);
		}
		else if (MyCharacter->GetCurrentPower() > 0)
		{
			MyCharacter->UpdatePower(-DeltaTime * DecayRate * (MyCharacter->GetInitialPower()));
		}
		if (MyCharacter->GetCurrentPower() < 0)
		{
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}
}

float ABatteryCollectorGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

void ABatteryCollectorGameMode::BeginPlay()
{
	Super::BeginPlay();
	// find all spawn volumes in level 
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABCSpawnVolume::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		ABCSpawnVolume* SpawnVolumeActor = Cast<ABCSpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawVolumesActors.AddUnique(SpawnVolumeActor);
		}
	}

	SetCurrentState(EBatteryPlayState::EPlaying); 

	//set the score to beat 
	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = MyCharacter->GetInitialPower() * 1.25f;
	}
	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const
{
	return CurrentState;
}

void ABatteryCollectorGameMode::SetCurrentState(EBatteryPlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(NewState);
}

void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
	case EBatteryPlayState::EPlaying:
	{
		//SpawnVolume active
		for (auto SpawnVolume : SpawVolumesActors)
		{
			SpawnVolume->SetSpawningActive(true);
		}
	}
	break;
	case EBatteryPlayState::EGameOver:
	{
		//SpawnVolume inactive 
		for (auto SpawnVolume : SpawVolumesActors)
		{
			SpawnVolume->SetSpawningActive(false);
		}
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC)
		{
			PC->SetCinematicMode(true, false, false, false, true);
		}
		ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (MyCharacter)
		{
			MyCharacter->GetMesh()->SetSimulatePhysics(true);
			MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
	}	
	break;
	case EBatteryPlayState::EWon:
	{
		//SpawnVolume inactive 
		//deseable input 
		//ragdoll the character 
		for (auto SpawnVolume : SpawVolumesActors)
		{
			SpawnVolume->SetSpawningActive(false);
		}
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC)
		{
			PC->SetCinematicMode(true, false, false, false, true);
		}

	}
	break;
	
	break;
	default:
	case EBatteryPlayState::EUnknow:
	{
		//do nothing 
	}
	
	break;
	}
}
