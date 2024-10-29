

#include "CTPickable.h"

#include "Catender02/Character/CTPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Physics/PhysicsFiltering.h"


/**
 * @brief Plays the pickup sound for the pickable object.
 *
 * This function checks if a pickup sound is assigned and plays it at the object's location using the gameplay statics.
 * It is typically called when the object is picked up.
 */
void ACTPickable::PlayPickupSound() const
{
	if (!PickupSound) return;
	UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
}

/**
 * @brief Plays the drop sound for the pickable object.
 *
 * This function checks if a drop sound is assigned and plays it at the object's location using the gameplay statics.
 * It is typically called when the object is dropped.
 */
void ACTPickable::PlayDropSound() const
{
	if (!DropSound) return;
	UGameplayStatics::PlaySoundAtLocation(this, DropSound, GetActorLocation());
}

/**
 * @brief Plays the pick animation for the pickable object.
 *
 * This function manipulates the sprite of the object to play the pick animation by setting it
 * to non-looping and reversing its direction. It is typically called when the object is picked up.
 */
void ACTPickable::PlayPickAnimation() const
{
	GetSprite()->SetLooping(false);
	GetSprite()->Reverse();
}

/**
 * @brief Disables collision for the pickable object.
 *
 * This function sets the collision response of the object's capsule component
 * to ignore collisions on the specified pickup channel. It is typically called after the object
 * has been picked up or is no longer needed for collision detection.
 */
void ACTPickable::DisableCollision() const
{
	for(const ECollisionChannel PickupChannel : PickupChannels)
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(PickupChannel, ECR_Ignore);
	}
}

/**
 * @brief Applies the resources contained in the pickable object to the world resource component.
 *
 * This function retrieves the world resource component from the game mode and attempts to add the
 * resources specified in the object's Resources array. If the world resource component is not available,
 * the function exits early. For each resource type and amount in the Resources array, the resource is
 * added to the world resource component.
 */
void ACTPickable::ApplyResources() const
{
	UCTWorldResourceComponent* ResourceComponent = GetGameMode()->GetWorldResourceComponent();

	if (!ResourceComponent) return;

	for(auto [ResourceType, Amount] : Resources)
	{
		ResourceComponent->TryAddResourceAmount(ResourceType, Amount);
	}
}

/**
 * @brief Destroys the pickup actor.
 *
 * This function is responsible for destroying the pickup actor instance. It is typically called after
 * a delay when the pickup is no longer needed, such as after being collected by a player character.
 */
void ACTPickable::DestroyPickup()
{
	Destroy();
}

ACTPickable::ACTPickable()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Pickup"));
	PickupComponent->SetupAttachment(GetRootComponent());
}

void ACTPickable::BeginPlay()
{
	Super::BeginPlay();

	GetSprite()->SetLooping(false);
	PickupComponent->OnComponentBeginOverlap.AddDynamic(this, &ACTPickable::OnCapsuleBeginOverlap);
}

void ACTPickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTPickable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACTPickable::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!OtherActor->IsA(ACTPlayerCharacter::StaticClass())) return;

	DisableCollision();
	PlayPickAnimation();
	PlayPickupSound();
	ApplyResources();

	FTimerHandle TimerHandle;
	
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&ACTPickable::DestroyPickup,
		DestructionTimer,
		false,
		DestructionTimer
	);
}

