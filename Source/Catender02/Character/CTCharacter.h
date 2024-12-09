#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "./Catender02/CTSortable.h"
#include "CTCharacter.generated.h"

UENUM(BlueprintType)
enum ENPCCharacterMovementType
{
	Walking,
	Running
};

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	float WalkingSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	float RunningSpeed;
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateRotation();
	
	UFUNCTION()
	virtual void Move(float MoveX);
	UFUNCTION()
	virtual bool CanMove();

	UPROPERTY(BlueprintAssignable)
	FOnRotationChanged OnRotationChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnMoveInput OnMoveInput;

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void SetMovement(ENPCCharacterMovementType MovementType);

	/**
 * Generates a random position within the bounds of the specified box component.
 *
 * @param Box The box component within which to generate a random position.
 * @return A random X coordinate within the bounds of the box.
 */
	UFUNCTION(BlueprintPure)
	virtual float GetRandomPositionInBox(USceneComponent* Box);
};
