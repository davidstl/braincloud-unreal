// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCClientProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCClientProxy : public UObject
{
	GENERATED_BODY()

public:
	UBCClientProxy(const FObjectInitializer& ObjectInitializer);

	/**
	* Set Soft Error Handling Mode. Disabled by default
	* If enabled, brainCloud will Log errors without an editor crash 
	*
	* Param - isEnabled The state of the soft error handling
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void SoftErrorHandlingMode(
			const bool isEnabled);

	/**
	* Set whether the brainCloud singleton should be able to be used
	* Disabling it will log a Error or Fatal log based on SoftErrorHandlingMode
	*
	* Param - isEnabled The state of the singleton usage mode
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void SingletonMode(
			const bool isEnabled);

	/**
	* Method initializes the BrainCloudClient.
	*
	* Param - serverURL The url to the brainCloud server
	* Param - secretKey The secret key for your app
	* Param - appId The app's id
	* Param - version The app's version
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void Initialize(
			ABrainCloud *brainCloud, 
			const FString& serverUrl = "https://sharedprod.braincloudservers.com/dispatcherv2",
			const FString& secretKey = "",
			const FString& appId = "",
			const FString& version = "1.0.0");

	/**
	* Initialize - initializes the identity service with the saved
	* anonymous installation id and most recently used profile id
	*
	* Param - profileId The id of the profile id that was most recently used by the app (on this device)
	* Param - anonymousId  The anonymous installation id that was generated for this device
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void InitializeIdentity(ABrainCloud *brainCloud, const FString& profileId, const FString& anonymousId);

	/**
	* Run callbacks, to be called once per frame from your main thread
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void RunCallbacks(ABrainCloud *brainCloud);

	/**
	* @deprecated This method has been implemented improperly,
	*
	* Remove BluePrints using it.
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void RestoreRecentSession(const FString& sessionId);

	/**
	* Set to true to enable logging packets to the output log
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void EnableLogging(ABrainCloud *brainCloud, bool shouldEnable);

	/**
	* Returns whether the client is authenticated with the brainCloud server.
	*
	* Return - True if authenticated, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static bool IsAuthenticated(ABrainCloud *brainCloud);

	/**
	* Returns whether the client is initialized.
	*
	* Return - True if initialized, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static bool IsInitialized(ABrainCloud *brainCloud);

	/**
	* Clears any pending messages from communication library.
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void ResetCommunication(ABrainCloud *brainCloud);

	/**
	* Send an empty message to the server, which essentially polls the
	* server for any new events to send to this client.
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void Heartbeat(ABrainCloud *brainCloud);

	//Setters

	/**
	* Set an interval in ms for which the BrainCloud will contact the server
	* and receive any pending events
	* Param - intervalInMilliseconds - The time between heartbeats in milliseconds
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void SetHeartbeatInterval(ABrainCloud *brainCloud, int32 intervalInMilliseconds);

	/**
	* Sets the packet timeouts using a list of integers that
	* represent timeout values in seconds for each packet retry. The
	* first item in the list represents the timeout for the first packet
	* attempt, the second for the second packet attempt, and so on.
	*
	* The number of entries in this array determines how many packet
	* retries will occur.
	*
	* By default, the packet timeout array is {10, 10, 10}
	*
	* Param - timeouts - An array of packet timeouts.
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void SetPacketTimeouts(ABrainCloud *brainCloud, const TArray<int32> & timeouts);

	/**
	* Sets the packet timeouts back to the default ie {10, 10, 10}
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void SetPacketTimeoutsToDefault(ABrainCloud *brainCloud);

	/**
	* Sets the authentication packet timeout which is tracked separately
	* from all other packets. Note that authentication packets are never
	* retried and so this value represents the total time a client would
	* wait to receive a reply to an authentication api call. By default
	* this timeout is set to 15 seconds.
	*
	* Param - timeoutSecs The timeout in seconds
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void SetAuthenticationPacketTimeout(ABrainCloud *brainCloud, int32 timeoutSecs);

	/**
	* Returns the low transfer rate timeout in secs
	*
	* Return - The low transfer rate timeout in secs
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static int32 GetUploadLowTransferRateTimeout(ABrainCloud *brainCloud);

	/**
	* Sets the timeout in seconds of a low speed upload
	* (ie transfer rate which is underneath the low transfer rate threshold).
	* By default this is set to 120 secs. Setting this value to 0 will
	* turn off the timeout.
	*
	* Param - timeoutSecs The timeout in secs
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void SetUploadLowTransferRateTimeout(ABrainCloud *brainCloud, int32 timeoutSecs);

	/**
	* Returns the low transfer rate threshold in bytes/sec
	*
	* Return - The low transfer rate threshold in bytes/sec
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static int32 GetUploadLowTransferRateThreshold(ABrainCloud *brainCloud);

	/**
	* Sets the low transfer rate threshold of an upload in bytes/sec.
	* If the transfer rate dips below the given threshold longer
	* than the specified timeout, the transfer will fail.
	* By default this is set to 50 bytes/sec. Note that this setting
	* only works on platforms that use libcurl (non-windows and win32 but
	* not windows store or phone apps).
	*
	* Param - bytesPerSec The low transfer rate threshold in bytes/sec
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void SetUploadLowTransferRateThreshold(ABrainCloud *brainCloud, int32 bytesPerSec);

	/**
	* Sets the error callback to return the status message instead of the
	* error json string. This flag is used to conform to pre-2.17 client
	* behaviour.
	*
	* Param - enabled If set to true, enable
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void SetOldStyleStatusMessageErrorCallback(ABrainCloud *brainCloud, bool enabled);

	/**
	* Sets whether the error callback is triggered when a 202 status
	* is received from the server. By default this is true and should
	* only be set to false for backward compatibility.
	*
	* Param - isError If set to true, 202 is treated as an error
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void SetErrorCallbackOn202Status(ABrainCloud *brainCloud, bool isError);

	//Getters
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static const FString & GetGameId(ABrainCloud *brainCloud);

	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static const FString & GetReleasePlatform(ABrainCloud *brainCloud);

	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static const FString & GetGameVersion(ABrainCloud *brainCloud);

	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static const FString & GetBrainCloudClientVersion(ABrainCloud *brainCloud);

	/**
	* Returns the list of packet timeouts.
	*
	* Return - the list of packet timeouts.
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		const TArray<int32> & GetPacketTimeouts(ABrainCloud *brainCloud);

	/**
	* Gets the authentication packet timeout which is tracked separately
	* from all other packets. Note that authentication packets are never
	* retried and so this value represents the total time a client would
	* wait to receive a reply to an authentication api call. By default
	* this timeout is set to 15 seconds.
	*
	* Return - The timeout in seconds
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static int32 GetAuthenticationPacketTimeout(ABrainCloud *brainCloud);

	/**
	* Enables the message caching upon network error, which is disabled by default.
	* Once enabled, if a client side network error is encountered
	* (i.e. brainCloud server is unreachable presumably due to the client
	* network being down) the sdk will do the following:
	*
	* 1 - cache the currently queued messages to brainCloud
	* 2 - call the network error callback
	* 3 - then expect the app to call either:
	*     a) retryCachedMessages() to retry sending to brainCloud
	*     b) flushCachedMessages() to dump all messages in the queue.
	*
	* Between steps 2 & 3, the app can prompt the user to retry connecting
	* to brainCloud to determine whether to follow path 3a or 3b.
	*
	* Note that if path 3a is followed, and another network error is encountered,
	* the process will begin all over again from step 1.
	*
	* WARNING - the brainCloud sdk will cache *all* api calls sent
	* when a network error is encountered if this mechanism is enabled.
	* This effectively freezes all communication with brainCloud.
	* Apps must call either retryCachedMessages() or flushCachedMessages()
	* for the brainCloud SDK to resume sending messages.
	* resetCommunication() will also clear the message cache.
	*
	* Param - enabled True if message should be cached on timeout
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void EnableNetworkErrorMessageCaching(ABrainCloud *brainCloud, bool enabled);

	/** 
	* Attempts to resend any cached messages. If no messages are in the cache,
	* this method does nothing.
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void RetryCachedMessages(ABrainCloud *brainCloud);

	/**
	* Flushes the cached messages to resume api call processing. This will dump
	* all of the cached messages in the queue.
	*
	* Param - sendApiErrorCallbacks If set to true API error callbacks will
	* be called for every cached message with statusCode CLIENT_NETWORK_ERROR
	* and reasonCode CLIENT_NETWORK_ERROR_TIMEOUT.
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void FlushCachedMessages(ABrainCloud *brainCloud, bool sendApiErrorCallbacks);


	/**
	* Inserts a marker which will tell the brainCloud comms layer
	* to close the message bundle off at this point. Any messages queued
	* before this method was called will likely be bundled together in
	* the next send to the server.
	*
	* To ensure that only a single message is sent to the server you would
	* do something like this:
	*
	* InsertEndOfMessageBundleMarker()
	* SomeApiCall()
	* InsertEndOfMessageBundleMarker()
	*
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void InsertEndOfMessageBundleMarker(ABrainCloud *brainCloud);

	/**
	* Sets the country code sent to brainCloud when a user authenticates.
	* Will override any auto detected country.
	* Param - countryCode ISO 3166-1 two-letter country code
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void OverrideCountryCode(ABrainCloud *brainCloud, const FString& countryCode);

	/**
	* Sets the language code sent to brainCloud when a user authenticates.
	* If the language is set to a non-ISO 639-1 standard value the game default will be used instead.
	* Will override any auto detected language.
	* Param - languageCode ISO 639-1 two-letter language code
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
		static void OverrideLanguageCode(ABrainCloud *brainCloud, const FString& languageCode);
};
