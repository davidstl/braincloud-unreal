// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BCAsyncMatchProxy.h"
#include "BCWrapperProxy.h"
#include "BrainCloudClient.h"
#include "ServiceName.h"
#include "BrainCloudWrapper.h"
#include "ServiceOperation.h"

UBCAsyncMatchProxy::UBCAsyncMatchProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::CreateMatch(ABrainCloud *brainCloud, FString jsonOpponentIds, FString pushNotificationMessage)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getAsyncMatchService()->createMatch(jsonOpponentIds, pushNotificationMessage, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::CreateMatchWithInitialTurn(ABrainCloud *brainCloud, FString jsonOpponentIds, FString jsonMatchState, FString pushNotificationMessage,
    FString nextPlayer, FString jsonSummary)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getAsyncMatchService()->createMatchWithInitialTurn(jsonOpponentIds, jsonMatchState, pushNotificationMessage, nextPlayer, jsonSummary, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::SubmitTurn(ABrainCloud *brainCloud, FString ownerId, FString matchId, int32 version, FString jsonMatchState, FString pushNotificationMessage,
    FString nextPlayer, FString jsonSummary, FString jsonStatistics)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getAsyncMatchService()->submitTurn(ownerId, matchId, version, jsonMatchState, pushNotificationMessage, nextPlayer, jsonSummary, jsonStatistics, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::UpdateMatchSummaryData(ABrainCloud *brainCloud, FString ownerId, FString matchId, int32 version, FString jsonSummary)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getAsyncMatchService()->updateMatchSummaryData(ownerId, matchId, version, jsonSummary, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::CompleteMatch(ABrainCloud *brainCloud, FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getAsyncMatchService()->completeMatch(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::ReadMatch(ABrainCloud *brainCloud, FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getAsyncMatchService()->readMatch(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::ReadMatchHistory(ABrainCloud *brainCloud, FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getAsyncMatchService()->readMatchHistory(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::FindMatches(ABrainCloud *brainCloud)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getAsyncMatchService()->findMatches(Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::FindCompleteMatches(ABrainCloud *brainCloud)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getAsyncMatchService()->findCompleteMatches(Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::AbandonMatch(ABrainCloud *brainCloud, FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getAsyncMatchService()->abandonMatch(ownerId, matchId, Proxy);
    return Proxy;
}

UBCAsyncMatchProxy* UBCAsyncMatchProxy::DeleteMatch(ABrainCloud *brainCloud, FString ownerId, FString matchId)
{
    UBCAsyncMatchProxy* Proxy = NewObject<UBCAsyncMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getAsyncMatchService()->deleteMatch(ownerId, matchId, Proxy);
    return Proxy;
}

//callbacks
void UBCAsyncMatchProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCAsyncMatchProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

