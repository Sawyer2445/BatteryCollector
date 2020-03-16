// Fill out your copyright notice in the Description page of Project Settings.


#include "BCBatteryPickup.h"

ABCBatteryPickup::ABCBatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);
	BatteryPower = 150.f;
}

void ABCBatteryPickup::WasCollected_Implementation()
{
	//Use base pickup behavior 
	Super::WasCollected_Implementation();

	Destroy();
}

float ABCBatteryPickup::GetBatteryPower()
{
	return BatteryPower;
}
