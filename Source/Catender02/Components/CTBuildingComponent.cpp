
#include "CTBuildingComponent.h"

#include "Catender02/Objects/CTBuildable.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

/**
 * @brief Resets the current progress of the building.
 *
 * This method sets the building's current progress to zero, effectively resetting any progress made
 * towards the current construction or upgrade.
 */
void UCTBuildingComponent::ResetCurrentProgress()
{
	CurrentProgress = 0;
}

UCTBuildingComponent::UCTBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

/**
 * @brief Retrieves the maximum building level.
 *
 * This method returns the maximum level the building can have, calculated based on the number
 * of levels defined in the building's level information array.
 *
 * @return The maximum level of the building, or 0 if the building has no levels.
 */
int UCTBuildingComponent::GetMaxBuildingLevel()
{
	if(!HasLevel()) return 0;
	return BuildingLevelInformation.Num() -1;
}

/**
 * @brief Retrieves the current level of the building.
 *
 * This method returns the current level of the building, which is an integer
 * representing the building's progression status.
 *
 * @return The current level of the building.
 */
int UCTBuildingComponent::GetCurrentBuildingLevel()
{
	return CurrentLevel;
}

/**
 * @brief Returns the current state of the building.
 *
 * This method retrieves the current state of the building, which is represented by the
 * EBuildingState enumeration. The state can be one of the following: Invisible, Inactive,
 * Active, Construction, or Destroyed.
 *
 * @return The current building state.
 */
EBuildingState UCTBuildingComponent::GetBuildingState()
{
	return BuildingState;
}

/**
 * @brief Sets the current building level, clamping it within valid bounds.
 *
 * This method updates the building level based on provided information:
 * - If no level information is available, it sets the current level to 0 and exits.
 * - Otherwise, it clamps the new level within the valid range (0 to number of levels - 1).
 *
 * After setting the new level, the method broadcasts the change using the `OnCurrentLevelChanged` delegate.
 *
 * @param NewLevel The desired new level to set the building to.
 */
void UCTBuildingComponent::SetCurrentBuildingLevel(const int NewLevel)
{
	const int OldLevel = CurrentLevel;
	
	if (BuildingLevelInformation.Num() == 0)
	{
		CurrentLevel = 0;
		return;
	}
		
	CurrentLevel = FMath::Clamp(NewLevel, 0, BuildingLevelInformation.Num() - 1);

	OnCurrentLevelChanged.Broadcast(OwningBuildable, OldLevel, NewLevel);
}

/**
 * @brief Updates the sprite (Flipbook) of the building based on its current state and level.
 *
 * This method first retrieves the sprite component and sets its visibility to true.
 * If the building doesn't have a level, it will set the flipbook to the default flipbook and return.
 * It then retrieves the level information and updates the sprite's flipbook based on the building's state.
 *
 * - Invisible: Sets the sprite's visibility to false.
 * - Inactive: Sets the sprite to the default flipbook.
 * - Active: Sets the sprite to the completed state's flipbook.
 * - Construction: Sets the sprite to the construction state's flipbook.
 * - Destroyed: Sets the sprite to the destroyed state's flipbook.
 * - Default: Sets the sprite to the default flipbook.
 */
void UCTBuildingComponent::UpdateSprite()
{
	UPaperFlipbookComponent* FlipbookComponent = OwningBuildable->GetSprite();
	
	if(!FlipbookComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("FlipbookComponent ist null!"));
		return;		
	}
	
	FlipbookComponent->SetVisibility(true);
	
	if(!HasLevel())
	{
		FlipbookComponent->SetFlipbook(DefaultFlipbook);
		return;
	}

	FBuildingLevelInformation LevelInformation = GetBuildingLevelInformation(CurrentLevel);

	switch (GetBuildingState())
	{
		case EBuildingState::Invisible:
			{
				FlipbookComponent->SetVisibility(false);
				break;
			}
		case EBuildingState::Inactive:
			{
				FlipbookComponent->SetFlipbook(DefaultFlipbook);
				break;
			}
		case EBuildingState::Active:
			{
				FlipbookComponent->SetFlipbook(LevelInformation.FinishFlipbook);
				break;
			}
		case EBuildingState::Construction:
			{
				FlipbookComponent->SetFlipbook(LevelInformation.ConstructionFlipbook);
				break;
			}
		case EBuildingState::Destroyed:
			{
				FlipbookComponent->SetFlipbook(LevelInformation.DestroyedFlipbook);
				break;
			}
		default:
			{
				FlipbookComponent->SetFlipbook(DefaultFlipbook);
			}
	}

	OwningBuildable->CreateDynamicMaterialForSprite();
}

/**
 * @brief Checks if the building has any levels defined.
 *
 * This method returns true if there is at least one level defined in the BuildingLevelInformation array.
 *
 * @return bool True if the building has levels, false otherwise.
 */
bool UCTBuildingComponent::HasLevel()
{
	return BuildingLevelInformation.Num() > 0;
}

/**
 * @brief Adds progress to the building's construction.
 *
 * This method adds a specified amount of progress to the building's current construction progress.
 * It first checks if the owning buildable object is set; if not, it logs a warning and exits.
 * Next, it ensures that the building has level information and currently is in the Construction state.
 * The method then retrieves the progress needed for the current building level and ensures it is greater than zero.
 * It updates the current progress by adding the specified amount and broadcasts the progress change event.
 * If the progress reaches or exceeds the required amount, it broadcasts the construction finished event.
 *
 * @param Amount The amount of progress to add to the building's construction.
 */
void UCTBuildingComponent::AddProgressToBuilding(const float Amount)
{
	if (!OwningBuildable)
    {
        UE_LOG(LogTemp, Warning, TEXT("OwningBuildable ist null!"));
        return;
    }
 
    if (!HasLevel()) return;
    if (BuildingState != EBuildingState::Construction) return;
 
    const float ProgressNeeded = GetProgressNeededForCurrentBuildingLevel();
    if (ProgressNeeded <= 0) return;
 
    const float OldProgress = CurrentProgress;
    
    CurrentProgress += Amount;
	float NewProgress = CurrentProgress;
    OnConstructionProgressChanged.Broadcast(OwningBuildable, OldProgress, NewProgress);
 
    if (CurrentProgress >= ProgressNeeded)
    {
        OnConstructionFinished.Broadcast(OwningBuildable);
    }
}

/**
 * @brief Retrieves the progress required to complete the current building level.
 *
 * This method checks if the building has a valid level. If no level is set, it returns 0.
 * Otherwise, it fetches the progress needed for the current building level from the level information.
 *
 * @return The amount of progress required for the current building level, or 0 if no valid level is set.
 */
float UCTBuildingComponent::GetProgressNeededForCurrentBuildingLevel()
{
	if(!HasLevel()) return 0;
	return GetBuildingLevelInformation(CurrentLevel).ProgressNeeded;
}

/**
 * @brief Updates the collision settings of the construction box component based on the building's state.
 *
 * This method enables or disables collision for the construction box component
 * depending on whether the building is in the construction state.
 *
 * @param NewBuildingState The new state of the building, used to determine the collision settings.
 */
void UCTBuildingComponent::UpdateCollision(EBuildingState NewBuildingState)
{
	if(!OwningBuildable) return;

	UBoxComponent* ConstructionBox = OwningBuildable->GetConstructionSiteBoxComponent();
	if(!ConstructionBox) return;
	
	if(NewBuildingState == EBuildingState::Construction)
	{
		ConstructionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		ConstructionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

/**
 * @brief Handles the payment of resources required for a building upgrade or construction.
 *
 * This function checks if the owning buildable object exists and then retrieves the `UCTWorldResourceComponent`
 * instance from the game mode. It fetches the resource requirements for the building's current level and attempts
 * to subtract the necessary amounts from the world resource component.
 *
 * - If `OwningBuildable` is null, the function returns immediately.
 * - Retrieves resource component via the game mode's `WorldResourceComponent`.
 * - Gets the resource requirements for the current building level.
 * - Iterates over each required resource and checks if it is unlocked. If not, attempts to subtract the needed amount.
 */
void UCTBuildingComponent::PayResources()
{
	if(!OwningBuildable) return;

	UCTWorldResourceComponent* ResourceComponent = OwningBuildable->GetGameMode()->WorldResourceComponent;
	
	FBuildingLevelInformation LevelInformation = GetBuildingLevelInformation(CurrentLevel);

	for (FResource NeededResource : LevelInformation.Resources)
	{
		if(ResourceComponent->IsUnlockResource(NeededResource.ResourceType)) continue;

		ResourceComponent->TrySubtractResourceAmount(NeededResource.ResourceType, NeededResource.Amount);
	}
}

/**
 * @brief Checks if the necessary resources are available for the building's current level.
 *
 * This method verifies whether the required resources are available for the building's current construction level
 * by comparing the resource requirements against the resource amounts in the world resource component.
 *
 * If the resources are insufficient, an OnConstructionFailed event is broadcasted with the building and the needed resources.
 *
 * @return true if all required resources are available, false otherwise.
 */
bool UCTBuildingComponent::CheckResourceRequirements()
{
	if(!OwningBuildable) return false;

	UCTWorldResourceComponent* ResourceComponent = OwningBuildable->GetGameMode()->WorldResourceComponent;
	
	bool Result = false;

	FBuildingLevelInformation LevelInformation = GetBuildingLevelInformation(CurrentLevel);

	for (FResource Resource : LevelInformation.Resources)
	{
		Result = ResourceComponent->CheckResource(Resource.ResourceType, Resource.Amount);
		if (!Result) break;
	}

	if (!Result)
	{
		OnConstructionFailed.Broadcast(OwningBuildable, LevelInformation.Resources);
	}
	
	return Result;
}

/**
 * @brief Attempts to upgrade the building to the next level.
 *
 * This method verifies if the owning buildable object is valid and checks
 * if the required resources are available. It then proceeds based on the current state
 * of the building:
 * - Invisible: Cannot upgrade, returns false.
 * - Inactive: Sets the building state to Construction, resets progress.
 * - Active: If the building is at the maximum level, returns false; otherwise,
 *           sets the building state to Construction, increments the building level, and resets progress.
 * - Destroyed: Sets the building state to Construction and resets progress.
 * - Construction: Already in progress, returns false.
 * - Default: Returns false.
 *
 * If the conditions for upgrading are met, resources are paid, the building is updated, and the method returns true.
 *
 * @return True if the building was successfully upgraded, false otherwise.
 */
 bool UCTBuildingComponent::UpgradeBuilding()
{
	if (!OwningBuildable)
		return false;
   
	if (!CheckResourceRequirements())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough Resources to Upgrade Buildable!"));
		return false;
	}
   
	switch (GetBuildingState())
	{
	case EBuildingState::Invisible:
	case EBuildingState::Construction:
		return false;
   
	case EBuildingState::Inactive:
		{
			SetBuildingState(EBuildingState::Construction);
			PayResources();
			UpdateBuilding();
			ResetCurrentProgress();
			OnConstructionStarted.Broadcast(OwningBuildable);
			return true;
		}
	case EBuildingState::Active:
		{
			if (GetMaxBuildingLevel() == GetCurrentBuildingLevel())
				return false;
   
			SetBuildingState(EBuildingState::Construction);
			SetCurrentBuildingLevel(GetCurrentBuildingLevel() + 1);
			PayResources();
			UpdateBuilding();
			ResetCurrentProgress();
			OnConstructionStarted.Broadcast(OwningBuildable);	
			return true;
		}
 
	case EBuildingState::Destroyed:
		{
			SetBuildingState(EBuildingState::Construction);
			UpdateBuilding();
			PayResources();
			ResetCurrentProgress();
			OnConstructionStarted.Broadcast(OwningBuildable);
			return true;
		}
   
	default:
		return false;
	}
}

/**
 * @brief Updates the building's visual appearance and collision settings.
 *
 * This method updates the building's sprite to reflect its current state
 * and level, and adjusts the collision settings accordingly.
 *
 * - Calls UpdateSprite() to update the building's sprite based on its state.
 * - Calls UpdateCollision(EBuildingState) to update the collision settings based on the current building state.
 */
void UCTBuildingComponent::UpdateBuilding()
{
	UpdateSprite();
	UpdateCollision(GetBuildingState());
}

bool UCTBuildingComponent::CanBeBuild()
{	
	if (GetBuildingState() == EBuildingState::Inactive)
	{
		UKismetSystemLibrary::PrintString(this, "CanBeBuild(): Inactive");
		return true;
	}

	if (GetBuildingState() == EBuildingState::Destroyed)
	{
		UKismetSystemLibrary::PrintString(this, "CanBeBuild(): Destroyed");
		return true;
	}
	
	if (GetMaxBuildingLevel() > GetCurrentBuildingLevel()
		&& GetBuildingState() == EBuildingState::Active)
	{		
		UKismetSystemLibrary::PrintString(this, "CanBeBuild(): Active and Max Level not Reached");
		return true;
	}

	
	return false;
}

TArray<FResource> UCTBuildingComponent::GetResourcesCostForCurrentLevel()
{
	FBuildingLevelInformation LevelInformation = GetBuildingLevelInformation(CurrentLevel);

	TArray<FResource> Resources;
	
	for (FResource Resource : LevelInformation.Resources)
	{
		Resources.Add(Resource);
	}

	return Resources;
}

/**
 * @brief Retrieves the building level information based on the provided level.
 *
 * This method accesses the BuildingLevelInformation array and returns the information
 * for the given building level. The level parameter should be a valid index within the array.
 *
 * @param Level The level of the building for which information is to be retrieved.
 * @return FBuildingLevelInformation The information associated with the specified building level.
 */
FBuildingLevelInformation UCTBuildingComponent::GetBuildingLevelInformation(int Level)
{
	return BuildingLevelInformation[Level];
}

/**
 * @brief Sets the building's state to a new state and broadcasts the state change.
 *
 * This method updates the building's state to the specified new state and triggers the
 * OnBuildingStateChanged event to notify any listeners of the state change.
 *
 * @param NewBuildingState The new state to set for the building.
 */
void UCTBuildingComponent::SetBuildingState(EBuildingState NewBuildingState)
{
	EBuildingState OldBuildingState = GetBuildingState();

	BuildingState = NewBuildingState;

	OnBuildingStateChanged.Broadcast(OwningBuildable, OldBuildingState, NewBuildingState);
}

/**
 * @brief Sets the state of the building to Active upon construction completion.
 *
 * This method is called when the construction of a buildable object has finished.
 * It updates the state of the building component to Active using the SetBuildingState method.
 *
 * @param Buildable Pointer to the buildable object whose construction has been completed.
 */
void UCTBuildingComponent::ConstructionFinished(ACTBuildable* Buildable)
{
	SetBuildingState(EBuildingState::Active);
	UpdateBuilding();
}

/**
 * @brief Handles the event when the construction progress of a buildable object changes.
 *
 * This method is invoked whenever there's a change in the construction progress
 * of a buildable object. It enables the component to react accordingly,
 * potentially updating the visual representation and/or triggering other
 * related logic based on the new progress value.
 *
 * @param Buildable The buildable object whose construction progress has changed.
 * @param OldProgress The previous construction progress value of the buildable object.
 * @param NewProgress The new construction progress value of the buildable object.
 */
void UCTBuildingComponent::ConstructionProgressChanged(ACTBuildable* Buildable, float OldProgress, float NewProgress)
{
}

/**
 * @brief Handles the event when a building's construction fails due to lack of resources.
 *
 * This method is called when the construction of a building cannot proceed because the
 * required resources are not available. It informs the appropriate system or user
 * about the failure and provides the list of needed resources.
 *
 * @param Buildable The building object whose construction has failed.
 * @param NeededResources The list of resources that are needed to proceed with the construction.
 */
void UCTBuildingComponent::ConstructionFailed(ACTBuildable* Buildable, TArray<FResource> NeededResources)
{
}

/**
 * @brief Handles changes in the building's state.
 *
 * This method is triggered when the building's state changes. It updates various
 * components or triggers events based on the transition from the old state to the new state.
 *
 * @param Buildable The buildable object whose state has changed.
 * @param OldBuildingState The previous state of the building.
 * @param NewBuildingState The new state of the building.
 */
void UCTBuildingComponent::BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldBuildingState,
                                                EBuildingState NewBuildingState)
{
}

/**
 * @brief Handles the event when the current level of a buildable object changes.
 *
 * This method is responsible for updating the component when the level of the associated buildable object changes.
 * It may involve updating visual elements, collision properties, and any other relevant attributes based on the new level.
 *
 * @param Buildable A pointer to the buildable object whose level has changed.
 * @param OldLevel The previous level of the buildable object.
 * @param NewLevel The new level of the buildable object.
 */
void UCTBuildingComponent::CurrentLevelChanged(ACTBuildable* Buildable, int OldLevel, int NewLevel)
{
}

/**
 * @brief Performs initialization when the game starts or when spawned.
 *
 * This method sets up the owning buildable object, updates the building state initially,
 * and binds dynamic delegates to various building-related events such as state changes,
 * level changes, construction progress, and completion or failure of construction.
 */
void UCTBuildingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningBuildable = Cast<ACTBuildable>(GetOwner());

	UpdateBuilding();
	
	OnBuildingStateChanged.AddDynamic
	(
		this,
		&UCTBuildingComponent::BuildingStateChanged
	);
	OnCurrentLevelChanged.AddDynamic
	(
		this,
		&UCTBuildingComponent::CurrentLevelChanged
	);
	OnConstructionProgressChanged.AddDynamic
	(
		this,
		&UCTBuildingComponent::ConstructionProgressChanged
	);
	OnConstructionFinished.AddDynamic
	(
		this,
		&UCTBuildingComponent::ConstructionFinished
	);
	OnConstructionFailed.AddDynamic
	(
		this,
		&UCTBuildingComponent::ConstructionFailed
	);
}

void UCTBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

