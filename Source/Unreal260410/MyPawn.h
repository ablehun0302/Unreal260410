// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class UMyStaticMeshComponent;

UCLASS()
class UNREAL260410_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UBoxComponent> Box;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UStaticMeshComponent> Body;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UMyStaticMeshComponent> Left;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UMyStaticMeshComponent> Right;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UArrowComponent> Arrow;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UFloatingPawnMovement> FloatingMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Pitch(float Value);
	void Roll(float Value);
	void Fire();
	void Booster();
	void UnBoost();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data);
	float MoveSpeed = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data);
	float RotationSpeed = 60.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data);
	float BoostValue = 0.5f;
};
