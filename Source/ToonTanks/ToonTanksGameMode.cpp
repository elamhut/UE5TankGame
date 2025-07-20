// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "TankPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDeath(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if (TankPlayerController)
		{
			TankPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (const auto DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		
		TargetTowers--;
		UE_LOG(LogGameMode, Warning, TEXT("Total Tower RN: %i"), TargetTowers);
		if (TargetTowers == 0)
			GameOver(true);
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	UE_LOG(LogTemp, Warning, TEXT("NUMBER OF TOWERS: %i"), TargetTowers);
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	if (TankPlayerController)
	{
		TankPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(TankPlayerController,
		                                                             &ATankPlayerController::SetPlayerEnabledState,
		                                                             true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
		                                TimerDelegate,
		                                StartDelay,
		                                false);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> AllTowers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), AllTowers);

	return AllTowers.Num();
}
