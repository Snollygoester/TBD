// Fill out your copyright notice in the Description page of Project Settings.

#include "C4Parent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
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
{

	if (ThisActorToIgnre == OtherActor || Cast<AC4Parent>(OtherActor))
	{
		return;
	}
	HitActor = OtherActor;

	if (bCanAttach) {
		bCanAttach = false;
		SetActorRotation(Hit.Normal.Rotation());
		UE_LOG(LogTemp, Warning, TEXT(" %s "), *OtherActor->GetName());
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
	Actors.Add(ThisActorToIgnre);
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



void AC4Parent::SetActorToIgnre(AActor * ToIgner)
{
	ThisActorToIgnre = ToIgner;
}

void AC4Parent::ExplodedAndStun()
{
	TArray<AActor*> Actors;
	Actors.Add(ThisActorToIgnre);
	if (!bHitShiled)
	{
		UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), ExplosionDamage / 2, BaseDamage / 2 , GetActorLocation(), ExplosionRadius, ExplosionRadius * 1.5, MaxDamagep, C4DamageTyep, Actors, this, GetInstigatorController());
	}
	bHitShiled = false;
	ParticleSystemComponent->SetWorldLocation(ProjectileMeshComponent->GetComponentLocation());
	SetRootComponent(ParticleSystemComponent);
	ParticleSystemComponent->Activate();
	ProjectileMeshComponent->DestroyComponent();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AC4Parent::TimerEndDestroy, 1);
}



