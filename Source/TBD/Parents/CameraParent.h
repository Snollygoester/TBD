// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraParent.generated.h"

UCLASS()
class TBD_API ACameraParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
/** Follow camera */
UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
class UCameraComponent* Camera;
UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
class USpringArmComponent* SpringArm;
void SetUp();
UPROPERTY()
TArray<class APawn*> PlayersRef;
void UpdateCameraDist();

};
