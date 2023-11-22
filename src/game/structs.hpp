/*  Datatypes from BO1. */
#pragma once

#include "../stdc++.hpp"

namespace game {
namespace types {

struct BuiltinFunctionDef {
    const char* actionString;
    void (*actionFunc)();
    int type;
};

static_assert(sizeof(BuiltinFunctionDef) == 12);

struct BuiltinMethodDef {
    const char* actionString;
    void (*actionFunc)();
    int type;
};

static_assert(sizeof(BuiltinMethodDef) == 12);

struct field_t {
    int cursor;
    int scroll;
    int drawWidth;
    int widthInPixels;
    float charHeight;
    int fixedSize;
    char buffer[256];
};

static_assert(sizeof(field_t) == 280);

struct cmd_function_s {
    cmd_function_s* next;
    char* name;
    char* autoCompleteDir;
    char* autoCompleteExt;
    void (*function)(void);
    bool consoleAccess;
};

static_assert(sizeof(cmd_function_s) == 24);
static_assert(offsetof(cmd_function_s, consoleAccess) == 20);

enum scriptInstance_t {
    SCRIPTINSTANCE_SERVER = 0x0,
    SCRIPTINSTANCE_CLIENT = 0x1
};

struct scrVarPub_t {
    const char* fieldBuffer;
    unsigned __int16 canonicalStrCount;
    bool developer;
    bool developer_script;
    bool evaluate;
    const char* error_message;
    int error_index;
    unsigned int time;
    unsigned int timeArrayId;
    unsigned int pauseArrayId;
    unsigned int levelId;
    unsigned int gameId;
    unsigned int animId;
    unsigned int freeEntList;
    unsigned int tempVariable;
    bool bInited;
    unsigned __int16 savecount;
    unsigned int checksum;
    unsigned int entId;
    unsigned int entFieldName;
    void* programHunkUser;
    const char* programBuffer;
    const char* endScriptBuffer;
    unsigned __int16* saveIdMap;
    unsigned __int16* saveIdMapRev;
    unsigned int numScriptThreads;
    unsigned int numScriptValues;
    unsigned int numScriptObjects;
    const char* varUsagePos;
    int ext_threadcount;
    int totalObjectRefCount;
    int totalVectorRefCount;
};

static_assert(sizeof(scrVarPub_t) == 116);

struct VariableStackBuffer {
    const char* pos;
    unsigned __int16 size;
    unsigned __int16 bufLen;
    unsigned int localId;
    char time;
    char buf[1];
};

union VariableUnion {
    int intValue;
    unsigned int uintValue;
    float floatValue;
    unsigned int stringValue;
    const float* vectorValue;
    const char* codePosValue;
    unsigned int pointerValue;
    VariableStackBuffer* stackValue;
    unsigned int entityOffset;
};

static_assert(sizeof(VariableUnion) == 4);

struct VariableValue {
    VariableUnion u;
    int type;
};

static_assert(sizeof(VariableValue) == 8);

struct function_stack_t {
    const char* pos;
    unsigned int localId;
    unsigned int localVarCount;
    VariableValue* top;
    VariableValue* startTop;
};

struct function_frame_t {
    function_stack_t fs;
    int topType;
};

static_assert(sizeof(function_frame_t) == 24);

struct scrVmPub_t {
    unsigned int* localVars;
    VariableValue* maxstack;
    int function_count;
    function_frame_t* function_frame;
    VariableValue* top;
    bool abort_on_error;
    bool terminal_error;
    bool block_execution;
    unsigned int inparamcount;
    unsigned int outparamcount;
    function_frame_t function_frame_start[32];
    VariableValue stack[2048];
};

static_assert(sizeof(scrVmPub_t) == 0x4320);
static_assert(offsetof(scrVmPub_t, inparamcount) == 0x18);
static_assert(offsetof(scrVmPub_t, outparamcount) == 0x1c);

union Variable_u {
    unsigned int prev;
    unsigned int prevSibling;
};

struct Variable {
    unsigned int id;
    Variable_u u;
};

struct ObjectInfo_u {
    unsigned short entnum;
    unsigned short size;
    unsigned int nextEntId;
    unsigned int self;
};

struct ObjectInfo {
    unsigned __int16 refCount;
    unsigned __int16 size;
};

union VariableValueInternal_u {
    VariableUnion u;
    ObjectInfo o;
};

/* 0x1f gets type */
/* 0x60 gets status */
/* >> 8 gets ? */
union VariableValueInternal_w {
    unsigned int status;
    unsigned int type;
    unsigned int name;
    unsigned int classnum;
    unsigned int notifyName;
    unsigned int waitTime;
    unsigned int parentLocalId;
};

struct VariableValueInternal {
    unsigned int id;            // hash
    VariableValueInternal_u u;  // u
    VariableValueInternal_w w;  // w
    char __pad[2];
    unsigned __int16 nextSibling;
};

static_assert(sizeof(VariableValueInternal) == 16);

struct scrVarGlob_t {
    VariableValueInternal* variableList;
};

struct SourceBufferInfo {
    const char* codePos;
    char* buf;
    const char* sourceBuf;
    int len;
    int sortedIndex;
    bool archive;
};

static_assert(sizeof(SourceBufferInfo) == 24);

struct scrParserPub_t {
    SourceBufferInfo* sourceBufferLookup;
    unsigned int sourceBufferLookupLen;
    const char* scriptfilename;
    const char* sourceBuf;
};

static_assert(sizeof(scrParserPub_t) == 16);

enum dvarType_t {
    DVAR_TYPE_BOOL = 0x0,
    DVAR_TYPE_FLOAT = 0x1,
    DVAR_TYPE_FLOAT_2 = 0x2,
    DVAR_TYPE_FLOAT_3 = 0x3,
    DVAR_TYPE_FLOAT_4 = 0x4,
    DVAR_TYPE_INT = 0x5,
    DVAR_TYPE_ENUM = 0x6,
    DVAR_TYPE_STRING = 0x7,
    DVAR_TYPE_COLOR = 0x8,
    DVAR_TYPE_INT64 = 0x9,
    DVAR_TYPE_LINEAR_COLOR_RGB = 0xA,
    DVAR_TYPE_COLOR_XYZ = 0xB,
    DVAR_TYPE_COUNT = 0xC,
};

/* unfinished union */
union DvarValue {
    char __pad[16];
};

static_assert(sizeof(DvarValue) == 16);

/* unfinished union */
union DvarLimits {
    char __pad[16];
};

static_assert(sizeof(DvarLimits) == 16);

struct dvar_t {
    const char* name;
    const char* description;
    int hash;
    unsigned int flags;
    dvarType_t type;
    bool modified;
    bool loadedFromSaveGame;
    char __pad1[2];
    DvarValue current;
    DvarValue latched;
    DvarValue saved;
    DvarValue reset;
    DvarLimits domain;
    dvar_t* hashNext;
    char __pad2[4];
};

static_assert(sizeof(dvar_t) == 112);

/* unfinished struct */
struct level_locals_t {
    void* clients;   /* gclient_t* */
    void* gentities; /* gentity_t* */
    int gentitySize;
    int num_entities;
    void* firstFreeEnt;   /* gentity_t* */
    void* lastFreeEnt;    /* gentity_t* */
    void* vehicles;       /* scr_vehicle_t* */
    void* firstFreeActor; /* gentity_t* */
    void* lastFreeActor;  /* gentity_t* */
};

struct OpcodeLookup {
    char* codePos;
    unsigned int sourcePosIndex;
    unsigned int sourcePosCount;
};

static_assert(sizeof(OpcodeLookup) == 12);

struct SourceLookup {
    unsigned int sourcePos;
    unsigned int type;
};

struct SaveSourceBufferInfo {
    char* sourceBuf;
    unsigned int len;
};

struct scrParserGlob_t {
    OpcodeLookup* opcodeLookup;
    unsigned int opcodeLookupMaxLen;
    unsigned int opcodeLookupLen;
    SourceLookup* sourcePosLookup;
    unsigned int sourcePosLookupMaxLen;
    unsigned int sourcePosLookupLen;
    unsigned int sourceBufferLookupMaxLen;
    unsigned char* currentCodePos;
    unsigned int currentSourcePosCount;
    SaveSourceBufferInfo* saveSourceBufferLookup;
    unsigned int saveSourceBufferLookupLen;
    int delayedSourceIndex;
    int threadStartSourceIndex;
};

/* (vector not used in game) */
struct ThreadDebugInfo {
    std::vector<const char*> pos;
    float varUsage;
    float endonUsage;
};

enum VarTypes {
    VAR_UNDEFINED = 0x0,
    VAR_OBJECT = 0x1,
    VAR_STRING = 0x2,
    VAR_ISTRING = 0x3,
    VAR_VECTOR = 0x4,
    VAR_FLOAT = 0x5,
    VAR_INT = 0x6,
    VAR_CODEPOS = 0x7,
    VAR_FUNCTION = 0x9,
    VAR_STACK = 0xa,
    VAR_ANIMATION = 0xb,
    VAR_RUNNING_THREAD = 0xd, /* Scr_GetThreadPos */
    VAR_WAITTILL_THREAD = 0xe,
    VAR_WAIT_THREAD = 0xf,
    VAR_CHILD = 0x11, /* not sure */
    VAR_ENTITY = 0x13,
    VAR_ARRAY = 0x14,
};

// static_assert(sizeof(ThreadDebugInfo) == 140);

struct CmdArgs {
    int nesting;
    int localClientNum[8];
    int controllerIndex[8];
    struct itemDef_s* itemDef[8];
    int argshift[8];
    int argc[8];
    const char** argv[8];
    char textPool[8192];
    const char* argvPool[512];
    int usedTextPool[8];
    int totalUsedArgvPool;
    int totalUsedTextPool;
};

struct scr_classStruct_t {
    unsigned short id;
    unsigned short entry;
    unsigned int entArrayId;
    char* name;
};

};  // namespace types

namespace globals {

// __declspec(selectany) std::unordered_map<std::string, types::BuiltinFunctionDef> function_map;
// __declspec(selectany) std::unordered_map<std::string, types::BuiltinMethodDef> method_map;
// __declspec(selectany) std::unordered_map<std::string, types::cmd_function_s> cmd_function_map;
// __declspec(selectany) std::vector<size_t> level_vars;

__declspec(selectany) types::field_t* g_consoleField = reinterpret_cast<types::field_t*>(0xc72280);
__declspec(selectany) types::cmd_function_s* cmd_functions = reinterpret_cast<types::cmd_function_s*>(0x2430014);

__declspec(selectany) types::scrVarPub_t* gScrVarPub = reinterpret_cast<types::scrVarPub_t*>(0x32c8680);
__declspec(selectany) types::scrVarGlob_t* gScrVarGlob = reinterpret_cast<types::scrVarGlob_t*>(0x32c8580);

__declspec(selectany) types::scrVmPub_t* gScrVmPub = reinterpret_cast<types::scrVmPub_t*>(0x32c8738);
__declspec(selectany) types::function_stack_t* function_stack = reinterpret_cast<types::function_stack_t*>(0x32d1e28);

__declspec(selectany) types::scrParserPub_t* gScrParserPub = reinterpret_cast<types::scrParserPub_t*>(0x32683ec);
__declspec(selectany) types::scrParserGlob_t* gScrParserGlob = reinterpret_cast<types::scrParserGlob_t*>(0x3268380);

// __declspec(selectany) types::scr_classStruct_t** gScrClassMap = reinterpret_cast<types::scr_classStruct_t**>(0xb8525c);
// __declspec(selectany) bool* g_mapLoaded = reinterpret_cast<bool*>(0x2ff6902);

};  // namespace globals
};  // namespace game