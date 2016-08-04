// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "RnD.h"
#include "InteractableChar.generated.h"

UCLASS()
class RND_API AInteractableChar : public ACharacter
{
	GENERATED_BODY()

public:
	AInteractableChar();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
    void OnInteract(AActor* Caller);
    virtual void OnInteract_Implementation(AActor* Caller);

	void OnBeginFocus();
	void OnEndFocus();
	void SetCanInteract(bool newCanInteract);

	int32 GetMoneyReward() const;

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	uint32 bCanInteract : 1;

	UPROPERTY(EditDefaultsOnly)
	EStencilColor StencilColor;

	UPROPERTY(EditDefaultsOnly)
	int32 MoneyReward;

private:
	TArray<UMeshComponent*> Meshes;
};
