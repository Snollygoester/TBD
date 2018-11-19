// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrenadeParent.generated.h"

UCLASS()
class TBD_API AGrenadeParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenadeParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Thorw(float Speed, FVector Direction);
private:
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent * ProjectileMovementComponent;
	void Exploded();
	UPROPERTY(EditAnywhere)
	float TimeEntilExplosion = 3;
	UPROPERTY(EditAnywhere)
		float HitDamage = 3;
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent * ParticleSystemComponent;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent * StaticMeshComponent;
	void TimerEndDestroy();
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
