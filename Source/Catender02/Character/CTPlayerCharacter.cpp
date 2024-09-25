
#include "CTPlayerCharacter.h"

#include "./Catender02/Objects/CTInteractable.h"

ACTPlayerCharacter::ACTPlayerCharacter()
{
	PlayerInteractionComponent = CreateDefaultSubobject<UCTPlayerInteractionComponent>("PlayerInteractionComponent");
	AddOwnedComponent(PlayerInteractionComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

UCTPlayerInteractionComponent* ACTPlayerCharacter::GetPlayerInteractionComponent() const
{
	return PlayerInteractionComponent;
}

UCTPlayerInteractionComponent* ACTPlayerCharacter::GetPlayerInteractionComponent()
{
	return PlayerInteractionComponent;
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

void ACTPlayerCharacter::MoveTriggered(const FInputActionValue& Value)
{
	const FVector2d MoveActionValue = Value.Get<FVector2d>();
	const float MoveX = MoveActionValue.X;

	Move(MoveX);
}

void ACTPlayerCharacter::MoveCompleted(const FInputActionValue& Value)
{
}

void ACTPlayerCharacter::InteractTriggered(const FInputActionValue& Value)
{
	ACTInteractable* Interactable = GetPlayerInteractionComponent()->GetFrontInteractable();

	if (!Interactable) return;

	Interact(Interactable);
}
