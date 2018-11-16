// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpItemWidget.h"
#include "Components/ProgressBar.h"
void UPickUpItemWidget::SetProgressBarImage(FSlateBrush Image)
{
	FSlateBrush Null;
	PickUpProgressBar->WidgetStyle.FillImage = Image;
	PickUpProgressBar->WidgetStyle.BackgroundImage = Null;
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
}

void UPickUpItemWidget::SetProgressBarPercent(float Percent)
{
	PickUpProgressBar->SetPercent(Percent);
}
