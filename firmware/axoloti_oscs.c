/*
 * Copyright (C) 2013, 2014 Johannes Taelman
 * Edited 2023 - 2024 by Ksoloti
 *
 * This file is part of Axoloti.
 *
 * Axoloti is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * Axoloti is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Axoloti. If not, see <http://www.gnu.org/licenses/>.
 */
#include "axoloti_defines.h"
#include "axoloti_oscs.h"

// http://www.cs.cmu.edu/~eli/tmp/hardsync/hardsync.zip

int16_t blept[BLEPSIZE] = {-1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6,
                           7, 8, 8, 9, 11, 12, 13, 14, 16, 18, 19, 21, 23, 26,
                           28, 31, 34, 37, 40, 43, 47, 51, 56, 60, 65, 71, 76,
                           82, 89, 96, 103, 111, 119, 128, 137, 147, 157, 168,
                           180, 192, 205, 219, 233, 248, 264, 281, 299, 317,
                           337, 357, 378, 401, 425, 449, 475, 502, 530, 560,
                           590, 623, 656, 691, 727, 765, 805, 846, 888, 932,
                           978, 1026, 1075, 1127, 1180, 1235, 1292, 1351, 1412,
                           1475, 1540, 1607, 1677, 1749, 1823, 1899, 1977, 2058,
                           2141, 2227, 2315, 2406, 2499, 2594, 2692, 2793, 2896,
                           3002, 3111, 3222, 3336, 3452, 3571, 3693, 3817, 3944,
                           4074, 4207, 4342, 4480, 4620, 4763, 4909, 5057, 5208,
                           5362, 5518, 5676, 5838, 6001, 6167, 6335, 6506, 6679,
                           6854, 7031, 7211, 7392, 7576, 7762, 7949, 8138, 8329,
                           8522, 8716, 8911, 9108, 9307, 9506, 9707, 9909,
                           10112, 10315, 10520, 10725, 10930, 11136, 11342,
                           11549, 11755, 11962, 12168, 12374, 12580, 12785,
                           12990, 13194, 13397, 13598, 13799, 13999, 14197,
                           14393, 14588, 14781, 14973, 15162, 15349, 15533,
                           15716, 15896, 16073, 16247, 16419, 16587, 16752,
                           16914, 17073, 17228, 17380, 17528, 17672, 17812,
                           17949, 18081, 18209, 18333, 18452, 18567, 18678,
                           18784, 18886, 18982, 19075, 19162, 19244, 19322,
                           19395, 19463, 19525, 19583, 19636, 19684, 19727,
                           19764, 19797, 19825, 19848, 19866, 19878, 19886,
                           19889, 19888, 19881, 19870, 19854, 19833, 19808,
                           19778, 19744, 19706, 19664, 19617, 19566, 19512,
                           19453, 19391, 19325, 19256, 19184, 19108, 19029,
                           18948, 18863, 18776, 18686, 18594, 18500, 18403,
                           18305, 18205, 18103, 18000, 17896, 17790, 17684,
                           17577, 17469, 17360, 17252, 17143, 17034, 16926,
                           16818, 16710, 16603, 16497, 16391, 16287, 16184,
                           16083, 15983, 15885, 15789, 15694, 15602, 15512,
                           15425, 15340, 15257, 15177, 15100, 15026, 14955,
                           14887, 14823, 14761, 14703, 14648, 14597, 14549,
                           14505, 14464, 14428, 14394, 14365, 14339, 14317,
                           14299, 14284, 14274, 14267, 14263, 14264, 14268,
                           14276, 14287, 14302, 14321, 14343, 14368, 14396,
                           14428, 14463, 14501, 14543, 14586, 14633, 14683,
                           14735, 14789, 14846, 14906, 14967, 15030, 15095,
                           15162, 15231, 15301, 15372, 15445, 15519, 15594,
                           15669, 15745, 15822, 15899, 15976, 16053, 16131,
                           16208, 16285, 16361, 16437, 16512, 16586, 16659,
                           16731, 16802, 16871, 16939, 17005, 17070, 17132,
                           17193, 17252, 17309, 17363, 17415, 17465, 17513,
                           17557, 17600, 17639, 17676, 17710, 17741, 17770,
                           17795, 17818, 17837, 17854, 17868, 17879, 17887,
                           17891, 17893, 17892, 17888, 17881, 17872, 17859,
                           17844, 17826, 17805, 17781, 17755, 17727, 17696,
                           17663, 17627, 17590, 17550, 17508, 17465, 17419,
                           17372, 17323, 17273, 17221, 17168, 17114, 17059,
                           17003, 16946, 16888, 16830, 16772, 16713, 16653,
                           16594, 16535, 16475, 16416, 16358, 16300, 16242,
                           16185, 16129, 16074, 16020, 15967, 15915, 15865,
                           15816, 15769, 15723, 15678, 15636, 15595, 15557,
                           15520, 15485, 15452, 15422, 15393, 15367, 15343,
                           15322, 15303, 15286, 15271, 15259, 15250, 15242,
                           15237, 15235, 15235, 15237, 15242, 15249, 15258,
                           15270, 15283, 15299, 15317, 15338, 15360, 15384,
                           15410, 15438, 15468, 15499, 15533, 15567, 15603,
                           15641, 15680, 15720, 15761, 15803, 15846, 15890,
                           15935, 15980, 16026, 16072, 16119, 16166, 16213,
                           16260, 16307, 16353, 16400, 16446, 16492, 16537,
                           16582, 16626, 16669, 16711, 16752, 16792, 16832,
                           16869, 16906, 16941, 16975, 17007, 17038, 17067,
                           17094, 17120, 17144, 17166, 17186, 17205, 17221,
                           17236, 17249, 17260, 17269, 17275, 17280, 17283,
                           17284, 17284, 17281, 17276, 17269, 17261, 17250,
                           17238, 17224, 17209, 17191, 17172, 17152, 17130,
                           17106, 17081, 17055, 17027, 16998, 16968, 16937,
                           16905, 16872, 16838, 16804, 16769, 16733, 16696,
                           16660, 16622, 16585, 16547, 16509, 16472, 16434,
                           16396, 16359, 16322, 16285, 16249, 16213, 16178,
                           16144, 16110, 16077, 16045, 16014, 15984, 15955,
                           15927, 15901, 15876, 15852, 15829, 15807, 15787,
                           15769, 15752, 15736, 15722, 15710, 15699, 15690,
                           15682, 15676, 15672, 15669, 15668, 15668, 15670,
                           15673, 15678, 15685, 15693, 15703, 15714, 15726,
                           15740, 15755, 15771, 15789, 15808, 15828, 15849,
                           15871, 15895, 15919, 15944, 15970, 15996, 16023,
                           16051, 16080, 16109, 16138, 16168, 16198, 16228,
                           16258, 16289, 16319, 16350, 16380, 16410, 16440,
                           16469, 16498, 16527, 16555, 16583, 16609, 16636,
                           16661, 16686, 16710, 16733, 16755, 16776, 16796,
                           16815, 16832, 16849, 16865, 16879, 16892, 16904,
                           16915, 16924, 16932, 16939, 16944, 16949, 16951,
                           16953, 16953, 16952, 16950, 16946, 16942, 16935,
                           16928, 16920, 16910, 16899, 16888, 16875, 16861,
                           16846, 16830, 16813, 16796, 16777, 16758, 16738,
                           16717, 16696, 16674, 16652, 16629, 16606, 16583,
                           16559, 16535, 16510, 16486, 16462, 16437, 16413,
                           16389, 16365, 16341, 16317, 16294, 16271, 16248,
                           16226, 16205, 16184, 16163, 16143, 16124, 16106,
                           16088, 16072, 16056, 16041, 16026, 16013, 16001,
                           15989, 15979, 15970, 15961, 15954, 15948, 15942,
                           15938, 15935, 15933, 15932, 15932, 15933, 15935,
                           15938, 15942, 15947, 15953, 15960, 15968, 15977,
                           15987, 15997, 16009, 16021, 16034, 16047, 16062,
                           16076, 16092, 16108, 16125, 16142, 16159, 16177,
                           16195, 16214, 16233, 16252, 16271, 16290, 16310,
                           16329, 16348, 16368, 16387, 16406, 16425, 16444,
                           16462, 16480, 16498, 16515, 16532, 16548, 16564,
                           16580, 16594, 16609, 16622, 16635, 16647, 16659,
                           16670, 16680, 16689, 16697, 16705, 16712, 16718,
                           16723, 16728, 16731, 16734, 16736, 16737, 16737,
                           16737, 16736, 16733, 16730, 16727, 16722, 16717,
                           16711, 16704, 16696, 16688, 16679, 16670, 16660,
                           16649, 16638, 16627, 16615, 16602, 16589, 16576,
                           16562, 16548, 16534, 16519, 16504, 16489, 16474,
                           16459, 16444, 16429, 16414, 16398, 16383, 16368,
                           16354, 16339, 16324, 16310, 16296, 16283, 16270,
                           16257, 16244, 16232, 16221, 16210, 16199, 16189,
                           16179, 16170, 16162, 16154, 16147, 16140, 16134,
                           16129, 16124, 16120, 16117, 16114, 16112, 16110,
                           16110, 16109, 16110, 16111, 16113, 16115, 16118,
                           16122, 16126, 16131, 16136, 16142, 16149, 16155,
                           16163, 16171, 16179, 16188, 16197, 16206, 16216,
                           16226, 16236, 16247, 16258, 16269, 16280, 16292,
                           16303, 16315, 16327, 16338, 16350, 16362, 16374,
                           16385, 16397, 16408, 16419, 16430, 16441, 16452,
                           16462, 16472, 16482, 16492, 16501, 16510, 16518,
                           16526, 16534, 16541, 16547, 16554, 16560, 16565,
                           16570, 16574, 16578, 16582, 16585, 16587, 16589,
                           16590, 16591, 16592, 16591, 16591, 16590, 16588,
                           16586, 16584, 16581, 16577, 16573, 16569, 16564,
                           16559, 16554, 16548, 16542, 16536, 16529, 16522,
                           16514, 16507, 16499, 16491, 16483, 16474, 16466,
                           16457, 16449, 16440, 16431, 16422, 16413, 16404,
                           16395, 16387, 16378, 16369, 16361, 16352, 16344,
                           16336, 16328, 16320, 16313, 16306, 16299, 16292,
                           16285, 16279, 16273, 16268, 16263, 16258, 16253,
                           16249, 16245, 16242, 16239, 16236, 16234, 16232,
                           16231, 16229, 16229, 16228, 16228, 16229, 16229,
                           16230, 16232, 16234, 16236, 16238, 16241, 16244,
                           16248, 16251, 16255, 16260, 16264, 16269, 16274,
                           16279, 16285, 16290, 16296, 16302, 16308, 16314,
                           16321, 16327, 16333, 16340, 16347, 16353, 16360,
                           16366, 16373, 16379, 16386, 16392, 16399, 16405,
                           16411, 16417, 16423, 16429, 16434, 16439, 16445,
                           16450, 16454, 16459, 16463, 16467, 16471, 16475,
                           16478, 16481, 16484, 16486, 16489, 16491, 16492,
                           16494, 16495, 16496, 16496, 16496, 16496, 16496,
                           16496, 16495, 16494, 16492, 16491, 16489, 16487,
                           16484, 16482, 16479, 16476, 16473, 16470, 16466,
                           16463, 16459, 16455, 16451, 16446, 16442, 16438,
                           16433, 16429, 16424, 16419, 16415, 16410, 16405,
                           16400, 16395, 16391, 16386, 16381, 16377, 16372,
                           16368, 16363, 16359, 16355, 16351, 16347, 16343,
                           16339, 16336, 16332, 16329, 16326, 16323, 16320,
                           16318, 16316, 16313, 16311, 16310, 16308, 16307,
                           16306, 16305, 16304, 16304, 16303, 16303, 16303,
                           16303, 16304, 16305, 16305, 16306, 16308, 16309,
                           16311, 16312, 16314, 16316, 16318, 16321, 16323,
                           16326, 16328, 16331, 16334, 16337, 16340, 16343,
                           16346, 16349, 16353, 16356, 16359, 16363, 16366,
                           16369, 16373, 16376, 16379, 16383, 16386, 16389,
                           16392, 16396, 16399, 16402, 16404, 16407, 16410,
                           16413, 16415, 16418, 16420, 16422, 16424, 16426,
                           16428, 16430, 16431, 16432, 16434, 16435, 16436,
                           16437, 16437, 16438, 16438, 16439, 16439, 16439,
                           16439, 16438, 16438, 16437, 16437, 16436, 16435,
                           16434, 16433, 16431, 16430, 16429, 16427, 16425,
                           16424, 16422, 16420, 16418, 16416, 16414, 16412,
                           16410, 16407, 16405, 16403, 16401, 16398, 16396,
                           16394, 16391, 16389, 16387, 16384, 16382, 16380,
                           16378, 16376, 16374, 16372, 16370, 16368, 16366,
                           16364, 16362, 16361, 16359, 16358, 16356, 16355,
                           16354, 16353, 16352, 16351, 16350, 16349, 16348,
                           16348, 16347, 16347, 16347, 16347, 16346, 16347,
                           16347, 16347, 16347, 16348, 16348, 16349, 16349,
                           16350, 16351, 16352, 16353, 16354, 16355, 16356,
                           16357, 16358, 16359, 16361, 16362, 16364, 16365,
                           16367, 16368, 16370, 16371, 16373, 16374, 16376,
                           16377, 16379, 16380, 16382, 16383, 16385, 16386,
                           16388, 16389, 16391, 16392, 16393, 16394, 16396,
                           16397, 16398, 16399, 16400, 16401, 16402, 16403,
                           16404, 16404, 16405, 16405, 16406, 16406, 16407,
                           16407, 16407, 16408, 16408, 16408, 16408, 16408,
                           16408, 16407, 16407, 16407, 16407, 16406, 16406,
                           16405, 16405, 16404, 16403, 16403, 16402, 16401,
                           16400, 16399, 16399, 16398, 16397, 16396, 16395,
                           16394, 16393, 16392, 16391, 16390, 16389, 16388,
                           16387, 16386, 16385, 16384, 16383, 16382, 16381,
                           16380, 16379, 16378, 16377, 16376, 16376, 16375,
                           16374, 16373, 16373, 16372, 16372, 16371, 16371,
                           16370, 16370, 16369, 16369, 16369, 16368, 16368,
                           16368, 16368, 16368, 16368, 16368, 16368, 16368,
                           16368, 16368, 16368, 16369, 16369, 16369, 16370,
                           16370, 16370, 16371, 16371, 16372, 16372, 16373,
                           16373, 16374, 16374, 16375, 16376, 16376, 16377,
                           16378, 16378, 16379, 16380, 16380, 16381, 16382,
                           16382, 16383, 16383, 16384, 16385, 16385, 16386,
                           16386, 16387, 16388, 16388, 16389, 16389, 16390,
                           16390, 16390, 16391, 16391, 16391, 16392, 16392,
                           16392, 16393, 16393, 16393, 16393, 16393, 16393,
                           16393, 16393, 16393, 16393, 16393, 16393, 16393,
                           16393, 16393, 16393, 16393, 16392, 16392, 16392,
                           16392, 16391, 16391, 16391, 16390, 16390, 16390,
                           16389, 16389, 16389, 16388, 16388, 16387, 16387,
                           16387, 16386, 16386, 16385, 16385, 16384, 16384,
                           16384, 16383, 16383, 16382, 16382, 16382, 16381,
                           16381, 16381, 16380, 16380, 16380, 16380, 16379,
                           16379, 16379, 16379, 16378, 16378, 16378, 16378,
                           16378, 16378, 16378, 16377, 16377, 16377, 16377,
                           16377, 16377, 16377, 16377, 16378, 16378, 16378,
                           16378, 16378, 16378, 16378, 16378, 16379, 16379,
                           16379, 16379, 16379, 16379, 16380, 16380, 16380,
                           16380, 16381, 16381, 16381, 16381, 16382, 16382,
                           16382, 16382, 16383, 16383, 16383, 16383, 16384,
                           16384, 16384, 16384, 16385, 16385, 16385, 16385,
                           16385, 16386, 16386, 16386, 16386, 16386, 16386,
                           16387, 16387, 16387, 16387, 16387, 16387, 16387,
                           16387, 16387, 16387, 16387, 16387, 16387, 16387,
                           16387, 16387, 16387, 16387, 16387, 16387, 16387,
                           16387, 16387, 16387, 16386, 16386, 16386, 16386,
                           16386, 16386, 16386, 16386, 16385, 16385, 16385,
                           16385, 16385, 16385, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16382, 16382, 16382, 16382,
                           16382, 16382, 16382, 16382, 16382, 16382, 16382,
                           16382, 16381, 16381, 16381, 16381, 16381, 16381,
                           16381, 16381, 16381, 16381, 16381, 16381, 16381,
                           16381, 16381, 16382, 16382, 16382, 16382, 16382,
                           16382, 16382, 16382, 16382, 16382, 16382, 16382,
                           16382, 16382, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16385, 16385, 16385, 16385, 16385, 16385, 16385,
                           16385, 16385, 16385, 16385, 16385, 16385, 16385,
                           16385, 16385, 16385, 16385, 16385, 16385, 16385,
                           16385, 16385, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16383, 16383,
                           16383, 16383, 16383, 16383, 16383, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384, 16384, 16384, 16384, 16384, 16384,
                           16384, 16384};
