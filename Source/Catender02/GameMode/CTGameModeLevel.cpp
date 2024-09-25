
#include "CTGameModeLevel.h"

ACTGameModeLevel::ACTGameModeLevel()
{
	SortingLayerDataComponent = CreateDefaultSubobject<UCTSortingLayerDataComponent>(TEXT("Sorting Layer Data Component"));
	AddOwnedComponent(SortingLayerDataComponent);

	WorldInteractableComponent = CreateDefaultSubobject<UCTWorldInteractableComponent>(TEXT("World Interactable Component"));
	AddOwnedComponent(WorldInteractableComponent);

	WorldResourceComponent = CreateDefaultSubobject<UCTWorldResourceComponent>(TEXT("World Ressource Component"));
}
