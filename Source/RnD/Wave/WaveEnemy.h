// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/InteractableChar.h"
#include "WaveEnemy.generated.h"

UCLASS()
class RND_API AWaveEnemy : public AInteractableChar
{
	GENERATED_BODY()
public:
	virtual void OnInteract_Implementation(AActor* Caller) override;

};
