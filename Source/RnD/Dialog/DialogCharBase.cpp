// Fill out your copyright notice in the Description page of Project Settings.

#include "RnD.h"
#include "DialogCharBase.h"


FDialogData ADialogCharBase::getDialogRowData(int32 RowID)
{
	FDialogData* Result = DialogDataTable->FindRow<FDialogData>(*FString::Printf(TEXT("%d"), RowID), "", true);
	if (Result) {
		return *Result;
	}
	else {
		return FDialogData();
	}
}

ADialogCharBase::ADialogCharBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADialogCharBase::BeginPlay()
{
	Super::BeginPlay();

}

void ADialogCharBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADialogCharBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ADialogCharBase::OnInteract_Implementation(AActor* Caller){

}
