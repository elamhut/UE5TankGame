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
	void ActorDeath(AActor* DeadActor) const;

protected:
	virtual void BeginPlay() override;

private:
	ATank* Tank;
	ATankPlayerController* TankPlayerController;

	float StartDelay{4.f};

	void HandleGameStart();
};
