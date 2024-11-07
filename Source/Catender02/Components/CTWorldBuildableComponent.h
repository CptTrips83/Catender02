
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTWorldBuildableComponent.generated.h"

UENUM(BlueprintType)
enum ECTDirection
{
	Left,
	Right
};

class ACTSortable;
class ACTBuildable;

/**
 * Sorts the list of buildables in ascending order based on their distance to the specified sortable object.
 *
 * This method uses a lambda function to compare the distances between buildable objects and the specified sortable object,
 * rearranging the array of buildables so that the closest ones come first.
 *
 * @param Sortable A pointer to an object of type ACTSortable used to determine the distances for sorting.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTWorldBuildableComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<ACTBuildable*> Buildables;

	/**
	 * Sorts the list of buildables in ascending order based on their distance to the specified sortable object.
	 *
	 * This method uses a lambda function to compare the distances between buildable objects and the specified sortable object,
	 * rearranging the array of buildables so that the closest ones come first.
	 *
	 * @param Sortable A pointer to an object of type ACTSortable used to determine the distances for sorting.
	 */
	UFUNCTION()
	void SortBuildablesByNearest(ACTSortable* Sortable);
	/**
	 * Sorts the list of buildables in ascending order based on their distance to the specified sortable object and direction.
	 *
	 * This method uses a lambda function to compare the distances between buildable objects and the specified sortable object while considering their direction,
	 * rearranging the array of buildables so that the closest ones in the specified direction come first.
	 *
	 * @param Sortable A pointer to an object of type ACTSortable used to determine the distances for sorting.
	 * @param BuildableDirection An enum value of type ECTDirection specifying the direction (e.g., Left, Right) used to filter buildables before sorting.
	 */
	UFUNCTION()
	void SortBuildablesByNearestAndDirection(ACTSortable* Sortable, ECTDirection BuildableDirection);
	
public:	
	UCTWorldBuildableComponent();
	/**
	 * Populates the list of buildables currently present in the world.
	 *
	 * This method clears the current list of buildables and then iterates through all actors of the class ACTBuildable found in the world.
	 * Each found actor is cast to ACTBuildable and, if successful, added to the Buildables array.
	 */
	UFUNCTION()
	void PopulateBuildables();
	/**
	 * Removes the specified buildable from the list of buildables tracked by this component.
	 *
	 * This method checks if the provided buildable is valid (non-null) and, if so, removes it from the Buildables array.
	 *
	 * @param Buildable A pointer to an ACTBuildable object that is to be removed from the Buildables array.
	 */
	UFUNCTION()
	void RemoveBuildable(ACTBuildable* Buildable);
	/**
	 * Finds the nearest buildable object that has an active work site for the specified sortable object.
	 *
	 * This method sorts the list of buildables in ascending order of their proximity to the given sortable object.
	 * It then iterates through the sorted list to find the first buildable that has an active work site for the provided sortable object,
	 * which should be of type ACTFriendlyNPCCharacter.
	 *
	 * @param Sortable A pointer to an object of type ACTSortable, representing the object whose distance to buildables is considered for sorting.
	 * @return A pointer to the nearest buildable object that has an active work site for the specified sortable object.
	 *         If no such buildable is found, returns nullptr.
	 */
	UFUNCTION(BlueprintPure)
	ACTBuildable* GetNearestBuildable(ACTSortable* Sortable);
	/**
	 * Finds the nearest buildable object in the specified direction for the given sortable object.
	 *
	 * This method sorts the list of buildables in ascending order based on their distance
	 * to the specified sortable object and filters them by the given direction.
	 *
	 * @param Sortable A pointer to an object of type ACTSortable used to determine the distances and direction for sorting.
	 * @param BuildableDirection An enum value of type ECTDirection specifying the direction used to filter the buildables.
	 * @return A pointer to the nearest buildable object in the specified direction. Returns nullptr if no suitable buildable is found.
	 */
	UFUNCTION(BlueprintPure)
	ACTBuildable* GetNearestBuildableByDirection(ACTSortable* Sortable, ECTDirection BuildableDirection);
	/**
	 * Finds the nearest buildable construction site for the given sortable object.
	 *
	 * This method iterates through the list of buildables and checks each one's building state.
	 * It collects buildables that are currently in the "Construction" state and returns the nearest one.
	 *
	 * @param Sortable A pointer to an object of type ACTSortable used to determine the distances for finding the nearest construction site.
	 * @return A pointer to the nearest buildable object that is in the construction state.
	 *         Returns nullptr if no such buildable is found.
	 */
	UFUNCTION(BlueprintPure)
	ACTBuildable* GetNearestConstructionSite(ACTSortable* Sortable);
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
