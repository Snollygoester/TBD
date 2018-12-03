// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShiledParent.generated.h"

UCLASS()
class TBD_API AShiledParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShiledParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Active();
	void Dactive();
	float CurrentHealth;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	bool bIsShiledActive = false;
private:
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * StaticMeshComponent;
	UPROPERTY(EditAnywhere)
		float Health = 100;
	UPROPERTY(EditAnywhere)
	float RgenDealy = 1;
	bool bCanShiledRegn = true;
	float RegnAmount = 10;
	void CanRgen();
	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent * WidgetComponent;
	class UProgressBar * ProgressBar;
};
