#ifndef __COLORTRANS_H__
#define __COLORTRANS_H__


const int		gYUV2RGB_YTable[256] = {
	-18,-17,-16,-15,-13,-12,-11,-10,-9,-8,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,8,9,10,11,12,13,15,16,17,18,19,20,22,23,24,25,26,27,29,30,31,32,33,34,36,37,38,39,40,41,43,44,45,46,47,48,50,51,52,53,54,55,57,58,59,60,61,62,64,65,66,67,68,69,71,72,73,74,75,76,77,79,80,81,82,83,84,86,87,88,89,90,91,93,94,95,96,97,98,100,101,102,103,104,105,107,108,109,110,111,112,114,115,116,117,118,119,121,122,123,124,125,126,128,129,130,131,132,133,135,136,137,138,139,140,142,143,144,145,146,147,148,150,151,152,153,154,155,157,158,159,160,161,162,164,165,166,167,168,169,171,172,173,174,175,176,178,179,180,181,182,183,185,186,187,188,189,190,192,193,194,195,196,197,199,200,201,202,203,204,206,207,208,209,210,211,213,214,215,216,217,218,219,221,222,223,224,225,226,228,229,230,231,232,233,235,236,237,238,239,240,242,243,244,245,246,247,249,250,251,252,253,254,256,257,258,259,260,261,263,264,265,266,267,268,270,271,272,273,274,275,277,278,
};

const int		gYUV2R_VTable[256] = {
	-204,-202,-201,-199,-197,-196,-194,-193,-191,-189,-188,-186,-185,-183,-181,-180,-178,-177,-175,-173,-172,-170,-169,-167,-165,-164,-162,-161,-159,-158,-156,-154,-153,-151,-150,-148,-146,-145,-143,-142,-140,-138,-137,-135,-134,-132,-130,-129,-127,-126,-124,-122,-121,-119,-118,-116,-114,-113,-111,-110,-108,-106,-105,-103,-102,-100,-98,-97,-95,-94,-92,-90,-89,-87,-86,-84,-82,-81,-79,-78,-76,-75,-73,-71,-70,-68,-67,-65,-63,-62,-60,-59,-57,-55,-54,-52,-51,-49,-47,-46,-44,-43,-41,-39,-38,-36,-35,-33,-31,-30,-28,-27,-25,-23,-22,-20,-19,-17,-15,-14,-12,-11,-9,-7,-6,-4,-3,-1,0,1,3,4,6,7,9,11,12,14,15,17,19,20,22,23,25,27,28,30,31,33,35,36,38,39,41,43,44,46,47,49,51,52,54,55,57,59,60,62,63,65,67,68,70,71,73,75,76,78,79,81,82,84,86,87,89,90,92,94,95,97,98,100,102,103,105,106,108,110,111,113,114,116,118,119,121,122,124,126,127,129,130,132,134,135,137,138,140,142,143,145,146,148,150,151,153,154,156,158,159,161,162,164,165,167,169,170,172,173,175,177,178,180,181,183,185,186,188,189,191,193,194,196,197,199,201,202,
};

const int		gYUV2G_VTable[256] = {
	-104,-103,-102,-101,-100,-99,-99,-98,-97,-96,-95,-95,-94,-93,-92,-91,-91,-90,-89,-88,-87,-86,-86,-85,-84,-83,-82,-82,-81,-80,-79,-78,-78,-77,-76,-75,-74,-73,-73,-72,-71,-70,-69,-69,-68,-67,-66,-65,-65,-64,-63,-62,-61,-60,-60,-59,-58,-57,-56,-56,-55,-54,-53,-52,-52,-51,-50,-49,-48,-47,-47,-46,-45,-44,-43,-43,-42,-41,-40,-39,-39,-38,-37,-36,-35,-34,-34,-33,-32,-31,-30,-30,-29,-28,-27,-26,-26,-25,-24,-23,-22,-21,-21,-20,-19,-18,-17,-17,-16,-15,-14,-13,-13,-12,-11,-10,-9,-8,-8,-7,-6,-5,-4,-4,-3,-2,-1,0,0,0,1,2,3,4,4,5,6,7,8,8,9,10,11,12,13,13,14,15,16,17,17,18,19,20,21,21,22,23,24,25,26,26,27,28,29,30,30,31,32,33,34,34,35,36,37,38,39,39,40,41,42,43,43,44,45,46,47,47,48,49,50,51,52,52,53,54,55,56,56,57,58,59,60,60,61,62,63,64,65,65,66,67,68,69,69,70,71,72,73,73,74,75,76,77,78,78,79,80,81,82,82,83,84,85,86,86,87,88,89,90,91,91,92,93,94,95,95,96,97,98,99,99,100,101,102,103,
};

const int		gYUV2G_UTable[256] = {
	-50,-49,-49,-48,-48,-48,-47,-47,-46,-46,-46,-45,-45,-44,-44,-44,-43,-43,-43,-42,-42,-41,-41,-41,-40,-40,-39,-39,-39,-38,-38,-37,-37,-37,-36,-36,-35,-35,-35,-34,-34,-34,-33,-33,-32,-32,-32,-31,-31,-30,-30,-30,-29,-29,-28,-28,-28,-27,-27,-26,-26,-26,-25,-25,-25,-24,-24,-23,-23,-23,-22,-22,-21,-21,-21,-20,-20,-19,-19,-19,-18,-18,-17,-17,-17,-16,-16,-16,-15,-15,-14,-14,-14,-13,-13,-12,-12,-12,-11,-11,-10,-10,-10,-9,-9,-8,-8,-8,-7,-7,-7,-6,-6,-5,-5,-5,-4,-4,-3,-3,-3,-2,-2,-1,-1,-1,0,0,0,0,0,1,1,1,2,2,3,3,3,4,4,5,5,5,6,6,7,7,7,8,8,8,9,9,10,10,10,11,11,12,12,12,13,13,14,14,14,15,15,16,16,16,17,17,17,18,18,19,19,19,20,20,21,21,21,22,22,23,23,23,24,24,25,25,25,26,26,26,27,27,28,28,28,29,29,30,30,30,31,31,32,32,32,33,33,34,34,34,35,35,35,36,36,37,37,37,38,38,39,39,39,40,40,41,41,41,42,42,43,43,43,44,44,44,45,45,46,46,46,47,47,48,48,48,49,49,
};

const int		gYUV2B_UTable[256] = {
	-258,-256,-254,-252,-250,-248,-246,-244,-242,-240,-238,-236,-234,-232,-230,-228,-226,-223,-221,-219,-217,-215,-213,-211,-209,-207,-205,-203,-201,-199,-197,-195,-193,-191,-189,-187,-185,-183,-181,-179,-177,-175,-173,-171,-169,-167,-165,-163,-161,-159,-157,-155,-153,-151,-149,-147,-145,-143,-141,-139,-137,-135,-133,-131,-129,-127,-125,-123,-121,-119,-117,-115,-113,-110,-108,-106,-104,-102,-100,-98,-96,-94,-92,-90,-88,-86,-84,-82,-80,-78,-76,-74,-72,-70,-68,-66,-64,-62,-60,-58,-56,-54,-52,-50,-48,-46,-44,-42,-40,-38,-36,-34,-32,-30,-28,-26,-24,-22,-20,-18,-16,-14,-12,-10,-8,-6,-4,-2,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,113,115,117,119,121,123,125,127,129,131,133,135,137,139,141,143,145,147,149,151,153,155,157,159,161,163,165,167,169,171,173,175,177,179,181,183,185,187,189,191,193,195,197,199,201,203,205,207,209,211,213,215,217,219,221,223,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,256,
};

const int		gRGB2Y_RTable[256] = {
	0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,14,14,14,14,15,15,15,15,16,16,16,16,17,17,17,17,18,18,18,19,19,19,19,20,20,20,20,21,21,21,21,22,22,22,22,23,23,23,23,24,24,24,24,25,25,25,25,26,26,26,26,27,27,27,28,28,28,28,29,29,29,29,30,30,30,30,31,31,31,31,32,32,32,32,33,33,33,33,34,34,34,34,35,35,35,35,36,36,36,37,37,37,37,38,38,38,38,39,39,39,39,40,40,40,40,41,41,41,41,42,42,42,42,43,43,43,43,44,44,44,44,45,45,45,46,46,46,46,47,47,47,47,48,48,48,48,49,49,49,49,50,50,50,50,51,51,51,51,52,52,52,52,53,53,53,53,54,54,54,54,55,55,55,56,56,56,56,57,57,57,57,58,58,58,58,59,59,59,59,60,60,60,60,61,61,61,61,62,62,62,62,63,63,63,63,64,64,64,65,65,65,
};

const int		gRGB2Y_GTable[256] = {
	0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,24,25,25,26,26,27,27,28,28,29,29,30,30,31,31,32,32,33,33,34,34,35,35,36,36,37,37,38,38,39,39,40,40,41,41,42,42,43,43,44,44,45,45,46,46,47,47,48,48,49,49,50,50,51,51,52,52,53,53,54,54,55,55,56,56,57,57,58,58,59,59,60,60,61,61,62,63,63,64,64,65,65,66,66,67,67,68,68,69,69,70,70,71,71,72,72,73,73,74,74,75,75,76,76,77,77,78,78,79,79,80,80,81,81,82,82,83,83,84,84,85,85,86,86,87,87,88,88,89,89,90,90,91,91,92,92,93,93,94,94,95,95,96,96,97,97,98,98,99,99,100,100,101,101,102,102,103,103,104,104,105,105,106,106,107,107,108,108,109,109,110,110,111,111,112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,119,120,120,121,121,122,122,123,123,124,124,125,126,126,127,127,128,128,
};

const int		gRGB2Y_BTable[256] = {
	0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,19,19,19,19,19,19,19,19,19,19,19,20,20,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,22,22,23,23,23,23,23,23,23,23,23,23,24,24,24,24,24,24,24,24,24,24,24,
};

const int		gRGB2U_RTable[256] = {
	0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-2,-2,-3,-3,-3,-3,-3,-3,-3,-4,-4,-4,-4,-4,-4,-5,-5,-5,-5,-5,-5,-5,-6,-6,-6,-6,-6,-6,-6,-7,-7,-7,-7,-7,-7,-7,-8,-8,-8,-8,-8,-8,-9,-9,-9,-9,-9,-9,-9,-10,-10,-10,-10,-10,-10,-10,-11,-11,-11,-11,-11,-11,-11,-12,-12,-12,-12,-12,-12,-13,-13,-13,-13,-13,-13,-13,-14,-14,-14,-14,-14,-14,-14,-15,-15,-15,-15,-15,-15,-15,-16,-16,-16,-16,-16,-16,-17,-17,-17,-17,-17,-17,-17,-18,-18,-18,-18,-18,-18,-18,-19,-19,-19,-19,-19,-19,-19,-20,-20,-20,-20,-20,-20,-21,-21,-21,-21,-21,-21,-21,-22,-22,-22,-22,-22,-22,-22,-23,-23,-23,-23,-23,-23,-23,-24,-24,-24,-24,-24,-24,-25,-25,-25,-25,-25,-25,-25,-26,-26,-26,-26,-26,-26,-26,-27,-27,-27,-27,-27,-27,-27,-28,-28,-28,-28,-28,-28,-29,-29,-29,-29,-29,-29,-29,-30,-30,-30,-30,-30,-30,-30,-31,-31,-31,-31,-31,-31,-31,-32,-32,-32,-32,-32,-32,-33,-33,-33,-33,-33,-33,-33,-34,-34,-34,-34,-34,-34,-34,-35,-35,-35,-35,-35,-35,-35,-36,-36,-36,-36,-36,-36,-37,-37,-37,-37,-37,-37,
};

const int		gRGB2U_GTable[256] = {
	0,0,0,0,-1,-1,-1,-2,-2,-2,-2,-3,-3,-3,-4,-4,-4,-4,-5,-5,-5,-6,-6,-6,-6,-7,-7,-7,-8,-8,-8,-9,-9,-9,-9,-10,-10,-10,-11,-11,-11,-11,-12,-12,-12,-13,-13,-13,-13,-14,-14,-14,-15,-15,-15,-16,-16,-16,-16,-17,-17,-17,-18,-18,-18,-18,-19,-19,-19,-20,-20,-20,-20,-21,-21,-21,-22,-22,-22,-22,-23,-23,-23,-24,-24,-24,-25,-25,-25,-25,-26,-26,-26,-27,-27,-27,-27,-28,-28,-28,-29,-29,-29,-29,-30,-30,-30,-31,-31,-31,-32,-32,-32,-32,-33,-33,-33,-34,-34,-34,-34,-35,-35,-35,-36,-36,-36,-36,-37,-37,-37,-38,-38,-38,-38,-39,-39,-39,-40,-40,-40,-41,-41,-41,-41,-42,-42,-42,-43,-43,-43,-43,-44,-44,-44,-45,-45,-45,-45,-46,-46,-46,-47,-47,-47,-48,-48,-48,-48,-49,-49,-49,-50,-50,-50,-50,-51,-51,-51,-52,-52,-52,-52,-53,-53,-53,-54,-54,-54,-54,-55,-55,-55,-56,-56,-56,-57,-57,-57,-57,-58,-58,-58,-59,-59,-59,-59,-60,-60,-60,-61,-61,-61,-61,-62,-62,-62,-63,-63,-63,-64,-64,-64,-64,-65,-65,-65,-66,-66,-66,-66,-67,-67,-67,-68,-68,-68,-68,-69,-69,-69,-70,-70,-70,-71,-71,-71,-71,-72,-72,-72,-73,-73,-73,-73,-74,
};

const int		gRGB2U_BTable[256] = {
	0,0,0,1,1,2,2,3,3,3,4,4,5,5,6,6,7,7,7,8,8,9,9,10,10,10,11,11,12,12,13,13,14,14,14,15,15,16,16,17,17,17,18,18,19,19,20,20,21,21,21,22,22,23,23,24,24,25,25,25,26,26,27,27,28,28,28,29,29,30,30,31,31,32,32,32,33,33,34,34,35,35,35,36,36,37,37,38,38,39,39,39,40,40,41,41,42,42,43,43,43,44,44,45,45,46,46,46,47,47,48,48,49,49,50,50,50,51,51,52,52,53,53,53,54,54,55,55,56,56,57,57,57,58,58,59,59,60,60,61,61,61,62,62,63,63,64,64,64,65,65,66,66,67,67,68,68,68,69,69,70,70,71,71,71,72,72,73,73,74,74,75,75,75,76,76,77,77,78,78,79,79,79,80,80,81,81,82,82,82,83,83,84,84,85,85,86,86,86,87,87,88,88,89,89,89,90,90,91,91,92,92,93,93,93,94,94,95,95,96,96,97,97,97,98,98,99,99,100,100,100,101,101,102,102,103,103,104,104,104,105,105,106,106,107,107,107,108,108,109,109,110,110,111,111,111,
};

const int		gRGB2V_RTable[256] = {
	0,0,0,1,1,2,2,3,3,3,4,4,5,5,6,6,7,7,7,8,8,9,9,10,10,10,11,11,12,12,13,13,14,14,14,15,15,16,16,17,17,17,18,18,19,19,20,20,21,21,21,22,22,23,23,24,24,25,25,25,26,26,27,27,28,28,28,29,29,30,30,31,31,32,32,32,33,33,34,34,35,35,35,36,36,37,37,38,38,39,39,39,40,40,41,41,42,42,43,43,43,44,44,45,45,46,46,46,47,47,48,48,49,49,50,50,50,51,51,52,52,53,53,53,54,54,55,55,56,56,57,57,57,58,58,59,59,60,60,61,61,61,62,62,63,63,64,64,64,65,65,66,66,67,67,68,68,68,69,69,70,70,71,71,71,72,72,73,73,74,74,75,75,75,76,76,77,77,78,78,79,79,79,80,80,81,81,82,82,82,83,83,84,84,85,85,86,86,86,87,87,88,88,89,89,89,90,90,91,91,92,92,93,93,93,94,94,95,95,96,96,97,97,97,98,98,99,99,100,100,100,101,101,102,102,103,103,104,104,104,105,105,106,106,107,107,107,108,108,109,109,110,110,111,111,111,
};

const int		gRGB2V_GTable[256] = {
	0,0,0,-1,-1,-1,-2,-2,-2,-3,-3,-4,-4,-4,-5,-5,-5,-6,-6,-6,-7,-7,-8,-8,-8,-9,-9,-9,-10,-10,-11,-11,-11,-12,-12,-12,-13,-13,-13,-14,-14,-15,-15,-15,-16,-16,-16,-17,-17,-18,-18,-18,-19,-19,-19,-20,-20,-20,-21,-21,-22,-22,-22,-23,-23,-23,-24,-24,-25,-25,-25,-26,-26,-26,-27,-27,-27,-28,-28,-29,-29,-29,-30,-30,-30,-31,-31,-32,-32,-32,-33,-33,-33,-34,-34,-34,-35,-35,-36,-36,-36,-37,-37,-37,-38,-38,-39,-39,-39,-40,-40,-40,-41,-41,-41,-42,-42,-43,-43,-43,-44,-44,-44,-45,-45,-46,-46,-46,-47,-47,-47,-48,-48,-48,-49,-49,-50,-50,-50,-51,-51,-51,-52,-52,-52,-53,-53,-54,-54,-54,-55,-55,-55,-56,-56,-57,-57,-57,-58,-58,-58,-59,-59,-59,-60,-60,-61,-61,-61,-62,-62,-62,-63,-63,-64,-64,-64,-65,-65,-65,-66,-66,-66,-67,-67,-68,-68,-68,-69,-69,-69,-70,-70,-71,-71,-71,-72,-72,-72,-73,-73,-73,-74,-74,-75,-75,-75,-76,-76,-76,-77,-77,-78,-78,-78,-79,-79,-79,-80,-80,-80,-81,-81,-82,-82,-82,-83,-83,-83,-84,-84,-85,-85,-85,-86,-86,-86,-87,-87,-87,-88,-88,-89,-89,-89,-90,-90,-90,-91,-91,-92,-92,-92,-93,-93,-93,
};

const int		gRGB2V_BTable[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-15,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-18,-18,
};



#endif //__COLORTRANS_H__
