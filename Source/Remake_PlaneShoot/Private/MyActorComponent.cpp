// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//for (int32 i = 0; i < Propellers.Num(); ++i)
	//{
	//	Propellers[i]->AddLocalRotation(FRotator(
	//		0,
	//		0,
	//		3200.0 * DeltaTime
	//	));
	//}

	for (auto Propeller : Propellers)
	{
		Propeller->AddLocalRotation(FRotator(
			0,
			0,
			3200.0 * DeltaTime
		));
	}

}

void UMyActorComponent::AddPropeller(USceneComponent* NewPropeller)
{
	if (NewPropeller)
	{
		Propellers.Add(NewPropeller);
	}
}

