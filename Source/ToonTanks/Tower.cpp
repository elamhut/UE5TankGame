// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATower::ATower()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	checkf(PlayerTank, TEXT("Couldn't get Pawn of type ATank in the Tower"));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::AimTurret() const
{
	const FVector TargetDirection = PlayerTank->GetActorLocation() - GetActorLocation();
	const FRotator LookAt = TargetDirection.Rotation();
	TurretMesh->SetWorldRotation(LookAt,
	                             false);
}

// Called every frame
void ATower::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		AimTurret();
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	GetWorldTimerManager().ClearTimer(FireRateTimerHandle);
}

void ATower::CheckFireCondition()
{
	if (InFireRange())
	{
		DoFire();
	}
}

bool ATower::InFireRange() const
{
	if (PlayerTank)
	{
		const float Distance = FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());

		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;
}
