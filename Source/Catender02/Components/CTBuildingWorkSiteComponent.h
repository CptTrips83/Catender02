
#pragma once

#include "CoreMinimal.h"
#include "CTBuildingComponent.h"
#include "Catender02/Character/CTFriendlyNPCCharacter.h"
#include "Components/ActorComponent.h"
#include "CTBuildingWorkSiteComponent.generated.h"


/**
 * A component that manages the work site for a building, including the assignment and tracking
 * of friendly NPC characters working on the site.
 *
 * This class is responsible for maintaining the state of the building work site, managing work places,
 * and controlling the friendly NPC characters assigned to work on the building. It interacts with other
 * building components to update and respond to changes in the building's state.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CATENDER02_API UCTBuildingWorkSiteComponent : public UActorComponent
{
	GENERATED_BODY()

	/**
	 * A list of friendly NPC characters currently working on the building work site.
	 *
	 * This array holds pointers to instances of ACTFriendlyNPCCharacter that are
	 * designated as working on the building work site. It is used to manage and
	 * track the friendly NPC characters involved with the work site.
	 *
	 * This property is visible anywhere and can be read in Blueprint scripts but is
	 * privately accessible within its own class. This restriction is enforced through
	 * the use of the "AllowPrivateAccess=true" metadata specifier.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<ACTFriendlyNPCCharacter*> WorkingFriendlyNPCCharacters;

	/**
	 * The number of total available work places on the building work site.
	 *
	 * This integer value represents the maximum number of work places available for NPC characters on the building work site.
	 * It is utilized to determine if additional NPC characters can be assigned to work on the work site.
	 *
	 * This property can be edited only in the defaults and read in Blueprint scripts but is privately accessible within its own class.
	 * This access restriction is controlled through the "AllowPrivateAccess=true" metadata specifier.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int AmountWorkPlaces = 1;

	/**
	 * A map associating building states with NPC character classes designated as workers.
	 *
	 * This map holds keys of type TEnumAsByte<EBuildingState>, representing different states of a building,
	 * and values of type TSubclassOf<ACTFriendlyNPCCharacter>, representing classes of friendly NPC characters
	 * that can work in those states. It is used to manage and map the types of NPC workers to the specific
	 * states of the building work site.
	 *
	 * This property is editable only in the defaults and can be read in Blueprint scripts, but is privately
	 * accessible within its own class. This access restriction is managed through the "AllowPrivateAccess=true"
	 * metadata specifier.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<TEnumAsByte<EBuildingState>, TSubclassOf<ACTFriendlyNPCCharacter>> BuildingStatesWorker;

	UPROPERTY()
	UCTBuildingComponent* BuildingComponent = nullptr;
	UPROPERTY()
	ACTBuildable* OwningBuildable = nullptr;
	
public:
	UCTBuildingWorkSiteComponent();

	/**
	 * Adds a friendly NPC character to the working friendly NPC characters list.
	 *
	 * Appends the given friendly NPC character pointer to the list of
	 * working friendly NPC characters if it is not null.
	 *
	 * @param Character A pointer to the friendly NPC character to be added.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AddFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character);
	/**
	 * Removes a friendly NPC character from the working friendly NPC characters list.
	 *
	 * Removes the given friendly NPC character pointer from the list of
	 * working friendly NPC characters if it is not null.
	 *
	 * @param Character A pointer to the friendly NPC character to be removed.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void RemoveFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character);
	/**
	 * Determines whether a given friendly NPC character is part of the working friendly NPC characters list.
	 *
	 * Checks the provided friendly NPC character pointer against a list of
	 * working friendly NPC characters to see if it is included.
	 *
	 * @param Character A pointer to the friendly NPC character to check.
	 * @return true if the friendly NPC character is part of the working friendly NPC characters list, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	virtual bool HasFriendlyNPCCharacter(ACTFriendlyNPCCharacter* Character);
	/**
	 * Counts the number of friendly NPC characters currently working.
	 *
	 * Retrieves the number of friendly NPC characters that are currently part
	 * of the working friendly NPC characters list.
	 *
	 * @return The number of friendly NPC characters currently working.
	 */
	UFUNCTION(BlueprintPure)
	virtual int CountFriendlyNPCCharacters(ACTFriendlyNPCCharacter* Character) const;
	/**
	 * Checks if there is an open work place available in the building work site.
	 *
	 * Evaluates the number of currently working NPC characters against the total number
	 * of available work places to determine if there is an open position.
	 *
	 * @return true if there is at least one open work place, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	virtual bool HasOpenWorkPlace(ACTFriendlyNPCCharacter* Character);	
	/**
	 * Determines if a given NPC character is associated with an active work site.
	 *
	 * Checks the building state of the building component and cross-references it
	 * with the mapping of building states to NPC character subclasses to determine
	 * if the given NPC character corresponds to the required subclass for the current building state.
	 *
	 * @param NPCCharacter A pointer to an NPC character to check.
	 * @return true if the NPC character is associated with an active work site, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	bool HasActiveWorkSite(ACTFriendlyNPCCharacter* NPCCharacter) const;
	
protected:
	virtual void BeginPlay() override;

	/**
	 * Handles updates to the building's state by responding to changes from an old state to a new state.
	 *
	 * This method is called when a building's state changes. It triggers necessary actions based on
	 * the transition from the old state to the new state, ensuring the building's work site remains
	 * consistent with its new state.
	 *
	 * @param Buildable Pointer to the buildable object whose state is changing.
	 * @param OldState The previous state of the building.
	 * @param NewState The new state of the building.
	 */
	UFUNCTION()
	virtual void BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldState, EBuildingState NewState);
	/**
	 * Retrieves the building component associated with the owning buildable.
	 *
	 * This method checks if there is an owning buildable object. If it exists, it obtains
	 * the building component from the owning buildable and updates the internal state
	 * to reflect this association. Additionally, it adds a listener to track changes
	 * in the building's state.
	 */
	UFUNCTION()
	void GetBuildingComponentFromOwner();
	/**
	 * Retrieves and sets the owning buildable component for the current work site component.
	 *
	 * This method accesses the owner of the current work site component and attempts to cast it to
	 * an ACTBuildable type. If successful, it sets the OwningBuildable member variable to this object.
	 * This allows the work site component to interact directly with the buildable component it is associated with.
	 */
	UFUNCTION()
	void GetOwningBuildableFromOwner();
	/**
	 * Registers a listener for building state changes.
	 *
	 * This method adds a dynamic listener to the building component's OnBuildingStateChanged event,
	 * enabling the UCTBuildingWorkSiteComponent to respond to changes in the building's state.
	 */
	UFUNCTION()
	void AddBuildingStateChangedListener();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
