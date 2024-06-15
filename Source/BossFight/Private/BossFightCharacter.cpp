#include "BossFightCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AbilitySystemComponent.h"

#include "Interfaces/CharactersAnimationInterface.h"
#include "Interfaces/InteractionInterface.h"
#include "Weapons/MasterWeapon.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ABossFightCharacter::ABossFightCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->InitSphereRadius(300.f);
	InteractionSphere->SetCollisionProfileName(TEXT("OverlapAll"));
	InteractionSphere->SetGenerateOverlapEvents(true);
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABossFightCharacter::OnBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ABossFightCharacter::OnEndOverlap);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

//////////////////////////////////////////////////////////////////////////
/// Protected
//////////////////////////////////////////////////////////////////////////

void ABossFightCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABossFightCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABossFightCharacter::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ABossFightCharacter::Interact);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &ABossFightCharacter::Equip);
		EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Started, this, &ABossFightCharacter::LightAttack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABossFightCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ABossFightCharacter::SetAnimWeaponType(TEnumAsByte<EWeaponType> WeaponType)
{
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (AnimInstance->GetClass()->ImplementsInterface(UCharactersAnimationInterface::StaticClass()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Weapon Type: %s"), *UEnum::GetValueAsString(WeaponType.GetValue())));
			ICharactersAnimationInterface::Execute_SetWeaponType(AnimInstance, WeaponType);
		}
	}
}

////////// Overlap //////////
void ABossFightCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IInteractionInterface* Interface = Cast<IInteractionInterface>(OtherActor))
	{
		Interactable = Interface;
	}
}

void ABossFightCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IInteractionInterface* Interface = Cast<IInteractionInterface>(OtherActor))
	{
		if (Interactable == Interface) { Interactable = nullptr; }
	}
}

////////// Abilities //////////
void ABossFightCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABossFightCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABossFightCharacter::Interact()
{
	if (Interactable != nullptr) { Interactable->Execute_Interact(Interactable->_getUObject(), this); }
}

void ABossFightCharacter::Equip()
{
	if (PossessedWeapon && AbilitySystemComponent) { PossessedWeapon->Equip(AbilitySystemComponent, bIsEquipped); }
}

void ABossFightCharacter::LightAttack()
{
	if (AbilitySystemComponent && bIsEquipped) { PossessedWeapon->LightAttack(AbilitySystemComponent); }
}

//////////////////////////////////////////////////////////////////////////
/// Public
//////////////////////////////////////////////////////////////////////////
void ABossFightCharacter::CollectWeapon(AMasterWeapon* Weapon)
{
	if (PossessedWeapon) { PossessedWeapon->Destroy(); }
	PossessedWeapon = Weapon;
	PossessedWeapon->AttachToSheith(GetMesh());
}

void ABossFightCharacter::PlayMontage(UAnimMontage* Montage)
{
	if (Montage && GetMesh())
	{
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Play(Montage);
			AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ABossFightCharacter::OnNotifyBegin);
		}
	}
}

void ABossFightCharacter::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == FName("AttachWeaponToHand")) { PossessedWeapon->AttachToHand(GetMesh()); }
	else if (NotifyName == FName("AttachWeaponToSheith")) { PossessedWeapon->AttachToSheith(GetMesh()); }
	else if (NotifyName == FName("DetachWeapon")) { PossessedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform); }
	else if (NotifyName == FName("EquipWeapon")) { bIsEquipped = true; SetAnimWeaponType(PossessedWeapon->GetWeaponType()); }
	else if (NotifyName == FName("UnEquipWeapon")) { bIsEquipped = false; SetAnimWeaponType(EWeaponType::UNARMED); }
}