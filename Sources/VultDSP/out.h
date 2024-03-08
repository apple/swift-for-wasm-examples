
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef OUT_H
#define OUT_H
#include <stdint.h>
// #include <math.h>
#include "vultin.h"
#include "out.tables.h"

typedef struct _tuple___real_real__ {
   float field_0;
   float field_1;
} _tuple___real_real__;

typedef struct Noise__ctx_type_0 {
   float w1;
} Noise__ctx_type_0;

typedef Noise__ctx_type_0 Noise_pink_type;

static_inline void Noise__ctx_type_0_init(Noise__ctx_type_0 &_output_){
   Noise__ctx_type_0 _ctx;
   _ctx.w1 = 0.0f;
   _output_ = _ctx;
   return ;
}

static_inline void Noise_pink_init(Noise__ctx_type_0 &_output_){
   Noise__ctx_type_0_init(_output_);
   return ;
}

float Noise_pink(Noise__ctx_type_0 &_ctx, float x);

typedef struct Noise__ctx_type_1 {
   int x2;
   int x1;
   Noise__ctx_type_0 _inst1cc;
} Noise__ctx_type_1;

typedef Noise__ctx_type_1 Noise_process_type;

void Noise__ctx_type_1_init(Noise__ctx_type_1 &_output_);

static_inline void Noise_process_init(Noise__ctx_type_1 &_output_){
   Noise__ctx_type_1_init(_output_);
   return ;
}

float Noise_process(Noise__ctx_type_1 &_ctx, float color);

typedef Noise__ctx_type_1 Noise_noteOn_type;

static_inline void Noise_noteOn_init(Noise__ctx_type_1 &_output_){
   Noise__ctx_type_1_init(_output_);
   return ;
}

static_inline void Noise_noteOn(Noise__ctx_type_1 &_ctx, int note, int velocity, int channel){
}

typedef Noise__ctx_type_1 Noise_noteOff_type;

static_inline void Noise_noteOff_init(Noise__ctx_type_1 &_output_){
   Noise__ctx_type_1_init(_output_);
   return ;
}

static_inline void Noise_noteOff(Noise__ctx_type_1 &_ctx, int note, int channel){
}

typedef Noise__ctx_type_1 Noise_controlChange_type;

static_inline void Noise_controlChange_init(Noise__ctx_type_1 &_output_){
   Noise__ctx_type_1_init(_output_);
   return ;
}

static_inline void Noise_controlChange(Noise__ctx_type_1 &_ctx, int control, int value, int channel){
}

typedef Noise__ctx_type_1 Noise_default_type;

static_inline void Noise_default_init(Noise__ctx_type_1 &_output_){
   Noise__ctx_type_1_init(_output_);
   return ;
}

static_inline void Noise_default(Noise__ctx_type_1 &_ctx){
}

typedef struct Util__ctx_type_0 {
   uint8_t pre;
} Util__ctx_type_0;

typedef Util__ctx_type_0 Util_edge_type;

static_inline void Util__ctx_type_0_init(Util__ctx_type_0 &_output_){
   Util__ctx_type_0 _ctx;
   _ctx.pre = false;
   _output_ = _ctx;
   return ;
}

static_inline void Util_edge_init(Util__ctx_type_0 &_output_){
   Util__ctx_type_0_init(_output_);
   return ;
}

static_inline uint8_t Util_edge(Util__ctx_type_0 &_ctx, uint8_t x){
   uint8_t ret;
   ret = (x && bool_not(_ctx.pre));
   _ctx.pre = x;
   return ret;
}

typedef struct Util__ctx_type_1 {
   float pre_x;
} Util__ctx_type_1;

typedef Util__ctx_type_1 Util_change_type;

static_inline void Util__ctx_type_1_init(Util__ctx_type_1 &_output_){
   Util__ctx_type_1 _ctx;
   _ctx.pre_x = 0.0f;
   _output_ = _ctx;
   return ;
}

static_inline void Util_change_init(Util__ctx_type_1 &_output_){
   Util__ctx_type_1_init(_output_);
   return ;
}

static_inline uint8_t Util_change(Util__ctx_type_1 &_ctx, float x){
   uint8_t v;
   v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

static_inline float Util_map(float x, float x0, float x1, float y0, float y1){
   return (y0 + (((x + (- x0)) * (y1 + (- y0))) / (x1 + (- x0))));
};

typedef struct Util__ctx_type_3 {
   float y1;
   float x1;
} Util__ctx_type_3;

typedef Util__ctx_type_3 Util_dcblock_type;

void Util__ctx_type_3_init(Util__ctx_type_3 &_output_);

static_inline void Util_dcblock_init(Util__ctx_type_3 &_output_){
   Util__ctx_type_3_init(_output_);
   return ;
}

float Util_dcblock(Util__ctx_type_3 &_ctx, float x0);

typedef struct Util__ctx_type_4 {
   float x;
} Util__ctx_type_4;

typedef Util__ctx_type_4 Util_smooth_type;

static_inline void Util__ctx_type_4_init(Util__ctx_type_4 &_output_){
   Util__ctx_type_4 _ctx;
   _ctx.x = 0.0f;
   _output_ = _ctx;
   return ;
}

static_inline void Util_smooth_init(Util__ctx_type_4 &_output_){
   Util__ctx_type_4_init(_output_);
   return ;
}

static_inline float Util_smooth(Util__ctx_type_4 &_ctx, float input){
   _ctx.x = (_ctx.x + (0.005f * (input + (- _ctx.x))));
   return _ctx.x;
}

typedef struct Util__ctx_type_5 {
   float x0;
} Util__ctx_type_5;

typedef Util__ctx_type_5 Util_average2_type;

static_inline void Util__ctx_type_5_init(Util__ctx_type_5 &_output_){
   Util__ctx_type_5 _ctx;
   _ctx.x0 = 0.0f;
   _output_ = _ctx;
   return ;
}

static_inline void Util_average2_init(Util__ctx_type_5 &_output_){
   Util__ctx_type_5_init(_output_);
   return ;
}

static_inline float Util_average2(Util__ctx_type_5 &_ctx, float x1){
   float result;
   result = (0.5f * (_ctx.x0 + x1));
   _ctx.x0 = x1;
   return result;
}

static_inline float Util_cubic_clipper(float x){
   if(x <= -0.666666666667f){
      return -0.666666666667f;
   }
   else
   {
      if(x >= 0.666666666667f){
         return 0.666666666667f;
      }
      else
      {
         return (x + (-0.333333333333f * x * x * x));
      }
   }
};

static_inline float Util_pitchToRate_1024_raw_c0(int index){
   return Util_pitchToRate_1024_c0[index];
};

static_inline float Util_pitchToRate_1024_raw_c1(int index){
   return Util_pitchToRate_1024_c1[index];
};

static_inline float Util_pitchToRate_1024_raw_c2(int index){
   return Util_pitchToRate_1024_c2[index];
};

static_inline float Util_pitchToRate_1024(float pitch){
   int index;
   index = int_clip(float_to_int((0.244094488189f * pitch)),0,31);
   return (float_wrap_array(Util_pitchToRate_1024_c0)[index] + (pitch * (float_wrap_array(Util_pitchToRate_1024_c1)[index] + (pitch * float_wrap_array(Util_pitchToRate_1024_c2)[index]))));
}

static_inline float Util_pitchToRate_raw_c0(int index){
   return Util_pitchToRate_c0[index];
};

static_inline float Util_pitchToRate_raw_c1(int index){
   return Util_pitchToRate_c1[index];
};

static_inline float Util_pitchToRate_raw_c2(int index){
   return Util_pitchToRate_c2[index];
};

static_inline float Util_pitchToRate(float pitch){
   int index;
   index = int_clip(float_to_int((0.244094488189f * pitch)),0,31);
   return (float_wrap_array(Util_pitchToRate_c0)[index] + (pitch * (float_wrap_array(Util_pitchToRate_c1)[index] + (pitch * float_wrap_array(Util_pitchToRate_c2)[index]))));
}

static_inline float Util_cvToPitch(float cv){
   return (24.f + (120.f * cv));
};

static_inline float Util_cvToRate_1024_raw_c0(int index){
   return Util_cvToRate_1024_c0[index];
};

static_inline float Util_cvToRate_1024_raw_c1(int index){
   return Util_cvToRate_1024_c1[index];
};

static_inline float Util_cvToRate_1024_raw_c2(int index){
   return Util_cvToRate_1024_c2[index];
};

static_inline float Util_cvToRate_1024(float cv){
   int index;
   index = int_clip(float_to_int((34.4444444444f * cv)),0,31);
   return (float_wrap_array(Util_cvToRate_1024_c0)[index] + (cv * (float_wrap_array(Util_cvToRate_1024_c1)[index] + (cv * float_wrap_array(Util_cvToRate_1024_c2)[index]))));
}

static_inline float Util_cvToRate_raw_c0(int index){
   return Util_cvToRate_c0[index];
};

static_inline float Util_cvToRate_raw_c1(int index){
   return Util_cvToRate_c1[index];
};

static_inline float Util_cvToRate_raw_c2(int index){
   return Util_cvToRate_c2[index];
};

static_inline float Util_cvToRate(float cv){
   int index;
   index = int_clip(float_to_int((141.111111111f * cv)),0,127);
   return (float_wrap_array(Util_cvToRate_c0)[index] + (cv * (float_wrap_array(Util_cvToRate_c1)[index] + (cv * float_wrap_array(Util_cvToRate_c2)[index]))));
}

static_inline float Util_pitchToCv(float pitch){
   return (0.00833333333333f * (-24.f + pitch));
};

static_inline float Util_cvToperiod_raw_c0(int index){
   return Util_cvToperiod_c0[index];
};

static_inline float Util_cvToperiod_raw_c1(int index){
   return Util_cvToperiod_c1[index];
};

static_inline float Util_cvToperiod_raw_c2(int index){
   return Util_cvToperiod_c2[index];
};

static_inline float Util_cvToperiod(float cv){
   int index;
   index = int_clip(float_to_int((31.f * cv)),0,31);
   return (float_wrap_array(Util_cvToperiod_c0)[index] + (cv * (float_wrap_array(Util_cvToperiod_c1)[index] + (cv * float_wrap_array(Util_cvToperiod_c2)[index]))));
}

static_inline float Util_cvTokHz_raw_c0(int index){
   return Util_cvTokHz_c0[index];
};

static_inline float Util_cvTokHz_raw_c1(int index){
   return Util_cvTokHz_c1[index];
};

static_inline float Util_cvTokHz_raw_c2(int index){
   return Util_cvTokHz_c2[index];
};

static_inline float Util_cvTokHz(float cv){
   int index;
   index = int_clip(float_to_int((31.f * cv)),0,31);
   return (float_wrap_array(Util_cvTokHz_c0)[index] + (cv * (float_wrap_array(Util_cvTokHz_c1)[index] + (cv * float_wrap_array(Util_cvTokHz_c2)[index]))));
}

static_inline float Ladder_tune_raw_c0(int index){
   return Ladder_tune_c0[index];
};

static_inline float Ladder_tune_raw_c1(int index){
   return Ladder_tune_c1[index];
};

static_inline float Ladder_tune_raw_c2(int index){
   return Ladder_tune_c2[index];
};

static_inline float Ladder_tune(float cut){
   int index;
   index = int_clip(float_to_int((127.f * cut)),0,127);
   return (float_wrap_array(Ladder_tune_c0)[index] + (cut * (float_wrap_array(Ladder_tune_c1)[index] + (cut * float_wrap_array(Ladder_tune_c2)[index]))));
}

typedef struct Ladder__ctx_type_4 {
   float p3;
   float p2;
   float p1;
   float p0;
} Ladder__ctx_type_4;

typedef Ladder__ctx_type_4 Ladder_heun_type;

void Ladder__ctx_type_4_init(Ladder__ctx_type_4 &_output_);

static_inline void Ladder_heun_init(Ladder__ctx_type_4 &_output_){
   Ladder__ctx_type_4_init(_output_);
   return ;
}

float Ladder_heun(Ladder__ctx_type_4 &_ctx, float input, float fh, float res);

typedef struct Ladder__ctx_type_5 {
   float p3;
   float p2;
   float p1;
   float p0;
} Ladder__ctx_type_5;

typedef Ladder__ctx_type_5 Ladder_euler_type;

void Ladder__ctx_type_5_init(Ladder__ctx_type_5 &_output_);

static_inline void Ladder_euler_init(Ladder__ctx_type_5 &_output_){
   Ladder__ctx_type_5_init(_output_);
   return ;
}

float Ladder_euler(Ladder__ctx_type_5 &_ctx, float input, float fh, float res);

typedef struct Ladder__ctx_type_6 {
   float fh;
   Ladder__ctx_type_5 e;
   Util__ctx_type_1 _inst13b;
} Ladder__ctx_type_6;

typedef Ladder__ctx_type_6 Ladder_process_euler_type;

void Ladder__ctx_type_6_init(Ladder__ctx_type_6 &_output_);

static_inline void Ladder_process_euler_init(Ladder__ctx_type_6 &_output_){
   Ladder__ctx_type_6_init(_output_);
   return ;
}

float Ladder_process_euler(Ladder__ctx_type_6 &_ctx, float input, float cut, float res);

typedef struct Ladder__ctx_type_7 {
   Ladder__ctx_type_4 h;
   float fh;
   Util__ctx_type_1 _inst13b;
} Ladder__ctx_type_7;

typedef Ladder__ctx_type_7 Ladder_process_heun_type;

void Ladder__ctx_type_7_init(Ladder__ctx_type_7 &_output_);

static_inline void Ladder_process_heun_init(Ladder__ctx_type_7 &_output_){
   Ladder__ctx_type_7_init(_output_);
   return ;
}

float Ladder_process_heun(Ladder__ctx_type_7 &_ctx, float input, float cut, float res);

typedef struct Ladder__ctx_type_8 {
   Ladder__ctx_type_7 _inst112;
} Ladder__ctx_type_8;

typedef Ladder__ctx_type_8 Ladder_process_type;

static_inline void Ladder__ctx_type_8_init(Ladder__ctx_type_8 &_output_){
   Ladder__ctx_type_8 _ctx;
   Ladder__ctx_type_7_init(_ctx._inst112);
   _output_ = _ctx;
   return ;
}

static_inline void Ladder_process_init(Ladder__ctx_type_8 &_output_){
   Ladder__ctx_type_8_init(_output_);
   return ;
}

static_inline float Ladder_process(Ladder__ctx_type_8 &_ctx, float input, float cut, float res){
   return Ladder_process_heun(_ctx._inst112,input,cut,res);
};

typedef struct Triangle__ctx_type_0 {
   uint8_t reset_state;
   float reset_phase;
   float rate;
   float phase;
   uint8_t direction;
   Util__ctx_type_0 _inst451;
   Util__ctx_type_0 _inst351;
   Util__ctx_type_1 _inst13b;
} Triangle__ctx_type_0;

typedef Triangle__ctx_type_0 Triangle_process_type;

void Triangle__ctx_type_0_init(Triangle__ctx_type_0 &_output_);

static_inline void Triangle_process_init(Triangle__ctx_type_0 &_output_){
   Triangle__ctx_type_0_init(_output_);
   return ;
}

float Triangle_process(Triangle__ctx_type_0 &_ctx, float cv, float reset, float disable);

typedef Triangle__ctx_type_0 Triangle_noteOn_type;

static_inline void Triangle_noteOn_init(Triangle__ctx_type_0 &_output_){
   Triangle__ctx_type_0_init(_output_);
   return ;
}

static_inline void Triangle_noteOn(Triangle__ctx_type_0 &_ctx, int note, int velocity, int channel){
}

typedef Triangle__ctx_type_0 Triangle_noteOff_type;

static_inline void Triangle_noteOff_init(Triangle__ctx_type_0 &_output_){
   Triangle__ctx_type_0_init(_output_);
   return ;
}

static_inline void Triangle_noteOff(Triangle__ctx_type_0 &_ctx, int note, int channel){
}

typedef Triangle__ctx_type_0 Triangle_controlChange_type;

static_inline void Triangle_controlChange_init(Triangle__ctx_type_0 &_output_){
   Triangle__ctx_type_0_init(_output_);
   return ;
}

static_inline void Triangle_controlChange(Triangle__ctx_type_0 &_ctx, int control, int value, int channel){
}

typedef Triangle__ctx_type_0 Triangle_default_type;

static_inline void Triangle_default_init(Triangle__ctx_type_0 &_output_){
   Triangle__ctx_type_0_init(_output_);
   return ;
}

static_inline void Triangle_default(Triangle__ctx_type_0 &_ctx){
   _ctx.rate = 0.759366720147f;
};

typedef struct Swept__ctx_type_0 {
   float out;
   Util__ctx_type_0 _inst151;
} Swept__ctx_type_0;

typedef Swept__ctx_type_0 Swept_process_type;

void Swept__ctx_type_0_init(Swept__ctx_type_0 &_output_);

static_inline void Swept_process_init(Swept__ctx_type_0 &_output_){
   Swept__ctx_type_0_init(_output_);
   return ;
}

float Swept_process(Swept__ctx_type_0 &_ctx, float gate, float start, float end, float rate);

typedef Swept__ctx_type_0 Swept_noteOn_type;

static_inline void Swept_noteOn_init(Swept__ctx_type_0 &_output_){
   Swept__ctx_type_0_init(_output_);
   return ;
}

static_inline void Swept_noteOn(Swept__ctx_type_0 &_ctx, int note, int velocity, int channel){
}

typedef Swept__ctx_type_0 Swept_noteOff_type;

static_inline void Swept_noteOff_init(Swept__ctx_type_0 &_output_){
   Swept__ctx_type_0_init(_output_);
   return ;
}

static_inline void Swept_noteOff(Swept__ctx_type_0 &_ctx, int note, int channel){
}

typedef Swept__ctx_type_0 Swept_controlChange_type;

static_inline void Swept_controlChange_init(Swept__ctx_type_0 &_output_){
   Swept__ctx_type_0_init(_output_);
   return ;
}

static_inline void Swept_controlChange(Swept__ctx_type_0 &_ctx, int control, int value, int channel){
}

typedef Swept__ctx_type_0 Swept_default_type;

static_inline void Swept_default_init(Swept__ctx_type_0 &_output_){
   Swept__ctx_type_0_init(_output_);
   return ;
}

static_inline void Swept_default(Swept__ctx_type_0 &_ctx){
}

static_inline float Saturate_tanh_table_raw_c0(int index){
   return Saturate_tanh_table_c0[index];
};

static_inline float Saturate_tanh_table_raw_c1(int index){
   return Saturate_tanh_table_c1[index];
};

static_inline float Saturate_tanh_table_raw_c2(int index){
   return Saturate_tanh_table_c2[index];
};

static_inline float Saturate_tanh_table(float x){
   int index;
   index = int_clip(float_to_int((5.f * (24.f + x))),0,240);
   return (float_wrap_array(Saturate_tanh_table_c0)[index] + (x * (float_wrap_array(Saturate_tanh_table_c1)[index] + (x * float_wrap_array(Saturate_tanh_table_c2)[index]))));
}

static_inline float Saturate_process(float x){
   return Saturate_tanh_table(x);
};

static_inline void Saturate_noteOn(int note, int velocity, int channel){
}

static_inline void Saturate_noteOff(int note, int channel){
}

static_inline void Saturate_controlChange(int control, int value, int channel){
}

static_inline void Saturate_default(){
}

typedef struct Ahr__ctx_type_0 {
   float target;
   int state;
   float rate;
   float out;
   float hold_phase;
   float do_ret_1;
   float do_ret_0;
   Util__ctx_type_0 _inst351;
   Util__ctx_type_0 _inst151;
} Ahr__ctx_type_0;

typedef Ahr__ctx_type_0 Ahr_do_type;

void Ahr__ctx_type_0_init(Ahr__ctx_type_0 &_output_);

static_inline void Ahr_do_init(Ahr__ctx_type_0 &_output_){
   Ahr__ctx_type_0_init(_output_);
   return ;
}

void Ahr_do(Ahr__ctx_type_0 &_ctx, float gate, float a, float h, float r);

typedef Ahr__ctx_type_0 Ahr_do_ret_0_type;

static_inline void Ahr_do_ret_0_init(Ahr__ctx_type_0 &_output_){
   Ahr__ctx_type_0_init(_output_);
   return ;
}

static_inline float Ahr_do_ret_0(Ahr__ctx_type_0 &_ctx){
   return _ctx.do_ret_0;
};

typedef Ahr__ctx_type_0 Ahr_do_ret_1_type;

static_inline void Ahr_do_ret_1_init(Ahr__ctx_type_0 &_output_){
   Ahr__ctx_type_0_init(_output_);
   return ;
}

static_inline float Ahr_do_ret_1(Ahr__ctx_type_0 &_ctx){
   return _ctx.do_ret_1;
};

typedef struct Ahr__ctx_type_1 {
   float process_ret_1;
   float process_ret_0;
   float knob3;
   float knob2;
   float knob1;
   Ahr__ctx_type_0 _inst147;
} Ahr__ctx_type_1;

typedef Ahr__ctx_type_1 Ahr_process_type;

void Ahr__ctx_type_1_init(Ahr__ctx_type_1 &_output_);

static_inline void Ahr_process_init(Ahr__ctx_type_1 &_output_){
   Ahr__ctx_type_1_init(_output_);
   return ;
}

static_inline void Ahr_process(Ahr__ctx_type_1 &_ctx, float gate){
   Ahr_do(_ctx._inst147,gate,_ctx.knob1,_ctx.knob2,_ctx.knob3);
   _ctx.process_ret_0 = Ahr_do_ret_0(_ctx._inst147);
   _ctx.process_ret_1 = Ahr_do_ret_1(_ctx._inst147);
   return ;
}

typedef Ahr__ctx_type_1 Ahr_process_ret_0_type;

static_inline void Ahr_process_ret_0_init(Ahr__ctx_type_1 &_output_){
   Ahr__ctx_type_1_init(_output_);
   return ;
}

static_inline float Ahr_process_ret_0(Ahr__ctx_type_1 &_ctx){
   return _ctx.process_ret_0;
};

typedef Ahr__ctx_type_1 Ahr_process_ret_1_type;

static_inline void Ahr_process_ret_1_init(Ahr__ctx_type_1 &_output_){
   Ahr__ctx_type_1_init(_output_);
   return ;
}

static_inline float Ahr_process_ret_1(Ahr__ctx_type_1 &_ctx){
   return _ctx.process_ret_1;
};

typedef Ahr__ctx_type_1 Ahr_noteOn_type;

static_inline void Ahr_noteOn_init(Ahr__ctx_type_1 &_output_){
   Ahr__ctx_type_1_init(_output_);
   return ;
}

static_inline void Ahr_noteOn(Ahr__ctx_type_1 &_ctx, int note, int velocity, int channel){
}

typedef Ahr__ctx_type_1 Ahr_noteOff_type;

static_inline void Ahr_noteOff_init(Ahr__ctx_type_1 &_output_){
   Ahr__ctx_type_1_init(_output_);
   return ;
}

static_inline void Ahr_noteOff(Ahr__ctx_type_1 &_ctx, int note, int channel){
}

typedef Ahr__ctx_type_1 Ahr_controlChange_type;

static_inline void Ahr_controlChange_init(Ahr__ctx_type_1 &_output_){
   Ahr__ctx_type_1_init(_output_);
   return ;
}

void Ahr_controlChange(Ahr__ctx_type_1 &_ctx, int control, int value, int channel);

typedef Ahr__ctx_type_1 Ahr_default_type;

static_inline void Ahr_default_init(Ahr__ctx_type_1 &_output_){
   Ahr__ctx_type_1_init(_output_);
   return ;
}

static_inline void Ahr_default(Ahr__ctx_type_1 &_ctx){
   _ctx.knob1 = 0.0f;
   _ctx.knob2 = 0.5f;
   _ctx.knob3 = 0.5f;
}

typedef struct Kick__ctx_type_0 {
   Noise__ctx_type_1 _inst5ab;
   Ahr__ctx_type_0 _inst447;
   Triangle__ctx_type_0 _inst3ca;
   Swept__ctx_type_0 _inst2eb;
   Ahr__ctx_type_0 _inst147;
} Kick__ctx_type_0;

typedef Kick__ctx_type_0 Kick_do_type;

void Kick__ctx_type_0_init(Kick__ctx_type_0 &_output_);

static_inline void Kick_do_init(Kick__ctx_type_0 &_output_){
   Kick__ctx_type_0_init(_output_);
   return ;
}

float Kick_do(Kick__ctx_type_0 &_ctx, float gate, float odecay, float pitch, float swept, float noise);

typedef struct Kick__ctx_type_1 {
   float swept;
   float pitch;
   float odecay;
   float noise;
   Kick__ctx_type_0 _inst120;
} Kick__ctx_type_1;

typedef Kick__ctx_type_1 Kick_process_type;

void Kick__ctx_type_1_init(Kick__ctx_type_1 &_output_);

static_inline void Kick_process_init(Kick__ctx_type_1 &_output_){
   Kick__ctx_type_1_init(_output_);
   return ;
}

static_inline float Kick_process(Kick__ctx_type_1 &_ctx, float gate){
   return Kick_do(_ctx._inst120,gate,_ctx.odecay,_ctx.pitch,_ctx.swept,_ctx.noise);
};

typedef Kick__ctx_type_1 Kick_noteOn_type;

static_inline void Kick_noteOn_init(Kick__ctx_type_1 &_output_){
   Kick__ctx_type_1_init(_output_);
   return ;
}

static_inline void Kick_noteOn(Kick__ctx_type_1 &_ctx, int note, int velocity, int channel){
}

typedef Kick__ctx_type_1 Kick_noteOff_type;

static_inline void Kick_noteOff_init(Kick__ctx_type_1 &_output_){
   Kick__ctx_type_1_init(_output_);
   return ;
}

static_inline void Kick_noteOff(Kick__ctx_type_1 &_ctx, int note, int channel){
}

typedef Kick__ctx_type_1 Kick_controlChange_type;

static_inline void Kick_controlChange_init(Kick__ctx_type_1 &_output_){
   Kick__ctx_type_1_init(_output_);
   return ;
}

void Kick_controlChange(Kick__ctx_type_1 &_ctx, int control, int value, int channel);

typedef Kick__ctx_type_1 Kick_default_type;

static_inline void Kick_default_init(Kick__ctx_type_1 &_output_){
   Kick__ctx_type_1_init(_output_);
   return ;
}

static_inline void Kick_default(Kick__ctx_type_1 &_ctx){
}

typedef struct Phase__ctx_type_0 {
   float rate;
   float phase;
   Util__ctx_type_0 _inst351;
   Util__ctx_type_1 _inst13b;
} Phase__ctx_type_0;

typedef Phase__ctx_type_0 Phase_process_type;

void Phase__ctx_type_0_init(Phase__ctx_type_0 &_output_);

static_inline void Phase_process_init(Phase__ctx_type_0 &_output_){
   Phase__ctx_type_0_init(_output_);
   return ;
}

float Phase_process(Phase__ctx_type_0 &_ctx, float cv, float reset);

typedef Phase__ctx_type_0 Phase_noteOn_type;

static_inline void Phase_noteOn_init(Phase__ctx_type_0 &_output_){
   Phase__ctx_type_0_init(_output_);
   return ;
}

static_inline void Phase_noteOn(Phase__ctx_type_0 &_ctx, int note, int velocity, int channel){
}

typedef Phase__ctx_type_0 Phase_noteOff_type;

static_inline void Phase_noteOff_init(Phase__ctx_type_0 &_output_){
   Phase__ctx_type_0_init(_output_);
   return ;
}

static_inline void Phase_noteOff(Phase__ctx_type_0 &_ctx, int note, int channel){
}

typedef Phase__ctx_type_0 Phase_controlChange_type;

static_inline void Phase_controlChange_init(Phase__ctx_type_0 &_output_){
   Phase__ctx_type_0_init(_output_);
   return ;
}

static_inline void Phase_controlChange(Phase__ctx_type_0 &_ctx, int control, int value, int channel){
}

typedef Phase__ctx_type_0 Phase_default_type;

static_inline void Phase_default_init(Phase__ctx_type_0 &_output_){
   Phase__ctx_type_0_init(_output_);
   return ;
}

static_inline void Phase_default(Phase__ctx_type_0 &_ctx){
   _ctx.rate = 0.759366720147f;
};

static_inline float Tables_nsine_raw_c0(int index){
   return Tables_nsine_c0[index];
};

static_inline float Tables_nsine_raw_c1(int index){
   return Tables_nsine_c1[index];
};

static_inline float Tables_nsine_raw_c2(int index){
   return Tables_nsine_c2[index];
};

static_inline float Tables_nsine(float x){
   int index;
   index = int_clip(float_to_int((127.f * x)),0,127);
   return (float_wrap_array(Tables_nsine_c0)[index] + (x * (float_wrap_array(Tables_nsine_c1)[index] + (x * float_wrap_array(Tables_nsine_c2)[index]))));
}

typedef struct Sine__ctx_type_0 {
   uint8_t trig;
   Phase__ctx_type_0 p;
   Util__ctx_type_0 _inst151;
} Sine__ctx_type_0;

typedef Sine__ctx_type_0 Sine_process_type;

void Sine__ctx_type_0_init(Sine__ctx_type_0 &_output_);

static_inline void Sine_process_init(Sine__ctx_type_0 &_output_){
   Sine__ctx_type_0_init(_output_);
   return ;
}

float Sine_process(Sine__ctx_type_0 &_ctx, float cv, float reset);



#endif // OUT_H
