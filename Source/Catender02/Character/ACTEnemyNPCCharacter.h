
#pragma once

#include "CoreMinimal.h"
#include "CTCharacter.h"
#include "ACTEnemyNPCCharacter.generated.h"

UCLASS()
class CATENDER02_API ACTEnemyNPCCharacter : public ACTCharacter
{
	GENERATED_BODY()

public:
	ACTEnemyNPCCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
