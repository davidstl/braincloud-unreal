// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "BrainCloudComms.h"
#include "ServerCall.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BrainCloud.h"
#include "BrainCloudCallbackHandler.h"

UBrainCloudCallbackHandler::UBrainCloudCallbackHandler(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UBrainCloudCallbackHandler::BeginDestroy()
{
	BrainCloudWrapper * bc = UBCWrapperProxy::GetBrainCloudInstance(_brainCloud);

    BrainCloudComms * comms = bc->getBCClient()->getBrainCloudComms();
    if (comms != nullptr)
    {
        if (comms->IsEventCallback(this)) comms->DeregisterEventCallback();
        if (comms->IsFileUploadCallback(this)) comms->DeregisterFileUploadCallback();
        if (comms->IsRewardCallback(this)) comms->DeregisterRewardCallback();
        if (comms->IsGlobalErrorCallback(this)) comms->DeregisterGlobalErrorCallback();
        if (comms->IsNetworkErrorCallback(this)) comms->DeregisterNetworkErrorCallback();
    }
	
    Super::BeginDestroy();
}

void UBrainCloudCallbackHandler::RegisterCallbacks(ABrainCloud* brainCloud, bool fileCallbacks, bool rewardCallback, bool eventCallback, bool globalErrorCallback, bool networkErrorCallback)
{
	_brainCloud = brainCloud;

	BrainCloudWrapper * bc = UBCWrapperProxy::GetBrainCloudInstance(brainCloud);

    if (fileCallbacks) bc->getBCClient()->registerFileUploadCallback(this);
    if (rewardCallback) bc->getBCClient()->registerRewardCallback(this);
    if (eventCallback) bc->getBCClient()->registerEventCallback(this);
    if (globalErrorCallback) bc->getBCClient()->registerGlobalErrorCallback(this);
    if (networkErrorCallback) bc->getBCClient()->registerNetworkErrorCallback(this);
}

void UBrainCloudCallbackHandler::fileUploadCompleted(const FString& fileUploadId, const FString& jsonResponse)
{
    FileUploadComplete.Broadcast(fileUploadId, jsonResponse);
}

void UBrainCloudCallbackHandler::fileUploadFailed(const FString& fileUploadId, int32 statusCode, int32 reasonCode, const FString& jsonResponse)
{
    FileUploadFailed.Broadcast(fileUploadId, statusCode, reasonCode, jsonResponse);
}

void UBrainCloudCallbackHandler::rewardCallback(const FString& jsonData)
{
    RewardCallback.Broadcast(jsonData);
}

void UBrainCloudCallbackHandler::eventCallback(const FString& jsonData)
{
    EventCallback.Broadcast(jsonData);
}

void UBrainCloudCallbackHandler::globalError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    GlobalErrorCallback.Broadcast(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode, jsonError);
}

void UBrainCloudCallbackHandler::networkError()
{
    NetworkErrorCallback.Broadcast();
}

