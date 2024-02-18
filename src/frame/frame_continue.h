#ifndef _FRAME_CONTINUE_H_
#define _FRAME_CONTINUE_H_

#include "frame_base.h"
#include "../epdgui/epdgui.h"

class Frame_Continue : public Frame_Base {
   public:
    Frame_Continue();
    ~Frame_Continue();
    int run();
    int init(epdgui_args_vector_t &args);
    void InitSwitch(EPDGUI_Switch *sw, String title, String subtitle,
                    const uint8_t *img1, const uint8_t *img2);

};

#endif  //_FRAME_CONTINUE_H_