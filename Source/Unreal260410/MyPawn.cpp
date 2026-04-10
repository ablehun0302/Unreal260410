// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "MyStaticMeshComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(40.0f, 44.2f, 12.4f));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/Plane/Meshes/SM_P38_Body.SM_P38_Body'"));

	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Left = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);
	Right = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Left->SetRelativeLocation(FVector(37.35f, 21.0f, 1.18f));
	Right->SetRelativeLocation(FVector(37.35f, -21.0f, 1.18f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(85.0f, 0.0f, 0.0f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 30.0f);
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	FloatingMovement->MaxSpeed = 1000.0f;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPawn::Pitch(float Value)
{
	AddActorLocalRotation(FRotator(RotationSpeed * Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0.0f, 0.0f));
}

void AMyPawn::Roll(float Value)
{
	AddActorLocalRotation(FRotator(0.0f, 0.0f, RotationSpeed * Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}

void AMyPawn::Fire()
{
}

void AMyPawn::Booster()
{
}

void AMyPawn::UnBoost()
{
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector());
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);
	PlayerInputComponent->BindAction(TEXT("Fire"),EInputEvent::IE_Pressed, this, &AMyPawn::Fire);
	PlayerInputComponent->BindAction(TEXT("Booster"),EInputEvent::IE_Pressed, this, &AMyPawn::Booster);
	PlayerInputComponent->BindAction(TEXT("Boost"), EInputEvent::IE_Released, this, &AMyPawn::UnBoost);
}