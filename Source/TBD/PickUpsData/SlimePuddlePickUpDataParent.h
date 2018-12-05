// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parents/PickUpDataParent.h"
#include "SlimePuddlePickUpDataParent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TBD_API USlimePuddlePickUpDataParent : public UPickUpDataParent
{
	GENERATED_BODY()
	void PickUpDoYourThing() override;
	// Called when the game starts
	virtual void BeginPlay() override;
	void DestroyComp();
	void UpdetaTimer();
private:
	class ACharacterParent * Owner;
	class UPickUpItemWidget * PickUpItemWidget;
	UPROPERTY(EditAnywhere)
	FSlateBrush Image;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASlimePuddleParent> SlimePuddleParentSubClass;
	UPROPERTY(EditAnywhere)
		ASlimePuddleParent * SlimePuddle;
	bool bIwasCalled = false;
	UPROPERTY(EditAnywhere)
		float AbilityTime = 10;
	UPROPERTY(EditAnywhere)
		float UpdateTime = 0.1;
	float RTime;
};
