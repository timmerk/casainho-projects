// Thermistor lookup table for RepRap Temperature Sensor Boards (http://make.rrrf.org/ts)
// Made with createTemperatureLookup.py (http://svn.reprap.org/trunk/reprap/firmware/Arduino/utilities/createTemperatureLookup.py)

#define NUMTEMPS 20
short temptable[NUMTEMPS][2] = {
  {
    22, 300  }
  ,
  {
    54, 245  }
  ,
  {
    107, 208  }
  ,
  {
    160, 188  }
  ,
  {
    213, 172  }
  ,
  {
    266, 162  }
  ,
  {
    319, 155  }
  ,
  {
    372, 148  }
  ,
  {
    425, 144  }
  ,
  {
    478, 139  }
  ,
  {
    531, 134  }
  ,
  {
    584, 129  }
  ,
  {
    637, 128  }
  ,
  {
    690, 125  }
  ,
  {
    743, 121  }
  ,
  {
    796, 119  }
  ,
  {
    849, 118  }
  ,
  {
    902, 115  }
  ,
  {
    955, 46  }
  ,
  {
    1008, 43  }
};
