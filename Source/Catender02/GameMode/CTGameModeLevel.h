
#pragma once

#include "CoreMinimal.h"
#include "Catender02/Components/CTSortingLayerDataComponent.h"
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

};
