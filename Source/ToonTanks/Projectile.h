// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Projectile.generated.h"


class UProjectileMovementComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	AProjectile();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,
	           AActor* OtherActor,
	           UPrimitiveComponent* OtherComponent,
	           FVector NormalImpulse,
	           const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	float ProjectileInitialSpeed{20.f};

	UPROPERTY(EditAnywhere)
	float ProjectileMaxSpeed{100.f};

	UPROPERTY(EditAnywhere)
	float Damage{20.f};
};
