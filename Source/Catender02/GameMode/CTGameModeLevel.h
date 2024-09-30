
#pragma once

#include "CoreMinimal.h"
#include "Catender02/Components/CTWorldBuildableComponent.h"
#include "Catender02/Components/CTSortingLayerDataComponent.h"
#include "Catender02/Components/CTWorldBuildingVisibilityComponent.h"
#include "Catender02/Components/CTWorldResourceComponent.h"
#include "GameFramework/GameModeBase.h"
#include "CTGameModeLevel.generated.h"


class ACTBuildingHQ;

UCLASS()
class CATENDER02_API ACTGameModeLevel : public AGameModeBase
{
	GENERATED_BODY()

	ACTBuildingHQ* BuildingHQ = nullptr;
	
public:

	ACTGameModeLevel();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCTSortingLayerDataComponent* SortingLayerDataComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCTWorldResourceComponent* WorldResourceComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCTWorldBuildableComponent* WorldBuildableComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCTWorldBuildingVisibilityComponent* WorldBuildingVisibilityComponent = nullptr;

	ACTBuildingHQ* GetBuildingHQ();
};
