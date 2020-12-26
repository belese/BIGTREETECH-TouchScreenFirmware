#ifndef _PRINTING_H_
#define _PRINTING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "variants.h"
#include "ff.h"


#ifndef M27_WATCH_OTHER_SOURCES
#define M27_WATCH_OTHER_SOURCES    false
#endif

#ifndef M27_REFRESH
#define M27_REFRESH   3
#endif

#ifdef RAPID_SERIAL_COMM
#define rapid_serial_loop()  loopBackEnd()
#define rapid_serial_comm()  if(isPrinting() == true && infoSettings.serial_alwaysOn != 1){loopBackEnd();}
#else
#define rapid_serial_loop()
#define rapid_serial_comm()
#endif


typedef enum {
  FILE_PROGRESS = 0,
#ifdef ENABLE_SLICER_PROGRESS
  SLICER_PROGRESS,
#endif
  FORCE_PROGRESS //only used if file is finished and progress are not at 100%
} PROGRESS_SOURCE; //higher will be the default progress updater


typedef struct
{
  FIL file;

  uint32_t time; // Printed time in sec
  uint32_t size; // Gcode file total size
  uint32_t cur;  // Gcode has printed file size
  uint8_t  progress;
  PROGRESS_SOURCE progress_source;

#ifdef ENABLE_SLICER_REMAINING_TIME
  uint32_t remaining_time; //current remaining time in sec (if set with M73 or M112)
#endif

  bool     printing; // 1 means printing, 0 means idle
  bool     pause;    // 1 means paused
  bool     m0_pause; // pause triggered through M0/M1 gcode
  bool     runout;   // 1: runout in printing, 0: idle
  bool     model_icon; // 1: model preview icon exist, 0: not exist

}PRINTING;

extern PRINTING infoPrinting;

bool isPrinting(void);
bool isPause(void);
bool isM0_Pause(void);
void breakAndContinue(void);
void resumeAndPurge(void);
void resumeAndContinue(void);

void setPrintingTime(uint32_t RTtime);

#ifdef ENABLE_SLICER_REMAINING_TIME
void setPrintingRemainingTime(int RTtime);
uint32_t getPrintingRemainingTime();
#endif

void exitPrinting(void);
void endPrinting(void);
void printingFinished(void);
void abortPrinting(void);
uint8_t *getCurGcodeName(char *path);
void sendPrintCodes(uint8_t index);

bool setPrintPause(bool is_pause, bool is_m0pause);

void setPrintSize(uint32_t size);
void setPrintCur(uint32_t cur);
uint32_t getPrintSize(void);
uint32_t getPrintCur(void);
bool getPrintRunout(void);
void setPrintRunout(bool runout);
void setPrintModelIcon(bool exist);
bool getPrintModelIcon(void);

void setPrintProgress(uint8_t progress, uint8_t source);
uint8_t   getPrintProgress(void);
uint32_t  getPrintTime(void);
void startNewPrint(void);

void printSetUpdateWaiting(bool isWaiting);

void getGcodeFromFile(void);

void shutdown(void);
void shutdownLoop(void);
void startShutdown(void);

void loopCheckPrinting(void);

void resetFilamentUsed(void);
void updateFilamentUsed(void);

#ifdef __cplusplus
}
#endif

#endif
