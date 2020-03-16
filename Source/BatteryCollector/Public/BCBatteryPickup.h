// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BCPickup.h"	
#include "BCBatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABCBatteryPickup : public ABCPickup
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABCBatteryPickup();

	/** Override WasCollected function - Implementation, because it's Blueprint Native Event */
	void WasCollected_Implementation() override;

	/** Public way to get Battery's power */
	float GetBatteryPower();
protected:
	/** Set the amount of power the battery gives to the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float BatteryPower;
	
};
