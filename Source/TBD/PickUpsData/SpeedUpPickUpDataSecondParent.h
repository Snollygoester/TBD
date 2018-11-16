// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parents/PickUpDataParent.h"
#include "SpeedUpPickUpDataSecondParent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TBD_API USpeedUpPickUpDataSecondParent : public UPickUpDataParent
{
	GENERATED_BODY()
	
protected:
 void PickUpDoYourThing() override;
 // Called when the game starts
 virtual void BeginPlay() override;
 void DestroyComp();
 void UpdetaTimer();
private:
	class ACharacterParent * Owner;
	float StartSpeed = 0;
	bool bIwasCalled = false;
	class UCharacterMovementComponent * MovementComponent;
	UPROPERTY(EditAnywhere)
		float Speedboost = 1260; //cm per s
	UPROPERTY(EditAnywhere)
		float AbilityTime = 2;
	UPROPERTY(EditAnywhere)
		float UpdateTime = 0.1;
	class UPickUpItemWidget * PickUpItemWidget;
	UPROPERTY(EditAnywhere)
	FSlateBrush Image;
	float RTime = 0;

};
