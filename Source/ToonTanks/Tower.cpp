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
}

// Called every frame
void ATower::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerTank)
	{
		const FVector ActorLocation = GetActorLocation();
		const FVector PlayerTankLocation = PlayerTank->GetActorLocation();
		const float Distance = FVector::Dist(ActorLocation, PlayerTankLocation);
		
		if (Distance <= FireRange)
		{
			const FVector TargetDirection = PlayerTankLocation - ActorLocation;
			const FRotator LookAt = TargetDirection.Rotation();
			TurretMesh->SetWorldRotation(LookAt,
			                             false);
		}
	}
}

// Called to bind functionality to input
void ATower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
