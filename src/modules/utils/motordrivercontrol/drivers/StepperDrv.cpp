#include "StepperDrv.h"

#include "TMC26X/TMC26X.h"
#include "TMC22X/TMC22X.h"
#include "DRV8711/drv8711.h"

#include <map>

void StepperDrv::set_current(uint16_t currentma){};

void StepperDrv::set_enable(bool enable){};

int StepperDrv::set_microsteps(int number_of_steps) {
	return number_of_steps;
}
int StepperDrv::get_microsteps() { return 0; }

bool StepperDrv::set_options(const StepperDrv::options_t& options){ return false; };

void StepperDrv::set_write_only(bool wo){ this->write_only = wo; };

void StepperDrv::dump_status(StreamOutput *stream){};

bool StepperDrv::set_raw_register(StreamOutput *stream, uint32_t reg, uint32_t val){ return false; };
bool StepperDrv::check_alarm(){ return false; };
