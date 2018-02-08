// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Renvoie les coordonnées de l'endroit où on vise
void UTankAimingComponent::AimAt(FVector HitLocation, float FiringVelocity)
{
	if (!Barrel) { return; }

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		LaunchVelocity,
		StartLocation,
		HitLocation,
		FiringVelocity,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret *TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator DeltaRotator = AimAsRotator - TurretRotator;
	Turret->Rotate(DeltaRotator.Yaw);
}
