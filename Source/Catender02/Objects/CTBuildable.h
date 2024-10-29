// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CTInteractable.h"
#include "Catender02/Components/CTBuildingComponent.h"
#include "Catender02/Components/CTBuildingWorkSiteComponent.h"
#include "CTBuildable.generated.h"

class UBoxComponent;
/**
 * @class ACTBuildable
 * @brief A class representing a buildable object within the game.
 *
 * ACTBuildable inherits from ACTInteractable and includes components and functionality
 * specific to building and construction activities.
 */
UCLASS()
class CATENDER02_API ACTBuildable : public ACTInteractable
{
	GENERATED_BODY()

	/**
	 * @brief Component responsible for managing building functionalities.
	 *
	 * This property points to an instance of UCTBuildingComponent, which encapsulates
	 * the attributes and methods necessary for building operations within the game.
	 * The property is editable anywhere and can be accessed and modified within blueprints.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTBuildingComponent* BuildingComponent = nullptr;

	/**
	 * @brief Component responsible for managing work site specific functionalities in building operations.
	 *
	 * This property holds an instance of UCTBuildingWorkSiteComponent, which is essential for handling
	 * various tasks associated with construction sites within the game. It is editable anywhere and
	 * can be read or written from within blueprints.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTBuildingWorkSiteComponent* BuildingWorkSiteComponent = nullptr;

	/**
	 * @brief Represents a collision box for defining the boundaries of a construction site within the game.
	 *
	 * The ConstructionSiteBoxComponent is an instance of UBoxComponent and is used to handle collision
	 * and boundary definitions specifically for construction sites. This component is editable anywhere and
	 * can be accessed and modified within blueprints, enabling flexible adjustments for construction site dimensions
	 * and behaviors in the game.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* ConstructionSiteBoxComponent = nullptr;

	/**
	 * @brief Represents a box component used for defining waiting areas within the game.
	 *
	 * The WaitingBoxComponent is an instance of UBoxComponent and is utilized to handle
	 * collision detection and boundary settings specifically for waiting zones. This component
	 * can be read or modified within blueprints, offering adjustable settings to fit desired
	 * waiting area dimensions and behaviors.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* WaitingBoxComponent = nullptr;
	
public:
	ACTBuildable();

	virtual void BeginPlay() override;

	/**
	 * @brief Interacts with another sortable object.
	 *
	 * This method overrides the base interact functionality to specifically handle interactions
	 * pertaining to buildable objects within the game. It attempts to upgrade the building
	 * associated with this object. If successful, it triggers an interaction sound on the player
	 * character and removes the highlight from the object.
	 *
	 * @param OtherSortable The other sortable object to interact with.
	 */
	virtual void Interact(ACTSortable* OtherSortable) override;

	/**
	 * @brief Handles the destruction behavior of the buildable object.
	 *
	 * This method is called when the buildable object is destroyed. It ensures that any necessary cleanup
	 * or teardown logic is executed by invoking the base class's Destroyed method.
	 */
	virtual void Destroyed() override;

	/**
	 * @brief Updates the collision state of the construction site box component.
	 *
	 * This method enables or disables the collision for the construction site box component
	 * based on the value of the IsActive parameter. When IsActive is true, the collision is set
	 * to QueryOnly; otherwise, it is set to NoCollision.
	 *
	 * @param IsActive A boolean flag indicating whether the collision should be active (true) or not (false).
	 */
	UFUNCTION()
	virtual void UpdateConstructionCollision(bool IsActive);

	/**
	 * @brief Retrieves the building component of the buildable object.
	 *
	 * This function returns the UCTBuildingComponent associated with the buildable object.
	 *
	 * @return A pointer to the UCTBuildingComponent.
	 */
	UFUNCTION()
	UCTBuildingComponent* GetBuildingComponent() const;
	/**
	 * @brief Retrieves the building work site component.
	 *
	 * This method returns the UCTBuildingWorkSiteComponent associated with the buildable object.
	 *
	 * @return A pointer to the UCTBuildingWorkSiteComponent.
	 */
	UFUNCTION()
	UCTBuildingWorkSiteComponent* GetBuildingWorkSiteComponent() const;
	/**
	 * @brief Retrieves the box component representing the construction site.
	 *
	 * This method returns the UBoxComponent that is used to define the bounds and collision
	 * properties of the construction site associated with this buildable object.
	 *
	 * @return A pointer to the UBoxComponent representing the construction site.
	 */
	UFUNCTION()
	UBoxComponent* GetConstructionSiteBoxComponent() const;
	/**
	 * @brief Retrieves the waiting box component of the buildable object.
	 *
	 * This method returns the UBoxComponent that represents the waiting box component of the
	 * buildable object, which is used to handle waiting interactions within the game.
	 *
	 * @return A pointer to the UBoxComponent representing the waiting box component.
	 */
	UFUNCTION()
	UBoxComponent* GetWaitingBoxComponent() const;

	/**
	 * @brief Checks if the buildable object can be interacted with.
	 *
	 * This method determines if the buildable object is in a state that allows
	 * interaction, depending on the status of its building component.
	 *
	 * @return True if the buildable object can be interacted with, false otherwise.
	 */
	virtual bool CanInteract() const override;

	/**
	 * @brief Processes the working state of a friendly NPC character.
	 *
	 * This method is a Blueprint Native Event that executes specific logic when an
	 * ACTFriendlyNPCCharacter is working.
	 *
	 * @param NPCCharacter Pointer to the ACTFriendlyNPCCharacter instance that is being processed.
	 */
	UFUNCTION(BlueprintNativeEvent)
	void ProcessWorking(ACTFriendlyNPCCharacter* NPCCharacter);

	/**
	 * @brief Handles the state change of a buildable object.
	 *
	 * This method updates the collision settings based on the new and old building states.
	 *
	 * @param Buildable A pointer to the buildable object whose state has changed.
	 * @param OldState The previous state of the building.
	 * @param NewState The new state of the building.
	 */
	UFUNCTION()
	virtual void BuildingStateChanged(ACTBuildable* Buildable, EBuildingState OldState, EBuildingState NewState);
};
