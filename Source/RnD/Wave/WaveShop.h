// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/InteractableActor.h"
#include "WaveShop.generated.h"

UCLASS()
class RND_API AWaveShop : public AInteractableActor
{
	GENERATED_BODY()
public:
	virtual void OnInteract_Implementation(AActor* Caller) override;
};
