// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecialEggParent.h"
#include "Kismet/GameplayStatics.h"
//#include "GameFramework/DamageType.h"
// Sets default values
ASpecialEggParent::ASpecialEggParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpecialEggParent::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpecialEggParent::OnHitDoYourThing(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, HitDamage, GetInstigatorController(), this, UDamageType::StaticClass());
}

// Called every frame
void ASpecialEggParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

