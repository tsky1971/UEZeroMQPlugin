// Fill out your copyright notice in the Description page of Project Settings.

#include "ZMQSubscriberComponent.h"


#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/EngineMessage.h"

// Sets default values for this component's properties
UZMQSubscriberComponent::UZMQSubscriberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UZMQSubscriberComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UZMQSubscriberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

