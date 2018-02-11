// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
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

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Initialize(UTankTurret *TurretToSet, UTankBarrel *BarrelToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();

protected:

	UPROPERTY(BlueprintReadOnly)
	EFireStatus FireStatus = EFireStatus::Reloading;

private:
	UTankBarrel *Barrel;
	UTankTurret *Turret;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FiringVelocity = 6000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 2;

	UPROPERTY(EditAnywhere, Category = "Setup")
	UClass *Projectile_BP;

	float LastFireTime = 0;

	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDireciton);

};
