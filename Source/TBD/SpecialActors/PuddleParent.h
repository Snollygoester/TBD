// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuddleParent.generated.h"

UCLASS()
class TBD_API APuddleParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuddleParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OverlapDoYourThing(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdetaTimer();
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent * Puddle;
	UPROPERTY(EditAnywhere)
		float UpdateTime = 0.1;
	float RTime;
	FVector RScale;
	FVector StartScale;
	UPROPERTY(EditAnywhere)
		float LifeTime = 10;
	void DestroyComp();
	void  GetActorToIgnire(AActor * ActorToIgnire);
	UPROPERTY()
		AActor * ThisActorToIgnire;
	UPROPERTY(EditAnywhere)
		bool bIsIce = false;
	
private:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
