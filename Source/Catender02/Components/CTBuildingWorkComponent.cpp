

#include "CTBuildingWorkComponent.h"

#include "Catender02/Objects/CTBuildable.h"


UCTBuildingWorkComponent::UCTBuildingWorkComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTBuildingWorkComponent::AddFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character)
{
	if (!Character)
	{
		return;
	}

	WorkingFriendlyNPCCharacters.Add(Character);
}

void UCTBuildingWorkComponent::RemoveFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character)
{
	if (!Character)
	{
		return;
	}

	WorkingFriendlyNPCCharacters.Remove(Character);
}

bool UCTBuildingWorkComponent::HasFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character)
{
	if (!Character)
	{
		return false;
	}

	return WorkingFriendlyNPCCharacters.Contains(Character);
}

int UCTBuildingWorkComponent::CountFriendlyNPCCharacters()
{
	return WorkingFriendlyNPCCharacters.Num();
}

bool UCTBuildingWorkComponent::HasOpenWorkPlace()
{
	return WorkingFriendlyNPCCharacters.Num() < AmountWorkPlaces;
}


void UCTBuildingWorkComponent::GetBuildingComponentFromOwner()
{
	if (!OwningBuildable)
	{
		return;
	}
	
	BuildingComponent = OwningBuildable->GetBuildingComponent();
	BuildingComponent->OnBuildingStateChanged.AddDynamic(
		this,
		&UCTBuildingWorkComponent::BuildingStateChanged
	);
}

void UCTBuildingWorkComponent::GetOwningBuildableFromOwner()
{
	OwningBuildable = Cast<ACTBuildable>(GetOwner());
}

void UCTBuildingWorkComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwningBuildableFromOwner();
	GetBuildingComponentFromOwner();
}

void UCTBuildingWorkComponent::BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldState,
	EBuildingState NewState)
{
	// Clear NPC Array
}

void UCTBuildingWorkComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UBoxComponent* UCTBuildingWorkComponent::GetActiveWorkSite() const
{	
	return nullptr;
}