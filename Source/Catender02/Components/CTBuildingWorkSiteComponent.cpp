

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

int UCTBuildingWorkSiteComponent::CountFriendlyNPCCharacters(ACTFriendlyNPCCharacter* Character) const
{
	int CountWorkplacesTaken = 0;

	if (WorkingFriendlyNPCCharacters.Num() > 0)
	{
		for(const ACTFriendlyNPCCharacter* AssignedCharacter : WorkingFriendlyNPCCharacters)
		{
			if(AssignedCharacter != Character)
			{
				CountWorkplacesTaken++;
			}
		}
	}

	return CountWorkplacesTaken;
}

bool UCTBuildingWorkSiteComponent::HasOpenWorkPlace(ACTFriendlyNPCCharacter* Character)
{
	return CountFriendlyNPCCharacters(Character) < AmountWorkPlaces;
}


void UCTBuildingWorkSiteComponent::AddBuildingStateChangedListener()
{
	BuildingComponent->OnBuildingStateChanged.AddDynamic(
		this,
		&UCTBuildingWorkSiteComponent::BuildingStateChanged
	);
}

void UCTBuildingWorkSiteComponent::GetBuildingComponentFromOwner()
{
	if (!OwningBuildable)
	{
		return;
	}
	
	BuildingComponent = OwningBuildable->GetBuildingComponent();
	AddBuildingStateChangedListener();
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
	for(int i = 0; i < WorkingFriendlyNPCCharacters.Num(); i++)
	{
		ACTFriendlyNPCCharacter* Character = WorkingFriendlyNPCCharacters[i];
		Character->WithdrawFromBuildingWorkSite(OwningBuildable);
	}
}

void UCTBuildingWorkSiteComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UCTBuildingWorkSiteComponent::HasActiveWorkSite(ACTFriendlyNPCCharacter* NPCCharacter) const
{
	if(!BuildingComponent) return false;
	if(!NPCCharacter) return false;
	
	const EBuildingState BuildingState = BuildingComponent->GetBuildingState();

	if (CountFriendlyNPCCharacters(NPCCharacter) >= AmountWorkPlaces)
	{
		return false;
	}

	if (!BuildingStatesWorker.Contains(BuildingState)) return false;
	
	const TSubclassOf<ACTFriendlyNPCCharacter> NeededNPCClass
				= BuildingStatesWorker.FindRef(BuildingState);
	
	if (NPCCharacter->IsA(NeededNPCClass))
	{		
		return true;
	}
	
	return false;
}