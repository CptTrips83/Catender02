// Fill out your copyright notice in the Description page of Project Settings.


#include "CTWidgetComponent.h"

#include "CTUserWidgetMain.h"
#include "Catender02/Objects/CTInteractable.h"


// Sets default values for this component's properties
UCTWidgetComponent::UCTWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCTWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
    UCTUserWidgetMain* MainWidget = Cast<UCTUserWidgetMain>(GetWidget());
	if (!MainWidget) return;
	ACTInteractable* Interactable = Cast<ACTInteractable>(GetOwner());
	if (!Interactable) return;	
	MainWidget->SetOwningInteractable(Interactable);
}


// Called every frame
void UCTWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

