#ifndef __RAIL_SWITCH_H__
#define __RAIL_SWITCH_H__
class RailSwitch {
  protected:
    int pin;
    bool pushed;
    unsigned long delay;
    unsigned long t;

  public:
    RailSwitch(int _pin);
    RailSwitch(int _pin, unsigned long _delay);
    void begin(void);
    void set_pushed(void);
    void reset_pushed(void);
    bool is_pushed(void);
};

void on_interrupt(void *arg);
#endif
