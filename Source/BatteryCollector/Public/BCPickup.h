// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BCPickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ABCPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABCPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Return mesh for the pickup */
	FORCEINLINE class UStaticMeshComponent* GetMesh() const
	{
		return PickupMesh;
	}

	/** Return whether pickup is active  */
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	/** Set new state for pickup */
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool NewPickupState);

protected:
	/** True when pickup can be used, and false when pickup  is deactivated*/
	bool bIsActive;

private:
	/** Static mesh to representation pickup in level*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;

};
