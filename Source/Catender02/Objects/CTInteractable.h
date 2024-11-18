#pragma once

#include "CoreMinimal.h"
#include "./Catender02/CTSortable.h"
#include "Catender02/UI/CTUserWidgetMain.h"
#include "Catender02/UI/CTWidgetComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "CTInteractable.generated.h"


/**
 * @brief An interactive actor that can be sorted within the game world and interacts with other actors.
 *
 * This class inherits from ACTSortable and provides functionality for interaction within the game
 * environment. It features an interaction box component for collision detection and an interaction
 * widget for UI elements.
 */
UCLASS()
class CATENDER02_API ACTInteractable : public ACTSortable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* InteractionBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTWidgetComponent* InteractionWidget;


	/**
	 * @brief Updates the collision state of the interaction box component.
	 *
	 * This method enables or disables the collision of the interaction box component
	 * based on the provided flag. If `CollisionEnabled` is true, collision is set to
	 * be query-only; otherwise, collision is disabled.
	 *
	 * @param CollisionEnabled A boolean flag that determines whether the interaction
	 *                         collision should be enabled or disabled.
	 */
protected:
	virtual void UpdateInteractionCollision(bool CollisionEnabled);
	
public:
	
	ACTInteractable();
		
	virtual void BeginPlay() override;

	/**
	 * @brief Creates a dynamic material instance for the sprite component.
	 *
	 * This method checks whether the sprite component has a valid material and converts it into a dynamic
	 * material instance if it is not already one. The dynamic material instance allows for real-time
	 * modification of material properties.
	 *
	 * It first verifies the presence of a sprite and its associated material, then creates and assigns
	 * a dynamic material instance to the sprite component, enabling dynamic changes in material properties.
	 */
	UFUNCTION()
	virtual void CreateDynamicMaterialForSprite();
	
	/**
	 * @brief Checks if the actor can be interacted with.
	 *
	 * This method determines if the actor is currently in a state that allows interaction.
	 *
	 * @return true if the actor can be interacted with, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	virtual bool CanInteract() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta=(ForceAsFunction))
	TArray<FResource> GetNeededResourcesForInteraction();
	
	/**
	 * @brief Sets the visibility of the interaction widget.
	 *
	 * This method toggles the visibility of the interaction widget based on the provided boolean flag.
	 * If the interaction widget class is not set, the widget will be hidden regardless of the flag.
	 *
	 * @param IsActive A boolean flag that determines whether the interaction widget should be visible.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void SetVisibilityInteractionWidget(bool IsActive);

	/**
	 * @brief Retrieves the interaction box component associated with this actor.
	 *
	 * This method provides access to the UBoxComponent that is used for handling interaction collisions
	 * within the game world.
	 *
	 * @return A pointer to the UBoxComponent used for interaction.
	 */
	UFUNCTION(BlueprintCallable)
	UBoxComponent* GetInteractionBoxComponent() const;

	/**
	 * @brief Retrieves the interaction widget associated with this actor.
	 *
	 * This method returns a pointer to the UCTWidgetComponent, which is used to display
	 * the interaction widget in the game world.
	 *
	 * @return A pointer to the UCTWidgetComponent used for interaction.
	 */
	UFUNCTION(BlueprintPure)
	UCTWidgetComponent* GetInteractionWidget() const;

	/**
	 * @brief Sets the active state of the interaction box component.
	 *
	 * This method updates the collision state of the interaction box component
	 * based on the provided active flag. If Active is true, the collision is set
	 * to query-only; otherwise, it disables the collision.
	 *
	 * @param Active A boolean flag that determines whether the interaction
	 *               collision should be enabled or disabled.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void SetActive(bool Active);

	/**
	 * @brief Toggles the highlight effect on the actor.
	 *
	 * This method sets the highlight multiplier of the material based on the
	 * provided flag, effectively toggling the highlight effect.
	 *
	 * @param IsHighlighted A boolean flag that determines whether the actor should be highlighted.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void Highlight(bool IsHighlighted);

	/**
	 * @brief Handles the event when an overlap begins with the interaction box component.
	 *
	 * This function is triggered when another actor begins overlapping with the interaction box component.
	 * It checks if the overlapping actor is a player character and if so, adds this actor to the player's
	 * list of overlapping interactables.
	 *
	 * @param OverlappedComp The component that was overlapped.
	 * @param OtherActor The actor that caused the overlap.
	 * @param OtherComp The specific component of the actor that caused the overlap.
	 * @param OtherBodyIndex The body index involved in the overlap.
	 * @param bFromSweep A boolean indicating if the overlap was the result of a sweep.
	 * @param SweepResult The result data of the sweep, if applicable.
	 */
	UFUNCTION()
	virtual void OnBoxBeginOverlapInteraction
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

	/**
	 * @brief Handles the event when an overlap ends with the interaction box component.
	 *
	 * This function is triggered when another actor stops overlapping with the interaction box component.
	 * It checks if the overlapping actor is a player character and, if so, removes this actor from the player's
	 * list of overlapping interactables.
	 *
	 * @param OverlappedComp The component that was overlapped.
	 * @param OtherActor The actor that caused the overlap to end.
	 * @param OtherComp The specific component of the actor that was involved in the overlap.
	 * @param OtherBodyIndex The body index involved in the overlap.
	 */
	UFUNCTION()
	virtual void OnBoxEndOverlapInteraction 
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	);


	/**
	 * @brief Executes an interaction with another sortable actor.
	 *
	 * This function is invoked to initiate an interaction between the current
	 * interactable actor and another sortable actor passed as a parameter.
	 * It defines the specific behavior that occurs during the interaction.
	 *
	 * @param OtherSortable The other sortable actor to interact with.
	 */
	virtual void Interact(ACTSortable* OtherSortable) override;
};
