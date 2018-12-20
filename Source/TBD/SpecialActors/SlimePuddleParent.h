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
		UPROPERTY()
			TArray<class UStaticMeshComponent *> Slowers;
		UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * Slower;
		UPROPERTY(VisibleAnywhere)
			class UStaticMeshComponent * Slower1;
		UPROPERTY(VisibleAnywhere)
			class UStaticMeshComponent * Slower2;
		UPROPERTY(VisibleAnywhere)
			class UStaticMeshComponent * Slower3;
		UPROPERTY(VisibleAnywhere)
			class UStaticMeshComponent * Slower4;
		UPROPERTY(VisibleAnywhere)
			class UStaticMeshComponent * Slower5;
		UPROPERTY(VisibleAnywhere)
			class UStaticMeshComponent * Slower6;
		UPROPERTY(VisibleAnywhere)
			class UStaticMeshComponent * Slower7;
		UPROPERTY(VisibleAnywhere)
			class UStaticMeshComponent * Slower8;
		UPROPERTY(VisibleAnywhere)
			class UStaticMeshComponent * Slower9;
		UFUNCTION()
			void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		UFUNCTION()
			void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	};
