// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuddleParent.h"
#include "SlimePuddleParent.generated.h"

UCLASS()
class TBD_API ASlimePuddleParent : public APuddleParent
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
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	private:

		float MaxDist = 200;
		UPROPERTY()
		TArray<class  ACharacterParent *> Characters;
		UPROPERTY()
			TArray<class  UCharacterMovementComponent *> CharactersMovement;
		UPROPERTY(EditAnywhere)
			float Min = 40;
		UPROPERTY(EditAnywhere)
			float Max = 120;
	};
