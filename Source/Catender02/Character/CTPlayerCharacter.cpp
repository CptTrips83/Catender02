
#include "CTPlayerCharacter.h"

#include "./Catender02/Objects/CTInteractable.h"
#include "Kismet/GameplayStatics.h"

ACTPlayerCharacter::ACTPlayerCharacter()
{
	PlayerInteractionComponent = CreateDefaultSubobject<UCTPlayerInteractionComponent>("PlayerInteractionComponent");
	AddOwnedComponent(PlayerInteractionComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

/**
 * Retrieves the player's interaction component.
 *
 * @return A pointer to the player's interaction component.
 */
UCTPlayerInteractionComponent* ACTPlayerCharacter::GetPlayerInteractionComponent() const
{
	return PlayerInteractionComponent;
}

void ACTPlayerCharacter::PlayInteractSound() const
{
	if(!InteractSound) return;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractSound, GetActorLocation());
}

void ACTPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	this->PlayerController = Cast<APlayerController>(GetController());

	if(!this->PlayerController) return;

	PlayerController->SetShowMouseCursor(false);

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

/**
 * Configures player input component and binds actions to corresponding methods.
 *
 * @param PlayerInputComponent The input component to set up.
 *
 */
void ACTPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Triggered,
			this,
			&ACTPlayerCharacter::MoveTriggered
		);
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Completed,
			this,
			&ACTPlayerCharacter::MoveCompleted
		);
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Canceled,
			this,
			&ACTPlayerCharacter::MoveCompleted
		);		
		EnhancedInputComponent->BindAction(
			InteractAction,
			ETriggerEvent::Started,
			this,
			&ACTPlayerCharacter::InteractTriggered
		);
	}
}

/**
 * Handles movement input triggered by the player.
 *
 * @param Value The input action value containing movement information.
 */
void ACTPlayerCharacter::MoveTriggered(const FInputActionValue& Value)
{
	const FVector2d MoveActionValue = Value.Get<FVector2d>();
	const float MoveX = MoveActionValue.X;

	Move(MoveX);
}

/**
 * Handles the actions to be taken when the movement input is completed or canceled.
 *
 * @param Value The input action value associated with the completed or canceled movement action.
 */
void ACTPlayerCharacter::MoveCompleted(const FInputActionValue& Value)
{
}

/**
 * Handles interaction input action when triggered.
 *
 * Retrieves the front interactable object from the player's interaction component.
 * If an interactable object exists, triggers the interaction process.
 *
 * @param Value The value associated with the input action trigger.
 *
 * @see UCTPlayerInteractionComponent::GetFrontInteractable()
 * @see ACTPlayerCharacter::Interact()
 */
void ACTPlayerCharacter::InteractTriggered(const FInputActionValue& Value)
{
	ACTInteractable* Interactable = GetPlayerInteractionComponent()->GetFrontInteractable();

	if (!Interactable) return;

	Interact(Interactable);
}
