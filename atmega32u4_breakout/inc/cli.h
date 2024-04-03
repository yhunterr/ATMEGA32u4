/*
 * cli.h
 *
 * Created: 2024-03-31 오후 8:29:33
 *  Author: sw
 */ 
#include "def.h"


#define CLI_CMD_LIST_MAX      16
#define CLI_CMD_NAME_MAX      16
#define CLI_LINE_HIS_MAX      4
#define CLI_LINE_BUF_MAX      32

typedef struct
{
    uint16_t   argc;
    char     **argv;

    int32_t  (*getData)(uint8_t index);
    float    (*getFloat)(uint8_t index);
    char    *(*getStr)(uint8_t index);
    bool     (*isStr)(uint8_t index, const char *p_str);
} cli_args_t;

bool cliInit(void);
bool cliOpen(uint8_t ch);
bool cliIsBusy(void);
bool cliOpenLog(uint8_t ch);
void cliLogo(void);
bool cliMain(void);
void cliPrintf(const char *fmt, ...);
bool cliAdd(const char *cmd_str, void (*p_func)(cli_args_t *));
bool cliKeepLoop(void);
void cliPutch(uint8_t data);
uint8_t  cliGetPort(void);
uint32_t cliAvailable(void);
uint8_t  cliRead(void);
uint32_t cliWrite(uint8_t *p_data, uint32_t length);
bool cliRunStr(const char *fmt, ...);
void cliShowCursor(bool visibility);
void cliMoveUp(uint8_t y);
void cliMoveDown(uint8_t y);

