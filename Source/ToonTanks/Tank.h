// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual void BeginPlay() override;
	void DoMove(const FVector2D* Value);
	void DoTurn(const FVector2D* Value);
	virtual void HandleDestruction() override;
	//Functions
protected:
	// Variables
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Tank Settings", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Tank Settings", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere)
	float MoveSpeed{100};

	UPROPERTY(EditAnywhere)
	float TurnSpeed{100};
};
