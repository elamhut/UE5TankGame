// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "HealthComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = ProjectileInitialSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjectileMaxSpeed;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particles"));
	TrailParticles->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	const auto MyOwner = GetOwner();
	if (!MyOwner)
	{
		this->Destroy();
		return;
	}

	if (OtherActor && OtherActor->GetComponentByClass<UHealthComponent>() && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor,
		                              Damage,
		                              MyOwner->GetInstigatorController(),
		                              this,
		                              UDamageType::StaticClass());

	}
	
	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,
		                                         HitParticles,
		                                         GetActorLocation(),
		                                         GetActorRotation());
	}
	
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,
		                                      HitSound,
		                                      GetActorLocation());
	}
	
	if (HitCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}
	this->Destroy();
}
