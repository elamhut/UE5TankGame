// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

class ATankPlayerController;
class ATank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDeath(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

protected:
	virtual void BeginPlay() override;

private:
	ATank* Tank;
	ATankPlayerController* TankPlayerController;

	float StartDelay{3.f};

	void HandleGameStart();

	int32 TargetTowers{0};
	int32 GetTargetTowerCount();
};
