// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlimePuddleParent.generated.h"

UCLASS()
class TBD_API ASlimePuddleParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlimePuddleParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * StaticMeshComponent;
	float MaxDist = 200;
	UPROPERTY()
	TArray<class  ACharacterParent *> Characters;
	UPROPERTY()
		TArray<class  UCharacterMovementComponent *> CharactersMovement;
};
