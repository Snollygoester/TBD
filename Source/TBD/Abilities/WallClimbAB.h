// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WallClimbAB.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TBD_API UWallClimbAB : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWallClimbAB();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float ClimbTime = 0;
	UPROPERTY(EditAnywhere)
	float TimeYouCanClimb = 1.4;
	UPROPERTY(EditAnywhere)
	class USceneComponent * SceneComponent;
	class ACharacter * Owner;
	class APlayerController * OwnerController;
};
