/* Automatically generated from Squeak on 18 July 2010 3:56:43 pm 
   by VMMaker 4.2.5
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
/*  The virtual machine proxy definition */
#include "sqVirtualMachine.h"
/* Configuration options */
#include "sqConfig.h"
/* Platform specific definitions */
#include "sqPlatformSpecific.h"

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
#undef EXPORT
// was #undef EXPORT(returnType) but screws NorCroft cc
#define EXPORT(returnType) static returnType
#endif
#include "SqueakSSL.h"

#include "sqMemoryAccess.h"


/*** Constants ***/

/*** Function Prototypes ***/
static VirtualMachine * getInterpreter(void);
#pragma export on
EXPORT(const char*) getModuleName(void);
#pragma export off
static sqInt halt(void);
static sqInt msg(char * s);
#pragma export on
EXPORT(sqInt) primitiveAccept(void);
EXPORT(sqInt) primitiveConnect(void);
EXPORT(sqInt) primitiveCreate(void);
EXPORT(sqInt) primitiveDecrypt(void);
EXPORT(sqInt) primitiveDestroy(void);
EXPORT(sqInt) primitiveEncrypt(void);
EXPORT(sqInt) primitiveGetIntProperty(void);
EXPORT(sqInt) primitiveGetStringProperty(void);
EXPORT(sqInt) primitiveSetIntProperty(void);
EXPORT(sqInt) primitiveSetStringProperty(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine* anInterpreter);
#pragma export off
/*** Variables ***/

#ifdef SQUEAK_BUILTIN_PLUGIN
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"SqueakSSL 18 July 2010 (i)"
#else
	"SqueakSSL 18 July 2010 (e)"
#endif
;



/*	Note: This is coded so that plugins can be run from Squeak. */

static VirtualMachine * getInterpreter(void) {
	return interpreterProxy;
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

EXPORT(const char*) getModuleName(void) {
	return moduleName;
}

static sqInt halt(void) {
	;
}

static sqInt msg(char * s) {
	fprintf(stderr, "\n%s: %s", moduleName, s);
}


/*	Primitive. Starts or continues a server handshake using the current session.
	Will eventually produce output to be sent to the client. Requires the host
	and cert name to be set for the session. Returns a code indicating the sate
	of the connection:
		> 0	 - Number of bytes to be sent to the client.
		0	 - Success. The connection is established.
		-1 	 - More input is required.
		< -1 - Other errors.
	 */

EXPORT(sqInt) primitiveAccept(void) {
    sqInt dstOop;
    sqInt handle;
    sqInt result;
    sqInt srcOop;
    sqInt start;
    char * dstPtr;
    sqInt srcLen;
    sqInt dstLen;
    char * srcPtr;

	if (!((interpreterProxy->methodArgumentCount()) == 5)) {
		return interpreterProxy->primitiveFail();
	}
	dstOop = interpreterProxy->stackObjectValue(0);
	srcLen = interpreterProxy->stackIntegerValue(1);
	start = interpreterProxy->stackIntegerValue(2);
	srcOop = interpreterProxy->stackObjectValue(3);
	handle = interpreterProxy->stackIntegerValue(4);
	if (interpreterProxy->failed()) {
		return null;
	}
	if (!(((start > 0) && (srcLen >= 0)) && ((interpreterProxy->isBytes(srcOop)) && ((interpreterProxy->isBytes(dstOop)) && ((interpreterProxy->byteSizeOf(srcOop)) >= ((start + srcLen) - 1)))))) {
		return interpreterProxy->primitiveFail();
	}
	srcPtr = interpreterProxy->firstIndexableField(srcOop);
	dstPtr = interpreterProxy->firstIndexableField(dstOop);
	srcPtr = (srcPtr + start) - 1;
	dstLen = interpreterProxy->byteSizeOf(dstOop);
	result = sqAcceptSSL(handle, srcPtr, srcLen, dstPtr, dstLen);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop((interpreterProxy->methodArgumentCount()) + 1);
	interpreterProxy->pushInteger(result);
}


/*	Primitive. Starts or continues a client handshake using the provided data.
	Will eventually produce output to be sent to the server. Requires the host
	name to be set for the session. 
	Returns:
		> 0	 - Number of bytes to be sent to the server
		0	 - Success. The connection is established.
		-1 	 - More input is required.
		< -1 - Other errors.
	 */

EXPORT(sqInt) primitiveConnect(void) {
    sqInt dstOop;
    sqInt handle;
    sqInt result;
    sqInt srcOop;
    sqInt start;
    char * dstPtr;
    sqInt srcLen;
    sqInt dstLen;
    char * srcPtr;

	if (!((interpreterProxy->methodArgumentCount()) == 5)) {
		return interpreterProxy->primitiveFail();
	}
	dstOop = interpreterProxy->stackObjectValue(0);
	srcLen = interpreterProxy->stackIntegerValue(1);
	start = interpreterProxy->stackIntegerValue(2);
	srcOop = interpreterProxy->stackObjectValue(3);
	handle = interpreterProxy->stackIntegerValue(4);
	if (interpreterProxy->failed()) {
		return null;
	}
	if (!(((start > 0) && (srcLen >= 0)) && ((interpreterProxy->isBytes(srcOop)) && ((interpreterProxy->isBytes(dstOop)) && ((interpreterProxy->byteSizeOf(srcOop)) >= ((start + srcLen) - 1)))))) {
		return interpreterProxy->primitiveFail();
	}
	srcPtr = interpreterProxy->firstIndexableField(srcOop);
	dstPtr = interpreterProxy->firstIndexableField(dstOop);
	srcPtr = (srcPtr + start) - 1;
	dstLen = interpreterProxy->byteSizeOf(dstOop);
	result = sqConnectSSL(handle, srcPtr, srcLen, dstPtr, dstLen);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop((interpreterProxy->methodArgumentCount()) + 1);
	interpreterProxy->pushInteger(result);
}


/*	Primitive. Creates a new SSL session and returns its handle. */

EXPORT(sqInt) primitiveCreate(void) {
    sqInt handle;

	if (!((interpreterProxy->methodArgumentCount()) == 0)) {
		return interpreterProxy->primitiveFail();
	}
	handle = sqCreateSSL();
	if (handle == 0) {
		return interpreterProxy->primitiveFail();
	}
	interpreterProxy->pop((interpreterProxy->methodArgumentCount()) + 1);
	interpreterProxy->pushInteger(handle);
}


/*	Primitive. Decrypts a buffer sent via the connection.
	Requires the session to be established.
	Returns:
		>=0 - Number of bytes decrypted in the result buffer
		< -1 - Other errors.
	 */

EXPORT(sqInt) primitiveDecrypt(void) {
    sqInt dstOop;
    sqInt handle;
    sqInt result;
    sqInt srcOop;
    sqInt start;
    char * dstPtr;
    sqInt srcLen;
    sqInt dstLen;
    char * srcPtr;

	if (!((interpreterProxy->methodArgumentCount()) == 5)) {
		return interpreterProxy->primitiveFail();
	}
	dstOop = interpreterProxy->stackObjectValue(0);
	srcLen = interpreterProxy->stackIntegerValue(1);
	start = interpreterProxy->stackIntegerValue(2);
	srcOop = interpreterProxy->stackObjectValue(3);
	handle = interpreterProxy->stackIntegerValue(4);
	if (interpreterProxy->failed()) {
		return null;
	}
	if (!(((start > 0) && (srcLen >= 0)) && ((interpreterProxy->isBytes(srcOop)) && ((interpreterProxy->isBytes(dstOop)) && ((interpreterProxy->byteSizeOf(srcOop)) >= ((start + srcLen) - 1)))))) {
		return interpreterProxy->primitiveFail();
	}
	srcPtr = interpreterProxy->firstIndexableField(srcOop);
	dstPtr = interpreterProxy->firstIndexableField(dstOop);
	srcPtr = (srcPtr + start) - 1;
	dstLen = interpreterProxy->byteSizeOf(dstOop);
	result = sqDecryptSSL(handle, srcPtr, srcLen, dstPtr, dstLen);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop((interpreterProxy->methodArgumentCount()) + 1);
	interpreterProxy->pushInteger(result);
}


/*	Primitive. Destroys an SSL session. */

EXPORT(sqInt) primitiveDestroy(void) {
    sqInt handle;
    sqInt result;

	if (!((interpreterProxy->methodArgumentCount()) == 1)) {
		return interpreterProxy->primitiveFail();
	}
	handle = interpreterProxy->stackIntegerValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	result = sqDestroySSL(handle);
	if (result == 0) {
		return interpreterProxy->primitiveFail();
	}
	interpreterProxy->pop(interpreterProxy->methodArgumentCount());
}


/*	Primitive. Encrypts a buffer to be sent to the via the connection.
	Requires the session to be established.
	Returns:
		>=0 - Number of bytes encrypted in the result buffer
		< -1 - Other errors.
	 */

EXPORT(sqInt) primitiveEncrypt(void) {
    sqInt dstOop;
    sqInt handle;
    sqInt result;
    sqInt srcOop;
    sqInt start;
    char * dstPtr;
    sqInt srcLen;
    sqInt dstLen;
    char * srcPtr;

	if (!((interpreterProxy->methodArgumentCount()) == 5)) {
		return interpreterProxy->primitiveFail();
	}
	dstOop = interpreterProxy->stackObjectValue(0);
	srcLen = interpreterProxy->stackIntegerValue(1);
	start = interpreterProxy->stackIntegerValue(2);
	srcOop = interpreterProxy->stackObjectValue(3);
	handle = interpreterProxy->stackIntegerValue(4);
	if (interpreterProxy->failed()) {
		return null;
	}
	if (!(((start > 0) && (srcLen >= 0)) && ((interpreterProxy->isBytes(srcOop)) && ((interpreterProxy->isBytes(dstOop)) && ((interpreterProxy->byteSizeOf(srcOop)) >= ((start + srcLen) - 1)))))) {
		return interpreterProxy->primitiveFail();
	}
	srcPtr = interpreterProxy->firstIndexableField(srcOop);
	dstPtr = interpreterProxy->firstIndexableField(dstOop);
	srcPtr = (srcPtr + start) - 1;
	dstLen = interpreterProxy->byteSizeOf(dstOop);
	result = sqEncryptSSL(handle, srcPtr, srcLen, dstPtr, dstLen);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop((interpreterProxy->methodArgumentCount()) + 1);
	interpreterProxy->pushInteger(result);
}


/*	Primitive. Returns an integer property for the session */

EXPORT(sqInt) primitiveGetIntProperty(void) {
    sqInt propID;
    sqInt handle;
    sqInt value;

	if (!((interpreterProxy->methodArgumentCount()) == 2)) {
		return interpreterProxy->primitiveFail();
	}
	propID = interpreterProxy->stackIntegerValue(0);
	handle = interpreterProxy->stackIntegerValue(1);
	if (interpreterProxy->failed()) {
		return null;
	}
	value = sqGetIntPropertySSL(handle, propID);
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->popthenPush((interpreterProxy->methodArgumentCount()) + 1, interpreterProxy->signed32BitIntegerFor(value));
}


/*	Primitive. Returns a string property for the session */

EXPORT(sqInt) primitiveGetStringProperty(void) {
    sqInt stringLen;
    sqInt propID;
    char * stringPtr;
    sqInt handle;
    char * oopPtr;
    sqInt i;
    sqInt stringOop;

	if (!((interpreterProxy->methodArgumentCount()) == 2)) {
		return interpreterProxy->primitiveFail();
	}
	propID = interpreterProxy->stackIntegerValue(0);
	handle = interpreterProxy->stackIntegerValue(1);
	if (interpreterProxy->failed()) {
		return null;
	}
	stringPtr = sqGetStringPropertySSL(handle, propID);
	if (interpreterProxy->failed()) {
		return null;
	}
	if (stringPtr == null) {
		stringOop = interpreterProxy->nilObject();
	} else {
		stringLen = strlen(stringPtr);
		stringOop = interpreterProxy->instantiateClassindexableSize(interpreterProxy->classString(), stringLen);
		oopPtr = interpreterProxy->firstIndexableField(stringOop);
		for (i = 0; i <= (stringLen - 1); i += 1) {
			oopPtr[i] = (stringPtr[i]);
		}
	}
	interpreterProxy->popthenPush((interpreterProxy->methodArgumentCount()) + 1, stringOop);
}


/*	Primitive. Sets a integer property for the session */

EXPORT(sqInt) primitiveSetIntProperty(void) {
    sqInt propID;
    sqInt handle;
    sqInt result;
    sqInt value;

	if (!((interpreterProxy->methodArgumentCount()) == 3)) {
		return interpreterProxy->primitiveFail();
	}
	value = interpreterProxy->signed32BitValueOf(interpreterProxy->stackValue(0));
	propID = interpreterProxy->stackIntegerValue(1);
	handle = interpreterProxy->stackIntegerValue(2);
	if (interpreterProxy->failed()) {
		return null;
	}
	result = sqSetIntPropertySSL(handle, propID, value);
	if (!(result)) {
		return interpreterProxy->primitiveFail();
	}
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop(interpreterProxy->methodArgumentCount());
}


/*	Primitive. Sets a string property for the session */

EXPORT(sqInt) primitiveSetStringProperty(void) {
    sqInt propID;
    sqInt handle;
    sqInt result;
    sqInt srcOop;
    sqInt srcLen;
    char * srcPtr;

	if (!((interpreterProxy->methodArgumentCount()) == 3)) {
		return interpreterProxy->primitiveFail();
	}
	srcOop = interpreterProxy->stackObjectValue(0);
	propID = interpreterProxy->stackIntegerValue(1);
	handle = interpreterProxy->stackIntegerValue(2);
	if (interpreterProxy->failed()) {
		return null;
	}
	if (!(interpreterProxy->isBytes(srcOop))) {
		return interpreterProxy->primitiveFail();
	}
	srcPtr = interpreterProxy->firstIndexableField(srcOop);
	srcLen = interpreterProxy->byteSizeOf(srcOop);
	result = sqSetStringPropertySSL(handle, propID, srcPtr, srcLen);
	if (!(result)) {
		return interpreterProxy->primitiveFail();
	}
	if (interpreterProxy->failed()) {
		return null;
	}
	interpreterProxy->pop(interpreterProxy->methodArgumentCount());
}


/*	Note: This is coded so that is can be run from Squeak. */

EXPORT(sqInt) setInterpreter(struct VirtualMachine* anInterpreter) {
    sqInt ok;

	interpreterProxy = anInterpreter;
	ok = interpreterProxy->majorVersion() == VM_PROXY_MAJOR;
	if (ok == 0) {
		return 0;
	}
	ok = interpreterProxy->minorVersion() >= VM_PROXY_MINOR;
	return ok;
}


#ifdef SQUEAK_BUILTIN_PLUGIN


void* SqueakSSL_exports[][3] = {
	{"SqueakSSL", "primitiveDestroy", (void*)primitiveDestroy},
	{"SqueakSSL", "primitiveDecrypt", (void*)primitiveDecrypt},
	{"SqueakSSL", "primitiveConnect", (void*)primitiveConnect},
	{"SqueakSSL", "primitiveEncrypt", (void*)primitiveEncrypt},
	{"SqueakSSL", "primitiveAccept", (void*)primitiveAccept},
	{"SqueakSSL", "primitiveSetIntProperty", (void*)primitiveSetIntProperty},
	{"SqueakSSL", "primitiveGetStringProperty", (void*)primitiveGetStringProperty},
	{"SqueakSSL", "primitiveSetStringProperty", (void*)primitiveSetStringProperty},
	{"SqueakSSL", "setInterpreter", (void*)setInterpreter},
	{"SqueakSSL", "primitiveGetIntProperty", (void*)primitiveGetIntProperty},
	{"SqueakSSL", "primitiveCreate", (void*)primitiveCreate},
	{"SqueakSSL", "getModuleName", (void*)getModuleName},
	{NULL, NULL, NULL}
};


#endif /* ifdef SQ_BUILTIN_PLUGIN */

