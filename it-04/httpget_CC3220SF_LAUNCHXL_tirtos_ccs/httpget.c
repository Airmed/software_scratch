/*
 * Copyright (c) 2015-2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#include "string.h"
#include <ti/display/Display.h>
#include <ti/net/http/httpclient.h>
#include "semaphore.h"
#include "Board.h"

#define HOSTNAME              "https://seniordesigndb.herokuapp.com"
//#define HOSTNAME              "https://ene81b7cpoywi.x.pipedream.net"
#define REQUEST_POST_URI "/" 
#define REQUEST_URI           "/"
#define con_type   "application/json" 
#define builtBuffPost  "{\"query\":\"insert into test(one, two, three, four) values (101, 102, 103, 104);\"}" /* Push data to database */
//#define builtBuff  ""
#define builtBuffGet          "{\"query\":\"select * from test;\"}" /* Get data from database */
//#define builtBuff           "{\"query\":\"DELETE FROM test WHERE id = 6;\"}" /* Delete data from database */
#define USER_AGENT            "HTTPClient (ARM; TI-RTOS)"
#define HTTP_MIN_RECV         (256)
const char header[] = "Basic dZdDpXGVz0N0\r\nContent-Type: application/json";
extern Display_Handle display;
extern sem_t ipEventSyncObj;
extern void printError(char *errString,
                       int code);

/*
 *  ======== httpTask ========
 *  Makes a HTTP GET request
 */


 void* httpTaskPost(void* pvParamaters){

    int16_t ret = 0;
    bool moreDataFlag = false;
    int16_t len = 0;
    char data[HTTP_MIN_RECV];
    
    
    HTTPClient_Handle httpClientHandle;
    int16_t statusCode;
    httpClientHandle = HTTPClient_create(&statusCode,0);
    
    if(statusCode < 0)
    {
    printError("httpTask: creation of http client handle failed",
    statusCode);
    }
    
    HTTPClient_setHeader(httpClientHandle, HTTPClient_HFIELD_REQ_AUTHORIZATION, header,strlen(header), HTTPClient_HFIELD_PERSISTENT);
    
    if(ret < 0)
    {
    printError("httpTask: setting request header failed", ret);
    }
    
    ret = HTTPClient_connect(httpClientHandle,HOSTNAME,0,0);
    if(ret < 0)
    {
    printError("httpTask: connect failed", ret);
    }

    
    ret  = HTTPClient_sendRequest(httpClientHandle, HTTP_METHOD_POST, REQUEST_POST_URI, builtBuffPost, strlen(builtBuffPost), 0);

    Display_printf(display, 0, 0, "post ret = %d \n", ret);
    
     len = 0;
    do
    {
        ret = HTTPClient_readResponseBody(httpClientHandle, data, sizeof(data),
                                          &moreDataFlag);
        if(ret < 0)
        {
            printError("httpTask: response body processing failed", ret);
        }
        Display_printf(display, 0, 0, "%.*s \r\n",ret,data);
        len += ret;
    }
    while(moreDataFlag);
    GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_ON); /* Succesful Post light LED9 */
    Display_printf(display, 0, 0, "PUSH SUCCESS \n");
    Display_printf(display, 0, 0, "Received %d bytes of payload\n", len);

    ret = HTTPClient_disconnect(httpClientHandle);
    if(ret < 0)
    {
        printError("httpTask: disconnect failed", ret);
    }

    HTTPClient_destroy(httpClientHandle);
    return(0);
 }
 
 
 void* httpTaskPull(void* pvParamaters){

    int16_t ret = 0;
    bool moreDataFlag = false;
    int16_t len = 0;
    char data[HTTP_MIN_RECV];
    
    
    HTTPClient_Handle httpClientHandle;
    int16_t statusCode;
    httpClientHandle = HTTPClient_create(&statusCode,0);
    
    if(statusCode < 0)
    {
    printError("httpTask: creation of http client handle failed",
    statusCode);
    }
    
    HTTPClient_setHeader(httpClientHandle, HTTPClient_HFIELD_REQ_AUTHORIZATION, header,strlen(header), HTTPClient_HFIELD_PERSISTENT);
    
    if(ret < 0)
    {
    printError("httpTask: setting request header failed", ret);
    }
    
    ret = HTTPClient_connect(httpClientHandle,HOSTNAME,0,0);
    if(ret < 0)
    {
    printError("httpTask: connect failed", ret);
    }

    
    ret  = HTTPClient_sendRequest(httpClientHandle, HTTP_METHOD_POST, REQUEST_POST_URI, builtBuffGet, strlen(builtBuffGet), 0);

    Display_printf(display, 0, 0, "post ret = %d \n", ret);
    
     len = 0;
    do
    {
        ret = HTTPClient_readResponseBody(httpClientHandle, data, sizeof(data),
                                          &moreDataFlag);
        if(ret < 0)
        {
            printError("httpTask: response body processing failed", ret);
        }
        Display_printf(display, 0, 0, "%.*s \r\n",ret,data);
        len += ret;
    }
    while(moreDataFlag);
    GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_ON); /* Succesful Query light LED10 */
    Display_printf(display, 0, 0, "PULL SUCCESS \n");
    Display_printf(display, 0, 0, "Received %d bytes of payload\n", len);

    ret = HTTPClient_disconnect(httpClientHandle);
    if(ret < 0)
    {
        printError("httpTask: disconnect failed", ret);
    }

    HTTPClient_destroy(httpClientHandle);
    return(0);
 }
 
 
 /*
  void* httpTask(void* pvParamaters){

    int16_t ret = 0;
    bool moreDataFlag = false;
    int16_t len = 0;
    char data[HTTP_MIN_RECV];

    
    HTTPClient_Handle httpClientHandle;
    int16_t statusCode;
    httpClientHandle = HTTPClient_create(&statusCode,0);
    if(statusCode < 0)
    {
    printError("httpTask: creation of http client handle failed",
    statusCode);
    }
    
    HTTPClient_setHeader(httpClientHandle, HTTPClient_HFIELD_REQ_AUTHORIZATION, header,strlen(header), HTTPClient_HFIELD_PERSISTENT);
    
    if(ret < 0)
    {
    printError("httpTask: setting request header failed", ret);
    }
    
    ret = HTTPClient_connect(httpClientHandle,HOSTNAME,0,0);
    if(ret < 0)
    {
    printError("httpTask: connect failed", ret);
    }

    
    ret  = HTTPClient_sendRequest(httpClientHandle, HTTP_METHOD_POST, REQUEST_POST_URI, builtBuff, strlen(builtBuff), 0);

    Display_printf(display, 0, 0, "post ret = %d \n", ret);
    
     len = 0;
    do
    {
        ret = HTTPClient_readResponseBody(httpClientHandle, data, sizeof(data),
                                          &moreDataFlag);
        if(ret < 0)
        {
            printError("httpTask: response body processing failed", ret);
        }
        Display_printf(display, 0, 0, "%.*s \r\n",ret,data);
        len += ret;
    }
    while(moreDataFlag);
    GPIO_write(Board_GPIO_LED2, Board_GPIO_LED_ON); 
    Display_printf(display, 0, 0, "Received %d bytes of payload\n", len);

    ret = HTTPClient_disconnect(httpClientHandle);
    if(ret < 0)
    {
        printError("httpTask: disconnect failed", ret);
    }

    HTTPClient_destroy(httpClientHandle);
    return(0);
 }
 */
 