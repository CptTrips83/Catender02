
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTPlayerInteractionComponent* PlayerInteractionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext *InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction *MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction *InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInputAction *PauseAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USoundBase* InteractSound;

	ACTPlayerCharacter();
	
	UFUNCTION(BlueprintPure)
	UCTPlayerInteractionComponent* GetPlayerInteractionComponent() const;

	UFUNCTION(BlueprintCallable)
	void PlayInteractSound() const;

	
protected:

	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void MoveTriggered(const FInputActionValue& Value);
	UFUNCTION()
	void MoveCompleted(const FInputActionValue& Value);

	UFUNCTION()
	void InteractTriggered(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent)
	void PauseTriggered(const FInputActionValue& Value);
	
private:
	UPROPERTY()
	APlayerController* PlayerController;
};
