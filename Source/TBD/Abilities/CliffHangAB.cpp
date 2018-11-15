// Fill out your copyright notice in the Description page of Project Settings.

#include "CliffHangAB.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
// Sets default values for this component's properties
UCliffHangAB::UCliffHangAB()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCliffHangAB::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());
	Owner->GetCharacterMovement()->SetPlaneConstraintEnabled(true);
	Owner->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &UCliffHangAB::OnOverlapBegin);
	Owner->GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &UCliffHangAB::OnOverlapEnd);
	// ...
	
}


// Called every frame
void UCliffHangAB::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCliffHangAB::hang()
{
	if (bOnTheWall)
	{
		Owner->GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0, 0, 1));
		Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}
}

void UCliffHangAB::Release()
{
	Owner->GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0, 0, 0));
	Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	FHitResult Hit;
	Owner->Landed(Hit);
}

void UCliffHangAB::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Edge"))
	{
		bOnTheWall = true;
	}
}

void UCliffHangAB::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Edge"))
	{
     bOnTheWall = false;
	}
}

