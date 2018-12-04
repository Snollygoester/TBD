// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileParent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProjectileParent::AProjectileParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>(FName("ProjectileMeshComponent"));
	ProjectileMovementComponent = CreateDefaultSubobject< UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	SetRootComponent(ProjectileMeshComponent);
	ProjectileMeshComponent->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AProjectileParent::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMeshComponent->OnComponentHit.AddDynamic(this, &AProjectileParent::OnCompHit);
}

void AProjectileParent::OnCompHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	OnHitDoYourThing( HitComp,  OtherActor,  OtherComp,  NormalImpulse, Hit);
}

void AProjectileParent::Thorw(float Speed, FVector Direction)
{
		ProjectileMovementComponent->SetVelocityInLocalSpace(Direction * Speed);
}

void AProjectileParent::OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
}

// Called every frame
void AProjectileParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

