// Fill out your copyright notice in the Description page of Project Settings.

#include "ShiledParent.h"
#include "Components/StaticMeshComponent.h"
#include "SpecialActors/SlimePuddleParent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Parents/CharacterParent.h"

// Sets default values
AShiledParent::AShiledParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShiledMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>(FName("ShiledMeshComponent"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("WidgetComponent"));
	WidgetComponent->AttachToComponent(ShiledMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void AShiledParent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = Health;
	ProgressBar = Cast<UProgressBar>( WidgetComponent->GetUserWidgetObject()->GetRootWidget());
}
float AShiledParent::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	  Owner->bIsBlocking = true;
		CurrentHealth = CurrentHealth - DamageAmount;
		bCanShiledRegn = false;
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AShiledParent::CanRgen, RgenDealy);
		if (CurrentHealth <= 0)
		{
			Dactive();
		}
		return DamageAmount;
}
void AShiledParent::CanRgen()
{
	bCanShiledRegn = true;
}
// Called every frame
void AShiledParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ProgressBar->SetPercent(CurrentHealth / Health);
	if (bCanShiledRegn)
	{
		if (CurrentHealth < Health)
		{
			CurrentHealth = (RegnAmount * DeltaTime) + CurrentHealth;
		}	
	}

}

void AShiledParent::Active()
{
	ShiledMeshComponent->ToggleVisibility();
	WidgetComponent->ToggleVisibility();
	ShiledMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	bIsShiledActive = true;
}

void AShiledParent::Dactive()
{
	ShiledMeshComponent->ToggleVisibility();
	WidgetComponent->ToggleVisibility();
	ShiledMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bIsShiledActive = false;
	Owner->bIsBlocking = false;
}

