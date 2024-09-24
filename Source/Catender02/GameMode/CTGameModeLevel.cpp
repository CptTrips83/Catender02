
#include "CTGameModeLevel.h"

ACTGameModeLevel::ACTGameModeLevel()
{
	SortingLayerDataComponent = CreateDefaultSubobject<UCTSortingLayerDataComponent>(TEXT("Sorting Layer Data Component"));
	AddOwnedComponent(SortingLayerDataComponent);	
}
