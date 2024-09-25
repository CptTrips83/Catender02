
#pragma once

#include "CoreMinimal.h"
#include "Catender02/Components/CTWorldInteractableComponent.h"
#include "Catender02/Components/CTSortingLayerDataComponent.h"
#include "Catender02/Components/CTWorldResourceComponent.h"
#include "GameFramework/GameModeBase.h"
#include "CTGameModeLevel.generated.h"


UCLASS()
class CATENDER02_API ACTGameModeLevel : public AGameModeBase
{
	GENERATED_BODY()

public:

	ACTGameModeLevel();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCTSortingLayerDataComponent* SortingLayerDataComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCTWorldInteractableComponent* WorldInteractableComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCTWorldResourceComponent* WorldResourceComponent = nullptr;
};
