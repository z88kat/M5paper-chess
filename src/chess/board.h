#ifndef _CHESS_BOARD_H_
#define _CHESS_BOARD_H_

#include "../epdgui/epdgui.h"
#include <M5EPD.h>
#include "../resources/imagePieces.h"



void drawBoard(M5EPD_Canvas *canvas);
void drawGrid(M5EPD_Canvas *canvas, int x, int y);

void drawPieces(M5EPD_Canvas *canvas, int x, int y);
const uint8_t *getPieceImageWhiteBackground(int piece);
const uint8_t *getPieceImageBlackBackground(int piece);
void cell_cb(epdgui_args_vector_t &args);
void destroy();
void loopInteraction(M5EPD_Canvas *canvas);
String getChessCellReference(int row, int column);

#endif  //_CHESS_BOARD_H_