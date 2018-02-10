// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.generated.h"

//forward declaration
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void BeginPlay() override;

	void AimAt(FVector HitLocation);

protected:

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent *TankAimingComponent;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent *TankMovementComponent;

public:	

	UFUNCTION(BlueprintCallable)
	void Fire();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FiringVelocity = 6000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 2;

	UPROPERTY(EditAnywhere, Category = "Setup")
	UClass *Projectile_BP;

	UTankBarrel *Barrel;

	float LastFireTime = 0;
};