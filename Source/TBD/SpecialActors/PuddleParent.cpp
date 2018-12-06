// Fill out your copyright notice in the Description page of Project Settings.

#include "PuddleParent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
APuddleParent::APuddleParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Puddle = CreateDefaultSubobject< UStaticMeshComponent>(FName("Puddle"));
}

// Called when the game starts or when spawned
void APuddleParent::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APuddleParent::DestroyComp, LifeTime);
	FTimerHandle TimerHandle1;
	RTime = LifeTime;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this, &APuddleParent::UpdetaTimer, UpdateTime, true);
	RScale = GetActorScale3D();
	StartScale = GetActorScale3D();
	Puddle->OnComponentBeginOverlap.AddDynamic(this, &APuddleParent::OnOverlapBegin);
}

void APuddleParent::OverlapDoYourThing(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

// Called every frame
void APuddleParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APuddleParent::UpdetaTimer()
{
	RScale = RScale - StartScale / LifeTime * UpdateTime;
	SetActorScale3D(RScale);
	RTime = RTime - UpdateTime;
}

void APuddleParent::DestroyComp()
{
	Destroy();
}

void APuddleParent::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OverlapDoYourThing(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
