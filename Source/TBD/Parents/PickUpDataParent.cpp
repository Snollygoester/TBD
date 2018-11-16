// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpDataParent.h"


// Sets default values for this component's properties
UPickUpDataParent::UPickUpDataParent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	// ...
}


// Called when the game starts
void UPickUpDataParent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPickUpDataParent::PickUpDoYourThing()
{
}


// Called every frame
void UPickUpDataParent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

