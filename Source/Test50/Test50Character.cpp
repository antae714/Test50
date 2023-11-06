// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test50Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "FSMBlueprint.h"
#include "FiniteStateMachine.h"

//////////////////////////////////////////////////////////////////////////
// ATest50Character

ATest50Character::ATest50Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATest50Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ATest50Character::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ATest50Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ATest50Character::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ATest50Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATest50Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATest50Character::TouchStopped);
}

void ATest50Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ATest50Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ATest50Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ATest50Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ATest50Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		UAnimInstance* animinstance = GetMesh()->GetAnimInstance();
		UClass* animclass1 = GetMesh()->GetAnimInstance()->GetClass();
		UBlueprintGeneratedClass* animclass2 = Cast<UBlueprintGeneratedClass>(animclass1);
		UAnimBlueprintGeneratedClass* animclass3 = Cast<UAnimBlueprintGeneratedClass>(animclass1);
		UObject* obj = animclass3->GetOuter();

		UField* animgraph = animclass1->GetSuperStruct()->Children;
		UFunction* animgraphFunc = Cast<UFunction>(animgraph);
		FProperty* tempppp = animgraphFunc->GetReturnProperty();

		TFieldIterator<FProperty> It(animgraphFunc);
		
		UObject* temp = m_FiniteStateMachine.GetDefaultObject();
		UObject* temp2 = m_FiniteStateMachine2.GetDefaultObject();
		UObject* temp_ = m_FiniteStateMachine.Get();
		UObject* temp2_ = m_FiniteStateMachine2.Get();
		UClass* tempclass = temp->GetClass();

		UClass* temp_Owner = Cast<UBlueprintGeneratedClass>(temp_)->GetOwnerClass();
		UStruct* temp_Owner2 = Cast<UBlueprintGeneratedClass>(temp_)->GetOwnerStruct();
		
		UClass* thisclass = this->GetClass();
		
		FProperty* NewVar_0prop = thisclass->FindPropertyByName(TEXT("NewVar_0"));
		UFunction* TESTFunction = thisclass->FindFunctionByName(TEXT("TESTFunction"));

		int a = 5;

		a = CastField<FIntProperty>(NewVar_0prop)->GetPropertyValue_InContainer(this, 0);
		ProcessEvent(TESTFunction, nullptr);
		a = CastField<FIntProperty>(NewVar_0prop)->GetPropertyValue_InContainer(this, 0);



		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);


	}
}

void ATest50Character::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
