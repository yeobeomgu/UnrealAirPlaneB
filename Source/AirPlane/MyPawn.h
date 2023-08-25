// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

//전방선언 하기 어렵다. (포인터로 받는애들만 전방선언으로 받는다)
#include "InputActionValue.h"
#include "MyPawn.generated.h"
//MyPawn.generated.h 위에 include해야함.

class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UFloatingPawnMovement;
class UMyActorComponent;

UCLASS()
class AIRPLANE_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Visible이면 보이기만 하는건데 다른 설정들이 바뀔 수 있는건 UBoxComponent안에 속성들 값이 그렇게 설정되어 있어서임.
	// BlueprintReadOnly Get만 나옴
	// BlueprintReadWrite 하면 둘다 나온다.
	// show Inherited Varied 하면 숨겨진 변수들이 뜬다. 
	// 컴포넌트는 get만 쓴다. (초기화 되면 안되니깐)

	// public이 아닐때 외부에서 쓰기위해 meta를 쓰면 됨.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UBoxComponent* Box;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Body;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Left;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Right;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UFloatingPawnMovement* Movement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UMyActorComponent* MyActorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float PropellerRotationSpeed = 3060;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float BoostValue = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Gold = 100;

	//UFUNCTION X
	void Pitch(float Value);
	
	void Roll(float Value);

	void Fire();
	void Boost();
	void UnBoost();

	// Digital, Axis1D, Axis2D, Axis3D를 전부 불러올 수 있게 const FInputActionValue&에 넣어둠
	void EnhancedBoost(const FInputActionValue& Value);

	void EnhancedUnBoost(const FInputActionValue& Value);

	void EnhancedFire(const FInputActionValue& Value);

	void EnhancedPitchAndRoll(const FInputActionValue& Value);



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	class UInputAction* IA_Boost;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_PitchAndRoll;


};


