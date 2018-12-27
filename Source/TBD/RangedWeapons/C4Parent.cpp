// Fill out your copyright notice in the Description page of Project Settings.

#include "C4Parent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpecialActors/ShiledParent.h"
#include "Parents/DamageTypeParent.h"
// Sets default values
AC4Parent::AC4Parent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ParticleSystemComponent = CreateDefaultSubobject< UParticleSystemComponent>(FName("ParticleSystemComponent"));
	ParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleSystemComponent->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AC4Parent::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AC4Parent::Exploded, TimeEntilExplosion);

}

void AC4Parent::OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{/*
	AShiledParent * Shiled = Cast<AShiledParent>(OtherActor);

	if (Shiled != nullptr)
	{
		FDamageEvent DamageEvent;
		Shiled->TakeDamage((ExplosionDamage * MaxDamagep), DamageEvent, GetInstigatorController(), this);
		bHitShiled = true;
		Exploded();
		return;
	}
	*/
	if (bCanAttach) {
		bCanAttach = false;
		UE_LOG(LogTemp, Warning, TEXT(" ImpactNormal %s "), *Hit.ImpactNormal.ToString());
		UE_LOG(LogTemp, Warning, TEXT(" GetActorRightVector %s "), *GetActorRightVector().ToString());
		SetActorRotation((FVector::CrossProduct(FVector(0,-1, 0), GetActorRightVector()).Rotation()));
		AttachToActor(OtherActor, FAttachmentTransformRules::KeepWorldTransform);
	}
}
// Called every frame
void AC4Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC4Parent::Exploded()
{
	TArray<AActor*> Actors;
	if (!bHitShiled)
	{
		UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), ExplosionDamage, BaseDamage, GetActorLocation(), ExplosionRadius, ExplosionRadius * 1.5, MaxDamagep, C4DamageTyep, Actors, this, GetInstigatorController());
	}
	bHitShiled = false;
	ParticleSystemComponent->SetWorldLocation(ProjectileMeshComponent->GetComponentLocation());
	SetRootComponent(ParticleSystemComponent);
	ParticleSystemComponent->Activate();
	ProjectileMeshComponent->DestroyComponent();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AC4Parent::TimerEndDestroy, 1);
}

void AC4Parent::TimerEndDestroy()
{
	Destroy();
}





