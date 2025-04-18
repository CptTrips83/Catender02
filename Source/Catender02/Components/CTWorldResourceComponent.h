
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTWorldResourceComponent.generated.h"

/**
 * Enum representing different resource types available in the game.
 * This enumeration defines various materials that players can collect or use.
 */
UENUM(BlueprintType)
enum EResourceType
{
	Gold,
	Meat,
	Wood,
	Stone,
	Iron
};

/**
 * A structure representing a resource in the game.
 * The resource is defined by its type and the amount available.
 */
USTRUCT(BlueprintType)
struct FResource
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<EResourceType> ResourceType = Gold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
	int Amount = 0;	
};

/**
 * A structure representing data related to a specific resource.
 * It contains information about the resource itself and its unlock status.
 */
USTRUCT(BlueprintType)
struct FResourceData
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FResource Resource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsUnlockResource = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams
(
	FResourceAmountChanged,
	EResourceType, Resource,
	int, OldAmount,
	int, NewAmount	
);

/**
 * A component that manages resources within a world context.
 * It allows adding, subtracting, and querying resources, along with keeping track of maximum limits and unlocking resources.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATENDER02_API UCTWorldResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCTWorldResourceComponent();

protected:
	virtual void BeginPlay() override;

	/**
	 * Retrieves resource data based on the specified resource type.
	 *
	 * @param ResourceType The type of resource to retrieve data for.
	 * @return A pointer to the resource data if the resource type is found, otherwise nullptr.
	 */
	FResourceData* GetResourceData(const EResourceType ResourceType);
public:
	UFUNCTION(BlueprintCallable)
	virtual FResourceData CreateResourceData(const FResource& Resource);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Represents the maximum amount of resources that can be stored.
	 *
	 * This value is editable only within the default configuration and can be read or modified via Blueprints.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MaxResources = 30;

	/**
	 * Array containing the resource data.
	 *
	 * This array can be edited anywhere within the Unreal Editor and can be read or modified via Blueprints.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FResourceData> Resources;

	/**
	 * Delegate called when the amount of a resource changes.
	 * It broadcasts information about the resource type, old amount, and new amount.
	 *
	 * Usage scenarios:
	 * - When resource amounts are adjusted by adding or subtracting.
	 * - For UI or other gameplay elements to update based on resource changes.
	 */
	UPROPERTY(BlueprintAssignable)
	FResourceAmountChanged OnResourceAmountChanged;

	/**
	 * Retrieves the current amount of a specified resource type.
	 *
	 * This function searches through the list of resources and returns the amount of the specified type.
	 * If the resource type is not found, it returns 0.
	 *
	 * @param ResourceType The type of resource whose amount is to be retrieved.
	 * @return The current amount of the specified resource type.
	 */
	UFUNCTION(BlueprintPure)
	int GetResourceAmount(const EResourceType ResourceType);
	/**
	 * Attempts to add a specified amount of a resource type.
	 *
	 * This function adds the specified amount to the resource type if there is enough available space.
	 * If the addition exceeds the maximum allowed resources, the remaining amount that couldn't be added is returned.
	 *
	 * @param ResourceType The type of resource to add.
	 * @param Amount The amount of resource to add.
	 * @return The amount of the resource that couldn't be added due to space constraints, or 0 if all resources were added successfully.
	 */
	UFUNCTION(BlueprintCallable)
	int TryAddResourceAmount(const EResourceType ResourceType, int Amount);
	/**
	 * Attempts to subtract a specified amount of a resource type from the current resource pool.
	 *
	 * This function decreases the specified amount from the resource type if there is enough available.
	 * If the resource type's amount is insufficient or if the specified amount is negative, the function will fail.
	 * Upon successful subtraction, it broadcasts the resource change event.
	 *
	 * @param ResourceType The type of resource to subtract.
	 * @param Amount The amount of resource to subtract.
	 * @return True if the resource amount was successfully subtracted; false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	bool TrySubtractResourceAmount(const EResourceType ResourceType, int Amount);

	UFUNCTION(BlueprintCallable)
	bool TrySubtractResources(const TArray<FResource> NeededResources);
	
	/**
	 * Sets the maximum amount of resources that can be stored.
	 *
	 * The new maximum amount will be clamped between 0 and 100.
	 *
	 * @param NewAmount The new maximum amount of resources to be set.
	 */
	UFUNCTION(BlueprintCallable)
	void SetMaxResources(int NewAmount);
	/**
	 * Checks if a given resource type is unlocked.
	 *
	 * This method retrieves the resource data for the specified resource type
	 * and checks if it is marked as unlocked.
	 *
	 * @param ResourceType The type of resource to check for unlock status.
	 * @return True if the resource type is unlocked, false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	bool IsUnlockResource(const EResourceType ResourceType);
	/**
	 * Calculates and returns the total amount of all resources currently stored.
	 * This excludes any resources marked as unlocked.
	 *
	 * @return The total amount of all resources, excluding unlocked resources.
	 */
	UFUNCTION(BlueprintPure)
	int GetAmountAllResources();
	/**
	 * Retrieves the maximum amount of resources that can be stored.
	 *
	 * This method returns the predefined limit on the number of resources
	 * that this component can hold.
	 *
	 * @return The maximum amount of resources.
	 */
	UFUNCTION(BlueprintPure)
	int GetMaxResources() const;
	/**
	 * Checks whether the specified resource type has the needed amount available.
	 *
	 * This function retrieves the resource data for the specified resource type and determines if
	 * the amount is sufficient to meet or exceed the needed amount. A positive result is returned
	 * if the resource is marked as unlocked and has at least 1 unit, or if it meets the required amount.
	 *
	 * @param Resource The type of resource to check.
	 * @param NeededAmount The amount of the resource required.
	 * @return True if the resource type has the needed amount or is unlocked with at least one unit available; false otherwise.
	 */
	UFUNCTION(BlueprintPure)
	bool CheckResource(EResourceType Resource, int NeededAmount);

	UFUNCTION(BlueprintPure)
	bool CheckResources(TArray<FResource> NeededResources);
};
