// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

class ServiceName;
class ServiceOperation;
class OperationParam;

/**
 * Pure virtual class providing a means for waking up the client when a
 * response is received from the server.
 */
class BCCLIENTPLUGIN_API IGlobalErrorCallback {

public:
    // Destructor - make sure it is virtual to avoid problems with
    // destroying a sub-classed object using an IGlobalErrorCallback pointer.
    virtual ~IGlobalErrorCallback()  { }

    /**
     * Errors are returned back to the layer which is interfacing with the
     * BrainCloud library through the serverError() callback.
     *
     * A server error might indicate a failure of the client to communicate
     * with the server after N retries.
     *
     * @param serviceName The service name being called
     * @param serviceOperation The service operation being called
     * @param statusCode The error status return code (400, 403, 500, etc)
     * @param reasonCode The brainCloud reason code (see reason codes on apidocs site)
     * @param jsonError The error json string
     */
    virtual void globalError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError) = 0;
};