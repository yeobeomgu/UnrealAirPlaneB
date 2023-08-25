// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyActorComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"




// Sets default values
AMyPawn::AMyPawn()
{
	//Tick�� ���� �����ϱ� �Ⱦ��� false�� �ٲٸ� ��.
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�޸𸮿� �ڽ� ������Ʈ�� ���� ��.
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	//�� �� �ٺ�. Root�� ����
	RootComponent = Box;

	//�̹� ������� ������ �������Ʈ ���� �ٲ��� �ʴ´�. (�ٽ� �����ؾ� �ٲ�)
	Box->SetBoxExtent(FVector(20, 20, 20));

	

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	//�޴� ���̺� �Ҷ� ������ �����Ҷ� ������� �ϴ� ��찡 �ִ�. (�ϵ��ڵ�)
	// Load Mesh
	// ó�� �ҷ����� �ٽô� �Ⱥҷ�����
	// �ڷ���.  ConstructorHelpers::FObjectFinder<UStaticMesh> <- ��������� �ڷ���.
	// �����Ҷ����� �ε��� ����Ѵ�. �׷��� static�� ������ �ѹ��� �Ѵ�.
	// CDO����°Ŷ� beginplay�� ������ ������.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}


	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);
	Left->SetRelativeLocation(FVector(37.f, - 20.f,1.f));

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Right->SetRelativeLocation(FVector(37.f, 20.f,1.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);

	}
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	MyActorComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("MyActorComponent"));

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("beginplay"));
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), BoostValue);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// dynamic_cast<>   �ڽ����� �ٲ�޶� / �ٵ� ������ ��ü������ ����.

	// if(EnhancedInputComponent) -> IsVaild
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("bind"));
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedBoost);
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AMyPawn::EnhancedUnBoost);
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedFire);
		EnhancedInputComponent->BindAction(IA_PitchAndRoll, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedPitchAndRoll);


	}
	
	


	
}

void AMyPawn::Pitch(float Value)
{
	//this-> �� ���� ����
	//double�� �ٲ� ������ ������ �����̶�� ��.
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	this->AddActorLocalRotation(FRotator(Value*DeltaSeconds*60.0f, 0, 0));

	//��ĥ �� ����
	//AddActorLocalRotation(FRotator(Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f, 0, 0));


}

void AMyPawn::Roll(float Value)
{
	//AddActorLocalRotation(FRotator(0, 0, Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f));

}

void AMyPawn::Fire()
{
	//GetWorld()->SpawnActor<>();
}

void AMyPawn::Boost()
{
	
}

void AMyPawn::UnBoost()
{
}



// #include "InputActionValue.h"
void AMyPawn::EnhancedBoost(const FInputActionValue& Value)
{
	//Get �ڿ� ����ó�� ����� �� �ִ�.
	//Value.Get<bool>()
	BoostValue = 5.0f;
	UE_LOG(LogTemp, Warning, TEXT("Hi"));
}

void AMyPawn::EnhancedUnBoost(const FInputActionValue& Value)
{
	BoostValue = 0.5f;
}

void AMyPawn::EnhancedFire(const FInputActionValue& Value)
{
	//GetWorld()->SpawnActor<>();
}

void AMyPawn::EnhancedPitchAndRoll(const FInputActionValue& Value)
{

}

