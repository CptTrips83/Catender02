

#include "CTBuildingWorkSiteComponent.h"

#include "Catender02/Objects/CTBuildable.h"


UCTBuildingWorkSiteComponent::UCTBuildingWorkSiteComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTBuildingWorkSiteComponent::AddFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character)
{
	if (!Character)
	{
		return;
	}

	WorkingFriendlyNPCCharacters.Add(Character);
}

void UCTBuildingWorkSiteComponent::RemoveFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character)
{
	if (!Character)
	{
		return;
	}

	WorkingFriendlyNPCCharacters.Remove(Character);
}

bool UCTBuildingWorkSiteComponent::HasFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character)
{
	if (!Character)
	{
		return false;
	}

	return WorkingFriendlyNPCCharacters.Contains(Character);
}

int UCTBuildingWorkSiteComponent::CountFriendlyNPCCharacters()
{
	return WorkingFriendlyNPCCharacters.Num();
}

bool UCTBuildingWorkSiteComponent::HasOpenWorkPlace()
{
	return WorkingFriendlyNPCCharacters.Num() < AmountWorkPlaces;
}


void UCTBuildingWorkSiteComponent::GetBuildingComponentFromOwner()
{
	if (!OwningBuildable)
	{
		return;
	}
	
	BuildingComponent = OwningBuildable->GetBuildingComponent();
	BuildingComponent->OnBuildingStateChanged.AddDynamic(
		this,
		&UCTBuildingWorkSiteComponent::BuildingStateChanged
	);
}

void UCTBuildingWorkSiteComponent::GetOwningBuildableFromOwner()
{
	OwningBuildable = Cast<ACTBuildable>(GetOwner());
}

void UCTBuildingWorkSiteComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwningBuildableFromOwner();
	GetBuildingComponentFromOwner();
}

void UCTBuildingWorkSiteComponent::BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldState,
	EBuildingState NewState)
{
	// Clear NPC Array
}

void UCTBuildingWorkSiteComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UBoxComponent* UCTBuildingWorkSiteComponent::GetActiveWorkSite() const
{	
	return nullptr;
}