/**
 *
 */

#include "board.h"

const int WIDTH = 540;
const int HEIGHT = 960;
const int TFT_BLACK_COLOR = 15; // This appears to be black based on gray scale level
const int TFT_WHITE_COLOR = 0;  // This appears to be white based on gray scale level
const int TFT_GRAY_COLOR = 7;

EPDGUI_Button *_board_cell_event[8][8];
EPDGUI_Button *key_textclear;

uint32_t _last_x, _last_y;

// An array which keeps track of the position of the pieces
// 0 - empty
// 1 - white pawn
// 2 - white knight
// 3 - white bishop
// 4 - white rook
// 5 - white queen
// 6 - white king
// -1 - black pawn
// -2 - black knight
// -3 - black bishop
// -4 - black rook
// -5 - black queen
// -6 - black king

// clang-format off
int boardPieces[8][8] = {
  {4, 2, 3, 5, 6, 3, 2, 4},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {-1, -1, -1, -1, -1, -1, -1, -1},
  {-4, -2, -3, -5, -6, -3, -2, -4}
};

// clang-format on
void drawBoard(M5EPD_Canvas *canvas) {
  // Something goes here

  _last_x = 0;
  _last_y = 0;

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
  //  canvas->pushImage(20, 10, 48, 48, piece_bb_white);
  // canvas->pushImage(20, 10, 48, 48, 15, piece_bb);

  key_textclear = new EPDGUI_Button("CLR", 50, startY + 150, 100, 52);
  key_textclear->Bind(EPDGUI_Button::EVENT_RELEASED, cell_cb);

  EPDGUI_AddObject(key_textclear);

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

      // EPDGUI_Button *_key_wifi[14];
      //      _board_cell_event[i][j] = new EPDGUI_Button((i * 60) + x, (j * 60) + y, 60, 60);
      //    _board_cell_event[i][j]->SetHide(false);
      //  _board_cell_event[i][j]->Bind(EPDGUI_Button::EVENT_RELEASED, cell_cb);
      // EPDGUI_AddObject(_board_cell_event[i][j]);
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
        // 1 -> 6 are white pieces
        // -1 -> -6 are black pieces

        // Depending on the cell we toggle black or white background
        if ((i + j) % 2 == 0) {
          // Draw the piece
          canvas->pushImage((j * 60) + x + 6, (i * 60) + y + 4, 48, 48, getPieceImageWhiteBackground(piece));
        } else {
          // Draw the piece
          canvas->pushImage((j * 60) + x + 6, (i * 60) + y + 4, 48, 48, getPieceImageBlackBackground(piece));
        }
      }
    }
  }
}

// function to return the static images from imagePieces.h
const uint8_t *getPieceImageWhiteBackground(int piece) {
  switch (piece) {
  case 1: // white pawn
    return piece_wp_white;
  case 2: // white knight
    return piece_bb_white;
  case 3: // white bishop
    return piece_bb_white;
  case 4: // white rook
    return piece_bb_white;
  case 5: // white queen
    return piece_bb_white;
  case 6: // white king
    return piece_bb_white;
  case -1: // black pawn
    return piece_bp_white;
  case -2: // black knight
    return piece_bb_white;
  case -3: // black bishop
    return piece_bb_white;
  case -4: // black rook
    return piece_bb_white;
  case -5: // black queen
    return piece_bb_white;
  case -6: // black king
    return piece_bk_white;
  }

  return piece_bb_white;
}

// function to return the static images from imagePieces.h
const uint8_t *getPieceImageBlackBackground(int piece) {
  switch (piece) {
  case 1: // white pawn
    return piece_wp_black;
  case 2: // white knight
    return piece_bb_black;
  case 3: // white bishop
    return piece_bb_black;
  case 4: // white rook
    return piece_bb_black;
  case 5: // white queen
    return piece_bb_black;
  case 6: // white king
    return piece_bb_black;
  case -1: // black pawn
    return piece_bp_black;
  case -2: // black knight
    return piece_bb_black;
  case -3: // black bishop
    return piece_bb_black;
  case -4: // black rook
    return piece_bb_black;
  case -5: // black queen
    return piece_bb_black;
  case -6: // black king
    return piece_bk_black;
  }

  return piece_bb_black;
}

void cell_cb(epdgui_args_vector_t &args) { Serial.println("Cell clicked"); }

void destroy() { delete key_textclear; }

/**
 * Get a string representation of the cell reference
 * eg: a1, a8, f6 etc
 */
String getChessCellReference(int row, int column) {
  // Convert the row and column number to a chess cell reference
  // eg. 0,0 -> a8
  // eg. 7,7 -> h1
  String cell = "";
  cell += (char)('a' + column);
  cell += (char)('8' - row);
  return cell;
}

/**
 * Get the name of the chess piece based upon the given value
 * 1 - white pawn
 * 2 - white knight
 * 3 - white bishop
 */
String getChessPieceName(int piece) {
  switch (piece) {
  case 1:
    return "White Pawn";
  case 2:
    return "White Knight";
  case 3:
    return "White Bishop";
  case 4:
    return "White Rook";
  case 5:
    return "White Queen";
  case 6:
    return "White King";
  case -1:
    return "Black Pawn";
  case -2:
    return "Black Knight";
  case -3:
    return "Black Bishop";
  case -4:
    return "Black Rook";
  case -5:
    return "Black Queen";
  case -6:
    return "Black King";
  }
  return "Empty Cell";
}

void loopInteraction(M5EPD_Canvas *canvas) {
  // put your main code here, to run repeatedly:
  // Serial.println("Loop");

  // The x and y position of the user's finger must be within bounds of the board
  // The x position must be between 30 and 510
  // The y position must be between 180 and 900

  if (((M5.TP.readFingerX(0) != _last_x) || (M5.TP.readFingerY(0) != _last_y)) && (M5.TP.readFingerX(0) > 30 && M5.TP.readFingerX(0) < 510) &&
      (M5.TP.readFingerY(0) > 180 && M5.TP.readFingerY(0) < 900)) {

    _last_x = M5.TP.readFingerX(0);
    _last_y = M5.TP.readFingerY(0);

    // String of the x,y position
    // String position = "X: " + String(_last_x) + ", Y: " + String(_last_y);
    // Serial.println(position);

    // We need to calculate which of the 64 cells the user has clicked
    // The starting x positon is 30 and the starting y position is 180 (100 from the top + 80 we stated)
    // Each cell is 60 x 60
    // Now we can calculate which cell the user has clicked

    // The x position is the column number
    // The y position is the row number
    // We can calculate the row and column number by dividing the x and y position by 60
    int column = (_last_x - 30) / 60;
    int row = (_last_y - 180) / 60;

    // The column row must be within the bounds of the board
    if (column < 0 || column > 7 || row < 0 || row > 7) {
      return;
    }

    // Get the selected cell, eg: a6
    String cell = getChessCellReference(row, column);

    // Get the piece in the array at the selected column and row
    int piece = boardPieces[row][column];

    // Get the name of the piece in the selected cell
    String pieceName = getChessPieceName(piece);

    Serial.println("Row: " + String(row) + ", Column: " + String(column) + ", Cell: " + cell + ", Piece: " + pieceName);

    // Set the font size
    canvas->setTextSize(26);
    // Write the name of the piece
    canvas->drawString(cell + " (" + pieceName + ")", 30, 15);
    canvas->pushCanvas(0, 100, UPDATE_MODE_DU);

    // M5.EPD.UpdateArea(0, 720, 0, 280, UPDATE_MODE_GL16);

    //_canvas_pos->fillCanvas(0);
    //_canvas_pos->drawString(buf, POS_RX, 30);
    //_canvas_pos->pushCanvas(300, 640, UPDATE_MODE_A2);
  }
}