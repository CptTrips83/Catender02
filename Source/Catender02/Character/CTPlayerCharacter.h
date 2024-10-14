
#pragma once

#include "CoreMinimal.h"
#include "CTCharacter.h"
#include "Catender02/Components/CTPlayerInteractionComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "CTPlayerCharacter.generated.h"

UCLASS()
class CATENDER02_API ACTPlayerCharacter : public ACTCharacter
{
	GENERATED_BODY()

	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCTPlayerInteractionComponent* PlayerInteractionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext *InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction *MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction *InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* InteractSound;

	ACTPlayerCharacter();
	
	UFUNCTION(BlueprintCallable)
	UCTPlayerInteractionComponent* GetPlayerInteractionComponent() const;

	UFUNCTION(BlueprintCallable)
	void PlayInteractSound() const;

	
protected:

	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void MoveTriggered(const FInputActionValue& Value);
	void MoveCompleted(const FInputActionValue& Value);

	void InteractTriggered(const FInputActionValue& Value);

private:
	APlayerController* PlayerController;
};
