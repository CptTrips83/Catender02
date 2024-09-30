// Fill out your copyright notice in the Description page of Project Settings.


#include "CTBuildable.h"

#include "Components/BoxComponent.h"

ACTBuildable::ACTBuildable()
{
	BuildingComponent = CreateDefaultSubobject<UCTBuildingComponent>(TEXT("Building Component"));
	AddOwnedComponent(BuildingComponent);

	ConstructionBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Construction Box"));
	ConstructionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructionBoxComponent->SetupAttachment(GetRootComponent());
	

	WaitingBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Waiting Box"));
	WaitingBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WaitingBoxComponent->SetupAttachment(GetRootComponent());
}

void ACTBuildable::Interact(ACTSortable* OtherSortable)
{
	Super::Interact(OtherSortable);

	if(!BuildingComponent->UpgradeBuilding()) return;

	const ACTPlayerCharacter* Player = Cast<ACTPlayerCharacter>(OtherSortable);
	Player->PlayInteractSound();
}

void ACTBuildable::Destroyed()
{		
	Super::Destroyed();			
}

UCTBuildingComponent* ACTBuildable::GetBuildingComponent()
{
	return BuildingComponent;
}

UBoxComponent* ACTBuildable::GetConstructionBoxComponent() const
{
	return ConstructionBoxComponent;
}

UBoxComponent* ACTBuildable::GetWaitingBoxComponent() const
{
	return WaitingBoxComponent;
}
