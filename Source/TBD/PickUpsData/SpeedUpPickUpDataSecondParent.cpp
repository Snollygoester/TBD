// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedUpPickUpDataSecondParent.h"
#include "Parents/CharacterParent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Widgets/PickUpItemWidget.h"

void USpeedUpPickUpDataSecondParent::PickUpDoYourThing() {
		
	if (!bIwasCalled)
	{
		Owner->ChangeSpeed(SpeedboostP);
		bIwasCalled = true;
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
	PickUpItemWidget = Owner->PickUpWidget;
	PickUpItemWidget->SetProgressBarImage(Image);
	PickUpItemWidget->SetProgressBarPercent(1);
	
}

void USpeedUpPickUpDataSecondParent::DestroyComp()
{
	Owner->ChangeSpeed( 1 / SpeedboostP);
	PickUpItemWidget->SetProgressBarPercent(0);
	DestroyComponent();
}

void USpeedUpPickUpDataSecondParent::UpdetaTimer()
{
	RTime = RTime - UpdateTime;
	PickUpItemWidget->SetProgressBarPercent(RTime / AbilityTime);
}
