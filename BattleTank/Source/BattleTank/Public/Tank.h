// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
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

	void AimAt(FVector HitLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent *TankAimingComponent;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(UTankBarrel *BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurretReference(UTankTurret *TurretToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();
	
private:
	UPROPERTY(EditAnywhere, Category = "Firing")
	float FiringVelocity = 6000;

	UPROPERTY(EditAnywhere, Category = "Setup")
	UClass *Projectile_BP;
	
	UTankBarrel *Barrel;
};