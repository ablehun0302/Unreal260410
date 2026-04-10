// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStaticMeshComponent.h"

UMyStaticMeshComponent::UMyStaticMeshComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/Plane/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		SetStaticMesh(SM_Propeller.Object);
	}
}

void UMyStaticMeshComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	AddRelativeRotation(FRotator(0.0f, 0.0f, 1800.0f * DeltaTime));
}