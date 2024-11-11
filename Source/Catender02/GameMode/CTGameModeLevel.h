
#pragma once

#include "CoreMinimal.h"
#include "Catender02/Components/CTWorldBuildableComponent.h"
#include "Catender02/Components/CTSortingLayerDataComponent.h"
#include "Catender02/Components/CTWorldBuildingVisibilityComponent.h"
#include "Catender02/Components/CTWorldDayTimeComponent.h"
#include "Catender02/Components/CTWorldResourceComponent.h"
#include "GameFramework/GameModeBase.h"
#include "CTGameModeLevel.generated.h"


class ACTBuildingHQ;

/**
 * A class representing the game mode for a specific level in the game.
 * This class extends AGameModeBase and is responsible for initializing and managing
 * core components related to building headquarters, sorting layers, world resources,
 * buildable objects, and building visibility.
 */
UCLASS()
class CATENDER02_API ACTGameModeLevel : public AGameModeBase
{
	GENERATED_BODY()

	/**
	 * Pointer to the building headquarters within the game level.
	 * This variable holds a reference to the ACTBuildingHQ instance, which manages the core functionalities related to the building headquarters.
	 * It is initialized during the BeginPlay method to ensure it references the correct in-game instance.
	 */
	UPROPERTY()
	ACTBuildingHQ* BuildingHQ = nullptr;

	/**
	 * A component responsible for managing sorting layer data within the game level.
	 * This variable holds a reference to the UCTSortingLayerDataComponent instance, which is used to
	 * update and retrieve sorting layers for game objects to ensure the correct rendering order and other layer-specific settings.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTSortingLayerDataComponent* SortingLayerDataComponent = nullptr;

	/**
	 * A component responsible for managing world resources within the game level.
	 * This variable holds a reference to the UCTWorldResourceComponent instance, which oversees the allocation,
	 * collection, and distribution of resources required for various game functions and enhancements.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTWorldResourceComponent* WorldResourceComponent = nullptr;

	/**
	 * A component responsible for managing buildable objects within the game world.
	 * This variable holds a reference to the UCTWorldBuildableComponent instance, enabling functionalities related to the creation,
	 * manipulation, and interaction of buildable objects in the game environment.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTWorldBuildableComponent* WorldBuildableComponent = nullptr;

	/**
	 * A component responsible for managing the visibility of buildings within the game level.
	 * This variable holds a reference to the UCTWorldBuildingVisibilityComponent instance, which handles tasks related to
	 * the visibility and rendering of buildings, interacting with collision channels and other visibility settings.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTWorldBuildingVisibilityComponent* WorldBuildingVisibilityComponent = nullptr;

	/**
	 * A component responsible for managing day and night cycles within the game world.
	 * This variable holds a reference to the UCTWorldDayTimeComponent instance, which is used to control
	 * the passage of time, including day and night transitions, adjusting lighting conditions, and other related tasks.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTWorldDayTimeComponent* WorldDayTimeComponent = nullptr;
	
public:

	ACTGameModeLevel();

	virtual void BeginPlay() override;


	/**
	 * Retrieves the building headquarters (HQ) within the game level.
	 *
	 * @return A pointer to the ACTBuildingHQ instance representing the building headquarters.
	 */
	UFUNCTION(BlueprintPure)
	ACTBuildingHQ* GetBuildingHQ();

	/**
	 * Retrieves the SortingLayerDataComponent associated with the ACTGameModeLevel instance.
	 *
	 * @return A pointer to the UCTSortingLayerDataComponent, which manages sorting layers for the game.
	 */
	UFUNCTION(BlueprintPure)
	UCTSortingLayerDataComponent* GetSortingLayerDataComponent();

	/**
	 * Retrieves the world resource component associated with this game mode level.
	 *
	 * @return A pointer to the UCTWorldResourceComponent instance managing the world resources.
	 */
	UFUNCTION(BlueprintPure)
	UCTWorldResourceComponent* GetWorldResourceComponent();

	/**
	 * Retrieves the world buildable component associated with the game mode.
	 * This component is responsible for managing the objects that can be built in the game world.
	 *
	 * @return A pointer to the UCTWorldBuildableComponent instance.
	 */
	UFUNCTION(BlueprintPure)
	UCTWorldBuildableComponent* GetWorldBuildableComponent();

	/**
	 * Retrieves the component responsible for managing the day and night cycles within the game world.
	 *
	 * @return A pointer to the UCTWorldDayTimeComponent instance which controls the passage of time.
	 */
	UFUNCTION(BlueprintPure)
	UCTWorldDayTimeComponent* GetWorldDayTimeComponent();
};
