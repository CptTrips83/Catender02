
#pragma once

#include "CoreMinimal.h"
#include "CTCharacter.h"
#include "Catender02/Components/CTPlayerInteractionComponent.h"
#include "CTPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CATENDER02_API ACTPlayerCharacter : public ACTCharacter
{
	GENERATED_BODY()

	
public:
	ACTPlayerCharacter();
	UCTPlayerInteractionComponent* PlayerInteractionComponent;
};
