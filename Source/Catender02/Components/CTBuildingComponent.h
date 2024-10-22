
#pragma once

#include "CoreMinimal.h"
#include "Catender02/Character/CTPlayerCharacter.h"
#include "Catender02/Components/CTWorldResourceComponent.h"
#include "Components/ActorComponent.h"
#include "CTBuildingComponent.generated.h"

class ACTBuildable;

/**
 * @brief Enumeration representing the different states of a building.
 *
 * This enum defines various possible states that a building can be in during its lifecycle, such as being invisible, inactive, active, under construction, or destroyed.
 */
UENUM(BlueprintType)
enum EBuildingState
{
	Invisible = 0,
	Inactive = 1,
	Active = 2,
	Construction = 3,
	Destroyed = 4,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FBuildingStateChanged,
	ACTBuildable*, Buildable,
	EBuildingState, OldState,
	EBuildingState, NewState
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FCurrentLevelChange,
	ACTBuildable*, Buildable,
	int, OldLevel,
	int, NewLevel
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam
(
	FConstructionFinished,
	ACTBuildable*, Building
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam
(
	FConstructionStarted,
	ACTBuildable*, Building
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FConstructionProgressChanged,
	ACTBuildable*, Building,
	float, OldProgress,
	float, NewProgress
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams
(
	FConstructionFailed,
	ACTBuildable*, Building,
	TArray<FResource>, NeededResources
);

/**
 * @brief Structure containing information about a building level.
 *
 * This structure holds various details required for different states of a building across levels.
 * It contains information about the progress needed for completion, different visual states of the building, and the resources required at this level.
 */
USTRUCT(BlueprintType)
struct FBuildingLevelInformation
{
	GENERATED_BODY()

	/**
	 * @brief Indicates the amount of progress required for the next building level.
	 *
	 * This variable specifies the amount of progress needed to upgrade the building to its next level.
	 * It is used to track the progress of construction or upgrades in the building component.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ProgressNeeded = 0.0f;
	/**
	 * @brief Represents the animation sequence for a building under construction.
	 *
	 * This variable holds a reference to the flipbook animation used to display the construction progress of a building.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperFlipbook* ConstructionFlipbook = nullptr;
	/**
	 * @brief Represents the finished animation sequence for a building.
	 *
	 * This variable holds a reference to the flipbook animation that is displayed when the construction of a building is completed.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperFlipbook* FinishFlipbook = nullptr;
	/**
	 * @brief Represents the animation sequence for a building in a destroyed state.
	 *
	 * This variable holds a reference to the flipbook animation that is displayed when the building is in a destroyed state.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPaperFlipbook* DestroyedFlipbook = nullptr;
	/**
	 * @brief Array of resources required for a specific action or level.
	 *
	 * This variable holds a collection of FResource structs, each representing a type of resource and its corresponding amount.
	 * It is utilized in various functions to manage resources needed for building construction or upgrades.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FResource> Resources;
};

/**
 * @brief A component that manages the building state and progression in the game.
 *
 * This class provides functionalities to handle different aspects of a building component, including level management,
 * state transitions, resource requirements, and progression tracking. It supports integration with the Blueprint system
 * for easy use within Unreal Engine.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

	/**
	 * @brief Pointer to the default flipbook animation for the building.
	 *
	 * This variable holds a reference to a UPaperFlipbook which represents
	 * the default animation state for the building. It is set to nullptr by default.
	 * The default flipbook is used in various states of the building, especially
	 * when specific animations for different states or levels are not provided.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	UPaperFlipbook* DefaultFlipbook = nullptr;
	/**
	 * @brief Integer representing the current level of the building.
	 *
	 * This variable keeps track of what level the building is currently in.
	 * It starts at level 0 by default and is updated as the building is upgraded.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int CurrentLevel = 0;
	/**
	 * @brief Variable representing the current state of the building.
	 *
	 * This variable holds the current state of the building using the EBuildingState enumeration, which can be Invisible, Inactive, Active, under Construction, or Destroyed.
	 * It is set to Invisible by default.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TEnumAsByte<EBuildingState> BuildingState = EBuildingState::Invisible;
	/**
	 * @brief Array of structures containing information about each building level.
	 *
	 * This variable holds a collection of FBuildingLevelInformation structs, each of which provides
	 * detailed data about a specific level of the building. It includes information such as progress requirements,
	 * animation sequences for different states (construction, complete, destroyed), and resources required for each level.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<FBuildingLevelInformation> BuildingLevelInformation;
	/**
	 * @brief Represents the current progress of a building through its construction or upgrade phase.
	 *
	 * This variable keeps track of how much progress has been made towards completing the current construction or upgrade of the building.
	 * It ranges from 0, indicating no progress, to a positive float value that will be compared against the required progress needed to complete the current level.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float CurrentProgress = 0;

	/**
	 * @brief Resets the current construction or upgrade progress of the building to zero.
	 *
	 * This method sets the variable CurrentProgress to 0, effectively resetting the progress made towards completing the current construction or upgrade of the building.
	 * It is invoked during various building operations such as starting construction or initiating an upgrade.
	 */
	void ResetCurrentProgress();
	
public:	
	UCTBuildingComponent();

	/**
	 * @brief Retrieves the maximum achievable level for the building component.
	 *
	 * This method returns the highest level that this building component can reach based on its
	 * current data. If the building does not have any levels, it returns 0.
	 *
	 * @return int The maximum building level, or 0 if no levels are available.
	 */
	UFUNCTION(BlueprintPure)
	virtual int GetMaxBuildingLevel();
	/**
	 * @brief Retrieves the current level of the building.
	 *
	 * This method returns the current level that the building has reached.
	 * It is used to determine building's progress through its upgrade stages.
	 *
	 * @return int The current building level.
	 */
	UFUNCTION(BlueprintPure)
	virtual int GetCurrentBuildingLevel();
	/**
	 * @brief Retrieves the current state of the building.
	 *
	 * This method returns the current state of the building using the EBuildingState enumeration. The state can be Invisible, Inactive, Active, under Construction, or Destroyed.
	 *
	 * @return EBuildingState The current state of the building.
	 */
	UFUNCTION(BlueprintPure)
	virtual EBuildingState GetBuildingState();
	/**
	 * @brief Sets the state of the building to the new specified state.
	 *
	 * This method changes the current state of the building to the provided new state.
	 * It also broadcasts an event indicating that the building state has changed from the old state to the new state.
	 *
	 * @param NewBuildingState The new state to which the building will be set, specified by the EBuildingState enumeration.
	 */
	virtual void SetBuildingState(EBuildingState NewBuildingState);
	/**
	 * @brief Adds progress to the current building's construction.
	 *
	 * This method updates the construction progress of the building by adding the specified amount.
	 * If the building is in the construction state and other preconditions are met, the progress is updated
	 * accordingly and relevant events are triggered upon reaching required progress thresholds.
	 *
	 * @param Amount The amount of progress to be added to the building's construction.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AddProgressToBuilding(float Amount);
	/**
	 * @brief Retrieves the progress needed to complete the current building level.
	 *
	 * This method calculates and returns the amount of progress required to finish the current building level. If there is no current level, it returns 0.
	 *
	 * @return The progress needed to complete the current building level, or 0 if there is no current level.
	 */
	UFUNCTION(BlueprintPure)
	virtual float GetProgressNeededForCurrentBuildingLevel();
	/**
	 * @brief Checks if the necessary resources are available for the building operation.
	 *
	 * This method verifies whether the required resources are available to proceed with a building operation by
	 * querying the WorldResourceComponent. If any resource is lacking, it broadcasts an event indicating the
	 * construction failure.
	 *
	 * @return True if all required resources are available, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	virtual bool CheckResourceRequirements();
	/**
	 * @brief Upgrades the building to the next level or initiates construction if certain conditions are met.
	 *
	 * This method checks various conditions such as resource availability, current state of the building, and
	 * current building level to determine if the building can be upgraded. It manages transitions in building states,
	 * handles resource payments, updates construction progress, and broadcasts the construction start event.
	 *
	 * @return True if the building upgrade or construction is successfully initiated; false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool UpgradeBuilding();

	/**
	 * @brief Determines whether the building can be built based on its current state.
	 *
	 * This method checks the current state of the building and returns true if the building
	 * is in a state that allows construction. The conditions checked include whether the
	 * building state is inactive, destroyed, or active with the maximum building level not yet reached.
	 *
	 * @return True if the building can be built, false otherwise.
	 */
	UFUNCTION()
	virtual bool CanBeBuild();
	/**
	 * @brief Retrieves the resource cost for the building's current level.
	 *
	 * This function calculates and returns an array of resources required for the building at its current level.
	 *
	 * @return An array of FResource objects representing the resources needed for the building's current level.
	 */
	UFUNCTION(BlueprintPure)
	virtual TArray<FResource> GetResourcesCostForCurrentLevel();
	
protected:
	/**
	 * @brief Pointer to the owning buildable actor.
	 *
	 * This variable holds a reference to the buildable actor that owns this component. It is initialized to nullptr.
	 */

	ACTBuildable* OwningBuildable = nullptr;	
	virtual void BeginPlay() override;

	/**
 * @brief Updates the current state of the building component.
 *
 * This method refreshes the visual representation and collision state of the building based on its current state.
 */
	UFUNCTION(BlueprintCallable)
	virtual void UpdateBuilding();
	
	/**
	 * @brief Retrieves the information for a specific building level.
	 *
	 * This method returns an object containing details and attributes associated with the specified building level.
	 *
	 * @param Level The level of the building for which information is being requested.
	 * @return An FBuildingLevelInformation object containing details of the specified building level.
	 */
	virtual FBuildingLevelInformation GetBuildingLevelInformation(int Level);
	/**
	 * @brief Sets the current building level.
	 *
	 * This method updates the current level of the building to the specified new level.
	 * It clamps the new level within a valid range based on the building level information and
	 * broadcasts an event if the level changes.
	 *
	 * @param NewLevel The new level to set for the building.
	 */
	virtual void SetCurrentBuildingLevel(int NewLevel);
	/**
	 * @brief Updates the sprite for the building component based on its current state and level.
	 *
	 * This method determines the appropriate flipbook to use for the sprite component depending on the building's state
	 * (Invisible, Inactive, Active, Construction, Destroyed) and visibility. It ensures the sprite visibility and assigns
	 * the correct flipbook animation corresponding to the building's condition.
	 * Additionally, it invokes the creation of a dynamic material for the sprite.
	 */
	virtual void UpdateSprite();
	/**
	 * @brief Updates the collision state of the building based on its current state.
	 *
	 * This method adjusts the collision settings of the building's construction site box component
	 * depending on the provided new state of the building.
	 *
	 * @param NewBuildingState The new state of the building which determines the collision configuration.
	 */
	virtual void UpdateCollision(EBuildingState NewBuildingState);
	/**
	 * @brief Deducts the necessary resources for a building component.
	 *
	 * This method checks if the owning buildable component is valid and then retrieves
	 * the world resource component from the game mode. It fetches the required resources
	 * for the current building level and attempts to subtract the required amounts from
	 * the world resources.
	 */
	virtual void PayResources();
	/**
	 * @brief Checks whether the building component has any levels.
	 *
	 * This method determines if the building component currently has any defined levels by examining the internal level information.
	 *
	 * @return True if the building component has one or more levels, false otherwise.
	 */
	virtual bool HasLevel();

	/**
	 * @brief Handles the completion of a building's construction.
	 *
	 * This method is called when the construction of a building is finished.
	 * It updates the building's state to active and updates its status accordingly.
	 *
	 * @param Buildable A pointer to the buildable object that has finished construction.
	 */
	UFUNCTION()
	virtual void ConstructionFinished(ACTBuildable* Buildable);
	/**
	 * @brief Handles updates to the construction progress of a buildable entity.
	 *
	 * This method is called when the construction progress of a buildable entity changes. It manages
	 * transitions and necessary updates based on the old and new progress values.
	 *
	 * @param Buildable Pointer to the buildable entity whose construction progress has changed.
	 * @param OldProgress The previous progress value.
	 * @param NewProgress The new progress value.
	 */
	UFUNCTION()
	virtual void ConstructionProgressChanged(ACTBuildable* Buildable, float OldProgress, float NewProgress);
	/**
	 * @brief Handles the event when construction of a buildable item fails.
	 *
	 * This method takes a buildable item and a list of needed resources, and processes the failure of constructing the item.
	 *
	 * @param Buildable The buildable item that failed to construct.
	 * @param NeededResources The array of resources that were needed for the construction.
	 */
	UFUNCTION()
	virtual void ConstructionFailed(ACTBuildable* Buildable, TArray<FResource> NeededResources);
	/**
	 * @brief Handles changes in the building state of a buildable object.
	 *
	 * This method is called whenever the building state of a given buildable object changes.
	 *
	 * @param Buildable A pointer to the buildable object whose state has changed.
	 * @param OldBuildingState The previous state of the building.
	 * @param NewBuildingState The new state of the building.
	 */
	UFUNCTION()
	virtual void BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldBuildingState, EBuildingState NewBuildingState);
	/**
	 * @brief Handles the change in the current level of a buildable object.
	 *
	 * This method is called whenever the level of a buildable object changes. It provides the buildable object that has changed,
	 * the old level, and the new level.
	 *
	 * @param Buildable Pointer to the buildable object for which the level has changed.
	 * @param OldLevel The previous level of the buildable object.
	 * @param NewLevel The new level of the buildable object.
	 */
	UFUNCTION()
	virtual void CurrentLevelChanged(ACTBuildable* Buildable, int OldLevel, int NewLevel);
	
public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Delegate that is called when the state of a building changes.
	 *
	 * This delegate is triggered whenever the building transitions between different states, allowing other parts of the application to respond to these changes.
	 */
	UPROPERTY(BlueprintAssignable)
	FBuildingStateChanged OnBuildingStateChanged;
	/**
	 * @brief Delegate for handling changes in the current level.
	 *
	 * This delegate is triggered whenever there is a change in the current level. It can be assigned
	 * to custom event handlers to perform actions when the level changes.
	 */
	UPROPERTY(BlueprintAssignable)
	FCurrentLevelChange OnCurrentLevelChanged;
	/**
	 * @brief Delegate invoked when the construction progress of a building changes.
	 *
	 * This delegate is triggered to notify subscribers whenever there is a change in the construction progress of a building.
	 */
	UPROPERTY(BlueprintAssignable)
	FConstructionProgressChanged OnConstructionProgressChanged;
	/**
	 * @brief Delegate triggered when construction starts.
	 *
	 * This delegate is called when the construction of a building begins. It can be used to handle or respond to construction start events.
	 */
	UPROPERTY(BlueprintAssignable)
	FConstructionStarted OnConstructionStarted;
	/**
	 * @brief Delegate that triggers when the construction process is completed.
	 *
	 * This delegate is used to notify subscribers that the construction of a building has been finished.
	 */
	UPROPERTY(BlueprintAssignable)
	FConstructionFinished OnConstructionFinished;
	/**
	 * @brief Delegate event triggered when construction of a building fails.
	 *
	 * This delegate event is broadcast when the construction process for a building cannot be completed successfully.
	 */
	UPROPERTY(BlueprintAssignable)
	FConstructionFailed OnConstructionFailed;
};
