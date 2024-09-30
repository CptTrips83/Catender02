
#pragma once

#include "CoreMinimal.h"
#include "CTCharacter.h"
#include "CTFriendlyNPCCharacter.generated.h"

class ACTBuilding;

UCLASS()
class CATENDER02_API ACTFriendlyNPCCharacter : public ACTCharacter
{
	GENERATED_BODY()

	
	
public:
	ACTFriendlyNPCCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
