
// key mapping for C-system accordion

const int buttonNote[10][7] = 
{
{43,37,31,25,19,13,7},
{40,34,28,22,16,10,0},
{45,39,33,27,21,15,9},
{42,36,30,24,18,12,0},
{44,38,32,26,20,14,8},
{41,35,29,23,17,11,0},
{46,40,34,28,22,16,10},
{43,37,31,25,19,13,0},
{45,39,33,27,21,15,9},
{42,36,30,24,18,12,0}
};


int midiNumber(int rInt, int cInt) {
  int val = buttonNote[rInt][cInt] + 12 * octive;
  return val;
}
