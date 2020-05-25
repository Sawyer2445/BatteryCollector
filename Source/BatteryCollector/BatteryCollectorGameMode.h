// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

//enum to store the current state of gameplay 
UENUM(BlueprintType)
enum class EBatteryPlayState : uint8
{
	EPlaying, 
	EGameOver, 
	EWon,
	EUnknow
};

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void Tick(float DeltaTime) override;

	/** Return power needed to win - needed to HUD */
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

	virtual	void BeginPlay() override;

	/** Return the current play state */
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrentState() const;

	/** Sets a new play state */
	UFUNCTION(BlueprintCallable, Category = "Power")
	void SetCurrentState(EBatteryPlayState NewState);
protected:
	/** The rate at which the character loses power */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float DecayRate;
	
	/** Needed power to win the game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float PowerToWin;

	/** Widget class to use our HUD */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** The instance of the HUD */
	UPROPERTY()
	class UUserWidget* CurrentWidget;
private:
	/** Keeps track the game current play state */
	EBatteryPlayState CurrentState;

	TArray<class ABCSpawnVolume*> SpawVolumesActors;

	/** Handle any functions calls they that change CurrentState  */
	void HandleNewState(EBatteryPlayState NewState);
};