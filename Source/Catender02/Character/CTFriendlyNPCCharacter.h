
#pragma once

#include "CoreMinimal.h"
#include "CTCharacter.h"
#include "CTFriendlyNPCCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FWaitingIsChanged,
	ACTFriendlyNPCCharacter*, NPC,
	bool, OldValue,
	bool, NewValue
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FWorkingIsChanged,
	ACTFriendlyNPCCharacter*, NPC,
	bool, OldValue,
	bool, NewValue
);

class ACTBuilding;

/**
 * Represents a friendly non-playable character (NPC) within the game world that can interact with building work sites.
 */
UCLASS()
class CATENDER02_API ACTFriendlyNPCCharacter : public ACTCharacter
{
	GENERATED_BODY()

	/**
	 * Pointer to a buildable object representing the current building work site assigned to the friendly NPC character.
	 */
	UPROPERTY()
	ACTBuildable* AssignedBuildable;

	UPROPERTY()
	bool IsWaiting = false;

	UPROPERTY()
	bool IsWorking = false;

	/**
	 * A soft pointer to an ACTBuilding object representing the home building associated with the friendly NPC character.
	 *
	 * This variable allows the assignment and retrieval of a home building in a blueprint-accessible manner.
	 * It also provides the flexibility of referencing an asset without loading it immediately.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TSoftObjectPtr<ACTBuilding> HomeBuilding;

	/**
	 * Defines the minimal interval, in seconds, for which an entity will remain in a waiting state.
	 * This variable can be edited anywhere and read within Blueprints.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	float MinWaitingInterval = 0.25f;

	/**
	 * Defines the maximal interval, in seconds, for which an entity will remain in a waiting state.
	 * This variable can be edited anywhere and read within Blueprints.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	float MaxWaitingInterval = 0.75f;
	
	UPROPERTY()
	FTimerHandle WaitingTimerHandle;

	/**
	 * Capsule component representing the work site area associated with the friendly NPC character.
	 * Used to detect overlaps and interactions specific to work sites.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCapsuleComponent* WorkSiteCapsule;

	/**
	 * Resets the collision settings for the work site capsule associated with the friendly NPC character.
	 * The capsule component's collision is first disabled and then set to query-only mode, ensuring that
	 * it can detect overlaps without affecting physics interactions.
	 */
	void ResetWorkSiteCapsule();
	
public:
	ACTFriendlyNPCCharacter();

protected:
	virtual void BeginPlay() override;

	/**
	 * Initiates the working process for the friendly NPC character.
	 * This method is intended to be implemented in Blueprint and can define custom behavior when the NPC starts working.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void StartWorking();

	/**
	 * Processes ongoing work for the friendly NPC character.
	 * This method can be overridden in Blueprint to define custom behavior during the NPC's working period.
	 */
	UFUNCTION(BlueprintNativeEvent)
	void ProcessWorking();

	/**
	 * Stops the working process for the friendly NPC character.
	 * This method is intended to be implemented in Blueprint and can define custom behavior when the NPC stops working.
	 */
	UFUNCTION(BlueprintImplementableEvent)	
	void StopWorking();

	/**
	 * Handles the begin overlap event for the work site detection capsule component.
	 * This method is triggered when another actor begins overlapping with the work site capsule component,
	 * primarily to check if the overlapping actor is a buildable work site and to start the working process accordingly.
	 *
	 * @param OverlappedComp The work site capsule component that triggered the overlap event.
	 * @param OtherActor The actor that is overlapping with the work site capsule component.
	 * @param OtherComp The specific component on the other actor that is overlapping with the work site capsule.
	 * @param OtherBodyIndex The index of the overlapping body.
	 * @param bFromSweep Whether the overlap event occurred from a sweeping movement.
	 * @param SweepResult The hit result data if the overlap event was caused by a sweep.
	 */
	UFUNCTION()
	virtual void OnWorkSiteBoxBeginOverlap
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

	/**
	 * Handles the end overlap event for the work site detection capsule component.
	 * This method is triggered when another actor stops overlapping with the work site capsule component.
	 *
	 * @param OverlappedComp The work site capsule component that triggered the overlap event.
	 * @param OtherActor The actor that was overlapping with the work site capsule component.
	 * @param OtherComp The specific component on the other actor that was overlapping with the work site capsule.
	 * @param OtherBodyIndex The index of the overlapping body.
	 */
	UFUNCTION()
	virtual void OnWorkSiteBoxEndOverlap
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	);
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/**
	 * Retrieves the currently assigned buildable object that the friendly NPC is associated with.
	 * @return The buildable object assigned to the NPC.
	 */
	UFUNCTION(BlueprintPure)
	virtual ACTBuildable* GetAssignedBuildable();
	
	/**
	 * Assigns the friendly NPC character to a specified building work site.
	 *
	 * @param Buildable A pointer to the buildable object representing the work site to assign the NPC to.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AssignToBuildingWorkSite(ACTBuildable* Buildable);
	/**
	 * Withdraws the friendly NPC character from a specified building work site.
	 *
	 * @param Buildable A pointer to the buildable object representing the work site to withdraw the NPC from.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void WithdrawFromBuildingWorkSite(ACTBuildable* Buildable);

	/**
	 * Retrieves the nearest working site for the friendly NPC character.
	 *
	 * @return A pointer to the nearest ACTBuildable object representing the work site, or nullptr if no suitable site is found.
	 */
	UFUNCTION(BlueprintPure)
	virtual ACTBuildable* GetNearestWorkingSite();

	/**
	 * Sets the waiting state of the friendly non-playable character (NPC).
	 *
	 * @param NewValue The new waiting state to be set.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void SetIsWaiting(bool NewValue);

	/**
	 * Checks if the friendly NPC character is currently waiting.
	 *
	 * @return True if the NPC character is waiting, otherwise false.
	 */
	UFUNCTION(BlueprintPure)
	virtual bool GetIsWaiting();

	/**
	 * Sets the working state of the friendly NPC character.
	 *
	 * @param NewValue A boolean indicating whether the NPC is currently working.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void SetIsWorking(bool NewValue);

	/**
	 * Checks if the NPC character is currently working at a building work site.
	 *
	 * @return true if the NPC is working, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	virtual bool GetIsWorking();

	/**
	 * Sets the home building for the friendly NPC character.
	 *
	 * @param Building A pointer to the building that will be set as the NPC character's home.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void SetHomeBuilding(ACTBuilding* Building);

	/**
	 * Retrieves the home building associated with this friendly NPC character.
	 *
	 * @return The home building as a soft object pointer.
	 */
	UFUNCTION(BlueprintPure)
	virtual TSoftObjectPtr<ACTBuilding> GetHomeBuilding();

	/**
	 * Retrieves the capsule component representing the work site associated with this friendly NPC character.
	 *
	 * @return A pointer to the capsule component that defines the work site.
	 */
	UFUNCTION(BlueprintPure)
	UCapsuleComponent* GetWorkSiteCapsule();
	
	//UFUNCTION(BlueprintPure)
	//virtual float GetRandomPositionInBox(USceneComponent* Box);

	/**
	 * Event delegate that is called when the waiting state changes.
	 *
	 * This delegate is marked as BlueprintAssignable, meaning it can be assigned
	 * to events or functions in Blueprint to handle changes in the waiting state
	 * of an object or character.
	 */
	UPROPERTY(BlueprintAssignable)
	FWaitingIsChanged OnWaitingIsChanged;

	/**
	 * Event delegate triggered when the working status changes.
	 */
	UPROPERTY(BlueprintAssignable)
	FWorkingIsChanged OnWorkingIsChanged;
};
