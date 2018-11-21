// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPointParent.generated.h"

UCLASS()
class TBD_API ASpawnPointParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPointParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector FindPointToSpawn();
private:
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	TArray<	FVector> SpawnPoints;
	UPROPERTY()
	TArray< class ACharacterParent *> CharactersParents;
	float Dist = 0;
	FVector FinalSpawnPoint;
};
