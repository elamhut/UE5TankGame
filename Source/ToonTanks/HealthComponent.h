﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


class AToonTanksGameMode;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor,
	                 float Damage,
	                 const UDamageType* DamageType,
	                 AController* Instigator,
	                 AActor* DamageCauser);

	UPROPERTY(EditAnywhere)
	float MaxHealth{100.f};

	UPROPERTY(EditAnywhere)
	float CurrentHealth;

	AToonTanksGameMode* TanksGameMode;
};
