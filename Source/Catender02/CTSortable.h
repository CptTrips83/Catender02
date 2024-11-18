#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Components/CTSortingComponent.h"
#include "GameMode/CTGameModeLevel.h"
#include "CTSortable.generated.h"


class UBoxComponent;

/**
 * Represents a sortable actor in the game world.
 * Inherits from APaperZDCharacter and incorporates functionality for sorting and interaction.
 */
UCLASS()
class CATENDER02_API ACTSortable : public APaperZDCharacter
{
	GENERATED_BODY()
	
	ACTGameModeLevel* GameModeLevel = nullptr;
	
	/**
	 * A component used for sorting game objects within the level.
	 * This property is exposed to the Unreal Editor for easy access and manipulation.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, DeprecatedProperty))
	UCTSortingComponent* SortingComponent = nullptr;
	
public:
	ACTSortable();

	/**
	 * Retrieves the game mode level associated with this sortable actor.
	 * This game mode level is used to manage various game mode-specific components and logic.
	 *
	 * @return A pointer to the ACTGameModeLevel instance associated with this actor.
	 */
	UFUNCTION(BlueprintPure)
	virtual ACTGameModeLevel* GetGameMode() const;

	/**
	 * Retrieves the sorting component associated with this actor.
	 * This component is used to manage the sorting layer and index of the actor within the game world.
	 *
	 * @return A pointer to the UCTSortingComponent instance associated with this actor.
	 */
	UFUNCTION(BlueprintPure)
	UCTSortingComponent* GetSortingComponent() const;
	
protected:
	
	UFUNCTION()
	virtual void OnBoxBeginOverlap
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
	
	UFUNCTION()
	virtual void OnBoxEndOverlap
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	);
		
	virtual void BeginPlay() override;
	/**
	 * @brief Executes an interaction with another sortable actor.
	 *
	 * This function is invoked to initiate an interaction between the current
	 * interactable actor and another sortable actor passed as a parameter.
	 * It defines the specific behavior that occurs during the interaction.
	 *
	 * @param OtherSortable The other sortable actor to interact with.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void Interact(ACTSortable* OtherSortable);

	virtual void InteractInternal(ACTSortable* OtherSortable);
};
