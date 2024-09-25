#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Components/CTSortingComponent.h"
#include "GameMode/CTGameModeLevel.h"
#include "CTSortable.generated.h"


UCLASS()
class CATENDER02_API ACTSortable : public APaperZDCharacter, public IInteract
{
public:
	ACTSortable();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCTSortingComponent* SortingComponent = nullptr;

protected:
	ACTGameModeLevel* GameModeLevel = nullptr;
	
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Interact(ACTSortable* OtherSortable);
};
