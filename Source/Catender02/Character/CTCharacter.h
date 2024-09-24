#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "./Catender02/CTSortable.h"
#include "CTCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams
(
	FOnRotationChanged,
	FRotator, OldRotation,
	FRotator, NewRotation
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam
(
	FOnMoveInput,
	float, InputValue
);

UCLASS()
class CATENDER02_API ACTCharacter : public ACTSortable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateRotation();
	
	virtual void Move(float MoveX);
	virtual bool CanMove();

	UPROPERTY(BlueprintAssignable)
	FOnRotationChanged OnRotationChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnMoveInput OnMoveInput;
};
