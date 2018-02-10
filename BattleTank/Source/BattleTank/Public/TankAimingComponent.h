// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFireStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	void AimAt(FVector HitLocation, float FiringVelocity);

	UFUNCTION(BlueprintCallable)
	void Initialize(UTankTurret *TurretToSet, UTankBarrel *BarrelToSet);

protected:

	UPROPERTY(BlueprintReadOnly)
	EFireStatus FireStatus = EFireStatus::Reloading;

private:
	UTankBarrel *Barrel;
	UTankTurret *Turret;

	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDireciton);

};
