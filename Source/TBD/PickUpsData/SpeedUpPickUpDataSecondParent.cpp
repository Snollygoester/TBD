// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedUpPickUpDataSecondParent.h"
#include "Parents/CharacterParent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Widgets/PickUpItemWidget.h"
#include "UObject/ConstructorHelpers.h"

void USpeedUpPickUpDataSecondParent::PickUpDoYourThing() {
		
	if (!bIwasCalled)
	{
		bIwasCalled = true;
		MovementComponent->MaxWalkSpeed = (StartSpeed + Speedboost);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USpeedUpPickUpDataSecondParent::DestroyComp, AbilityTime);
		FTimerHandle TimerHandle1;
		RTime = AbilityTime;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this, &USpeedUpPickUpDataSecondParent::UpdetaTimer, UpdateTime, true);
	}
}

void USpeedUpPickUpDataSecondParent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacterParent>(GetOwner());
	MovementComponent = Cast< UCharacterMovementComponent>(Owner->GetMovementComponent());
	PickUpItemWidget = Owner->PickUpWidget;
	PickUpItemWidget->SetProgressBarImage(Image);
	StartSpeed = MovementComponent->MaxWalkSpeed;
	PickUpItemWidget->SetProgressBarPercent(1);
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
}

void USpeedUpPickUpDataSecondParent::DestroyComp()
{
	MovementComponent->MaxWalkSpeed = StartSpeed;
	DestroyComponent();
}

void USpeedUpPickUpDataSecondParent::UpdetaTimer()
{
	RTime = RTime - UpdateTime;
	PickUpItemWidget->SetProgressBarPercent(RTime / AbilityTime);
}
