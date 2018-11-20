// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JetPack_AB.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TBD_API UJetPack_AB : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJetPack_AB();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	float FlyingTime;
	UPROPERTY(EditAnywhere)
	float MaxFuel = 100;
	float Fuel;
	UPROPERTY(EditAnywhere)
		float HoverTime = 4;
	UPROPERTY(EditAnywhere)
		float FuelLostPerSec = 50;
	UPROPERTY(EditAnywhere)
		float FuelAddtPerSec = 10;
	class ACharacterParent * Owner;
	class APlayerController * OwnerController;
	class UCharacterMovementComponent * MovementComponent;
	void StartRechargeing();
	UPROPERTY(EditAnywhere)
		float ChargDelay = 1.5;
	float LoopTime = 0.1;
	bool bCanRecharg = false;
};
