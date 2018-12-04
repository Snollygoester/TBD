// Fill out your copyright notice in the Description page of Project Settings.

#include "GrenadeParent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShiledParent.h"
// Sets default values
AGrenadeParent::AGrenadeParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ParticleSystemComponent = CreateDefaultSubobject< UParticleSystemComponent>(FName("ParticleSystemComponent"));
	ParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleSystemComponent->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void AGrenadeParent::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGrenadeParent::Exploded, TimeEntilExplosion);
	
}

void AGrenadeParent::OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	AShiledParent * Shiled = Cast<AShiledParent>(OtherActor);

	if (Shiled != nullptr)
	{
		FDamageEvent DamageEvent;
		Shiled->TakeDamage((HitDamage + MaxExplosionDamage), DamageEvent, GetInstigatorController(), this);
		bHitShiled = true;
		Exploded();
		return;
	}
	UGameplayStatics::ApplyDamage(OtherActor, HitDamage, GetInstigatorController(), this, UDamageType::StaticClass());
}
// Called every frame
void AGrenadeParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrenadeParent::Exploded()
{
	TArray<AActor*> Actors;
	if (!bHitShiled)
	{
		UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), MaxExplosionDamage, MinExplosionDamage, GetActorLocation(), ExplosionRadius, ExplosionRadius * 1.5, MinExplosionDamage * 0.5, UDamageType::StaticClass(), Actors, this, GetInstigatorController());
	}
	bHitShiled = false;
	ParticleSystemComponent->SetWorldLocation(ProjectileMeshComponent->GetComponentLocation());
	SetRootComponent(ParticleSystemComponent);
	ParticleSystemComponent->Activate();
	ProjectileMeshComponent->DestroyComponent();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGrenadeParent::TimerEndDestroy, 1);
}

void AGrenadeParent::TimerEndDestroy()
{
	Destroy();
}

