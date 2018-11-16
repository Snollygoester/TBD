// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpParent.generated.h"

UCLASS()
class TBD_API APickUpParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UPickUpDataParent> PickUpData;
private:
	UPROPERTY(EditAnywhere)
		float RPS = 0.5;
	float Trun = 0;

	
};
