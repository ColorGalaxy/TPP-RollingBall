// Fill out your copyright notice in the Description page of Project Settings.

#include "BiliCodeGameModeBase.h"
#include "Engine.h"
#include "Player/SphereBase.h"

ABiliCodeGameModeBase::ABiliCodeGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;//����Tick,Ĭ�ϲ�����

	DeathSum = 0;
	IsEnd = false;
}

void ABiliCodeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//GetWorld()->GetFirstPlayerController()->GetPawn();//�ҵ���һ����ҿ�����
	ASphereBase * Pawn = Cast<ASphereBase>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Pawn)//��ȡ���ٸ�ֵ���Ƚϰ�ȫ
	{
		PlayerPawn = Pawn;
		StartPosition = PlayerPawn->GetActorLocation();//��ʼ�������
		//CameraStartPos = PlayerPawn->CameraArmComp->RelativeLocation; ��������
	}
}

void ABiliCodeGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, StartPosition.ToString());//������ʾ������Ϣ
}


void ABiliCodeGameModeBase::SetPlayerLocation()
{
	//PlayerPawn->SetActorLocation(StartPosition);//����С�򣨸��ڵ㣩λ��
	PlayerPawn->SphereMeshComp->SetRelativeLocation(StartPosition);//����С��λ��
	//FVector NewLocation = PlayerPawn->SphereMeshComp->GetRelativeTransform().GetLocation() - StartPosition;��������
	//PlayerPawn->CameraArmComp->SetRelativeLocation(CameraStartPos);��������
	PlayerPawn->SphereMeshComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));//�ٶȹ���
	PlayerPawn->SphereMeshComp->SetPhysicsAngularVelocity(FVector(0, 0, 0));
	DeathSum++;
}

void ABiliCodeGameModeBase::SetStartPosition(FVector Location)
{
	if (Location != FVector(0, 0, 0))
	{
		StartPosition = Location;
		//CameraStartPos = PlayerPawn->CameraArmComp->RelativeLocation;��������
	}
}

void ABiliCodeGameModeBase::SetPlayerInput(bool isInput)//�޸�����ܷ�����
{
	PlayerPawn->IsInput = isInput;
	if (!isInput)//�ж������������Ϸ����
	{
		IsEnd = true;
	}
	PlayerPawn->SphereMeshComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));//�ٶȹ���
	PlayerPawn->SphereMeshComp->SetPhysicsAngularVelocity(FVector(0, 0, 0));
}

