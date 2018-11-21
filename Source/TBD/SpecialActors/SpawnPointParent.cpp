// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPointParent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Parents/CharacterParent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
// Sets default values
ASpawnPointParent::ASpawnPointParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));

}

// Called when the game starts or when spawned
void ASpawnPointParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPointParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnPointParent::FindPointToSpawn()
{
	TArray<AActor *> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterParent::StaticClass(), Actors);
	BoxComponent->GetScaledBoxExtent();
	return FVector();
}

