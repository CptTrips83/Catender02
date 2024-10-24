
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

	UPROPERTY()
	ACTBuildingHQ* BuildingHQ = nullptr;
	
public:

	ACTGameModeLevel();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTSortingLayerDataComponent* SortingLayerDataComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTWorldResourceComponent* WorldResourceComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTWorldBuildableComponent* WorldBuildableComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTWorldBuildingVisibilityComponent* WorldBuildingVisibilityComponent = nullptr;

	UFUNCTION(BlueprintPure)
	ACTBuildingHQ* GetBuildingHQ();

	UFUNCTION(BlueprintPure)
	UCTSortingLayerDataComponent* GetSortingLayerDataComponent();
	
	UFUNCTION(BlueprintPure)
	UCTWorldResourceComponent* GetWorldResourceComponent();	

	UFUNCTION(BlueprintPure)
	UCTWorldBuildableComponent* GetWorldBuildableComponent();
};
