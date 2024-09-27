
#include "CTGameModeLevel.h"

ACTGameModeLevel::ACTGameModeLevel()
{
	SortingLayerDataComponent = CreateDefaultSubobject<UCTSortingLayerDataComponent>(TEXT("Sorting Layer Data Component"));
	AddOwnedComponent(SortingLayerDataComponent);

	WorldResourceComponent = CreateDefaultSubobject<UCTWorldResourceComponent>(TEXT("World Ressource Component"));
	AddOwnedComponent(WorldResourceComponent);

	WorldBuildableComponent = CreateDefaultSubobject<UCTWorldBuildableComponent>(TEXT("World Buildable Component"));
	AddOwnedComponent(WorldBuildableComponent);
}
