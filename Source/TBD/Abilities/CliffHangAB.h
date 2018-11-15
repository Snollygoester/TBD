// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CliffHangAB.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TBD_API UCliffHangAB : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCliffHangAB();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void hang();
	void Release();
private:
	UPROPERTY()
 class ACharacter * Owner;
	bool bOnTheWall = false; //It's your bool bOnTheWall
	
};
