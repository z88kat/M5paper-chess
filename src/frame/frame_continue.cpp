
#include "frame_continue.h"
#include "../chess/board.h"

M5EPD_Canvas *canvas;

/**
 * First this is called, appears to be called once only
 */
Frame_Continue::Frame_Continue(void) {
  _frame_name = "Frame_Continue";
  Serial.println("Frame_Continue::Frame_Continue");

  M5EPD_Canvas canvas_temp(&M5.EPD);
  canvas_temp.createRender(36);

  exitbtn("Home");
  _canvas_title->drawString("Chess", 270, 34);

  _key_exit->AddArgs(EPDGUI_Button::EVENT_RELEASED, 0, (void *)(&_is_run));
  _key_exit->Bind(EPDGUI_Button::EVENT_RELEASED, &Frame_Base::exit_cb);
}

/**
 *  Called when we exit the page
 */
Frame_Continue::~Frame_Continue(void) {

  // Something goes here
  Serial.println("Frame_Continue::~Frame_Continue 3rd called???");
}

/**
 * Second Once the pagee is entered draw it here.
 * Called every time we enter the page
 */
int Frame_Continue::init(epdgui_args_vector_t &args) {
  Serial.println("Frame_Continue::init");
  _is_run = 1;
  M5.EPD.Clear();
  _canvas_title->pushCanvas(0, 8, UPDATE_MODE_NONE);

  canvas = new M5EPD_Canvas(&M5.EPD);

  // Set the start 32 pixels from the top
  canvas->createCanvas(540, 960 - 100);

  // Width, height
  // canvas->createCanvas(540, 132);

  drawBoard(canvas);

  EPDGUI_AddObject(_key_exit);
  return 3;
}

int Frame_Continue::run() {
  Frame_Base::run();

  loopInteraction(canvas);
  return 1;
}