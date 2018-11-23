// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
void UHealthWidget::SetHealthBarColor(FLinearColor Color)
{
	HealthBar->SetFillColorAndOpacity(Color);
	
}

void UHealthWidget::SetHealthBarPercent(float Percent)
{
	HealthBar->SetPercent(Percent);
}

void UHealthWidget::SetFuelBarPercent(float Percent)
{
	FuelBar->SetPercent(Percent);
}

void UHealthWidget::SetXimage()
{
	switch (I)
	{
	case 0: {
		Ximage->SetVisibility(ESlateVisibility::Visible);
		I++;
		return;
	}

	case 1: {
		Ximage1->SetVisibility(ESlateVisibility::Visible);
		I++;
		return;
	}
	case 2: {
		Ximage2->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	}
	
}
