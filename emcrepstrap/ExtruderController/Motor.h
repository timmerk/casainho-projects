#define DIRECTION 7
#define STEP 5

void enableTimer1Interrupt(void)
{
  //enable our interrupt!
  TIMSK1 |= (1<<OCIE1A);
}

void disableTimer1Interrupt(void)
{
  TIMSK1 &= ~(1<<ICIE1);
  TIMSK1 &= ~(1<<OCIE1A);
}

void setTimer1Resolution(byte r)
{
  //from table 15-5 in that atmega168 datasheet:
  // we're setting CS12 - CS10 which correspond to the binary numbers 0-5
  // 0 = no timer
  // 1 = no prescaler
  // 2 = clock/8
  // 3 = clock/64
  // 4 = clock/256
  // 5 = clock/1024

  if (r > 5)
    r = 5;

  TCCR1B &= B11111000;
  TCCR1B |= r;
}

void setTimer1Ceiling(unsigned int c)
{
  OCR1A = c;
}

unsigned int getTimer1Ceiling(unsigned long ticks)
{
  // our slowest speed at our highest resolution ( (2^16-1) * 0.0625 usecs = 4095 usecs)
  if (ticks <= 65535L)
    return (ticks & 0xffff);
  // our slowest speed at our next highest resolution ( (2^16-1) * 0.5 usecs = 32767 usecs)
  else if (ticks <= 524280L)
    return ((ticks / 8) & 0xffff);
  // our slowest speed at our medium resolution ( (2^16-1) * 4 usecs = 262140 usecs)
  else if (ticks <= 4194240L)
    return ((ticks / 64) & 0xffff);
  // our slowest speed at our medium-low resolution ( (2^16-1) * 16 usecs = 1048560 usecs)
  else if (ticks <= 16776960L)
    return (ticks / 256);
  // our slowest speed at our lowest resolution ((2^16-1) * 64 usecs = 4194240 usecs)
  else if (ticks <= 67107840L)
    return (ticks / 1024);
  //its really slow... hopefully we can just get by with super slow.
  else
    return 65535;
}

byte getTimer1Resolution(unsigned long ticks)
{
  // these also represent frequency: 1000000 / ticks / 2 = frequency in hz.

  // our slowest speed at our highest resolution ( (2^16-1) * 0.0625 usecs = 4095 usecs (4 millisecond max))
  // range: 8Mhz max - 122hz min
  if (ticks <= 65535L)
    return 1;
  // our slowest speed at our next highest resolution ( (2^16-1) * 0.5 usecs = 32767 usecs (32 millisecond max))
  // range:1Mhz max - 15.26hz min
  else if (ticks <= 524280L)
    return 2;
  // our slowest speed at our medium resolution ( (2^16-1) * 4 usecs = 262140 usecs (0.26 seconds max))
  // range: 125Khz max - 1.9hz min
  else if (ticks <= 4194240L)
    return 3;
  // our slowest speed at our medium-low resolution ( (2^16-1) * 16 usecs = 1048560 usecs (1.04 seconds max))
  // range: 31.25Khz max - 0.475hz min
  else if (ticks <= 16776960L)
    return 4;
  // our slowest speed at our lowest resolution ((2^16-1) * 64 usecs = 4194240 usecs (4.19 seconds max))
  // range: 7.812Khz max - 0.119hz min
  else if (ticks <= 67107840L)
    return 5;
  //its really slow... hopefully we can just get by with super slow.
  else
    return 5;
}

void setTimer1Ticks(unsigned long ticks)
{
  // ticks is the delay between interrupts in 62.5 nanosecond ticks.
  //
  // we break it into 5 different resolutions based on the delay.
  // then we set the resolution based on the size of the delay.
  // we also then calculate the timer ceiling required. (ie what the counter counts to)
  // the result is the timer counts up to the appropriate time and then fires an interrupt.
  
  setTimer1Ceiling(getTimer1Ceiling(ticks));
  setTimer1Resolution(getTimer1Resolution(ticks));
}

void setupTimer1Interrupt()
{
  //clear the registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;
  TIMSK1 = 0;

  //waveform generation = 0100 = CTC
  TCCR1B &= ~(1<<WGM13);
  TCCR1B |=  (1<<WGM12);
  TCCR1A &= ~(1<<WGM11);
  TCCR1A &= ~(1<<WGM10);

  //output mode = 00 (disconnected)
  TCCR1A &= ~(1<<COM1A1);
  TCCR1A &= ~(1<<COM1A0);
  TCCR1A &= ~(1<<COM1B1);
  TCCR1A &= ~(1<<COM1B0);

  //start off with a slow frequency.
  setTimer1Resolution(5);
  setTimer1Ceiling(65535);
  disableTimer1Interrupt();
}

class StepperMotor
{
    protected:
    enum MotorStatus {
        MachineOff = 1,
    };

    int pv;
    int sv;
    int speed;
    unsigned char status;

    public:
    
    StepperMotor(void)
    {
        speed = 0;
    }

    /* Do whatever necessary to init the pin mode. */
    virtual void init()
    {
        pinMode(DIRECTION, OUTPUT);
        pinMode(STEP, OUTPUT);
        
        disableTimer1Interrupt();
        setupTimer1Interrupt();
    }

    /* De-energize the motor. Also get called in E-Stop and such. */
    virtual void turnOff()
    {
      this->setSpeed(0); /* Setting speed = 0 stops the motor. There is now way to fully turn off the motor. */
    }

    /* Energize the motor. Get called in Turn-On in EMC2. */
    virtual void turnOn()
    {
      /* Do nothing here. Motor is turned on everytime speed is changed. */
    }

    /* returns the Current Value (The current step) */
    int getPV()
    {
        return pv;
    }

    /* returns the Set Value */
    int getSV()
    {
        return sv;
    }

    /* Set number of steps in one secound */
    void setSpeed(int _speed)
    {
        if ((status & MachineOff)) return;
        
        pv = sv = speed = _speed;

        /* My stepper motor is working in 1/16 step mode, which are 200 * 16 steps for each
         * revolution.
         */
        if (speed == 0)
        {
          disableTimer1Interrupt(); /* This stop the steppers impulses for motor */
          return;
        }
        else
        {
          enableTimer1Interrupt(); /* This starts the steppers impulses for motor */
        }

        /* Set direction pin for Stepper motor controller */
        if (speed > 0)
        {
          digitalWrite(DIRECTION, 1);
        }
        else
        {
          digitalWrite(DIRECTION, 0);
        }
        
        /* Speed = 10000 means 1 revolution per second. */
        setTimer1Ticks((unsigned long) ((50000000) / ((unsigned long) abs(speed))));
        enableTimer1Interrupt(); /* This starts the steppers impulses for motor */
    }
};

