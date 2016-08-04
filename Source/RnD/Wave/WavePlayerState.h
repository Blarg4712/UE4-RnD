// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "WavePlayerState.generated.h"

UCLASS()
class RND_API AWavePlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	void AddMoney(int32 Amount);

	UFUNCTION(BlueprintCallable, Category="Score")
	int32 GetMoney() const;

private:
	UPROPERTY(Replicated)
	int32 Money;
};
