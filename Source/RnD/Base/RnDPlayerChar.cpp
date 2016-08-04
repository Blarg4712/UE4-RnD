// Fill out your copyright notice in the Description page of Project Settings.

#include "RnD.h"
#include "RnDPlayerChar.h"
#include "InteractableActor.h"

ARnDPlayerChar::ARnDPlayerChar(){
	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamera"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	FPSCamera->AttachTo(RootComponent);
	CameraBoom->AttachTo(RootComponent);
	TPSCamera->AttachTo(CameraBoom);
	TPSCamera->bAutoActivate = false;

	bIsInFPS = true;
	bAllowInput = true;
	bCrouched = false;
	bCanInteract = false;

	TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), false, this);
	//GetCapsuleComponent()->InitCapsuleSize(DefaultCapsuleRadius, DefaultCapsuleHalfHeight);
}

void ARnDPlayerChar::SetupPlayerInputComponent(class UInputComponent* InputComponent){
	InputComponent->BindAxis("MoveForward", this, &ARnDPlayerChar::MoveFwd);
	InputComponent->BindAxis("MoveRight", this, &ARnDPlayerChar::MoveRight);
	InputComponent->BindAxis("LookYaw", this, &ARnDPlayerChar::LookYaw);
	InputComponent->BindAxis("LookPitch", this, &ARnDPlayerChar::LookPitch);
	InputComponent->BindAction("CameraSwitch", IE_Pressed, this, &ARnDPlayerChar::SwitchCamera);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &ARnDPlayerChar::MyCrouch);
	InputComponent->BindAction("Interact", IE_Pressed, this, &ARnDPlayerChar::Interact);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARnDPlayerChar::Jump);
}

void ARnDPlayerChar::BeginPlay(){
	Super::BeginPlay();
	SpeedCoeff = StandingSpeedCoeff;
}

void ARnDPlayerChar::Tick(float DeltaSeconds){
	Super::Tick(DeltaSeconds);
	if(Controller && Controller->IsLocalController()){
		Bearing = GetActorRotation().Yaw;
		HandleFocus();
		Pitch = Controller->GetControlRotation().Pitch;
		if(Pitch > 180) Pitch -= 360;
	}
}

void ARnDPlayerChar::HandleFocus(){
	AInteractableActor* Interactable = Cast<AInteractableActor>(GetFocusedActor());

	if(Interactable){
		if(Interactable != FocusedActor){
			if(FocusedActor) FocusedActor->OnEndFocus();
			Interactable->OnBeginFocus();
			FocusedActor = Interactable;
		}
	}
	else {
		if(FocusedActor) FocusedActor->OnEndFocus();
		FocusedActor = nullptr;
	}
}

AActor* ARnDPlayerChar::GetFocusedActor(){
	if(!Controller){
		return nullptr;
	}

	FVector CameraLocation;
	FRotator CameraRotation;
	FHitResult Hit(ForceInit);
	Controller->GetPlayerViewPoint(CameraLocation, CameraRotation);

	float DistanceCameraHead = FMath::Abs( (CameraLocation - GetMesh()->GetSocketLocation(HeadSocketName)).Size() );

	const FVector Start = CameraLocation;
	const FVector End = Start + (CameraRotation.Vector() * (InteractionDistance + DistanceCameraHead));

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, TraceParams);

	if(Hit.GetActor())
		return Hit.GetActor();
	else
		return nullptr;
}

void ARnDPlayerChar::MoveFwd(float val){
	if(bAllowInput){
		FRotator Rotation(0, GetControlRotation().Yaw, 0);
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, val*SpeedCoeff, false);
	}
}

void ARnDPlayerChar::MoveRight(float val){
	if(bAllowInput){
		FRotator Rotation(0, GetControlRotation().Yaw, 0);
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, val*SpeedCoeff, false);
	}
}

void ARnDPlayerChar::LookPitch(float val){
	if(bAllowInput){
		AddControllerPitchInput(val);
	}
}

void ARnDPlayerChar::LookYaw(float val){
	if(bAllowInput){
		AddControllerYawInput(val);
	}
}

void ARnDPlayerChar::SwitchCamera(){
	if(bAllowInput){
		if(bIsInFPS){
			bIsInFPS = false;
			FPSCamera->Deactivate();
			TPSCamera->Activate();
		}
		else{
			bIsInFPS = true;
			FPSCamera->Activate();
			TPSCamera->Deactivate();
		}
	}
}

void ARnDPlayerChar::MyCrouch(){
	if(bAllowInput){
		if(bCrouched){
			ExitCrouch();
		}
		else{
			EnterCrouch();
		}
	}
}

void ARnDPlayerChar::EnterCrouch(){
	GetCapsuleComponent()->SetCapsuleSize(CrouchedCapsuleRadius, CrouchedCapsuleHalfHeight, true);
	AddActorWorldOffset(FVector(0, 0, CrouchedCapsuleHalfHeight - DefaultCapsuleHalfHeight));
	FPSCamera->AddRelativeLocation(FVector(0, 0, CrouchedCapsuleHalfHeight - DefaultCapsuleHalfHeight));
	CameraBoom->AddRelativeLocation(FVector(0, 0, CrouchedCapsuleHalfHeight - DefaultCapsuleHalfHeight));
	GetMesh()->AddRelativeLocation(FVector(0, 0, DefaultCapsuleHalfHeight - CrouchedCapsuleHalfHeight));
	SpeedCoeff = CrouchedSpeedCoeff;
	bCrouched = true;
}

void ARnDPlayerChar::ExitCrouch(){
	FHitResult Hit(ForceInit);
	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0, 0, CrouchedCapsuleHalfHeight + DefaultCapsuleRadius);
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	if(!Hit.bBlockingHit){
		GetCapsuleComponent()->SetCapsuleSize(DefaultCapsuleRadius, DefaultCapsuleHalfHeight, true);
		AddActorWorldOffset(FVector(0, 0, DefaultCapsuleHalfHeight - CrouchedCapsuleHalfHeight));
		FPSCamera->AddRelativeLocation(FVector(0, 0, DefaultCapsuleHalfHeight - CrouchedCapsuleHalfHeight));
		CameraBoom->AddRelativeLocation(FVector(0, 0, DefaultCapsuleHalfHeight - CrouchedCapsuleHalfHeight));
		GetMesh()->AddRelativeLocation(FVector(0, 0, CrouchedCapsuleHalfHeight - DefaultCapsuleHalfHeight));
		SpeedCoeff = StandingSpeedCoeff;
		bCrouched = false;
	}
}

void ARnDPlayerChar::Interact(){
	if(bAllowInput){
		AActor* Focused = GetFocusedActor();
		if(Focused){
			if(Focused->IsA(AInteractableActor::StaticClass())){
				AInteractableActor* Interactable = Cast<AInteractableActor>(Focused);
				Interactable->OnInteract(this);
			}
			else if (Focused->IsA(AInteractableChar::StaticClass())) {
				AInteractableChar* Interactable = Cast<AInteractableChar>(Focused);
				Interactable->OnInteract(this);
			}
		}
	}
}

void ARnDPlayerChar::Jump(){
	if(GetCharacterMovement()->IsMovingOnGround()){
		GetCharacterMovement()->DoJump(true);
		bJumping = true;
	}
}
