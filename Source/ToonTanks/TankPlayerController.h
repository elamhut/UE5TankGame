// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"

#include "TankPlayerController.generated.h"

class ATank;
class UInputMappingContext;

UCLASS()
class TOONTANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	void HandleMove(const FInputActionValue& Value);
	void HandleTurn(const FInputActionValue& Value);

private:
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> TurnAction;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> RotateAction;

	UPROPERTY()
	TObjectPtr<ATank> TankPlayer;

	
};
