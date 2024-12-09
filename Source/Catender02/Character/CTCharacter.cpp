
#include "CTCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

/**
 * @brief Updates the rotation of the character based on its current velocity.
 *
 * This function checks the current velocity of the character and adjusts the yaw rotation
 * accordingly. If the velocity in the X direction is negative, it sets the yaw to 180 degrees.
 * The updated rotation is then set in the controller.
 */
void ACTCharacter::UpdateRotation()
{
	const FVector CurrentVelocity = GetCharacterMovement()->Velocity;
	
	if(CurrentVelocity.X == 0) return;
		
	AController* CharacterController = GetController();
	
	if(!CharacterController) return;

	const FRotator OldRotation = CharacterController->GetControlRotation();
	
	float Yaw = 0;

	if(CurrentVelocity.X < 0)
	{
		Yaw = 180;
	}

	const FRotator NewRotation = FRotator(0, Yaw, 0);
	
	CharacterController->SetControlRotation(NewRotation);

	OnRotationChanged.Broadcast(OldRotation, NewRotation);
}

/**
 * @brief Moves the character along the X-axis.
 *
 * This function adds movement input along the X-axis based on the given `MoveX` parameter.
 * Before adding movement input, it checks whether the character is allowed to move by
 * invoking the `CanMove()` function. If the character can move, the movement input is added
 * and the `OnMoveInput` event is broadcast with the `MoveX` value.
 *
 * @param MoveX The amount to move the character along the X-axis.
 */
void ACTCharacter::Move(const float MoveX)
{
	if(!CanMove()) return;
	
	AddMovementInput(FVector(MoveX, 0, 0));

	UpdateRotation();

	OnMoveInput.Broadcast(MoveX);
}

/**
 * @brief Determines if the character is allowed to move.
 *
 * This function checks the conditions necessary for the character to move
 * and returns true if all conditions permit movement.
 *
 * @return true if the character can move, false otherwise.
 */
bool ACTCharacter::CanMove()
{
	return true;
}

void ACTCharacter::SetMovement(ENPCCharacterMovementType MovementType)
{
	MovementType == ENPCCharacterMovementType::Walking ?
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed :
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
}

