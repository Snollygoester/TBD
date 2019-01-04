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
FTimerDelegate C4TimerDelegate;
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
}

void AC4Parent::OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	C4TimerDelegate.BindUFunction(this, FName("Exploded"), OtherActor);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, C4TimerDelegate, TimeEntilExplosion, false);
	if (ThisActorToIgnre == OtherActor || Cast<AC4Parent>(OtherActor))
	{
		return;
	}
	HitActor = OtherActor;
	AShiledParent * Shiled = Cast<AShiledParent>(OtherActor);

	if (Shiled != nullptr)
	{
		FDamageEvent DamageEvent;
		Shiled->TakeDamage((ExplosionDamage * MaxDamagep), DamageEvent, GetInstigatorController(), this);
		bHitShiled = true;
		Exploded(OtherActor);
		return;
	}

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


void AC4Parent::Exploded(AActor * Other)
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

void AC4Parent::ExplodedAndStun(AActor * Other)
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



