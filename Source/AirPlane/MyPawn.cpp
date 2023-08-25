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
	//Tick을 쓰면 느리니깐 안쓰면 false로 바꾸면 됨.
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//메모리에 박스 컨포넌트가 생긴 것.
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	//맨 위 근본. Root로 설정
	RootComponent = Box;

	//이미 만들었기 때문에 블루프린트 값은 바뀌지 않는다. (다시 생성해야 바뀜)
	Box->SetBoxExtent(FVector(20, 20, 20));

	

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	//메뉴 테이블 할때 무조건 시작할때 읽으라고 하는 경우가 있다. (하드코드)
	// Load Mesh
	// 처음 불러오고 다시는 안불러오게
	// 자료형.  ConstructorHelpers::FObjectFinder<UStaticMesh> <- 여기까지가 자료형.
	// 생성할때마다 로딩을 계속한다. 그래서 static을 넣으면 한번만 한다.
	// CDO만드는거라 beginplay에 넣으면 꺼진다.
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

	// dynamic_cast<>   자식으로 바꿔달라 / 근데 느려서 자체적으로 만듬.

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
	//this-> 는 생략 가능
	//double로 바뀐 이유는 영상쪽 때문이라고 함.
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	this->AddActorLocalRotation(FRotator(Value*DeltaSeconds*60.0f, 0, 0));

	//합칠 수 있음
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
	//Get 뒤에 인자처럼 갖고올 수 있다.
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

