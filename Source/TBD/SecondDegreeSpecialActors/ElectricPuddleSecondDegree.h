// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpecialActors/PuddleParent.h"
#include "ElectricPuddleSecondDegree.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API AElectricPuddleSecondDegree : public APuddleParent
{
	GENERATED_BODY()
private:
	void OverlapDoYourThing(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UPROPERTY()
		class ACharacter * chart;
	UPROPERTY()
	class UCharacterMovementComponent * chartM;
	void UpdateElectric();
	UPROPERTY(EditAnywhere)
	float StunTime = 2;

	
	
	
};
