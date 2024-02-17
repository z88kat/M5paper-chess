/**
 *
 */

#include "board.h"

const int WIDTH = 540;
const int HEIGHT = 960;
const int TFT_BLACK_COLOR = 15; // This appears to be black based on gray scale level
const int TFT_WHITE_COLOR = 0;  // This appears to be white based on gray scale level
const int TFT_GRAY_COLOR = 7;

// An array which keeps track of the position of the pieces
// 0 - empty
// 1 - white pawn
// 2 - white knight
// 3 - white bishop
// 4 - white rook
// 5 - white queen
// 6 - white king
// 7 - black pawn
// 8 - black knight
// 9 - black bishop
// 10 - black rook
// 11 - black queen
// 12 - black king

// clang-format off
int boardPieces[8][8] = {
  {4, 2, 3, 5, 6, 3, 2, 4},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {7, 7, 7, 7, 7, 7, 7, 7},
  {10, 8, 9, 11, 12, 9, 8, 10}
};

// clang-format on
void drawBoard(M5EPD_Canvas *canvas) {
  // Something goes here

  String title = "Chess";

  canvas->setTextSize(26);
  // x0 (across), int32_t y0 (down)
  // canvas->drawString("Move: Yours", 20, 0);

  // int32_t x0 (across), int32_t y0 (down), int32_t x1, int32_t y1, uint32_t color
  // 540, 960
  // canvas->drawLine(5, 30, WIDTH - 10, 30, 10, 4);

  // canvas->drawLine(5, 0, WIDTH - 10, 0, TFT_BLACK_COLOR);

  // Draw a 8 x 8 grid of squares
  drawGrid(canvas, 30, 80);

  // Draw the pieces on the board
  drawPieces(canvas, 30, 80);

  // Below thre grid write information about the game
  int startY = (8 * 60) + 80 + 60; // starting point

  // Write the move number
  // canvas->drawString("Move: Yours", 20, startY);

  // draw an image to the screen piece_bb (black bishop)
  canvas->pushImage(20, 10, 48, 48, piece_bb);

  // Push canvas to y-axis 100px from the top
  canvas->pushCanvas(0, 100, UPDATE_MODE_GC16); //

  Serial.println("Drawing board");
}

/**
 * Draw a 8 x 8 grid of squares
 * canvas: M5EPD_Canvas
 * x: int the x position to start drawing the grid
 * y: int the y position to start drawing the grid
 */
void drawGrid(M5EPD_Canvas *canvas, int x, int y) {

  // Draw a 8 x 8 grid of squares
  for (int i = 0; i < 8; i++) {

    // For each row write the row number 1 - 8
    canvas->drawString(String(8 - i), 10, (i * 60) + y + 20);

    for (int j = 0; j < 8; j++) {
      // Draw a square
      // Every alternate square is black otherwise white
      if ((i + j) % 2 == 0) {
        // White square, needs a black border
        canvas->drawRect((i * 60) + x, (j * 60) + y, 60, 60, TFT_BLACK_COLOR);
      } else {
        // Black square,
        canvas->fillRect((i * 60) + x, (j * 60) + y, 60, 60, TFT_BLACK_COLOR);
      }
    }
  }

  // Under the grid write the letters a - h
  int start = (8 * 60) + y - 5; // starting point of the letters
  for (int i = 0; i < 8; i++) {
    canvas->drawString(String((char)('a' + i)), (i * 60) + x + 20, start + 20);
  }
}

void drawPieces(M5EPD_Canvas *canvas, int x, int y) {

  // Get the font size
  canvas->setTextSize(26);

  // Loop over the boardPieces array and draw the pieces on the board
  // We use text to draw the pieces eg. "♟" for black pawn
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int piece = boardPieces[i][j];
      if (piece != 0) {

        // Set the text color based upon the piece number
        // < 7 are white pieces
        // >= 7 are black pieces

        // Draw the piece
        canvas->drawString(getPiece(piece), (j * 60) + x + 10, (i * 60) + y + 20);
        //        canvas->drawString(getPiece(piece), (i * 60) + x, (j * 60) + y);
      }
    }
  }
}

/**
 * Get the piece to draw on the board
 */
String getPiece(int piece) {
  switch (piece) {
  case 1: // white pawn
    return "wP";
  case 2: // white knight
    return "wK";
  case 3: // white bishop
    return "wB";
  case 4: // white rook
    return "wR";
  case 5: // white queen
    return "wQ";
  case 6: // white king
    return "wK";
  case 7: // black pawn
    return "bP";
  case 8: // black knight
    return "bK";
  case 9: // black bishop
    return "bB";
  case 10: // black rook
    return "bR";
  case 11: // black queen
    return "bQ";
  case 12: // black king
    return "bK";
  }

  return "";
}