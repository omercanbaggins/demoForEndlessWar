// Fill out your copyright notice in the Description page of Project Settings.
// omercandmrc

#include "PawnBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PrimitiveSoldier.h"
#include "OverlappingObjects.h"
#include "Components/BoxComponent.h"
#include "OverlapRespond.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon.h"

APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;
	ChildfirstSoldier = CreateDefaultSubobject<UChildActorComponent>(FName("asker1"));
	cam = CreateDefaultSubobject<UCameraComponent>(FName("cam"));
	cmboom = CreateDefaultSubobject<USpringArmComponent>(FName("ip"));
	sphere = CreateDefaultSubobject<UBoxComponent>(FName("col"));

	SetRootComponent(sphere);

	cmboom->SetupAttachment(ChildfirstSoldier);
	cam->SetupAttachment(cmboom);
	ChildfirstSoldier->SetupAttachment(GetRootComponent());

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;
}

TArray<UChildActorComponent*> childactors;
TArray<UActorComponent*> Comps;

FVector APawnBase::getLoc() const
{
	return tempVec;
}

void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	StartVectorY = GetActorLocation().Y;
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	ChildfirstSoldier->SetChildActorClass(childSoldierclass);
	sphere->OnComponentBeginOverlap.AddDynamic(this, &APawnBase::OnComponentBeginOverlap);
	tempVec = FVector(0);
	/*
	Comps = (GetComponentsByClass(childactorClass));
	for(int j =0;j<Comps.Num();j++){
		childactors.Add(Cast<UChildActorComponent>(Comps[j]));

	}
	//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::FromInt(childactors.Num()), true);
	//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString(childactors[0]->GetChildActorClass()->GetName()), true);
	*/
}

void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(GetActorForwardVector()/3);
	StartVectorY = GetActorLocation().Y;
	tempVec = GetActorLocation();
}

void APawnBase::slide(float V){
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::SanitizeFloat(V), true);

	if ((StartVectorY) > 225 && V > 0);
	else if ((StartVectorY) <-225 && V < 0);
	else AddMovementInput(GetActorRightVector() * V);
}

void APawnBase::ZoomInZoomOut(float V){
	if ((cmboom->TargetArmLength + 25 * V > 700) || (cmboom->TargetArmLength +25 * V < 200));
	else cmboom->TargetArmLength +=25*V;
}

void APawnBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult){

	IOverlapRespond* overlappedActor = Cast<IOverlapRespond>(OtherActor); //cast interface 
	if (overlappedActor) {
		Destroy();
	}
	else {
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("castFailed"), true);
	}
}
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("slide"), this, &APawnBase::slide); //for moving
	PlayerInputComponent->BindAxis(FName("Zoom"),  this, &APawnBase::ZoomInZoomOut); //camera Zoom in Zoom out
	PlayerInputComponent->BindAxis(FName("Rotate"), this, &APawnBase::rotatePlayer);
}
void APawnBase::rotatePlayer(float V) {
	//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::SanitizeFloat(V), true);
	//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::FromInt(ChildfirstSoldier->GetComponentRotation().Yaw), true);

	if ((ChildfirstSoldier->GetComponentRotation().Yaw > 50 && V > 0)); //do nothing
	else if ((ChildfirstSoldier->GetComponentRotation().Yaw < -50 && V < 0)); // do nothing
	else ChildfirstSoldier->AddLocalRotation(FRotator(0, 3 * V, 0));
}

//TSubclassOf<class AWeapon> weaponClass;
//APrimitiveSoldier* tempW;
//AWeapon* weaponTemp;

//void APawnBase::changeWeaponParams(FName nameROW) //it will change iteratively all weapons of child soldier class.
//{
	/*if ((childactors.Num() > 0)) { // check if array is valid or not
		for (int i = 0; i < childactors.Num() && childactors[i]; i++) {
			tempW = Cast<APrimitiveSoldier>(childactors[i]->GetChildActor());
			if (tempW) {
				//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::FromInt(tempW->a), true);
				//since child actors array's type is UActorComponent, we need to cast it to Child actor component
				weaponTemp = Cast<AWeapon>(tempW->childWeapon->GetChildActor());
				if (weaponTemp) {
					weaponTemp->setWeaponType(nameROW);
					GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("succeed"), true);

					// it will invoke function which calls struct members to replace veriables of weapon.
				}
			}
			else {

			}
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("arrayyok"), true);

	}
}*/
//}

