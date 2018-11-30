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
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>(FName("StaticMeshComponent"));
	ProjectileMovementComponent = CreateDefaultSubobject< UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ParticleSystemComponent = CreateDefaultSubobject< UParticleSystemComponent>(FName("ParticleSystemComponent"));
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->SetNotifyRigidBodyCollision(true);
	ParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleSystemComponent->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void AGrenadeParent::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGrenadeParent::Exploded, TimeEntilExplosion);
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AGrenadeParent::OnCompHit);
}

// Called every frame
void AGrenadeParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrenadeParent::Thorw(float Speed , FVector Direction)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(Direction * Speed);

}

void AGrenadeParent::Exploded()
{
	TArray<AActor*> Actors;
	if (!bHitShiled)
	{
		UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), MaxExplosionDamage, MinExplosionDamage, GetActorLocation(), ExplosionRadius, ExplosionRadius * 1.5, MinExplosionDamage * 0.5, UDamageType::StaticClass(), Actors, this, GetInstigatorController());
	}
	bHitShiled = false;
	ParticleSystemComponent->SetWorldLocation(StaticMeshComponent->GetComponentLocation());
	SetRootComponent(ParticleSystemComponent);
	ParticleSystemComponent->Activate();
	StaticMeshComponent->DestroyComponent();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGrenadeParent::TimerEndDestroy, 1);
}

void AGrenadeParent::TimerEndDestroy()
{
	Destroy();
}

void AGrenadeParent::OnCompHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{ 
	AShiledParent * Shiled = Cast<AShiledParent>(OtherActor);
	if (Shiled != nullptr)
	{
		Shiled->CurrentHealth = Shiled->CurrentHealth - (HitDamage + MaxExplosionDamage);
		bHitShiled = true;
		Exploded();
		return;
	}
	UGameplayStatics::ApplyDamage(OtherActor, HitDamage, GetInstigatorController(), this, UDamageType::StaticClass());
}


