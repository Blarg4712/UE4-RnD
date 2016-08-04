// Fill out your copyright notice in the Description page of Project Settings.

#include "RnD.h"
#include "WavePlayerState.h"
#include "Net/UnrealNetwork.h"

void AWavePlayerState::AddMoney(int32 Amount){
	Money += Amount;
}

int32 AWavePlayerState::GetMoney() const{
	return Money;
}

void AWavePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWavePlayerState, Money);
}
