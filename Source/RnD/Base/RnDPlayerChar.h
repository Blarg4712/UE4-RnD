// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableChar.h"
#include "RnDPlayerChar.generated.h"

UCLASS()
class RND_API ARnDPlayerChar : public AInteractableChar
{
	GENERATED_BODY()
public:
    ARnDPlayerChar();

    virtual void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Interaction
	AActor* GetFocusedActor();
	void HandleFocus();

	//Inputs
	void MoveFwd(float val);
	void MoveRight(float val);
	void LookPitch(float val);
	void LookYaw(float val);
	void SwitchCamera();
	void MyCrouch();
	void EnterCrouch();
	void ExitCrouch();
	void Interact();
	void Jump();

protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCamera;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* TPSCamera;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

private:
	UPROPERTY(BlueprintReadOnly, Category="Navigation", meta=(AllowPrivateAccess="true"))
	float Bearing;
	float Pitch;
	float SpeedCoeff;
	class AInteractableActor* FocusedActor;
	uint32 bIsInFPS : 1;
	UPROPERTY(BlueprintReadWrite, Category="State", meta=(AllowPrivateAccess="true"))
	uint32 bAllowInput : 1;
	UPROPERTY(BlueprintReadOnly, Category="State", meta=(AllowPrivateAccess="true"))
	uint32 bCrouched : 1;
	UPROPERTY(BlueprintReadWrite, Category="State", meta=(AllowPrivateAccess="true"))
	uint32 bJumping : 1;

	UPROPERTY(EditDefaultsOnly)
	float DefaultCapsuleHalfHeight;
	UPROPERTY(EditDefaultsOnly)
	float DefaultCapsuleRadius;
	UPROPERTY(EditDefaultsOnly)
	float CrouchedCapsuleHalfHeight;
	UPROPERTY(EditDefaultsOnly)
	float CrouchedCapsuleRadius;
	UPROPERTY(EditDefaultsOnly)
	float StandingSpeedCoeff;
	UPROPERTY(EditDefaultsOnly)
	float CrouchedSpeedCoeff;
	UPROPERTY(EditDefaultsOnly)
	FName HeadSocketName;
	UPROPERTY(EditDefaultsOnly)
	float InteractionDistance;

	FCollisionQueryParams TraceParams;
};
