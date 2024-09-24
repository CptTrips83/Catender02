
#include "CTPlayerCharacter.h"

ACTPlayerCharacter::ACTPlayerCharacter()
{
	PlayerInteractionComponent = CreateDefaultSubobject<UCTPlayerInteractionComponent>("PlayerInteractionComponent");
	AddOwnedComponent(PlayerInteractionComponent);
}
