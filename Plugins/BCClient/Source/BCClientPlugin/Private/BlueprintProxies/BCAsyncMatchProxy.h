// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"

#include "BCAsyncMatchProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCAsyncMatchProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCAsyncMatchProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Creates an instance of an asynchronous match.
    *
    * Service Name - AsyncMatch
    * Service Operation - Create
    *
    * Param - jsonOpponentIds  JSON string identifying the opponent platform and id for this match.
    *
    * Platforms are identified as:
    * BC - a brainCloud profile id
    * FB - a Facebook id
    *
    * An example of this string would be:
    * [
    *     {
    *         "platform": "BC",
    *         "id": "some-braincloud-profile"
    *     },
    *     {
    *         "platform": "FB",
    *         "id": "some-facebook-id"
    *     }
    * ]
    *
    * Param - pushNotificationMessage Optional push notification message to send to the other party.
    *  Refer to the Push Notification functions for the syntax required.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
        static UBCAsyncMatchProxy* CreateMatch(ABrainCloud *brainCloud, FString jsonOpponentIds, FString pushNotificationMessage);

    /**
    * Creates an instance of an asynchronous match with an initial turn.
    *
    * Service Name - AsyncMatch
    * Service Operation - Create
    *
    * Param - jsonOpponentIds  JSON string identifying the opponent platform and id for this match.
    *
    * Platforms are identified as:
    * BC - a brainCloud profile id
    * FB - a Facebook id
    *
    * An exmaple of this string would be:
    * [
    *     {
    *         "platform": "BC",
    *         "id": "some-braincloud-profile"
    *     },
    *     {
    *         "platform": "FB",
    *         "id": "some-facebook-id"
    *     }
    * ]
    *
    * Param - jsonMatchState    JSON string blob provided by the caller
    * Param - pushNotificationMessage Optional push notification message to send to the other party.
    * Refer to the Push Notification functions for the syntax required.
    * Param - nextPlayer Optionally, force the next player player to be a specific player
    * Param - jsonSummary Optional JSON string defining what the other player will see as a summary of the game when listing their games
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
        static UBCAsyncMatchProxy* CreateMatchWithInitialTurn(ABrainCloud *brainCloud, FString jsonOpponentIds, FString jsonMatchState,
            FString pushNotificationMessage, FString nextPlayer, FString jsonSummary);

    /**
    * Submits a turn for the given match.
    *
    * Service Name - AsyncMatch
    * Service Operation - SubmitTurn
    *
    * Param - ownerId Match owner identfier
    * Param - matchId Match identifier
    * Param - version Game state version to ensure turns are submitted once and in order
    * Param - jsonMatchState JSON string provided by the caller
    * Param - pushNotificationMessage Optional push notification message to send to the other party.
    *  Refer to the Push Notification functions for the syntax required.
    * Param - nextPlayer Optionally, force the next player player to be a specific player
    * Param - jsonSummary Optional JSON string that other players will see as a summary of the game when listing their games
    * Param - jsonStatistics Optional JSON string blob provided by the caller
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
        static UBCAsyncMatchProxy* SubmitTurn(ABrainCloud *brainCloud, FString ownerId, FString matchId, int32 version, FString jsonMatchState, FString pushNotificationMessage,
        FString nextPlayer, FString jsonSummary, FString jsonStatistics);

    /**
    * Allows the current player (only) to update Summary data without having to submit a whole turn.
    *
    * Service Name - AsyncMatch
    * Service Operation - UpdateMatchSummary
    *
    * Param - ownerId Match owner identfier
    * Param - matchId Match identifier
    * Param - version Game state version to ensure turns are submitted once and in order
    * Param - jsonSummary JSON string that other players will see as a summary of the game when listing their games
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
        static UBCAsyncMatchProxy* UpdateMatchSummaryData(ABrainCloud *brainCloud, FString ownerId, FString matchId, int32 version, FString jsonSummary);

    /**
    * Marks the given match as complete.
    *
    * Service Name - AsyncMatch
    * Service Operation - Complete
    *
    * Param - ownerId Match owner identifier
    * Param - matchId Match identifier
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
        static UBCAsyncMatchProxy* CompleteMatch(ABrainCloud *brainCloud, FString ownerId, FString matchId);

    /**
    * Returns the current state of the given match.
    *
    * Service Name - AsyncMatch
    * Service Operation - ReadMatch
    *
    * Param - ownerId   Match owner identifier
    * Param - matchId   Match identifier
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
        static UBCAsyncMatchProxy* ReadMatch(ABrainCloud *brainCloud, FString ownerId, FString matchId);

    /**
    * Returns the match history of the given match.
    *
    * Service Name - AsyncMatch
    * Service Operation - ReadMatchHistory
    *
    * Param - ownerId   Match owner identifier
    * Param - matchId   Match identifier
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
        static UBCAsyncMatchProxy* ReadMatchHistory(ABrainCloud *brainCloud, FString ownerId, FString matchId);

    /**
    * Returns all matches that are NOT in a COMPLETE state for which the player is involved.
    *
    * Service Name - AsyncMatch
    * Service Operation - FindMatches
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
        static UBCAsyncMatchProxy* FindMatches(ABrainCloud *brainCloud);

    /**
    * Returns all matches that are in a COMPLETE state for which the player is involved.
    *
    * Service Name - AsyncMatch
    * Service Operation - FindMatchesCompleted
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
        static UBCAsyncMatchProxy* FindCompleteMatches(ABrainCloud *brainCloud);

    /**
    * Marks the given match as abandoned.
    *
    * Service Name - AsyncMatch
    * Service Operation - Abandon
    *
    * The JSON returned in the callback is as follows:
    * {
    *     "status": 200,
    *     "data": {}
    * }
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
        static UBCAsyncMatchProxy* AbandonMatch(ABrainCloud *brainCloud, FString ownerId, FString matchId);

    /**
    * Removes the match and match history from the server. DEBUG ONLY, in production it is recommended
    *   the user leave it as completed.
    *
    * Service Name - AsyncMatch
    * Service Operation - Delete
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
        static UBCAsyncMatchProxy* DeleteMatch(ABrainCloud *brainCloud, FString ownerId, FString matchId);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

	UPROPERTY()
		ABrainCloud *BrainCloudRef;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
