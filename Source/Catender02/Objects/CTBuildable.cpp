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

void ACTBuildable::BeginPlay()
{
	Super::BeginPlay();

	GetBuildingComponent()->OnBuildingStateChanged.AddDynamic(this, &ACTBuildable::BuildingStateChanged);
}

/**
 * Overrides the Interact method to handle interaction with another sortable object.
 *
 * This function first calls the parent class's Interact method. If the building upgrade is successful,
 * it then plays an interaction sound on the player character.
 *
 * @param OtherSortable A pointer to the other sortable object that is interacting with this buildable.
 */
void ACTBuildable::Interact(ACTSortable* OtherSortable)
{
	Super::Interact(OtherSortable);

	if(!BuildingComponent->UpgradeBuilding()) return;

	const ACTPlayerCharacter* Player = Cast<ACTPlayerCharacter>(OtherSortable);
	Player->PlayInteractSound();

	Highlight(false);
}

void ACTBuildable::Destroyed()
{		
	Super::Destroyed();			
}

void ACTBuildable::UpdateConstructionCollision(const bool IsActive)
{
	GetConstructionBoxComponent()->SetCollisionEnabled(IsActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

UCTBuildingComponent* ACTBuildable::GetBuildingComponent() const
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

bool ACTBuildable::CanInteract() const
{	
	return BuildingComponent->CanBeBuild();
}

void ACTBuildable::BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldState, EBuildingState NewState)
{
	if(NewState == EBuildingState::Construction)
	{
		UpdateInteractionCollision(false);
		UpdateConstructionCollision(true);
		return;
	}
	if(OldState == EBuildingState::Construction)
	{
		UpdateInteractionCollision(true);
		UpdateConstructionCollision(false);
	}
}
